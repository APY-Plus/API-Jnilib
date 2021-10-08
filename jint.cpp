#include "jint.hpp"

static PyObject* jint_desc(jintObject *self) {
    return PyLong_FromLong(jint_Val(self));
}

static bool convert_to_jint(PyObject *obj, jint *val) {
    if (jint_Check(obj)) {
        *val = jint_Val(obj);
    } else if (PyLong_Check(obj)) {
        *val = PyLong_AsLong(obj);
    } else {
        return false;
    }
    return true;
}
static jintObject* jint_add(PyObject *self, PyObject *other) {
    jint a, b;
    if (convert_to_jint(self, &a) && convert_to_jint(other, &b))
        return jint_FromValue(a + b);
    return (jintObject*)Py_NotImplemented;
}
static jintObject* jint_sub(PyObject *self, PyObject *other) {
    jint a, b;
    if (convert_to_jint(self, &a) && convert_to_jint(other, &b))
        return jint_FromValue(a - b);
    return (jintObject*)Py_NotImplemented;
}
static jintObject* jint_mul(PyObject *self, PyObject *other) {
    jint a, b;
    if (convert_to_jint(self, &a) && convert_to_jint(other, &b))
        return jint_FromValue(a * b);
    return (jintObject*)Py_NotImplemented;
}
static jintObject* jint_mod(PyObject *self, PyObject *other) {
    jint a, b;
    if (convert_to_jint(self, &a) && convert_to_jint(other, &b))
        return jint_FromValue(a % b);
    INC_RETURN_NOTIMPLEMENTED(jintObject*);
}
static PyObject* jint_divmod(PyObject *self, PyObject *other) {
    PyObject *result = PyTuple_New(2);
    jintObject *div, *mod;
    if (result) {
        jint a, b;
        if (!convert_to_jint(self, &a) || !convert_to_jint(other, &b)) {
            Py_DECREF(result);
            Py_INCREF(Py_NotImplemented);
            return Py_NotImplemented;
        }
        div = jint_FromValue(a / b);
        mod = jint_FromValue(a % b);
        PyTuple_SetItem(result, 0, div);
        PyTuple_SetItem(result, 1, mod);
    }
    return result;
}
static jintObject* jint_pow(PyObject *base, PyObject *exp, PyObject *mod) {
    jint a, b, c;
    jintObject *result;
    if (mod == Py_None) {
        if (convert_to_jint(base, &a) && convert_to_jint(exp, &b))
            return jint_FromValue(pow(a, b));
    } else {
        if (convert_to_jint(base, &a) && convert_to_jint(exp, &b), convert_to_jint(mod, &c))
            return jint_FromValue((jint)pow(a, b) % c);
    }
    INC_RETURN_NOTIMPLEMENTED(jintObject*);
}
static jintObject* jint_neg(jintObject* self) {
    return jint_FromValue(-jint_Val(self));
}
static jintObject* jint_abs(jintObject* self) {
    jint value = jint_Val(self);
    if (value > 0)
        INC_RETURN(self);
    else
        return jint_FromValue(-jint_Val(self));
}
static bool jint_bool(jintObject *self) {
    return jint_Val(self);
}
static jintObject* jint_invert(jintObject *self) {
    return jint_FromValue(~jint_Val(self));
}
static jintObject* jint_lshift(PyObject *self, PyObject *other) {
    jint a, b;
    if (convert_to_jint(self, &a) && convert_to_jint(other, &b))
        return jint_FromValue(a << b);
    INC_RETURN_NOTIMPLEMENTED(jintObject*);
}
static jintObject* jint_rshift(PyObject *self, PyObject *other) {
    jint a, b;
    if (convert_to_jint(self, &a) && convert_to_jint(other, &b))
        return jint_FromValue(a >> b);
    INC_RETURN_NOTIMPLEMENTED(jintObject*);
}
static jintObject* jint_and(PyObject *self, PyObject *other) {
    jint a, b;
    if (convert_to_jint(self, &a) && convert_to_jint(other, &b))
        return jint_FromValue(a & b);
    INC_RETURN_NOTIMPLEMENTED(jintObject*);
}
static jintObject* jint_xor(PyObject *self, PyObject *other) {
    jint a, b;
    if (convert_to_jint(self, &a) && convert_to_jint(other, &b))
        return jint_FromValue(a ^ b);
    INC_RETURN_NOTIMPLEMENTED(jintObject*);
}
static jintObject* jint_or(PyObject *self, PyObject *other) {
    jint a, b;
    if (convert_to_jint(self, &a) && convert_to_jint(other, &b))
        return jint_FromValue(a | b);
    INC_RETURN_NOTIMPLEMENTED(jintObject*);
}
static PyObject* jint_long(jintObject *self) {
    return PyLong_FromLong(jint_Val(self));
}
static PyObject* jint_float(jintObject *self) {
    return PyFloat_FromDouble(jint_Val(self));
}
static jintObject* jint_div(PyObject *self, PyObject *other) {
    jint a, b;
    if (convert_to_jint(self, &a) && convert_to_jint(other, &b))
        return jint_FromValue(a / b);
    INC_RETURN_NOTIMPLEMENTED(jintObject*);
}

