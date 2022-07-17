/* $Id: idf.h,v 1.1 2005/09/01 12:13:33 beng Exp $ */

/* User-declared part of idf structure */

struct id_u {
	int id_res;
	struct symbol *id_df;
};

#define IDF_TYPE	struct id_u
#define id_reserved	id_user.id_res
#define id_def		id_user.id_df

#include	<idf_pkg.spec>
