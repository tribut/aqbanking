/***************************************************************************
 begin       : Mon Mar 01 2004
 copyright   : (C) 2004-2013 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 * This file is part of the project "AqBanking".                           *
 * Please see toplevel file COPYING of that project for license details.   *
 ***************************************************************************/


#ifndef AQBANKING_JOBDELETEDATEDTRANSFER_BE_H
#define AQBANKING_JOBDELETEDATEDTRANSFER_BE_H


#include <aqbanking/jobdeletedatedtransfer.h>


/** @addtogroup G_AB_JOBS_DATED_TRANSFER_DEL
 *
 */
/*@{*/

/** @name Backend Functions
 *
 * Functions in this group are only to be called by banking backends.
 */
/*@{*/

/**
 * This function lets the backend specify the limits for some of the fields
 * of a @ref AB_TRANSACTION.
 */
AQBANKING_API AQBANKING_DEPRECATED
void AB_JobDeleteDatedTransfer_SetFieldLimits(AB_JOB *j,
                                              AB_TRANSACTION_LIMITS *limits);
/*@}*/ 


/*@}*/ /* addtogroup */


#endif

