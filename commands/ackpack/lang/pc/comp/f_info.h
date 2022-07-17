/* F I L E   D E S C R I P T O R   S T R U C T U R E */

struct f_info {
	unsigned short f_lineno;
	const char *f_filename;
	const char *f_workingdir;
};

extern struct f_info file_info;
#define LineNumber file_info.f_lineno
#define FileName file_info.f_filename
