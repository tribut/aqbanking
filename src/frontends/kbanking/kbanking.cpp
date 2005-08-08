/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id$
    begin       : Mon Mar 01 2004
    copyright   : (C) 2004 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


#ifdef HAVE_CONFIG_H
# include <config.h>
#endif


#include "kbanking_p.h"
#include "progress.h"
#include "simplebox.h"
#include "inputbox.h"
#include "flagstaff.h"
#include "mapaccount.h"
#include "importer.h"
#include "pickstartdate.h"
#include "printdialog.h"
#include "selectbank.h"

#include <aqbanking/jobgetbalance.h>
#include <aqbanking/jobgettransactions.h>

#include <assert.h>
#include <qstring.h>
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <qapplication.h>
#include <qdatetime.h>
#include <qwidget.h>
#include <qtranslator.h>
#include <qtextcodec.h>


#include <gwenhywfar/debug.h>



KBanking::KBanking(const char *appname,
                   const char *fname)
:Banking(appname, fname)
,_parentWidget(0)
,_lastWidgetId(0)
,_logLevel(AB_Banking_LogLevelInfo)
,_translator(0){
  _flagStaff=new FlagStaff();
}



KBanking::~KBanking(){
  if (_translator) {
    qApp->removeTranslator(_translator);
    delete _translator;
  }
  delete _flagStaff;
}



int KBanking::_extractHTML(const char *text, GWEN_BUFFER *tbuf) {
  GWEN_BUFFEREDIO *bio;
  GWEN_XMLNODE *xmlNode;
  GWEN_BUFFER *buf;
  int rv;

  buf=GWEN_Buffer_new(0, 256, 0, 1);
  GWEN_Buffer_AppendString(buf, text);
  GWEN_Buffer_Rewind(buf);
  bio=GWEN_BufferedIO_Buffer2_new(buf, 1);
  GWEN_BufferedIO_SetReadBuffer(bio, 0, 256);
  xmlNode=GWEN_XMLNode_new(GWEN_XMLNodeTypeTag, "html");
  rv=GWEN_XML_Parse(xmlNode, bio,
		    GWEN_XML_FLAGS_DEFAULT |
                    GWEN_XML_FLAGS_HANDLE_OPEN_HTMLTAGS);
  GWEN_BufferedIO_Close(bio);
  GWEN_BufferedIO_free(bio);
  if (rv) {
    DBG_NOTICE(0, "here");
    GWEN_XMLNode_free(xmlNode);
    return -1;
  }
  else {
    GWEN_XMLNODE *nn;

    nn=GWEN_XMLNode_FindFirstTag(xmlNode, "html", 0, 0);
    if (nn) {
      GWEN_XMLNODE *on, *onn;

      on=GWEN_XMLNode_new(GWEN_XMLNodeTypeTag, "root");
      onn=GWEN_XMLNode_new(GWEN_XMLNodeTypeTag, "qt");
      GWEN_XMLNode_AddChild(on, onn);
      GWEN_XMLNode_AddChildrenOnly(onn, nn, 1);

        /* text contains HTML tag, take it */
      bio=GWEN_BufferedIO_Buffer2_new(tbuf, 0);
      GWEN_BufferedIO_SetWriteBuffer(bio, 0, 256);
      rv=GWEN_XMLNode_WriteToStream(on, bio, GWEN_XML_FLAGS_DEFAULT);
      GWEN_XMLNode_free(on);
      if (rv) {
	DBG_ERROR(AQBANKING_LOGDOMAIN, "Error writing data to stream");
	GWEN_BufferedIO_Abandon(bio);
	GWEN_BufferedIO_free(bio);
        GWEN_XMLNode_free(xmlNode);
	return -1;
      }
      else {
	rv=GWEN_BufferedIO_Close(bio);
	GWEN_BufferedIO_free(bio);
        if (rv) {
          GWEN_XMLNode_free(xmlNode);
          return -1;
        }
      }
    }
    else {
      GWEN_XMLNode_free(xmlNode);
      return 1;
    }
  }
  GWEN_XMLNode_free(xmlNode);
  return 0;
}



