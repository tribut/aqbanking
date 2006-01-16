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


#include <qapplication.h>
#include <qtranslator.h>
#include <qtextcodec.h>

#include <gwenhywfar/logger.h>
#include <gwenhywfar/debug.h>

#include <stdio.h>

#include <qbanking/qbanking.h>


#include "qbhelpbrowser.h"




int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QBanking *ab;
  QTranslator translator(0);

  GWEN_Logger_SetLevel(0, GWEN_LoggerLevelInfo);

  QString datadir(PKGDATADIR);
  if (translator.load(QTextCodec::locale()+QString(".qm"),
		      datadir + QString("/i18n/"))) {
    DBG_INFO(0, "I18N available for your language");
    app.installTranslator(&translator);
  }
  else {
    DBG_WARN(0, "Internationalisation is not available for your language");
  }

  ab=new QBanking("qt3-wizard", 0);
  if (ab->init()) {
    fprintf(stderr, "Error on init.\n");
    return 2;
  }

  QObject::connect(&app,SIGNAL(lastWindowClosed()),
                   &app,SLOT(quit()));

  if (argc>1 && strcasecmp(argv[1], "debug")==0) {
    QBHelpBrowser *hb;
    hb=new QBHelpBrowser("/tmp/index.html", ".", 0, "help viewer");
    app.setMainWidget(hb);
    hb->show();
    return app.exec();
  }
  else {
    ab->setupDialog();
  }

  if (ab->fini()) {
    fprintf(stderr, "Error on fini.\n");
  }
  fprintf(stderr, "FINI done.\n");

  delete ab;

  return 0;
}




