/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: idf.h,v 1.1 2005/09/01 12:13:20 beng Exp $ */
struct id_usr {
	union {
		struct macro *idu_macro;
		struct idf *idu_file;
	} idu_x;
	int idu_resmac;
};

#define IDF_TYPE struct id_usr
#define IDF_HSIZE 6
#define id_macro id_user.idu_x.idu_macro
#define id_file id_user.idu_x.idu_file
#define id_resmac id_user.idu_resmac

#include <idf_pkg.spec>
