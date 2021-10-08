#include "jfloat.hpp"

static PyObject* jfloat_desc(jfloatObject *self) {
    const char *result = PyOS_double_to_string(jfloat_Val(self), 'g', 6, 
                        Py_DTSF_ADD_DOT_0, NULL);
    return PyUnicode_FromString(result);
}

static bool convert_to_jfloat(PyObject *obj, jfloat *val) {
    if (jfloat_Check(obj)) {
        *val = jfloat_Val(obj);
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
static jfloatObject* jfloat_add(PyObject *self, PyObject *other) {
    jfloat a, b;
    if (convert_to_jfloat(self, &a) && convert_to_jfloat(other, &b))
        return jfloat_FromValue(a + b);
    return (jfloatObject*)Py_NotImplemented;
}
static jfloatObject* jfloat_sub(PyObject *self, PyObject *other) {
    jfloat a, b;
    if (convert_to_jfloat(self, &a) && convert_to_jfloat(other, &b))
        return jfloat_FromValue(a - b);
    return (jfloatObject*)Py_NotImplemented;
}
static jfloatObject* jfloat_mul(PyObject *self, PyObject *other) {
    jfloat a, b;
    if (convert_to_jfloat(self, &a) && convert_to_jfloat(other, &b))
        return jfloat_FromValue(a * b);
    return (jfloatObject*)Py_NotImplemented;
}
static jfloatObject* jfloat_pow(PyObject *base, PyObject *exp, PyObject *mod) {
    jfloat a, b;
    jfloatObject *result;
    if (mod != Py_None) {
        PyErr_SetString(PyExc_TypeError, "pow() 3rd argument not "
            "allowed unless all arguments are integers");
        return NULL;
    }
    if (convert_to_jfloat(base, &a) && convert_to_jfloat(exp, &b))
        return jfloat_FromValue(pow(a, b));
    INC_RETURN_NOTIMPLEMENTED(jfloatObject*);
}
static jfloatObject* jfloat_neg(jfloatObject* self) {
    return jfloat_FromValue(-jfloat_Val(self));
}
static jfloatObject* jfloat_abs(jfloatObject* self) {
    jfloat value = jfloat_Val(self);
    if (value > 0)
        INC_RETURN(self);
    else
        return jfloat_FromValue(-jfloat_Val(self));
} 
static bool jfloat_bool(jfloatObject *self) {
    return jfloat_Val(self);
}
static PyObject* jfloat_long(jfloatObject *self) {
    return PyLong_FromLong(jfloat_Val(self));
}
static PyObject* jfloat_float(jfloatObject *self) {
    return PyFloat_FromDouble(jfloat_Val(self));
}
static jfloatObject* jfloat_div(PyObject *self, PyObject *other) {
    jfloat a, b;
    if (convert_to_jfloat(self, &a) && convert_to_jfloat(other, &b)) {
        if (b == 0.0) {
            PyErr_SetString(PyExc_ZeroDivisionError, "float division by zero");
            return NULL;
        }
        return jfloat_FromValue(a / b);
    }
    INC_RETURN_NOTIMPLEMENTED(jfloatObject*);
}

static PyObject* jfloat_richcompare(jfloatObject* self, PyObject *other, int op) {
    jfloat a, b;
    if (convert_to_jfloat(self, &a) && convert_to_jfloat(other, &b))
        Py_RETURN_RICHCOMPARE(a, b, op);
    INC_RETURN_NOTIMPLEMENTED(jfloatObject*);
}
static jfloatObject* jfloat_alloc(PyTypeObject* type, Py_ssize_t nitems) {
    jfloatObject *obj = (jfloatObject*)PyType_GenericAlloc(type, nitems);
    for (Py_ssize_t i=0; i<nitems+1; i++) {
        obj[i].desc = (descfunc)jfloat_desc;
    }
    return obj;
}
static jfloatObject* jfloat_jfloat(PyObject* x) {
    jfloatObject *result = NULL;
    if (jfloat_Check(x)) {
        Py_INCREF(x);
        result = (jfloatObject*)x;
    } else if (PyNumber_Check(x)) {
        PyObject *number = PyNumber_Float(x);
        if (number != NULL) {
            result = jfloat_FromValue(PyFloat_AsDouble(number));
            Py_DECREF(number);
        }
    } else {
        _BadArgument("jfloat", "argument", "number", x);
    }
    return result;
}
static jfloatObject* jfloat_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x = NULL;
    if (!PyArg_UnpackTuple(args, "jfloat", 0, 1, &x))
        return NULL;
    if (x == NULL)
        return jfloat_FromValue(0);
    return jfloat_jfloat(x);
}

static PyNumberMethods jfloat_as_number = {
    .nb_add = (binaryfunc)jfloat_add,
    .nb_subtract = (binaryfunc)jfloat_sub,
    .nb_multiply = (binaryfunc)jfloat_mul,
    .nb_power = (ternaryfunc)jfloat_pow,
    .nb_negative = (unaryfunc)jfloat_neg,
    .nb_positive = (unaryfunc)jfloat_jfloat,
    .nb_absolute = (unaryfunc)jfloat_abs,
    .nb_bool = (inquiry)jfloat_bool,
    .nb_int = (unaryfunc)jfloat_long,
    .nb_float = (unaryfunc)jfloat_float,
    .nb_floor_divide = (binaryfunc)jfloat_div,
    .nb_true_divide = (binaryfunc)jfloat_div,
};

PyTypeObject jfloat_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jflaot",
    .tp_as_number = &jfloat_as_number,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "jfloat type",
    .tp_richcompare = (richcmpfunc)jfloat_richcompare,
    .tp_base = &jvalue_Type,
    .tp_alloc = (allocfunc)jfloat_alloc,
    .tp_new = (newfunc)jfloat_new,
};

jfloatObject* jfloat_FromValue(jfloat value) {
    PyTypeObject *type = &jfloat_Type;
    jfloatObject *self = (jfloatObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jfloat_Val(self) = value;
    return self;
}