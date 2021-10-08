#include "jshort.hpp"

static PyObject* jshort_desc(jshortObject *self) {
    return PyLong_FromLong(jshort_Val(self));
}

static bool convert_to_jshort(PyObject *obj, jshort *val) {
    if (jshort_Check(obj)) {
        *val = jshort_Val(obj);
    } else if (PyLong_Check(obj)) {
        *val = PyLong_AsLong(obj);
    } else {
        return false;
    }
    return true;
}
static jshortObject* jshort_add(PyObject *self, PyObject *other) {
    jshort a, b;
    if (convert_to_jshort(self, &a) && convert_to_jshort(other, &b))
        return jshort_FromValue(a + b);
    return (jshortObject*)Py_NotImplemented;
}
static jshortObject* jshort_sub(PyObject *self, PyObject *other) {
    jshort a, b;
    if (convert_to_jshort(self, &a) && convert_to_jshort(other, &b))
        return jshort_FromValue(a - b);
    return (jshortObject*)Py_NotImplemented;
}
static jshortObject* jshort_mul(PyObject *self, PyObject *other) {
    jshort a, b;
    if (convert_to_jshort(self, &a) && convert_to_jshort(other, &b))
        return jshort_FromValue(a * b);
    return (jshortObject*)Py_NotImplemented;
}
static jshortObject* jshort_mod(PyObject *self, PyObject *other) {
    jshort a, b;
    if (convert_to_jshort(self, &a) && convert_to_jshort(other, &b))
        return jshort_FromValue(a % b);
    INC_RETURN_NOTIMPLEMENTED(jshortObject*);
}
static PyObject* jshort_divmod(PyObject *self, PyObject *other) {
    PyObject *result = PyTuple_New(2);
    jshortObject *div, *mod;
    if (result) {
        jshort a, b;
        if (!convert_to_jshort(self, &a) || !convert_to_jshort(other, &b)) {
            Py_DECREF(result);
            Py_INCREF(Py_NotImplemented);
            return Py_NotImplemented;
        }
        div = jshort_FromValue(a / b);
        mod = jshort_FromValue(a % b);
        PyTuple_SetItem(result, 0, div);
        PyTuple_SetItem(result, 1, mod);
    }
    return result;
}
static jshortObject* jshort_pow(PyObject *base, PyObject *exp, PyObject *mod) {
    jshort a, b, c;
    jshortObject *result;
    if (mod == Py_None) {
        if (convert_to_jshort(base, &a) && convert_to_jshort(exp, &b))
            return jshort_FromValue(pow(a, b));
    } else {
        if (convert_to_jshort(base, &a) && convert_to_jshort(exp, &b), convert_to_jshort(mod, &c))
            return jshort_FromValue((jshort)pow(a, b) % c);
    }
    INC_RETURN_NOTIMPLEMENTED(jshortObject*);
}
static jshortObject* jshort_neg(jshortObject* self) {
    return jshort_FromValue(-jshort_Val(self));
}
static jshortObject* jshort_abs(jshortObject* self) {
    jshort value = jshort_Val(self);
    if (value > 0)
        INC_RETURN(self);
    else
        return jshort_FromValue(-jshort_Val(self));
}
static bool jshort_bool(jshortObject *self) {
    return jshort_Val(self);
}
static jshortObject* jshort_invert(jshortObject *self) {
    return jshort_FromValue(~jshort_Val(self));
}
static jshortObject* jshort_lshift(PyObject *self, PyObject *other) {
    jshort a, b;
    if (convert_to_jshort(self, &a) && convert_to_jshort(other, &b))
        return jshort_FromValue(a << b);
    INC_RETURN_NOTIMPLEMENTED(jshortObject*);
}
static jshortObject* jshort_rshift(PyObject *self, PyObject *other) {
    jshort a, b;
    if (convert_to_jshort(self, &a) && convert_to_jshort(other, &b))
        return jshort_FromValue(a >> b);
    INC_RETURN_NOTIMPLEMENTED(jshortObject*);
}
static jshortObject* jshort_and(PyObject *self, PyObject *other) {
    jshort a, b;
    if (convert_to_jshort(self, &a) && convert_to_jshort(other, &b))
        return jshort_FromValue(a & b);
    INC_RETURN_NOTIMPLEMENTED(jshortObject*);
}
static jshortObject* jshort_xor(PyObject *self, PyObject *other) {
    jshort a, b;
    if (convert_to_jshort(self, &a) && convert_to_jshort(other, &b))
        return jshort_FromValue(a ^ b);
    INC_RETURN_NOTIMPLEMENTED(jshortObject*);
}
static jshortObject* jshort_or(PyObject *self, PyObject *other) {
    jshort a, b;
    if (convert_to_jshort(self, &a) && convert_to_jshort(other, &b))
        return jshort_FromValue(a | b);
    INC_RETURN_NOTIMPLEMENTED(jshortObject*);
}
static PyObject* jshort_long(jshortObject *self) {
    return PyLong_FromLong(jshort_Val(self));
}
static PyObject* jshort_float(jshortObject *self) {
    return PyFloat_FromDouble(jshort_Val(self));
}
static jshortObject* jshort_div(PyObject *self, PyObject *other) {
    jshort a, b;
    if (convert_to_jshort(self, &a) && convert_to_jshort(other, &b))
        return jshort_FromValue(a / b);
    INC_RETURN_NOTIMPLEMENTED(jshortObject*);
}

