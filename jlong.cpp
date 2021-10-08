#include "jlong.hpp"

static PyObject* jlong_desc(jlongObject *self) {
    return PyLong_FromLong(jlong_Val(self));
}

static bool convert_to_jlong(PyObject *obj, jlong *val) {
    if (jlong_Check(obj)) {
        *val = jlong_Val(obj);
    } else if (PyLong_Check(obj)) {
        *val = PyLong_AsLong(obj);
    } else {
        return false;
    }
    return true;
}
static jlongObject* jlong_add(PyObject *self, PyObject *other) {
    jlong a, b;
    if (convert_to_jlong(self, &a) && convert_to_jlong(other, &b))
        return jlong_FromValue(a + b);
    return (jlongObject*)Py_NotImplemented;
}
static jlongObject* jlong_sub(PyObject *self, PyObject *other) {
    jlong a, b;
    if (convert_to_jlong(self, &a) && convert_to_jlong(other, &b))
        return jlong_FromValue(a - b);
    return (jlongObject*)Py_NotImplemented;
}
static jlongObject* jlong_mul(PyObject *self, PyObject *other) {
    jlong a, b;
    if (convert_to_jlong(self, &a) && convert_to_jlong(other, &b))
        return jlong_FromValue(a * b);
    return (jlongObject*)Py_NotImplemented;
}
static jlongObject* jlong_mod(PyObject *self, PyObject *other) {
    jlong a, b;
    if (convert_to_jlong(self, &a) && convert_to_jlong(other, &b))
        return jlong_FromValue(a % b);
    INC_RETURN_NOTIMPLEMENTED(jlongObject*);
}
static PyObject* jlong_divmod(PyObject *self, PyObject *other) {
    PyObject *result = PyTuple_New(2);
    jlongObject *div, *mod;
    if (result) {
        jlong a, b;
        if (!convert_to_jlong(self, &a) || !convert_to_jlong(other, &b)) {
            Py_DECREF(result);
            Py_INCREF(Py_NotImplemented);
            return Py_NotImplemented;
        }
        div = jlong_FromValue(a / b);
        mod = jlong_FromValue(a % b);
        PyTuple_SetItem(result, 0, div);
        PyTuple_SetItem(result, 1, mod);
    }
    return result;
}
static jlongObject* jlong_pow(PyObject *base, PyObject *exp, PyObject *mod) {
    jlong a, b, c;
    jlongObject *result;
    if (mod == Py_None) {
        if (convert_to_jlong(base, &a) && convert_to_jlong(exp, &b))
            return jlong_FromValue(pow(a, b));
    } else {
        if (convert_to_jlong(base, &a) && convert_to_jlong(exp, &b), convert_to_jlong(mod, &c))
            return jlong_FromValue((jlong)pow(a, b) % c);
    }
    INC_RETURN_NOTIMPLEMENTED(jlongObject*);
}
static jlongObject* jlong_neg(jlongObject* self) {
    return jlong_FromValue(-jlong_Val(self));
}
static jlongObject* jlong_abs(jlongObject* self) {
    jlong value = jlong_Val(self);
    if (value > 0)
        INC_RETURN(self);
    else
        return jlong_FromValue(-jlong_Val(self));
}
static bool jlong_bool(jlongObject *self) {
    return jlong_Val(self);
}
static jlongObject* jlong_invert(jlongObject *self) {
    return jlong_FromValue(~jlong_Val(self));
}
static jlongObject* jlong_lshift(PyObject *self, PyObject *other) {
    jlong a, b;
    if (convert_to_jlong(self, &a) && convert_to_jlong(other, &b))
        return jlong_FromValue(a << b);
    INC_RETURN_NOTIMPLEMENTED(jlongObject*);
}
static jlongObject* jlong_rshift(PyObject *self, PyObject *other) {
    jlong a, b;
    if (convert_to_jlong(self, &a) && convert_to_jlong(other, &b))
        return jlong_FromValue(a >> b);
    INC_RETURN_NOTIMPLEMENTED(jlongObject*);
}
static jlongObject* jlong_and(PyObject *self, PyObject *other) {
    jlong a, b;
    if (convert_to_jlong(self, &a) && convert_to_jlong(other, &b))
        return jlong_FromValue(a & b);
    INC_RETURN_NOTIMPLEMENTED(jlongObject*);
}
static jlongObject* jlong_xor(PyObject *self, PyObject *other) {
    jlong a, b;
    if (convert_to_jlong(self, &a) && convert_to_jlong(other, &b))
        return jlong_FromValue(a ^ b);
    INC_RETURN_NOTIMPLEMENTED(jlongObject*);
}
static jlongObject* jlong_or(PyObject *self, PyObject *other) {
    jlong a, b;
    if (convert_to_jlong(self, &a) && convert_to_jlong(other, &b))
        return jlong_FromValue(a | b);
    INC_RETURN_NOTIMPLEMENTED(jlongObject*);
}
static PyObject* jlong_long(jlongObject *self) {
    return PyLong_FromLong(jlong_Val(self));
}
static PyObject* jlong_float(jlongObject *self) {
    return PyFloat_FromDouble(jlong_Val(self));
}
static jlongObject* jlong_div(PyObject *self, PyObject *other) {
    jlong a, b;
    if (convert_to_jlong(self, &a) && convert_to_jlong(other, &b))
        return jlong_FromValue(a / b);
    INC_RETURN_NOTIMPLEMENTED(jlongObject*);
}

