/***************************************************************************
 begin       : Sat Jun 26 2010
 copyright   : (C) 2010 by Martin Preuss
 email       : martin@aqbanking.de

 ***************************************************************************
 * This file is part of the project "AqBanking".                           *
 * Please see toplevel file COPYING of that project for license details.   *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif



#include "dlg_rdh_special_p.h"
#include "i18n_l.h"

#include <aqbanking/user.h>
#include <aqbanking/banking_be.h>

#include <aqhbci/user.h>
#include <aqhbci/provider.h>

#include <gwenhywfar/gwenhywfar.h>
#include <gwenhywfar/misc.h>
#include <gwenhywfar/pathmanager.h>
#include <gwenhywfar/debug.h>
#include <gwenhywfar/gui.h>


#define DIALOG_MINWIDTH  200
#define DIALOG_MINHEIGHT 100



GWEN_INHERIT(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG)




GWEN_DIALOG *AH_RdhSpecialDialog_new(AB_BANKING *ab) {
  GWEN_DIALOG *dlg;
  AH_RDH_SPECIAL_DIALOG *xdlg;
  GWEN_BUFFER *fbuf;
  int rv;

  dlg=GWEN_Dialog_new("ah_rdh_special");
  GWEN_NEW_OBJECT(AH_RDH_SPECIAL_DIALOG, xdlg);
  GWEN_INHERIT_SETDATA(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG, dlg, xdlg,
		       AH_RdhSpecialDialog_FreeData);
  GWEN_Dialog_SetSignalHandler(dlg, AH_RdhSpecialDialog_SignalHandler);

  /* get path of dialog description file */
  fbuf=GWEN_Buffer_new(0, 256, 0, 1);
  rv=GWEN_PathManager_FindFile(AB_PM_LIBNAME, AB_PM_DATADIR,
			       "aqbanking/backends/aqhbci/dialogs/dlg_rdh_special.dlg",
			       fbuf);
  if (rv<0) {
    DBG_INFO(AQHBCI_LOGDOMAIN, "Dialog description file not found (%d).", rv);
    GWEN_Buffer_free(fbuf);
    GWEN_Dialog_free(dlg);
    return NULL;
  }

  /* read dialog from dialog description file */
  rv=GWEN_Dialog_ReadXmlFile(dlg, GWEN_Buffer_GetStart(fbuf));
  if (rv<0) {
    DBG_INFO(AQHBCI_LOGDOMAIN, "here (%d).", rv);
    GWEN_Buffer_free(fbuf);
    GWEN_Dialog_free(dlg);
    return NULL;
  }
  GWEN_Buffer_free(fbuf);

  xdlg->banking=ab;

  /* preset */
  xdlg->hbciVersion=300;
  xdlg->rdhVersion=0;

  /* done */
  return dlg;
}



void GWENHYWFAR_CB AH_RdhSpecialDialog_FreeData(void *bp, void *p) {
  AH_RDH_SPECIAL_DIALOG *xdlg;

  xdlg=(AH_RDH_SPECIAL_DIALOG*) p;
  GWEN_FREE_OBJECT(xdlg);
}



int AH_RdhSpecialDialog_GetHbciVersion(const GWEN_DIALOG *dlg) {
  AH_RDH_SPECIAL_DIALOG *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG, dlg);
  assert(xdlg);

  return xdlg->hbciVersion;
}



void AH_RdhSpecialDialog_SetHbciVersion(GWEN_DIALOG *dlg, int i) {
  AH_RDH_SPECIAL_DIALOG *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG, dlg);
  assert(xdlg);

  xdlg->hbciVersion=i;
}



int AH_RdhSpecialDialog_GetRdhVersion(const GWEN_DIALOG *dlg) {
  AH_RDH_SPECIAL_DIALOG *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG, dlg);
  assert(xdlg);

  return xdlg->rdhVersion;
}



void AH_RdhSpecialDialog_SetRdhVersion(GWEN_DIALOG *dlg, int i) {
  AH_RDH_SPECIAL_DIALOG *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG, dlg);
  assert(xdlg);

  xdlg->rdhVersion=i;
}



uint32_t AH_RdhSpecialDialog_GetFlags(const GWEN_DIALOG *dlg) {
  AH_RDH_SPECIAL_DIALOG *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG, dlg);
  assert(xdlg);

  return xdlg->flags;
}



void AH_RdhSpecialDialog_SetFlags(GWEN_DIALOG *dlg, uint32_t fl) {
  AH_RDH_SPECIAL_DIALOG *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG, dlg);
  assert(xdlg);

  xdlg->flags=fl;
}



void AH_RdhSpecialDialog_AddFlags(GWEN_DIALOG *dlg, uint32_t fl) {
  AH_RDH_SPECIAL_DIALOG *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG, dlg);
  assert(xdlg);

  xdlg->flags&=~fl;
}



