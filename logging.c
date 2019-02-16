#include <Python.h>
#include <stdio.h>
#include <stdarg.h>
#include "logging.h"

/***********************************************************/
/* define logging function and logtypes for python.logging */
/* by H.Dickten 2014                                       */
/***********************************************************/

void lib_log(char *fmt, ...)
{
	static char buf[256];//Internal string buffer
    static PyObject *logging = NULL;
    static PyObject *string = NULL;

    // import logging module on demand
    if (logging == NULL){
        logging = PyImport_ImportModuleNoBlock("logging");
        if (logging == NULL)
            PyErr_SetString(PyExc_ImportError,
                "Could not import module 'logging'");
    }

	va_list args;
    va_start(args, fmt);
	vsprintf(buf,fmt, args);
	va_end(args);

    // build msg-string
    string = Py_BuildValue("s", buf);

	PyObject_CallMethod(logging, "error", "O", string);

    //// call function depending on loglevel
    //switch (type)
    //{
    //    case info:
    //        PyObject_CallMethod(logging, "info", "O", string);
    //        break;
    //
    //    case warning:
    //        PyObject_CallMethod(logging, "warn", "O", string);
    //        break;
    //
    //    case error:
    //        PyObject_CallMethod(logging, "error", "O", string);
    //        break;
    //
    //    case debug:
    //        PyObject_CallMethod(logging, "debug", "O", string);
    //        break;
    //}
    Py_DECREF(string);
}