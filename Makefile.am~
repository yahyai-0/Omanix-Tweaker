## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po \
	desktop \
	icons

omanix_tweakerdocdir = ${prefix}/doc/omanix_tweaker
omanix_tweakerdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(omanix_tweakerdoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(omanix_tweakerdocdir)
