/* This file is auto-generated from "pin.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "pin_p.h"
#include <gwenhywfar/misc.h>
#include <gwenhywfar/db.h>
#include <gwenhywfar/debug.h>
#include <assert.h>
#include <stdlib.h>
#include <strings.h>



GWEN_LIST_FUNCTIONS(AB_PIN, AB_Pin)
GWEN_LIST2_FUNCTIONS(AB_PIN, AB_Pin)


AB_PIN *AB_Pin_new() {
  AB_PIN *st;

  GWEN_NEW_OBJECT(AB_PIN, st)
  st->_usage=1;
  GWEN_LIST_INIT(AB_PIN, st)
  return st;
}


void AB_Pin_free(AB_PIN *st) {
  if (st) {
    assert(st->_usage);
    if (--(st->_usage)==0) {
  if (st->token)
    free(st->token);
  if (st->value)
    free(st->value);
  if (st->hash)
    free(st->hash);
  if (st->status)
    free(st->status);
  GWEN_LIST_FINI(AB_PIN, st)
  GWEN_FREE_OBJECT(st);
    }
  }

}


AB_PIN *AB_Pin_dup(const AB_PIN *d) {
  AB_PIN *st;

  assert(d);
  st=AB_Pin_new();
  if (d->token)
    st->token=strdup(d->token);
  if (d->value)
    st->value=strdup(d->value);
  if (d->hash)
    st->hash=strdup(d->hash);
  if (d->status)
    st->status=strdup(d->status);
  return st;
}


int AB_Pin_toDb(const AB_PIN *st, GWEN_DB_NODE *db) {
  assert(st);
  assert(db);
  if (st->token)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "token", st->token))
      return -1;
  if (st->value)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "value", st->value))
      return -1;
  if (st->hash)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "hash", st->hash))
      return -1;
  if (st->status)
    if (GWEN_DB_SetCharValue(db, GWEN_DB_FLAGS_OVERWRITE_VARS, "status", st->status))
      return -1;
  return 0;
}


AB_PIN *AB_Pin_fromDb(GWEN_DB_NODE *db) {
AB_PIN *st;

  assert(db);
  st=AB_Pin_new();
  AB_Pin_SetToken(st, GWEN_DB_GetCharValue(db, "token", 0, 0));
  AB_Pin_SetValue(st, GWEN_DB_GetCharValue(db, "value", 0, 0));
  AB_Pin_SetHash(st, GWEN_DB_GetCharValue(db, "hash", 0, 0));
  AB_Pin_SetStatus(st, GWEN_DB_GetCharValue(db, "status", 0, 0));
  st->_modified=0;
  return st;
}


const char *AB_Pin_GetToken(const AB_PIN *st) {
  assert(st);
  return st->token;
}


void AB_Pin_SetToken(AB_PIN *st, const char *d) {
  assert(st);
  if (st->token)
    free(st->token);
  if (d && *d)
    st->token=strdup(d);
  else
    st->token=0;
  st->_modified=1;
}




const char *AB_Pin_GetValue(const AB_PIN *st) {
  assert(st);
  return st->value;
}


void AB_Pin_SetValue(AB_PIN *st, const char *d) {
  assert(st);
  if (st->value)
    free(st->value);
  if (d && *d)
    st->value=strdup(d);
  else
    st->value=0;
  st->_modified=1;
}




const char *AB_Pin_GetHash(const AB_PIN *st) {
  assert(st);
  return st->hash;
}


void AB_Pin_SetHash(AB_PIN *st, const char *d) {
  assert(st);
  if (st->hash)
    free(st->hash);
  if (d && *d)
    st->hash=strdup(d);
  else
    st->hash=0;
  st->_modified=1;
}




const char *AB_Pin_GetStatus(const AB_PIN *st) {
  assert(st);
  return st->status;
}


void AB_Pin_SetStatus(AB_PIN *st, const char *d) {
  assert(st);
  if (st->status)
    free(st->status);
  if (d && *d)
    st->status=strdup(d);
  else
    st->status=0;
  st->_modified=1;
}




int AB_Pin_IsModified(const AB_PIN *st) {
  assert(st);
  return st->_modified;
}


void AB_Pin_SetModified(AB_PIN *st, int i) {
  assert(st);
  st->_modified=i;
}


void AB_Pin_Attach(AB_PIN *st) {
  assert(st);
  st->_usage++;
}
AB_PIN *AB_Pin_List2__freeAll_cb(AB_PIN *st, void *user_data) {
  AB_Pin_free(st);
return 0;
}


void AB_Pin_List2_freeAll(AB_PIN_LIST2 *stl) {
  if (stl) {
    AB_Pin_List2_ForEach(stl, AB_Pin_List2__freeAll_cb, 0);
    AB_Pin_List2_free(stl); 
  }
}




AB_PIN_LIST *AB_Pin_List_dup(const AB_PIN_LIST *stl) {
  if (stl) {
    AB_PIN_LIST *nl;
    AB_PIN *e;

    nl=AB_Pin_List_new();
    e=AB_Pin_List_First(stl);
    while(e) {
      AB_PIN *ne;

      ne=AB_Pin_dup(e);
      assert(ne);
      AB_Pin_List_Add(ne, nl);
      e=AB_Pin_List_Next(e);
    } /* while (e) */
    return nl;
  }
  else
    return 0;
}



