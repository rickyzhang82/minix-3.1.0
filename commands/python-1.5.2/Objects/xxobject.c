/***********************************************************
Copyright 1991-1995 by Stichting Mathematisch Centrum, Amsterdam,
The Netherlands.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the names of Stichting Mathematisch
Centrum or CWI or Corporation for National Research Initiatives or
CNRI not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

While CWI is the initial source for this software, a modified version
is made available by the Corporation for National Research Initiatives
(CNRI) at the Internet address ftp://ftp.python.org.

STICHTING MATHEMATISCH CENTRUM AND CNRI DISCLAIM ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL STICHTING MATHEMATISCH
CENTRUM OR CNRI BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.

******************************************************************/

/* Use this file as a template to start implementing a new object type.
   If your objects will be called foobar, start by copying this file to
   foobarobject.c, changing all occurrences of xx to foobar and all
   occurrences of Xx by Foobar.  You will probably want to delete all
   references to 'x_attr' and add your own types of attributes
   instead.  Maybe you want to name your local variables other than
   'xp'.  If your object type is needed in other files, you'll have to
   create a file "foobarobject.h"; see intobject.h for an example. */


/* Xx objects */

#include "Python.h"

typedef struct {
	PyObject_HEAD
	PyObject	*x_attr;	/* Attributes dictionary */
} xxobject;

staticforward PyTypeObject Xxtype;

#define is_xxobject(v)		((v)->ob_type == &Xxtype)

static xxobject *
newxxobject(arg)
	PyObject *arg;
{
	xxobject *xp;
	xp = PyObject_NEW(xxobject, &Xxtype);
	if (xp == NULL)
		return NULL;
	xp->x_attr = NULL;
	return xp;
}

/* Xx methods */

static void
xx_dealloc(xp)
	xxobject *xp;
{
	Py_XDECREF(xp->x_attr);
	PyMem_DEL(xp);
}

static PyObject *
xx_demo(self, args)
	xxobject *self;
	PyObject *args;
{
	if (!PyArg_NoArgs(args))
		return NULL;
	Py_INCREF(Py_None);
	return Py_None;
}

static PyMethodDef xx_methods[] = {
	{"demo",	(PyCFunction)xx_demo},
	{NULL,		NULL}		/* sentinel */
};

static PyObject *
xx_getattr(xp, name)
	xxobject *xp;
	char *name;
{
	if (xp->x_attr != NULL) {
		PyObject *v = PyDict_GetItemString(xp->x_attr, name);
		if (v != NULL) {
			Py_INCREF(v);
			return v;
		}
	}
	return Py_FindMethod(xx_methods, (PyObject *)xp, name);
}

static int
xx_setattr(xp, name, v)
	xxobject *xp;
	char *name;
	PyObject *v;
{
	if (xp->x_attr == NULL) {
		xp->x_attr = PyDict_New();
		if (xp->x_attr == NULL)
			return -1;
	}
	if (v == NULL) {
		int rv = PyDict_DelItemString(xp->x_attr, name);
		if (rv < 0)
			PyErr_SetString(PyExc_AttributeError,
			        "delete non-existing xx attribute");
		return rv;
	}
	else
		return PyDict_SetItemString(xp->x_attr, name, v);
}

static PyTypeObject Xxtype = {
	PyObject_HEAD_INIT(&PyType_Type)
	0,			/*ob_size*/
	"xx",			/*tp_name*/
	sizeof(xxobject),	/*tp_basicsize*/
	0,			/*tp_itemsize*/
	/* methods */
	(destructor)xx_dealloc, /*tp_dealloc*/
	0,			/*tp_print*/
	(getattrfunc)xx_getattr, /*tp_getattr*/
	(setattrfunc)xx_setattr, /*tp_setattr*/
	0,			/*tp_compare*/
	0,			/*tp_repr*/
	0,			/*tp_as_number*/
	0,			/*tp_as_sequence*/
	0,			/*tp_as_mapping*/
	0,			/*tp_hash*/
};
