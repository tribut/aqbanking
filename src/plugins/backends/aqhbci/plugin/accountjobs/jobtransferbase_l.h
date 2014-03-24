/***************************************************************************
    begin       : Mon Mar 01 2004
    copyright   : (C) 2004-2013 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


#ifndef AH_JOBTRANSFERBASE_L_H
#define AH_JOBTRANSFERBASE_L_H


#include "accountjob_l.h"


typedef int (*AH_JOB_TRANSFERBASE_EXCHANGE_FN)(AH_JOB *j, AB_JOB *bj,
                                                 AB_IMEXPORTER_CONTEXT *ctx);


AH_JOB *AH_Job_TransferBase_new(const char *jobName,
                                  AB_TRANSACTION_TYPE tt,
                                  AB_TRANSACTION_SUBTYPE tst,
                                  AB_USER *u, AB_ACCOUNT *account);

const char *AH_Job_TransferBase_GetFiid(const AH_JOB *j);


void AH_Job_TransferBase_SetExchangeParamsFn(AH_JOB *j, AH_JOB_TRANSFERBASE_EXCHANGE_FN f);
void AH_Job_TransferBase_SetExchangeArgsFn(AH_JOB *j, AH_JOB_TRANSFERBASE_EXCHANGE_FN f);
void AH_Job_TransferBase_SetExchangeResultsFn(AH_JOB *j, AH_JOB_TRANSFERBASE_EXCHANGE_FN f);




int AH_Job_TransferBase_SepaExportTransactions(AH_JOB *j, const char *profileName, GWEN_BUFFER *destBuf);

int AH_Job_TransferBase_ExchangeArgs_SepaDated(AH_JOB *j, AB_JOB *bj, AB_IMEXPORTER_CONTEXT *ctx);
int AH_Job_TransferBase_ExchangeArgs_SepaUndated(AH_JOB *j, AB_JOB *bj, AB_IMEXPORTER_CONTEXT *ctx);
int AH_Job_TransferBase_ExchangeArgs_SepaDatedDebit(AH_JOB *j, AB_JOB *bj, AB_IMEXPORTER_CONTEXT *ctx);


/**
 * @name SEPA Descriptors
 * For jobs which have their own list of supported SEPA formats in their BPD those can be handled here.
 * Those jobs MUST call @ref AH_Job_TransferBase_LoadSepaDescriptors inside the constructor.
 */
/*@{*/

/**
 * Load list of supported SEPA descriptors from the job's BPD.
 */
void AH_Job_TransferBase_LoadSepaDescriptors(AH_JOB *j);

/**
 * Find a SEPA descriptor in the internal list of supported SEPA descriptors read from the BPD.
 */
const char *AH_Job_TransferBase_FindSepaDescriptor(AH_JOB *j, const char *tmpl);

/*@}*/



#endif /* AH_JOBTRANSFERBASE_L_H */