int KBanking::messageBox(GWEN_TYPE_UINT32 flags,
                         const char *title,
                         const char *text,
                         const char *b1,
                         const char *b2,
                         const char *b3){
  int rv;
  GWEN_BUFFER *buf;

  buf=GWEN_Buffer_new(0, strlen(text), 0, 1);
  if (!_extractHTML(text, buf)) {
    text=GWEN_Buffer_GetStart(buf);
  }

  switch(flags & AB_BANKING_MSG_FLAGS_TYPE_MASK) {
  case AB_BANKING_MSG_FLAGS_TYPE_WARN:
    rv=QMessageBox::warning(0, QString::fromUtf8(title), QString::fromUtf8(text), 
			    b1 ? QString::fromUtf8(b1) : QString::null,
			    b2 ? QString::fromUtf8(b2) : QString::null,
			    b3 ? QString::fromUtf8(b3) : QString::null);
    break;
  case AB_BANKING_MSG_FLAGS_TYPE_ERROR:
    rv=QMessageBox::critical(0, QString::fromUtf8(title), QString::fromUtf8(text), 
			     b1 ? QString::fromUtf8(b1) : QString::null,
			     b2 ? QString::fromUtf8(b2) : QString::null,
			     b3 ? QString::fromUtf8(b3) : QString::null);
    break;
  case AB_BANKING_MSG_FLAGS_TYPE_INFO:
  default:
    rv=QMessageBox::information(0, QString::fromUtf8(title), QString::fromUtf8(text),
				b1 ? QString::fromUtf8(b1) : QString::null,
				b2 ? QString::fromUtf8(b2) : QString::null,
				b3 ? QString::fromUtf8(b3) : QString::null);
    break;
  }
  rv++;
  GWEN_Buffer_free(buf);
  return rv;
}



int KBanking::inputBox(GWEN_TYPE_UINT32 flags,
                       const char *title,
                       const char *text,
                       char *buffer,
                       int minLen,
                       int maxLen){
  GWEN_BUFFER *buf;

  buf=GWEN_Buffer_new(0, strlen(text), 0, 1);
  if (!_extractHTML(text, buf)) {
    text=GWEN_Buffer_GetStart(buf);
  }

  KBInputBox ib(QString::fromUtf8(title), QString::fromUtf8(text),
		flags, minLen, maxLen, 0, "InputBox", true);
  GWEN_Buffer_free(buf);
  if (ib.exec()==QDialog::Accepted) {
    QString s;
    int l;

    s=ib.getInput();
    l=s.length();
    if (l && l<maxLen-1) {
      memmove(buffer, s.latin1(), l);
      buffer[l]=0;
    }
    else {
      DBG_ERROR(0, "Bad pin length");
      return AB_ERROR_INVALID;
    }
    return 0;
  }
  else {
    DBG_WARN(0, "Aborted by user");
    return AB_ERROR_USER_ABORT;
  }
}



GWEN_TYPE_UINT32 KBanking::showBox(GWEN_TYPE_UINT32 flags,
                                   const char *title,
                                   const char *text){
  GWEN_TYPE_UINT32 id;
  KBSimpleBox *b;
  QWidget *w;
  GWEN_BUFFER *buf;

  buf=GWEN_Buffer_new(0, strlen(text), 0, 1);
  if (!_extractHTML(text, buf)) {
    text=GWEN_Buffer_GetStart(buf);
  }

  w=_findProgressWidget(0);
  id=++_lastWidgetId;
  b=new KBSimpleBox(id, QString::fromUtf8(title),
		    QString::fromUtf8(text),
		    w, "SimpleBox",
		    Qt::WType_TopLevel | Qt::WType_Dialog | Qt::WShowModal);
  GWEN_Buffer_free(buf);
  //b->setModal(true);
  if (flags & AB_BANKING_SHOWBOX_FLAGS_BEEP)
    QApplication::beep();

  b->show();
  _simpleBoxWidgets.push_front(b);
  qApp->processEvents();
  return id;
}



