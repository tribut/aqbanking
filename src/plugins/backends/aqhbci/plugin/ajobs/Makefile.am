
AM_CFLAGS=-DBUILDING_AQHBCI @visibility_cflags@

INCLUDES = -I$(aqbanking_symlinkdir) $(all_includes) \
  -I$(srcdir)/../joblayer \
  -I$(srcdir)/../msglayer \
  -I$(srcdir)/../banking \
  -I$(srcdir)/../applayer \
  -I$(srcdir)/..

noinst_LTLIBRARIES=libhbciaccjobs.la

noinst_HEADERS=\
  accountjob_l.h \
  accountjob_p.h \
  jobgetbalance_l.h \
  jobgetbalance_p.h \
  jobgettransactions_l.h \
  jobgettransactions_p.h \
  jobforeignxferwh_l.h \
  jobforeignxferwh_p.h \
  jobloadcellphone_l.h \
  jobloadcellphone_p.h \
  jobsepadebitdatedsinglecreate_l.h \
  jobsepadebitdatedsinglecreate_p.h \
  jobsepadebitdatedmulticreate_l.h \
  jobsepadebitdatedmulticreate_p.h \
  jobsepacor1datedmulticreate_l.h \
  jobsepacor1datedmulticreate_p.h \
  jobsepaxfermulti_l.h \
  jobsepaxfermulti_p.h \
  jobsepaxfersingle_l.h \
  jobsepaxfersingle_p.h \
  jobsepadebitsingle_l.h \
  jobsepadebitsingle_p.h \
  jobsepacor1datedsinglecreate_l.h \
  jobsepacor1datedsinglecreate_p.h \
  jobtransferbase_l.h jobtransferbase_p.h \
  jobsepastandingordercreate_l.h  \
  jobsepastandingorderget_l.h jobsepastandingorderget_p.h \
  jobsepastandingordermodify_l.h \
  jobsepastandingorderdelete_l.h

libhbciaccjobs_la_SOURCES=\
  accountjob.c \
  jobgetbalance.c \
  jobgettransactions.c \
  jobforeignxferwh.c \
  jobloadcellphone.c \
  jobsepadebitdatedsinglecreate.c \
  jobsepadebitdatedmulticreate.c \
  jobsepacor1datedmulticreate.c \
  jobsepaxfermulti.c \
  jobsepaxfersingle.c \
  jobsepadebitsingle.c \
  jobsepacor1datedsinglecreate.c \
  jobtransferbase.c \
  jobsepastandingordercreate.c \
  jobsepastandingorderget.c \
  jobsepastandingordermodify.c \
  jobsepastandingorderdelete.c


sources:
	for f in $(libhbciaccjobs_la_SOURCES); do \
	  echo $(subdir)/$$f >>$(top_srcdir)/i18nsources; \
	done
	for d in $(SUBDIRS); do \
	  $(MAKE) -C $$d sources; \
	done

xmlfiles=\
  $(srcdir)/jobgetbalance.xml \
  $(srcdir)/jobgettransactions.xml \
  $(srcdir)/jobforeignxferwh.xml \
  $(srcdir)/jobloadcellphone.xml \
  $(srcdir)/jobsepadebitdatedsinglecreate.xml \
  $(srcdir)/jobsepadebitdatedmulticreate.xml \
  $(srcdir)/jobsepacor1datedmulticreate.xml \
  $(srcdir)/jobsepaxfermulti.xml \
  $(srcdir)/jobsepaxfersingle.xml \
  $(srcdir)/jobsepadebitsingle.xml \
  $(srcdir)/jobsepacor1datedsinglecreate.xml \
  $(srcdir)/jobsepastandingordercreate.xml \
  $(srcdir)/jobsepastandingorderget.xml \
  $(srcdir)/jobsepastandingordermodify.xml \
  $(srcdir)/jobsepastandingorderdelete.xml

EXTRA_DIST=$(xmlfiles)

accountjobs.xml: $(xmlfiles)
	$(XMLMERGE) -v --compact -o $@ $(xmlfiles)

all-local: accountjobs.xml

CLEANFILES = accountjobs.xml
