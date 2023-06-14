#include <stdio.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

#include "afniheaders.h"

static PyObject *afnidespike_despike_c(const PyObject *self, PyObject *args)
{
    PyObject *arg_timeseries = NULL;
    int arg_mode = NULL;

    if (!PyArg_ParseTuple(args, "O!i",
                          &PyArray_Type, &arg_timeseries,
                          &arg_mode))
    {
        return NULL;
    }

    PyObject *timeseries_array;
#if NPY_API_VERSION >= 0x0000000c
    timeseries_array = PyArray_FROM_OTF(arg_timeseries, NPY_FLOAT, NPY_ARRAY_INOUT_ARRAY2);
#else
    timeseries_array = PyArray_FROM_OTF(arg_timeseries, NPY_FLOAT, NPY_ARRAY_INOUT_ARRAY);
#endif

    if (timeseries_array == NULL) goto fail;

    int num_spikes;
    if (arg_mode == 0)
    {
        num_spikes = DES_despike9(
            (int)PyArray_SIZE(timeseries_array),
            (float *)PyArray_DATA(timeseries_array),
            NULL);
    }
    else
    {
        num_spikes = DES_despike25(
            (int)PyArray_SIZE(timeseries_array),
            (float *)PyArray_DATA(timeseries_array),
            NULL);
    }

#if NPY_API_VERSION >= 0x0000000c
    PyArray_ResolveWritebackIfCopy(timeseries_array);
#endif
    Py_DECREF(timeseries_array);

    PyObject *re = Py_BuildValue("i", num_spikes);

    return re;

 fail:
#if NPY_API_VERSION >= 0x0000000c
    PyArray_DiscardWritebackIfCopy(timeseries_array );
#endif
    Py_XDECREF(timeseries_array);
    return NULL;
}

static PyMethodDef afnidespike_methods[] = {
    {
        "despike",
        afnidespike_despike_c,
        METH_VARARGS,
        "Despike a time-series.",
    },
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef afnidespike_definition = {
    PyModuleDef_HEAD_INIT,
    "afnidespike",
    "Wrapper for AFNI despike.",
    -1,
    afnidespike_methods};

PyMODINIT_FUNC PyInit_afnidespike(void)
{
    Py_Initialize();
    import_array();
    return PyModule_Create(&afnidespike_definition);
}