void KBanking::hideBox(GWEN_TYPE_UINT32 id){
  if (_simpleBoxWidgets.size()==0) {
    DBG_WARN(0, "No simpleBox widgets");
    return;
  }
  if (id==0) {
    KBSimpleBox *b;

    b=_simpleBoxWidgets.front();
    b->close(true);
    _simpleBoxWidgets.pop_front();
  }
  else {
    std::list<KBSimpleBox*>::iterator it;
    for (it=_simpleBoxWidgets.begin(); it!=_simpleBoxWidgets.end(); it++) {
      if ((*it)->getId()==id) {
        (*it)->close(true);
        _simpleBoxWidgets.erase(it);
        break;
      }
    }
  }
  qApp->processEvents();
}



GWEN_TYPE_UINT32 KBanking::progressStart(const char *title,
                                         const char *text,
                                         GWEN_TYPE_UINT32 total){
  GWEN_TYPE_UINT32 id;
  KBProgress *pr;
  GWEN_BUFFER *buf;

  buf=GWEN_Buffer_new(0, strlen(text), 0, 1);
  if (!_extractHTML(text, buf)) {
    text=GWEN_Buffer_GetStart(buf);
  }

  _cleanupProgressWidgets();
  id=++_lastWidgetId;
  pr=new KBProgress(id, QString::fromUtf8(title), 
		    QString::fromUtf8(text), 
		    _parentWidget, "ProgressWidget",
                    Qt::WType_Dialog | Qt::WShowModal);
  GWEN_Buffer_free(buf);
  if (pr->start(total)) {
    DBG_ERROR(0, "Could not start progress dialog");
    delete pr;
    return 0;
  }
  pr->show();
  _progressWidgets.push_front(pr);
  return id;
}



KBProgress *KBanking::_findProgressWidget(GWEN_TYPE_UINT32 id) {
  std::list<KBProgress*>::iterator it;

  if (_progressWidgets.size()==0) {
    DBG_WARN(0, "No progress widgets");
    return 0;
  }
  if (id==0)
    return _progressWidgets.front();
  for (it=_progressWidgets.begin(); it!=_progressWidgets.end(); it++) {
    if ((*it)->getId()==id)
      return *it;
  }

  DBG_WARN(0, "Progress widget \"%08x\" not found", (unsigned int)id);
  return 0;
}



void KBanking::_cleanupProgressWidgets() {
  std::list<KBProgress*>::iterator it;

  while(1) {
    bool del;

    del=false;
    for (it=_progressWidgets.begin(); it!=_progressWidgets.end(); it++) {
      if ((*it)->isClosed()) {
        delete *it;
        _progressWidgets.erase(it);
        del=true;
        break;
      }
    } /* for */
    if (!del)
      break;
  } /* while */
}



int KBanking::progressAdvance(GWEN_TYPE_UINT32 id,
                              GWEN_TYPE_UINT32 progress){
  KBProgress *pr;

  pr=_findProgressWidget(id);
  if (pr) {
    return pr->advance(progress);
  }
  else
    return AB_ERROR_NOT_FOUND;
}



int KBanking::progressLog(GWEN_TYPE_UINT32 id,
                          AB_BANKING_LOGLEVEL level,
                          const char *chartext){
  KBProgress *pr;
  QString text(QString::fromUtf8(chartext));

  // Necessary when passing this QString into the macros
  const char *latin1text = text.latin1();

  if (level>_logLevel) {
    DBG_NOTICE(0, "Not logging this: %02d: %s (we are at %d)",
               level, latin1text, _logLevel);
    /* don't log this */
    return 0;
  }

  DBG_INFO(0, "%02d: %s", level, latin1text);
  pr=_findProgressWidget(id);
  if (pr) {
    return pr->log(level, text);
  }
  else {
    return AB_ERROR_NOT_FOUND;
  }
}



int KBanking::progressEnd(GWEN_TYPE_UINT32 id){
  KBProgress *pr;
  int res;

  if (_progressWidgets.size()==0) {
    DBG_INFO(0, "No active progress widget");
    return AB_ERROR_NOT_FOUND;
  }

  res=AB_ERROR_NOT_FOUND;
  if (id==0) {
    pr=_progressWidgets.front();
    res=pr->end();
    _progressWidgets.pop_front();
  }
  else {
    std::list<KBProgress*>::iterator it;

    for (it=_progressWidgets.begin(); it!=_progressWidgets.end(); it++) {
      if ((*it)->getId()==id) {
	res=(*it)->end();
	_progressWidgets.erase(it);
	break;
      }
    }
  }

  return res;
}



