/* This file is auto-generated from "bankinfoservice.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "bankinfoservice_p.h"
#include <gwenhywfar/misc.h>
#include <gwenhywfar/db.h>
#include <gwenhywfar/debug.h>
#include <assert.h>
#include <stdlib.h>
#include <strings.h>

#include <gwenhywfar/types.h>
#include <aqbanking/error.h>


GWEN_LIST_FUNCTIONS(AB_BANKINFO_SERVICE, AB_BankInfoService)
GWEN_LIST2_FUNCTIONS(AB_BANKINFO_SERVICE, AB_BankInfoService)




AB_BANKINFO_SERVICE *AB_BankInfoService_new() {
  AB_BANKINFO_SERVICE *st;

  GWEN_NEW_OBJECT(AB_BANKINFO_SERVICE, st)
  st->_usage=1;
  GWEN_LIST_INIT(AB_BANKINFO_SERVICE, st)
  return st;
}


void AB_BankInfoService_free(AB_BANKINFO_SERVICE *st) {
  if (st) {
    assert(st->_usage);
    if (--(st->_usage)==0) {
  if (st->type)
    free(st->type);
  if (st->address)
    free(st->address);
  if (st->suffix)
    free(st->suffix);
  if (st->pversion)
    free(st->pversion);
  if (st->mode)
    free(st->mode);
  if (st->aux1)
    free(st->aux1);
  if (st->aux2)
    free(st->aux2);
  if (st->aux3)
    free(st->aux3);
  if (st->aux4)
    free(st->aux4);
  GWEN_LIST_FINI(AB_BANKINFO_SERVICE, st)
  GWEN_FREE_OBJECT(st);
    }
  }

}


AB_BANKINFO_SERVICE *AB_BankInfoService_dup(const AB_BANKINFO_SERVICE *d) {
  AB_BANKINFO_SERVICE *st;

  assert(d);
  st=AB_BankInfoService_new();
  if (d->type)
    st->type=strdup(d->type);
  if (d->address)
    st->address=strdup(d->address);
  if (d->suffix)
    st->suffix=strdup(d->suffix);
  if (d->pversion)
    st->pversion=strdup(d->pversion);
  if (d->mode)
    st->mode=strdup(d->mode);
  if (d->aux1)
    st->aux1=strdup(d->aux1);
  if (d->aux2)
    st->aux2=strdup(d->aux2);
  if (d->aux3)
    st->aux3=strdup(d->aux3);
  if (d->aux4)
    st->aux4=strdup(d->aux4);
  return st;
}


int AB_BankInfoService_toDb(const AB_BANKINFO_SERVICE *st, GWEN_DB_NODE *db) {
  assert(st);
  assert(db);
  if (st->type)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "type", st->type))
      return -1;
  if (st->address)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "address", st->address))
      return -1;
  if (st->suffix)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "suffix", st->suffix))
      return -1;
  if (st->pversion)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "pversion", st->pversion))
      return -1;
  if (st->mode)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "mode", st->mode))
      return -1;
  if (st->aux1)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "aux1", st->aux1))
      return -1;
  if (st->aux2)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "aux2", st->aux2))
      return -1;
  if (st->aux3)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "aux3", st->aux3))
      return -1;
  if (st->aux4)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "aux4", st->aux4))
      return -1;
  return 0;
}


int AB_BankInfoService_ReadDb(AB_BANKINFO_SERVICE *st, GWEN_DB_NODE *db) {
  assert(st);
  assert(db);
  AB_BankInfoService_SetType(st, GWEN_DB_GetCharValue(db, "type", 0, 0));
  AB_BankInfoService_SetAddress(st, GWEN_DB_GetCharValue(db, "address", 0, 0));
  AB_BankInfoService_SetSuffix(st, GWEN_DB_GetCharValue(db, "suffix", 0, 0));
  AB_BankInfoService_SetPversion(st, GWEN_DB_GetCharValue(db, "pversion", 0, 0));
  AB_BankInfoService_SetMode(st, GWEN_DB_GetCharValue(db, "mode", 0, 0));
  AB_BankInfoService_SetAux1(st, GWEN_DB_GetCharValue(db, "aux1", 0, 0));
  AB_BankInfoService_SetAux2(st, GWEN_DB_GetCharValue(db, "aux2", 0, 0));
  AB_BankInfoService_SetAux3(st, GWEN_DB_GetCharValue(db, "aux3", 0, 0));
  AB_BankInfoService_SetAux4(st, GWEN_DB_GetCharValue(db, "aux4", 0, 0));
  return 0;
}


AB_BANKINFO_SERVICE *AB_BankInfoService_fromDb(GWEN_DB_NODE *db) {
  AB_BANKINFO_SERVICE *st;

  assert(db);
  st=AB_BankInfoService_new();
  AB_BankInfoService_ReadDb(st, db);
  st->_modified=0;
  return st;
}




const char *AB_BankInfoService_GetType(const AB_BANKINFO_SERVICE *st) {
  assert(st);
  return st->type;
}


void AB_BankInfoService_SetType(AB_BANKINFO_SERVICE *st, const char *d) {
  assert(st);
  if (st->type)
    free(st->type);
  if (d && *d)
    st->type=strdup(d);
  else
    st->type=0;
  st->_modified=1;
}




const char *AB_BankInfoService_GetAddress(const AB_BANKINFO_SERVICE *st) {
  assert(st);
  return st->address;
}


void AB_BankInfoService_SetAddress(AB_BANKINFO_SERVICE *st, const char *d) {
  assert(st);
  if (st->address)
    free(st->address);
  if (d && *d)
    st->address=strdup(d);
  else
    st->address=0;
  st->_modified=1;
}




const char *AB_BankInfoService_GetSuffix(const AB_BANKINFO_SERVICE *st) {
  assert(st);
  return st->suffix;
}


void AB_BankInfoService_SetSuffix(AB_BANKINFO_SERVICE *st, const char *d) {
  assert(st);
  if (st->suffix)
    free(st->suffix);
  if (d && *d)
    st->suffix=strdup(d);
  else
    st->suffix=0;
  st->_modified=1;
}




const char *AB_BankInfoService_GetPversion(const AB_BANKINFO_SERVICE *st) {
  assert(st);
  return st->pversion;
}


void AB_BankInfoService_SetPversion(AB_BANKINFO_SERVICE *st, const char *d) {
  assert(st);
  if (st->pversion)
    free(st->pversion);
  if (d && *d)
    st->pversion=strdup(d);
  else
    st->pversion=0;
  st->_modified=1;
}




const char *AB_BankInfoService_GetMode(const AB_BANKINFO_SERVICE *st) {
  assert(st);
  return st->mode;
}


void AB_BankInfoService_SetMode(AB_BANKINFO_SERVICE *st, const char *d) {
  assert(st);
  if (st->mode)
    free(st->mode);
  if (d && *d)
    st->mode=strdup(d);
  else
    st->mode=0;
  st->_modified=1;
}




const char *AB_BankInfoService_GetAux1(const AB_BANKINFO_SERVICE *st) {
  assert(st);
  return st->aux1;
}


void AB_BankInfoService_SetAux1(AB_BANKINFO_SERVICE *st, const char *d) {
  assert(st);
  if (st->aux1)
    free(st->aux1);
  if (d && *d)
    st->aux1=strdup(d);
  else
    st->aux1=0;
  st->_modified=1;
}




const char *AB_BankInfoService_GetAux2(const AB_BANKINFO_SERVICE *st) {
  assert(st);
  return st->aux2;
}


void AB_BankInfoService_SetAux2(AB_BANKINFO_SERVICE *st, const char *d) {
  assert(st);
  if (st->aux2)
    free(st->aux2);
  if (d && *d)
    st->aux2=strdup(d);
  else
    st->aux2=0;
  st->_modified=1;
}




const char *AB_BankInfoService_GetAux3(const AB_BANKINFO_SERVICE *st) {
  assert(st);
  return st->aux3;
}


void AB_BankInfoService_SetAux3(AB_BANKINFO_SERVICE *st, const char *d) {
  assert(st);
  if (st->aux3)
    free(st->aux3);
  if (d && *d)
    st->aux3=strdup(d);
  else
    st->aux3=0;
  st->_modified=1;
}




const char *AB_BankInfoService_GetAux4(const AB_BANKINFO_SERVICE *st) {
  assert(st);
  return st->aux4;
}


void AB_BankInfoService_SetAux4(AB_BANKINFO_SERVICE *st, const char *d) {
  assert(st);
  if (st->aux4)
    free(st->aux4);
  if (d && *d)
    st->aux4=strdup(d);
  else
    st->aux4=0;
  st->_modified=1;
}




int AB_BankInfoService_IsModified(const AB_BANKINFO_SERVICE *st) {
  assert(st);
  return st->_modified;
}


void AB_BankInfoService_SetModified(AB_BANKINFO_SERVICE *st, int i) {
  assert(st);
  st->_modified=i;
}


void AB_BankInfoService_Attach(AB_BANKINFO_SERVICE *st) {
  assert(st);
  st->_usage++;
}
AB_BANKINFO_SERVICE *AB_BankInfoService_List2__freeAll_cb(AB_BANKINFO_SERVICE *st, void *user_data) {
  AB_BankInfoService_free(st);
return 0;
}


void AB_BankInfoService_List2_freeAll(AB_BANKINFO_SERVICE_LIST2 *stl) {
  if (stl) {
    AB_BankInfoService_List2_ForEach(stl, AB_BankInfoService_List2__freeAll_cb, 0);
    AB_BankInfoService_List2_free(stl); 
  }
}


AB_BANKINFO_SERVICE_LIST *AB_BankInfoService_List_dup(const AB_BANKINFO_SERVICE_LIST *stl) {
  if (stl) {
    AB_BANKINFO_SERVICE_LIST *nl;
    AB_BANKINFO_SERVICE *e;

    nl=AB_BankInfoService_List_new();
    e=AB_BankInfoService_List_First(stl);
    while(e) {
      AB_BANKINFO_SERVICE *ne;

      ne=AB_BankInfoService_dup(e);
      assert(ne);
      AB_BankInfoService_List_Add(ne, nl);
      e=AB_BankInfoService_List_Next(e);
    } /* while (e) */
    return nl;
  }
  else
    return 0;
}