void AH_RdhSpecialDialog_SubFlags(GWEN_DIALOG *dlg, uint32_t fl) {
  AH_RDH_SPECIAL_DIALOG *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG, dlg);
  assert(xdlg);

  xdlg->flags&=~fl;
}



void AH_RdhSpecialDialog_Init(GWEN_DIALOG *dlg) {
  AH_RDH_SPECIAL_DIALOG *xdlg;
  GWEN_DB_NODE *dbPrefs;
  int i;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG, dlg);
  assert(xdlg);

  dbPrefs=GWEN_Dialog_GetPreferences(dlg);

  GWEN_Dialog_SetCharProperty(dlg,
			      "",
			      GWEN_DialogProperty_Title,
			      0,
			      I18N("HBCI Keyfile Special Settings"),
			      0);

  GWEN_Dialog_SetCharProperty(dlg, "hbciVersionCombo", GWEN_DialogProperty_AddValue, 0, "2.01", 0);
  GWEN_Dialog_SetCharProperty(dlg, "hbciVersionCombo", GWEN_DialogProperty_AddValue, 0, "2.10", 0);
  GWEN_Dialog_SetCharProperty(dlg, "hbciVersionCombo", GWEN_DialogProperty_AddValue, 0, "2.20", 0);
  GWEN_Dialog_SetCharProperty(dlg, "hbciVersionCombo", GWEN_DialogProperty_AddValue, 0, "3.0", 0);

  /* toGui */
  switch(xdlg->hbciVersion) {
  case 201: GWEN_Dialog_SetIntProperty(dlg, "hbciVersionCombo", GWEN_DialogProperty_Value, 0, 0, 0); break;
  case 210: GWEN_Dialog_SetIntProperty(dlg, "hbciVersionCombo", GWEN_DialogProperty_Value, 0, 1, 0); break;
  case 220: GWEN_Dialog_SetIntProperty(dlg, "hbciVersionCombo", GWEN_DialogProperty_Value, 0, 2, 0); break;
  case 300: GWEN_Dialog_SetIntProperty(dlg, "hbciVersionCombo", GWEN_DialogProperty_Value, 0, 3, 0); break;
  default:  break;
  }

  GWEN_Dialog_SetCharProperty(dlg, "rdhVersionCombo", GWEN_DialogProperty_AddValue, 0, I18N("(auto)"), 0);
  GWEN_Dialog_SetCharProperty(dlg, "rdhVersionCombo", GWEN_DialogProperty_AddValue, 0, "1", 0);
  GWEN_Dialog_SetCharProperty(dlg, "rdhVersionCombo", GWEN_DialogProperty_AddValue, 0, "2", 0);
  GWEN_Dialog_SetCharProperty(dlg, "rdhVersionCombo", GWEN_DialogProperty_AddValue, 0, "9", 0);
  GWEN_Dialog_SetCharProperty(dlg, "rdhVersionCombo", GWEN_DialogProperty_AddValue, 0, "10", 0);

  /* toGui */
  switch(xdlg->rdhVersion) {
  case 0:  GWEN_Dialog_SetIntProperty(dlg, "rdhVersionCombo", GWEN_DialogProperty_Value, 0, 0, 0); break;
  case 1:  GWEN_Dialog_SetIntProperty(dlg, "rdhVersionCombo", GWEN_DialogProperty_Value, 0, 1, 0); break;
  case 2:  GWEN_Dialog_SetIntProperty(dlg, "rdhVersionCombo", GWEN_DialogProperty_Value, 0, 2, 0); break;
  case 9: GWEN_Dialog_SetIntProperty(dlg, "rdhVersionCombo", GWEN_DialogProperty_Value, 0, 3, 0); break;
  case 10: GWEN_Dialog_SetIntProperty(dlg, "rdhVersionCombo", GWEN_DialogProperty_Value, 0, 4, 0); break;
  default:  break;
  }

  GWEN_Dialog_SetIntProperty(dlg, "bankDoesntSignCheck", GWEN_DialogProperty_Value, 0,
			     (xdlg->flags & AH_USER_FLAGS_BANK_DOESNT_SIGN)?1:0,
			     0);

  GWEN_Dialog_SetIntProperty(dlg, "bankUsesSignSeqCheck", GWEN_DialogProperty_Value, 0,
			     (xdlg->flags & AH_USER_FLAGS_BANK_USES_SIGNSEQ)?1:0,
			     0);

  /* read width */
  i=GWEN_DB_GetIntValue(dbPrefs, "dialog_width", 0, -1);
  if (i>=DIALOG_MINWIDTH)
    GWEN_Dialog_SetIntProperty(dlg, "", GWEN_DialogProperty_Width, 0, i, 0);

  /* read height */
  i=GWEN_DB_GetIntValue(dbPrefs, "dialog_height", 0, -1);
  if (i>=DIALOG_MINHEIGHT)
    GWEN_Dialog_SetIntProperty(dlg, "", GWEN_DialogProperty_Height, 0, i, 0);
}



