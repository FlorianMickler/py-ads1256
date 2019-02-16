#include <Python.h>
#include "wrapper.h"
#include "logging.h"

/* Docstrings */
//static char module_docstring[] =
//    "Esta biblioteca é um wrapper ";

/* Available functions */
static PyObject *adc_read_channel(PyObject *self, PyObject *args);
static PyObject *adc_read_all_channels(PyObject *self, PyObject *args);
static PyObject *adc_start(PyObject *self, PyObject *args);
static PyObject *adc_stop(PyObject *self, PyObject *args);
static PyObject *adc_test(PyObject *self, PyObject *args);

/* Module specification */
static PyMethodDef module_methods[] = {
 //   {"chi2", chi2_chi2, METH_VARARGS, chi2_docstring},
    {"read_channel", adc_read_channel, METH_VARARGS, "Read a channel"},
    {"read_all_channels", adc_read_all_channels, METH_VARARGS, "Read all channels"},
    {"start", adc_start, METH_VARARGS, "Start ads1256 acquisition"},
    {"stop", adc_stop, 0, "Stop ads1256"},
	{"test", adc_test, 0, ""},
    {NULL, NULL, 0, NULL}
};

/* Initialize the module */
DL_EXPORT(void) initads1256(void)
{
    Py_InitModule("ads1256", module_methods);
}

static PyObject *adc_start(PyObject *self, PyObject *args)
{
    char *gain, *rate;
    int value;

    /* Parse the input tuple */
    if (!PyArg_ParseTuple(args, "ss", &gain, &rate))
        return NULL;
	
    /* execute the code */ 
    value = adcStart(4,"0", gain, rate);

    /* Build the output tuple */
    PyObject *ret = Py_BuildValue("i",value);
    return ret;
}

static PyObject *adc_read_channel(PyObject *self, PyObject *args)
{

    int ch;
    long int retorno;
    PyObject *yerr_obj;
    


    /* Parse the input tuple */
    if (!PyArg_ParseTuple(args, "i", &ch,&yerr_obj))
        return NULL;
                                       

    /* execute the code */ 
    retorno = readChannel(ch);
    return Py_BuildValue("l",retorno);
}


static PyObject *adc_read_all_channels(PyObject *self, PyObject *args)
{
    //PyObject *yerr_obj;
    long int v[8];
                                         

    /* execute the code */ 
    readChannels(v);

    /* Build the output tuple */
    PyObject *ret = Py_BuildValue("[l,l,l,l,l,l,l,l]",
	 v[0],
	 v[1],
	 v[2],
	 v[3],
	 v[4],
	 v[5],
	 v[6],
	 v[7]
     );
    return ret;
}

static PyObject *adc_stop(PyObject *self, PyObject *args)
{
    /* execute the code */ 
    int value = adcStop();

    /* Build the output tuple */
    PyObject *ret = Py_BuildValue("i",value);
    return ret;
}

static PyObject *adc_test(PyObject *self, PyObject *args)
{
	lib_log("TEST");
	return NULL;
}

