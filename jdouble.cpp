#include "jdouble.hpp"

static PyObject* jdouble_desc(jdoubleObject *self) {
    const char *result = PyOS_double_to_string(jdouble_Val(self), 'g', 6, 
                        Py_DTSF_ADD_DOT_0, NULL);
    return PyUnicode_FromString(result);
}

static bool convert_to_jdouble(PyObject *obj, jdouble *val) {
    if (jdouble_Check(obj)) {
        *val = jdouble_Val(obj);
    } else if (PyNumber_Check(obj)) {
        PyObject *number = PyNumber_Float(obj);
        if (number == NULL)
            return false;
        *val = PyFloat_AsDouble(number);
        Py_DECREF(number);
    } else {
        return false;
    }
    return true;
}
static jdoubleObject* jdouble_add(PyObject *self, PyObject *other) {
    jdouble a, b;
    if (convert_to_jdouble(self, &a) && convert_to_jdouble(other, &b))
        return jdouble_FromValue(a + b);
    return (jdoubleObject*)Py_NotImplemented;
}
static jdoubleObject* jdouble_sub(PyObject *self, PyObject *other) {
    jdouble a, b;
    if (convert_to_jdouble(self, &a) && convert_to_jdouble(other, &b))
        return jdouble_FromValue(a - b);
    return (jdoubleObject*)Py_NotImplemented;
}
static jdoubleObject* jdouble_mul(PyObject *self, PyObject *other) {
    jdouble a, b;
    if (convert_to_jdouble(self, &a) && convert_to_jdouble(other, &b))
        return jdouble_FromValue(a * b);
    return (jdoubleObject*)Py_NotImplemented;
}
static jdoubleObject* jdouble_pow(PyObject *base, PyObject *exp, PyObject *mod) {
    jdouble a, b;
    jdoubleObject *result;
    if (mod != Py_None) {
        PyErr_SetString(PyExc_TypeError, "pow() 3rd argument not "
            "allowed unless all arguments are integers");
        return NULL;
    }
    if (convert_to_jdouble(base, &a) && convert_to_jdouble(exp, &b))
        return jdouble_FromValue(pow(a, b));
    INC_RETURN_NOTIMPLEMENTED(jdoubleObject*);
}
static jdoubleObject* jdouble_neg(jdoubleObject* self) {
    return jdouble_FromValue(-jdouble_Val(self));
}
static jdoubleObject* jdouble_abs(jdoubleObject* self) {
    jdouble value = jdouble_Val(self);
    if (value > 0)
        INC_RETURN(self);
    else
        return jdouble_FromValue(-jdouble_Val(self));
} 
static bool jdouble_bool(jdoubleObject *self) {
    return jdouble_Val(self);
}
static PyObject* jdouble_long(jdoubleObject *self) {
    return PyLong_FromLong(jdouble_Val(self));
}
static PyObject* jdouble_float(jdoubleObject *self) {
    return PyFloat_FromDouble(jdouble_Val(self));
}
static jdoubleObject* jdouble_div(PyObject *self, PyObject *other) {
    jdouble a, b;
    if (convert_to_jdouble(self, &a) && convert_to_jdouble(other, &b)) {
        if (b == 0.0) {
            PyErr_SetString(PyExc_ZeroDivisionError, "float division by zero");
            return NULL;
        }
        return jdouble_FromValue(a / b);
    }
    INC_RETURN_NOTIMPLEMENTED(jdoubleObject*);
}

static PyObject* jdouble_richcompare(jdoubleObject* self, PyObject *other, int op) {
    jdouble a, b;
    if (convert_to_jdouble(self, &a) && convert_to_jdouble(other, &b))
        Py_RETURN_RICHCOMPARE(a, b, op);
    INC_RETURN_NOTIMPLEMENTED(jdoubleObject*);
}
static jdoubleObject* jdouble_alloc(PyTypeObject* type, Py_ssize_t nitems) {
    jdoubleObject *obj = (jdoubleObject*)PyType_GenericAlloc(type, nitems);
    for (Py_ssize_t i=0; i<nitems+1; i++) {
        obj[i].desc = (descfunc)jdouble_desc;
    }
    return obj;
}
static jdoubleObject* jdouble_jdouble(PyObject* x) {
    jdoubleObject *result = NULL;
    if (jdouble_Check(x)) {
        Py_INCREF(x);
        result = (jdoubleObject*)x;
    } else if (PyNumber_Check(x)) {
        PyObject *number = PyNumber_Float(x);
        if (number != NULL) {
            result = jdouble_FromValue(PyFloat_AsDouble(number));
            Py_DECREF(number);
        }
    } else {
        _BadArgument("jdouble", "argument", "number", x);
    }
    return result;
}
static jdoubleObject* jdouble_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x = NULL;
    if (!PyArg_UnpackTuple(args, "jdouble", 0, 1, &x))
        return NULL;
    if (x == NULL)
        return jdouble_FromValue(0);
    return jdouble_jdouble(x);
}

static PyNumberMethods jdouble_as_number = {
    .nb_add = (binaryfunc)jdouble_add,
    .nb_subtract = (binaryfunc)jdouble_sub,
    .nb_multiply = (binaryfunc)jdouble_mul,
    .nb_power = (ternaryfunc)jdouble_pow,
    .nb_negative = (unaryfunc)jdouble_neg,
    .nb_positive = (unaryfunc)jdouble_jdouble,
    .nb_absolute = (unaryfunc)jdouble_abs,
    .nb_bool = (inquiry)jdouble_bool,
    .nb_int = (unaryfunc)jdouble_long,
    .nb_float = (unaryfunc)jdouble_float,
    .nb_floor_divide = (binaryfunc)jdouble_div,
    .nb_true_divide = (binaryfunc)jdouble_div,
};

PyTypeObject jdouble_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jflaot",
    .tp_as_number = &jdouble_as_number,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "jdouble type",
    .tp_richcompare = (richcmpfunc)jdouble_richcompare,
    .tp_base = &jvalue_Type,
    .tp_alloc = (allocfunc)jdouble_alloc,
    .tp_new = (newfunc)jdouble_new,
};

jdoubleObject* jdouble_FromValue(jdouble value) {
    PyTypeObject *type = &jdouble_Type;
    jdoubleObject *self = (jdoubleObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jdouble_Val(self) = value;
    return self;
}