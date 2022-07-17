/*
 * Compile-in this chunk of code unless we've turned it off specifically
 * or in general (id=_windows_1257).
 */

#ifndef INCL_CHARSET_windows_1257
#define INCL_CHARSET_windows_1257 1

/*ifdef NO_CHARSET*/
#ifdef  NO_CHARSET
#undef  NO_CHARSET
#endif
#define NO_CHARSET 0 /* force default to always be active */

/*ifndef NO_CHARSET_windows_1257*/
#ifndef NO_CHARSET_windows_1257

#if    ALL_CHARSETS
#define NO_CHARSET_windows_1257 0
#else
#define NO_CHARSET_windows_1257 1
#endif

#endif /* ndef(NO_CHARSET_windows_1257) */

#if NO_CHARSET_windows_1257
#define UC_CHARSET_SETUP_windows_1257 /*nothing*/
#else

/*
 *  uni_hash.tbl
 *
 *  Do not edit this file; it was automatically generated by
 *
 *  ./makeuctb ./cp1257_uni.tbl
 *
 */

static CONST u8 dfont_unicount_windows_1257[256] = 
{
	  0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   0,
	  1,   0,   1,   0,   1,   1,   1,   1,
	  0,   1,   0,   1,   0,   1,   1,   1,
	  0,   1,   1,   1,   1,   1,   1,   1,
	  0,   1,   0,   1,   0,   1,   1,   0,
	  1,   0,   1,   1,   1,   0,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1,
	  1,   1,   1,   1,   1,   1,   1,   1
};

static CONST u16 dfont_unitable_windows_1257[211] = 
{
	0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
	0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f,
	0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
	0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f,
	0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
	0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f,
	0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
	0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f,
	0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
	0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f,
	0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
	0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x20ac,
	0x201a, 0x201e, 0x2026, 0x2020, 0x2021, 0x2030, 0x2039, 0x00a8,
	0x02c7, 0x00b8, 0x2018, 0x2019, 0x201c, 0x201d, 0x2022, 0x2013,
	0x2014, 0x2122, 0x203a, 0x00af, 0x02db, 0x00a0, 0x00a2, 0x00a3,
	0x00a4, 0x00a6, 0x00a7, 0x00d8, 0x00a9, 0x0156, 0x00ab, 0x00ac,
	0x00ad, 0x00ae, 0x00c6, 0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4,
	0x00b5, 0x00b6, 0x00b7, 0x00f8, 0x00b9, 0x0157, 0x00bb, 0x00bc,
	0x00bd, 0x00be, 0x00e6, 0x0104, 0x012e, 0x0100, 0x0106, 0x00c4,
	0x00c5, 0x0118, 0x0112, 0x010c, 0x00c9, 0x0179, 0x0116, 0x0122,
	0x0136, 0x012a, 0x013b, 0x0160, 0x0143, 0x0145, 0x00d3, 0x014c,
	0x00d5, 0x00d6, 0x00d7, 0x0172, 0x0141, 0x015a, 0x016a, 0x00dc,
	0x017b, 0x017d, 0x00df, 0x0105, 0x012f, 0x0101, 0x0107, 0x00e4,
	0x00e5, 0x0119, 0x0113, 0x010d, 0x00e9, 0x017a, 0x0117, 0x0123,
	0x0137, 0x012b, 0x013c, 0x0161, 0x0144, 0x0146, 0x00f3, 0x014d,
	0x00f5, 0x00f6, 0x00f7, 0x0173, 0x0142, 0x015b, 0x016b, 0x00fc,
	0x017c, 0x017e, 0x02d9
};

/* static struct unipair_str repl_map_windows_1257[]; */

static CONST struct unimapdesc_str dfont_replacedesc_windows_1257 = {0,NULL,0,1};
#define UC_CHARSET_SETUP_windows_1257 UC_Charset_Setup("windows-1257",\
"Baltic Rim (windows-1257)",\
dfont_unicount_windows_1257,dfont_unitable_windows_1257,211,\
dfont_replacedesc_windows_1257,128,1,1257)

#endif /* NO_CHARSET_windows_1257 */

#endif /* INCL_CHARSET_windows_1257 */