void KBanking::setParentWidget(QWidget *w) {
  _parentWidget=w;
}



FlagStaff *KBanking::flagStaff(){
  return _flagStaff;
}



int KBanking::enqueueJob(AB_JOB *j){
  int rv;

  rv=Banking::enqueueJob(j);

  _flagStaff->queueUpdated();
  return rv;
}



int KBanking::dequeueJob(AB_JOB *j){
  int rv;

  rv=Banking::dequeueJob(j);
  _flagStaff->queueUpdated();
  return rv;
}



int KBanking::executeQueue(){
  int rv;

  rv=Banking::executeQueue();
  _flagStaff->queueUpdated();
  return rv;
}



void KBanking::accountsUpdated(){
  _flagStaff->accountsUpdated();
}



void KBanking::invokeHelp(const char *subject){
}



bool KBanking::mapAccount(const AB_ACCOUNT *a){
  return false;
}



bool KBanking::addTransaction(const AB_ACCOUNT *a, const AB_TRANSACTION *t){
  return false;
}



bool KBanking::setAccountStatus(const AB_ACCOUNT *a,
                                const AB_ACCOUNT_STATUS *ast){
  return false;
}



AB_ACCOUNT *KBanking::_getAccount(const char *accountId){
  AB_ACCOUNT *a;

  a=AB_Banking_GetAccountByAlias(getCInterface(), accountId);
  if (!a) {
    // should not happen anyway
    QMessageBox::critical(0,
			  QWidget::tr("Account Not Mapped"),
			  QWidget::tr("<qt>"
				      "<p>"
				      "The given application account has not "
				      "been mapped to banking accounts."
				      "</p>"
				      "</qt>"
				     ),
			  QWidget::tr("Dismiss"),0,0,0);
    return 0;
  }

  return a;
}




bool KBanking::requestBalance(const char *accountId){
  AB_ACCOUNT *a;
  int rv;

  if (!accountId) {
    DBG_ERROR(AQBANKING_LOGDOMAIN,
              "Account id is required");
    return AB_ERROR_INVALID;
  }

  a=_getAccount(accountId);
  if (!a)
    return false;

  rv=AB_Banking_RequestBalance(getCInterface(),
			       AB_Account_GetBankCode(a),
			       AB_Account_GetAccountNumber(a));
  if (rv) {
    DBG_ERROR(AQBANKING_LOGDOMAIN,
	      "Request error (%d)",
	      rv);
    QMessageBox::critical(0,
                          QWidget::tr("Queue Error"),
                          QWidget::tr("<qt>"
				      "<p>"
				      "Unable to enqueue your request."
				      "</p>"
				      "</qt>"
				     ),
			  QWidget::tr("Dismiss"),0,0,0);
    return false;
  }

  DBG_INFO(AQBANKING_LOGDOMAIN,
	   "Job successfully enqueued");
  return true;
}



