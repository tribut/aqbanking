/* This file is auto-generated from "eutransferinfo.xml" by the typemaker
   tool of Gwenhywfar. 
   Do not edit this file -- all changes will be lost! */
#ifndef EUTRANSFERINFO_H
#define EUTRANSFERINFO_H

/** @page P_AB_EUTRANSFER_INFO_PUBLIC AB_EuTransferInfo (public)
This page describes the properties of AB_EUTRANSFER_INFO
@anchor AB_EUTRANSFER_INFO_CountryCode
<h3>CountryCode</h3>
<p>
This is the two-character ISO country code (as used in toplevel domains). For Germany use &quot;DE&quot;.</p>
<p>
Set this property with @ref AB_EuTransferInfo_SetCountryCode, 
get it with @ref AB_EuTransferInfo_GetCountryCode
</p>

@anchor AB_EUTRANSFER_INFO_FieldLimits
<h3>FieldLimits</h3>
<p>
This is the list of known field limits for an AB_TRANSACTION. This object remains the owner of lists returned via @ref AB_EuTransfer_GetFieldLimits..</p>
<p>
Set this property with @ref AB_EuTransferInfo_SetFieldLimits, 
get it with @ref AB_EuTransferInfo_GetFieldLimits
</p>

@anchor AB_EUTRANSFER_INFO_LimitLocalValue
<h3>LimitLocalValue</h3>
<p>
Optional limit for a transfer in local currency.</p>
<p>
Set this property with @ref AB_EuTransferInfo_SetLimitLocalValue, 
get it with @ref AB_EuTransferInfo_GetLimitLocalValue
</p>

@anchor AB_EUTRANSFER_INFO_LimitForeignValue
<h3>LimitForeignValue</h3>
<p>
Optional limit for a transfer in foreign currency.</p>
<p>
Set this property with @ref AB_EuTransferInfo_SetLimitForeignValue, 
get it with @ref AB_EuTransferInfo_GetLimitForeignValue
</p>

*/
#ifdef __cplusplus
extern "C" {
#endif

typedef struct AB_EUTRANSFER_INFO AB_EUTRANSFER_INFO;

#ifdef __cplusplus
} /* __cplusplus */
#endif

#include <gwenhywfar/db.h>
#include <gwenhywfar/misc.h>
#include <gwenhywfar/list2.h>
#include <gwenhywfar/types.h>
#include <aqbanking/value.h>
#include <aqbanking/transactionlimits.h>

#ifdef __cplusplus
extern "C" {
#endif


GWEN_LIST_FUNCTION_LIB_DEFS(AB_EUTRANSFER_INFO, AB_EuTransferInfo, AQBANKING_API)
AB_EUTRANSFER_INFO_LIST *AB_EuTransferInfo_List_dup(const AB_EUTRANSFER_INFO_LIST *stl);

GWEN_LIST2_FUNCTION_LIB_DEFS(AB_EUTRANSFER_INFO, AB_EuTransferInfo, AQBANKING_API)

/** Destroys all objects stored in the given LIST2 and the list itself
*/
AQBANKING_API void AB_EuTransferInfo_List2_freeAll(AB_EUTRANSFER_INFO_LIST2 *stl);
/** Creates a deep copy of the given LIST2.
*/
AQBANKING_API AB_EUTRANSFER_INFO_LIST2 *AB_EuTransferInfo_List2_dup(const AB_EUTRANSFER_INFO_LIST2 *stl);

/** Creates a new object.
*/
AQBANKING_API AB_EUTRANSFER_INFO *AB_EuTransferInfo_new();
/** Destroys the given object.
*/
AQBANKING_API void AB_EuTransferInfo_free(AB_EUTRANSFER_INFO *st);
/** Increments the usage counter of the given object, so an additional free() is needed to destroy the object.
*/
AQBANKING_API void AB_EuTransferInfo_Attach(AB_EUTRANSFER_INFO *st);
/** Creates and returns a deep copy of thegiven object.
*/
AQBANKING_API AB_EUTRANSFER_INFO *AB_EuTransferInfo_dup(const AB_EUTRANSFER_INFO*st);
/** Creates an object from the data in the given GWEN_DB_NODE
*/
AQBANKING_API AB_EUTRANSFER_INFO *AB_EuTransferInfo_fromDb(GWEN_DB_NODE *db);
/** Stores an object in the given GWEN_DB_NODE
*/
AQBANKING_API int AB_EuTransferInfo_toDb(const AB_EUTRANSFER_INFO*st, GWEN_DB_NODE *db);
/** Returns 0 if this object has not been modified, !=0 otherwise
*/
AQBANKING_API int AB_EuTransferInfo_IsModified(const AB_EUTRANSFER_INFO *st);
/** Sets the modified state of the given object
*/
AQBANKING_API void AB_EuTransferInfo_SetModified(AB_EUTRANSFER_INFO *st, int i);

/**
* Returns the property @ref AB_EUTRANSFER_INFO_CountryCode
*/
AQBANKING_API const char *AB_EuTransferInfo_GetCountryCode(const AB_EUTRANSFER_INFO *el);
/**
* Set the property @ref AB_EUTRANSFER_INFO_CountryCode
*/
AQBANKING_API void AB_EuTransferInfo_SetCountryCode(AB_EUTRANSFER_INFO *el, const char *d);

/**
* Returns the property @ref AB_EUTRANSFER_INFO_FieldLimits
*/
AQBANKING_API const AB_TRANSACTION_LIMITS *AB_EuTransferInfo_GetFieldLimits(const AB_EUTRANSFER_INFO *el);
/**
* Set the property @ref AB_EUTRANSFER_INFO_FieldLimits
*/
AQBANKING_API void AB_EuTransferInfo_SetFieldLimits(AB_EUTRANSFER_INFO *el, const AB_TRANSACTION_LIMITS *d);

/**
* Returns the property @ref AB_EUTRANSFER_INFO_LimitLocalValue
*/
AQBANKING_API const AB_VALUE *AB_EuTransferInfo_GetLimitLocalValue(const AB_EUTRANSFER_INFO *el);
/**
* Set the property @ref AB_EUTRANSFER_INFO_LimitLocalValue
*/
AQBANKING_API void AB_EuTransferInfo_SetLimitLocalValue(AB_EUTRANSFER_INFO *el, const AB_VALUE *d);

/**
* Returns the property @ref AB_EUTRANSFER_INFO_LimitForeignValue
*/
AQBANKING_API const AB_VALUE *AB_EuTransferInfo_GetLimitForeignValue(const AB_EUTRANSFER_INFO *el);
/**
* Set the property @ref AB_EUTRANSFER_INFO_LimitForeignValue
*/
AQBANKING_API void AB_EuTransferInfo_SetLimitForeignValue(AB_EUTRANSFER_INFO *el, const AB_VALUE *d);


#ifdef __cplusplus
} /* __cplusplus */
#endif


#endif /* EUTRANSFERINFO_H */
