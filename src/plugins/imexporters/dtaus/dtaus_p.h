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


#ifndef AQHBCI_IMEX_DTAUS_P_H
#define AQHBCI_IMEX_DTAUS_P_H


#include <gwenhywfar/dbio.h>
#include <aqbanking/imexporter_be.h>


typedef struct AH_IMEXPORTER_DTAUS AH_IMEXPORTER_DTAUS;
struct AH_IMEXPORTER_DTAUS {
  GWEN_DB_NODE *dbData;
  GWEN_DBIO *dbio;
};


AB_IMEXPORTER* dtaus_factory(AB_BANKING *ab, GWEN_DB_NODE *db);
void GWENHYWFAR_CB AH_ImExporterDTAUS_FreeData(void *bp, void *p);

int AH_ImExporterDTAUS_Import(AB_IMEXPORTER *ie,
                              AB_IMEXPORTER_CONTEXT *ctx,
                              GWEN_BUFFEREDIO *bio,
                              GWEN_DB_NODE *params);

int AH_ImExporterDTAUS_CheckFile(AB_IMEXPORTER *ie, const char *fname);

int AH_ImExporterDTAUS__ImportFromGroup(AB_IMEXPORTER_CONTEXT *ctx,
                                        GWEN_DB_NODE *db,
                                        GWEN_DB_NODE *dbParams);

#endif /* AQHBCI_IMEX_DTAUS_P_H */