void AH_RdhSpecialDialog_Fini(GWEN_DIALOG *dlg) {
  AH_RDH_SPECIAL_DIALOG *xdlg;
  int i;
  GWEN_DB_NODE *dbPrefs;
  uint32_t flags;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG, dlg);
  assert(xdlg);

  dbPrefs=GWEN_Dialog_GetPreferences(dlg);

  /* fromGui */
  i=GWEN_Dialog_GetIntProperty(dlg, "hbciVersionCombo", GWEN_DialogProperty_Value, 0, -1);
  switch(i) {
  case 0: xdlg->hbciVersion=201; break;
  default:
  case 1: xdlg->hbciVersion=210; break;
  case 2: xdlg->hbciVersion=220; break;
  case 3: xdlg->hbciVersion=300; break;
  }

  i=GWEN_Dialog_GetIntProperty(dlg, "rdhVersionCombo", GWEN_DialogProperty_Value, 0, -1);
  switch(i) {
  case 1: xdlg->rdhVersion=1; break;
  case 2: xdlg->rdhVersion=2; break;
  case 3: xdlg->rdhVersion=9; break;
  case 4: xdlg->rdhVersion=10; break;
  default:
  case 0: xdlg->rdhVersion=0; break;
  }

  flags=0;
  if (GWEN_Dialog_GetIntProperty(dlg, "bankDoesntSignCheck", GWEN_DialogProperty_Value, 0, 0))
    flags|=AH_USER_FLAGS_BANK_DOESNT_SIGN;
  if (GWEN_Dialog_GetIntProperty(dlg, "bankUsesSignSeqCheck", GWEN_DialogProperty_Value, 0, 0))
    flags|=AH_USER_FLAGS_BANK_USES_SIGNSEQ;
  xdlg->flags=flags;

  /* store dialog width */
  i=GWEN_Dialog_GetIntProperty(dlg, "", GWEN_DialogProperty_Width, 0, -1);
  GWEN_DB_SetIntValue(dbPrefs,
		      GWEN_DB_FLAGS_OVERWRITE_VARS,
		      "dialog_width",
		      i);

  /* store dialog height */
  i=GWEN_Dialog_GetIntProperty(dlg, "", GWEN_DialogProperty_Height, 0, -1);
  GWEN_DB_SetIntValue(dbPrefs,
		      GWEN_DB_FLAGS_OVERWRITE_VARS,
		      "dialog_height",
		      i);
}



int AH_RdhSpecialDialog_HandleActivated(GWEN_DIALOG *dlg, const char *sender) {
  DBG_NOTICE(0, "Activated: %s", sender);
  if (strcasecmp(sender, "okButton")==0)
    return GWEN_DialogEvent_ResultAccept;
  else if (strcasecmp(sender, "abortButton")==0)
    return GWEN_DialogEvent_ResultReject;
  else if (strcasecmp(sender, "helpButton")==0) {
    /* TODO: open a help dialog */
  }

  return GWEN_DialogEvent_ResultNotHandled;
}



int GWENHYWFAR_CB AH_RdhSpecialDialog_SignalHandler(GWEN_DIALOG *dlg,
							   GWEN_DIALOG_EVENTTYPE t,
							   const char *sender) {
  AH_RDH_SPECIAL_DIALOG *xdlg;

  assert(dlg);
  xdlg=GWEN_INHERIT_GETDATA(GWEN_DIALOG, AH_RDH_SPECIAL_DIALOG, dlg);
  assert(xdlg);

  switch(t) {
  case GWEN_DialogEvent_TypeInit:
    AH_RdhSpecialDialog_Init(dlg);
    return GWEN_DialogEvent_ResultHandled;;

  case GWEN_DialogEvent_TypeFini:
    AH_RdhSpecialDialog_Fini(dlg);
    return GWEN_DialogEvent_ResultHandled;;

  case GWEN_DialogEvent_TypeValueChanged:
    return GWEN_DialogEvent_ResultHandled;;

  case GWEN_DialogEvent_TypeActivated:
    return AH_RdhSpecialDialog_HandleActivated(dlg, sender);

  case GWEN_DialogEvent_TypeEnabled:
  case GWEN_DialogEvent_TypeDisabled:
  case GWEN_DialogEvent_TypeClose:

  case GWEN_DialogEvent_TypeLast:
    return GWEN_DialogEvent_ResultNotHandled;

  }

  return GWEN_DialogEvent_ResultNotHandled;
}