static PyObject* jlong_richcompare(jlongObject* self, PyObject *other, int op) {
    jlong a, b;
    if (convert_to_jlong(self, &a) && convert_to_jlong(other, &b))
        Py_RETURN_RICHCOMPARE(a, b, op);
    INC_RETURN_NOTIMPLEMENTED(jlongObject*);
}
static jlongObject* jlong_alloc(PyTypeObject *type, Py_ssize_t nitems) {
    jlongObject *obj = (jlongObject*)PyType_GenericAlloc(type, nitems);
    for (Py_ssize_t i=0; i<nitems+1; i++)
        obj[i].desc = (descfunc)jlong_desc;
    return obj;
}
static jlongObject* jlong_jlong(PyObject *x) {
    jlongObject *result = NULL;
    if (jlong_Check(x)) {
        Py_INCREF(x);
        result = (jlongObject*)x;
    } else if (PyNumber_Check(x)) {
        PyObject *number = PyNumber_Long(x);
        if (number != NULL) {
            result = jlong_FromValue(PyLong_AsLong(number));
            Py_DECREF(number);
        }
    } else {
        _BadArgument("jlong", "argument", "number", x);
    }
    return result;
}
static jlongObject* jlong_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x = NULL;
    if (!PyArg_UnpackTuple(args, "jlong", 0, 1, &x))
        return NULL;
    if (x == NULL)
        return jlong_FromValue(0);
    return jlong_jlong(x);
}

static PyNumberMethods jlong_as_number = {
    .nb_add = (binaryfunc)jlong_add,
    .nb_subtract = (binaryfunc)jlong_sub,
    .nb_multiply = (binaryfunc)jlong_mul,
    .nb_remainder = (binaryfunc)jlong_mod,
    .nb_divmod = (binaryfunc)jlong_divmod,
    .nb_power = (ternaryfunc)jlong_pow,
    .nb_negative = (unaryfunc)jlong_neg,
    .nb_positive = (unaryfunc)jlong_jlong,
    .nb_absolute = (unaryfunc)jlong_abs,
    .nb_bool = (inquiry)jlong_bool,
    .nb_invert = (unaryfunc)jlong_invert,
    .nb_lshift = (binaryfunc)jlong_lshift,
    .nb_rshift = (binaryfunc)jlong_rshift,
    .nb_and = (binaryfunc)jlong_and,
    .nb_xor = (binaryfunc)jlong_xor,
    .nb_or = (binaryfunc)jlong_or,
    .nb_int = (unaryfunc)jlong_long,
    .nb_float = (unaryfunc)jlong_float,
    .nb_floor_divide = (binaryfunc)jlong_div,
    .nb_true_divide = (binaryfunc)jlong_div,
    .nb_index = (unaryfunc)jlong_long,
};

PyTypeObject jlong_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jlong",
    .tp_as_number = &jlong_as_number,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "jlong type",
    .tp_richcompare = (richcmpfunc)jlong_richcompare,
    .tp_base = &jvalue_Type,
    .tp_alloc = (allocfunc)jlong_alloc,
    .tp_new = (newfunc)jlong_new,
};


jlongObject* jlong_FromValue(jlong value) {
    PyTypeObject *type = &jlong_Type;
    jlongObject *self = (jlongObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jlong_Val(self) = value;
    return self;
}