static PyObject* jshort_richcompare(jshortObject* self, PyObject *other, int op) {
    jshort a, b;
    if (convert_to_jshort(self, &a) && convert_to_jshort(other, &b))
        Py_RETURN_RICHCOMPARE(a, b, op);
    INC_RETURN_NOTIMPLEMENTED(jshortObject*);
}
static jshortObject* jshort_alloc(PyTypeObject *type, Py_ssize_t nitems) {
    jshortObject *obj = (jshortObject*)PyType_GenericAlloc(type, nitems);
    for (Py_ssize_t i=0; i<nitems+1; i++)
        obj[i].desc = (descfunc)jshort_desc;
    return obj;
}
static jshortObject* jshort_jshort(PyObject *x) {
    jshortObject *result = NULL;
    if (jshort_Check(x)) {
        Py_INCREF(x);
        result = (jshortObject*)x;
    } else if (PyNumber_Check(x)) {
        PyObject *number = PyNumber_Long(x);
        if (number != NULL) {
            result = jshort_FromValue(PyLong_AsLong(number));
            Py_DECREF(number);
        }
    } else {
        _BadArgument("jshort", "argument", "number", x);
    }
    return result;
}
static jshortObject* jshort_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x = NULL;
    if (!PyArg_UnpackTuple(args, "jshort", 0, 1, &x))
        return NULL;
    if (x == NULL)
        return jshort_FromValue(0);
    return jshort_jshort(x);
}


static PyNumberMethods jshort_as_number = {
    .nb_add = (binaryfunc)jshort_add,
    .nb_subtract = (binaryfunc)jshort_sub,
    .nb_multiply = (binaryfunc)jshort_mul,
    .nb_remainder = (binaryfunc)jshort_mod,
    .nb_divmod = (binaryfunc)jshort_divmod,
    .nb_power = (ternaryfunc)jshort_pow,
    .nb_negative = (unaryfunc)jshort_neg,
    .nb_positive = (unaryfunc)jshort_jshort,
    .nb_absolute = (unaryfunc)jshort_abs,
    .nb_bool = (inquiry)jshort_bool,
    .nb_invert = (unaryfunc)jshort_invert,
    .nb_lshift = (binaryfunc)jshort_lshift,
    .nb_rshift = (binaryfunc)jshort_rshift,
    .nb_and = (binaryfunc)jshort_and,
    .nb_xor = (binaryfunc)jshort_xor,
    .nb_or = (binaryfunc)jshort_or,
    .nb_int = (unaryfunc)jshort_long,
    .nb_float = (unaryfunc)jshort_float,
    .nb_floor_divide = (binaryfunc)jshort_div,
    .nb_true_divide = (binaryfunc)jshort_div,
    .nb_index = (unaryfunc)jshort_long,
};


PyTypeObject jshort_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jshort",
    .tp_as_number = &jshort_as_number,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "jshort type",
    .tp_richcompare = (richcmpfunc)jshort_richcompare,
    .tp_base = &jvalue_Type,
    .tp_alloc = (allocfunc)jshort_alloc,
    .tp_new = (newfunc)jshort_new,
};


jshortObject* jshort_FromValue(jshort value) {
    PyTypeObject *type = &jshort_Type;
    jshortObject *self = (jshortObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jshort_Val(self) = value;
    return self;
}