bool KBanking::requestTransactions(const char *accountId,
                                   const QDate &fromDate,
                                   const QDate &toDate){
  AB_ACCOUNT *a;
  int rv;
  AB_JOB *job;

  if (!accountId) {
    DBG_ERROR(AQBANKING_LOGDOMAIN,
              "Account id is required");
    return AB_ERROR_INVALID;
  }

  a=_getAccount(accountId);
  if (!a)
    return false;

  job=AB_JobGetTransactions_new(a);
  rv=AB_Job_CheckAvailability(job);
  if (rv) {
    DBG_NOTICE(0, "Job \"GetTransactions\" is not available (%d)", rv);
    AB_Job_free(job);
    QMessageBox::critical(0,
			  QWidget::tr("Job Not Available"),
			  QWidget::tr("The job you requested is not available"
				      "with\n"
				      "the backend which handles "
				      "this account.\n"),
			  QWidget::tr("Dismiss"), 0, 0, 0);
    return false;
  }

  /* check/set fromDate */
  if (fromDate.isValid()) {
    GWEN_TIME *ti1;

    ti1=GWEN_Time_new(fromDate.year(),
		      fromDate.month()-1,
		      fromDate.day(), 0, 0, 0, 0);
    AB_JobGetTransactions_SetFromTime(job, ti1);
    GWEN_Time_free(ti1);
  }
  else {
    GWEN_DB_NODE *db;

    db=getAppData();
    assert(db);
    db=GWEN_DB_GetGroup(db, GWEN_PATH_FLAGS_NAMEMUSTEXIST,
			"banking/lastUpdate");
    if (db) {
      GWEN_TIME *ti;

      ti=GWEN_Time_fromDb(db);
      if (ti) {
	AB_JobGetTransactions_SetFromTime(job, ti);
	GWEN_Time_free(ti);
      }
    }
    else {
      QDate qd;
      GWEN_TIME *ti1;
      int days;
      int day, month, year;

      ti1=GWEN_CurrentTime();
      days=AB_JobGetTransactions_GetMaxStoreDays(job);
      if (days!=-1) {
	GWEN_TIME *ti2;
  
	ti2=GWEN_Time_fromSeconds(GWEN_Time_Seconds(ti1)-(60*60*24*days));
	GWEN_Time_free(ti1);
	ti1=ti2;
      }
      if (GWEN_Time_GetBrokenDownDate(ti1, &day, &month, &year)) {
	DBG_ERROR(0, "Bad date");
	qd=QDate();
      }
      else
	qd=QDate(year, month+1, day);
      GWEN_Time_free(ti1);

      PickStartDate psd(qd, QDate(), 3, 0, "PickStartDate", true);
      if (psd.exec()!=QDialog::Accepted) {
	AB_Job_free(job);
	return false;
      }
      qd=psd.getDate();
      if (qd.isValid()) {
	ti1=GWEN_Time_new(qd.year(), qd.month()-1, qd.day(), 0, 0, 0, 0);
	AB_JobGetTransactions_SetFromTime(job, ti1);
	GWEN_Time_free(ti1);
      }
    }
  }

  /* check/set toDate */
  if (toDate.isValid()) {
    GWEN_TIME *ti1;

    ti1=GWEN_Time_new(toDate.year(),
		      toDate.month()-1,
		      toDate.day(), 0, 0, 0, 0);
    AB_JobGetTransactions_SetToTime(job, ti1);
    GWEN_Time_free(ti1);
  }

  DBG_NOTICE(0, "Enqueuing job");
  rv=enqueueJob(job);
  AB_Job_free(job);
  if (rv) {
    DBG_ERROR(0,
	      "Request error (%d)",
	      rv);
    QMessageBox::critical(0,
			  QWidget::tr("Queue Error"),
			  QWidget::tr("<qt>"
				      "<p>"
				      "Unable to enqueue your request."
				      "</p>"
				      "</qt>"
				     ),
			  QWidget::tr("Dismiss"),0,0,0);
    return false;
  }
  else {
    GWEN_TIME *ti1;
    GWEN_DB_NODE *dbT;

    ti1=GWEN_CurrentTime();
    dbT=getAppData();
    assert(dbT);
    dbT=GWEN_DB_GetGroup(dbT, GWEN_DB_FLAGS_OVERWRITE_GROUPS,
			 "banking/lastUpdate");
    assert(dbT);
    if (GWEN_Time_toDb(ti1, dbT)) {
      DBG_ERROR(0, "Could not save time");
    }
    GWEN_Time_free(ti1);
  }

  DBG_INFO(AQBANKING_LOGDOMAIN,
	   "Job successfully enqueued");
  statusMessage(QWidget::tr("Jobs added to outbox"));

  return true;
}



void KBanking::setAccountAlias(AB_ACCOUNT *a, const char *alias){
  assert(a);
  assert(alias);

  AB_Banking_SetAccountAlias(getCInterface(), a, alias);
}



