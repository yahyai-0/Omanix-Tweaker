dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(omanix_tweaker, 0.5)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX




dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=omanix_tweaker
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT


PROGRAMNAME_LOCALEDIR=[${datadir}/locale]
AC_SUBST(PROGRAMNAME_LOCALEDIR)

LT_INIT



PKG_CHECK_MODULES(SQLITE3,sqlite3)

PKG_CHECK_MODULES(OMANIX_TWEAKER, [gtkmm-2.4 gconfmm-2.6 libsoup-gnome-2.4])




AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
icons/Makefile
icons/32x32/Makefile
icons/48x48/Makefile
icons/scalable/Makefile
desktop/Makefile
])