static PyObject* jint_richcompare(jintObject* self, PyObject *other, int op) {
    jint a, b;
    if (convert_to_jint(self, &a) && convert_to_jint(other, &b))
        Py_RETURN_RICHCOMPARE(a, b, op);
    INC_RETURN_NOTIMPLEMENTED(jintObject*);
}
static jintObject* jint_alloc(PyTypeObject *type, Py_ssize_t nitems) {
    jintObject *obj = (jintObject*)PyType_GenericAlloc(type, nitems);
    for (Py_ssize_t i=0; i<nitems+1; i++)
        obj[i].desc = (descfunc)jint_desc;
    return obj;
}
static jintObject* jint_jint(PyObject *x) {
    jintObject *result = NULL;
    if (jint_Check(x)) {
        Py_INCREF(x);
        result = (jintObject*)x;
    } else if (PyNumber_Check(x)) {
        PyObject *number = PyNumber_Long(x);
        if (number != NULL) {
            result = jint_FromValue(PyLong_AsLong(number));
            Py_DECREF(number);
        }
    } else {
        _BadArgument("jint", "argument", "number", x);
    }
    return result;
}
static jintObject* jint_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x = NULL;
    if (!PyArg_UnpackTuple(args, "jint", 0, 1, &x))
        return NULL;
    if (x == NULL)
        return jint_FromValue(0);
    return jint_jint(x);
}


static PyNumberMethods jint_as_number = {
    .nb_add = (binaryfunc)jint_add,
    .nb_subtract = (binaryfunc)jint_sub,
    .nb_multiply = (binaryfunc)jint_mul,
    .nb_remainder = (binaryfunc)jint_mod,
    .nb_divmod = (binaryfunc)jint_divmod,
    .nb_power = (ternaryfunc)jint_pow,
    .nb_negative = (unaryfunc)jint_neg,
    .nb_positive = (unaryfunc)jint_jint,
    .nb_absolute = (unaryfunc)jint_abs,
    .nb_bool = (inquiry)jint_bool,
    .nb_invert = (unaryfunc)jint_invert,
    .nb_lshift = (binaryfunc)jint_lshift,
    .nb_rshift = (binaryfunc)jint_rshift,
    .nb_and = (binaryfunc)jint_and,
    .nb_xor = (binaryfunc)jint_xor,
    .nb_or = (binaryfunc)jint_or,
    .nb_int = (unaryfunc)jint_long,
    .nb_float = (unaryfunc)jint_float,
    .nb_floor_divide = (binaryfunc)jint_div,
    .nb_true_divide = (binaryfunc)jint_div,
    .nb_index = (unaryfunc)jint_long,
};


PyTypeObject jint_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jint",
    .tp_as_number = &jint_as_number,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "jint type",
    .tp_richcompare = (richcmpfunc)jint_richcompare,
    .tp_base = &jvalue_Type,
    .tp_alloc = (allocfunc)jint_alloc,
    .tp_new = (newfunc)jint_new,
};


jintObject* jint_FromValue(jint value) {
    PyTypeObject *type = &jint_Type;
    jintObject *self = (jintObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jint_Val(self) = value;
    return self;
}