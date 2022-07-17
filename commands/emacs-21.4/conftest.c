
#include "/usr/src/packages/packages/emacs-21.4/src/s/minix.h"
#include "/usr/src/packages/packages/emacs-21.4/src/m/intel386.h"
#ifndef LIBS_MACHINE
#define LIBS_MACHINE
#endif
#ifndef LIBS_SYSTEM
#define LIBS_SYSTEM
#endif
#ifndef C_SWITCH_SYSTEM
#define C_SWITCH_SYSTEM
#endif
#ifndef C_SWITCH_MACHINE
#define C_SWITCH_MACHINE
#endif
configure___ libsrc_libs=LIBS_MACHINE LIBS_SYSTEM
configure___ c_switch_system=C_SWITCH_SYSTEM
configure___ c_switch_machine=C_SWITCH_MACHINE

#ifndef LIB_X11_LIB
#define LIB_X11_LIB -lX11
#endif

#ifndef LIBX11_MACHINE
#define LIBX11_MACHINE
#endif

#ifndef LIBX11_SYSTEM
#define LIBX11_SYSTEM
#endif
configure___ LIBX=LIB_X11_LIB LIBX11_MACHINE LIBX11_SYSTEM

#ifdef UNEXEC
configure___ unexec=UNEXEC
#else
configure___ unexec=unexec.o
#endif

#ifdef SYSTEM_MALLOC
configure___ system_malloc=yes
#else
configure___ system_malloc=no
#endif

#ifdef USE_MMAP_FOR_BUFFERS
configure___ use_mmap_for_buffers=yes
#else
configure___ use_mmap_for_buffers=no
#endif

#ifndef C_DEBUG_SWITCH
#defåa