bool KBanking::askMapAccount(const char *id,
                             const char *bankCode,
                             const char *accountId){
  MapAccount *w;

  w=new MapAccount(this, bankCode, accountId,
                   _parentWidget, "MapAccount", true);
  if (w->exec()==QDialog::Accepted) {
    AB_ACCOUNT *a;

    a=w->getAccount();
    assert(a);
    DBG_NOTICE(0,
               "Mapping application account \"%s\" to "
               "online account \"%s/%s\"",
               id,
               AB_Account_GetBankCode(a),
               AB_Account_GetAccountNumber(a));
    setAccountAlias(a, id);
    delete w;
    return true;
  }

  delete w;
  return false;
}



bool KBanking::importContext(AB_IMEXPORTER_CONTEXT *ctx){
  AB_IMEXPORTER_ACCOUNTINFO *ai;

  ai=AB_ImExporterContext_GetFirstAccountInfo(ctx);
  while(ai) {
    if (!importAccountInfo(ai))
      return false;
    ai=AB_ImExporterContext_GetNextAccountInfo(ctx);
  }
  return true;
}


bool KBanking::importAccountInfo(AB_IMEXPORTER_ACCOUNTINFO *ai){
  DBG_NOTICE(0, "Import account info function not overloaded");
  return false;
}



bool KBanking::interactiveImport(){
  Importer *w;
  bool res;

  w=new Importer(this, 0, "Importer", true);
  if (!w->init()) {
    delete w;
    return false;
  }
  res=(w->exec()==QDialog::Accepted);
  res&=w->fini();
  delete w;
  return res;
}



int KBanking::init(){
  int rv;

  rv=Banking::init();
  if (rv)
    return rv;

  _translator=new QTranslator(0);
  if (_translator->load(QTextCodec::locale()+QString(".qm"),
			QString(DATADIR "/i18n/"))) {
    DBG_INFO(0, "I18N available for your language");
    qApp->installTranslator(_translator);
  }
  else {
    DBG_WARN(0, "Internationalisation is not available for your language");
    delete _translator;
    _translator=0;
  }

  return 0;
}



int KBanking::fini(){
  int rv;

  rv=Banking::fini();
  if (_translator) {
    qApp->removeTranslator(_translator);
    delete _translator;
    _translator=0;
  }

  return rv;
}



void KBanking::outboxCountChanged(int count){
  _flagStaff->outboxCountChanged(count);
}



void KBanking::statusMessage(const QString &s){
  _flagStaff->statusMessage(s);
}



int KBanking::print(const char *docTitle,
                    const char *docType,
                    const char *descr,
                    const char *text){
  GWEN_BUFFER *buf1;
  GWEN_BUFFER *buf2;
  int rv;

  buf1=GWEN_Buffer_new(0, strlen(descr)+32, 0, 1);
  if (!_extractHTML(descr, buf1)) {
    descr=GWEN_Buffer_GetStart(buf1);
  }
  buf2=GWEN_Buffer_new(0, strlen(text)+32, 0, 1);
  if (!_extractHTML(text, buf2)) {
    text=GWEN_Buffer_GetStart(buf2);
  }

  PrintDialog pdlg(this, docTitle, docType, descr, text, 0,
                   "printdialog", true);

  if (pdlg.exec()==QDialog::Accepted)
    rv=0;
  else
    rv=AB_ERROR_USER_ABORT;

  GWEN_Buffer_free(buf2);
  GWEN_Buffer_free(buf1);
  return rv;
}



std::string KBanking::QStringToUtf8String(const QString &qs) {
  std::string result;
  QCString utfData=qs.utf8();
  int len;
  int i;

  len=utfData.length();
  for (i=0; i<len; i++)
    result+=(unsigned char)utfData[i];

  return result;
}



AB_BANKINFO *KBanking::selectBank(QWidget* parent,
                                  const QString &title,
                                  const QString &country,
                                  const QString &bankCode,
                                  const QString &swiftCode,
                                  const QString &bankName,
                                  const QString &location) {
  return SelectBank::selectBank(this, parent, title, country,
				bankCode, swiftCode,
				bankName, location);
}











