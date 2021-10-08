#include "jchar.hpp"


static PyObject* jchar_desc(jcharObject *self) {
    jchar x = jchar_Val(self);
    Py_ssize_t newsize = 1;
    switch(x) {
        case '\0': case '\t': case '\n': case '\r':
            newsize = 2;
            break;
        default:
            if (x < ' ' || x >= 0x7f)
                newsize = (x <= 0xff) ? 4 : 6;
    }

    PyObject *result = PyUnicode_New(newsize, 0xffff);
    if (result != NULL) {
        Py_UCS2 *data = PyUnicode_2BYTE_DATA(result);
        switch(x) {
            case '\t': case '\n': case '\r':
                *data++ = '\\';
                *data++ = x;
                break;
            case '\0':
                *data++ = '\\';
                *data++ = '0';
                break;
            default:
                if (x >= ' ' && x < 0x7f) {
                    *data ++ = x;
                } else if (x <= 0xff) {
                    *data++ = '\\';
                    *data++ = 'x';
                    *data++ = Py_hexdigits[(x & 0xf0) >> 4];
                    *data++ = Py_hexdigits[x & 0xf];
                } else {
                    *data++ = '\\';
                    *data++ = 'u';
                    *data++ = Py_hexdigits[(x & 0xf000) >> 12];
                    *data++ = Py_hexdigits[(x & 0xf00) >> 8];
                    *data++ = Py_hexdigits[(x & 0xf0) >> 4];
                    *data++ = Py_hexdigits[x & 0xf];
                }
        }
    }
    return result;
}


static bool convert_to_jchar(PyObject *obj, jchar *val) {
    if (jchar_Check(obj)) {
        *val = jchar_Val(obj);
    } else if (PyLong_Check(obj)) {
        *val = PyLong_AsLong(obj);
    } else {
        return false;
    }
    return true;
}
static jcharObject* jchar_add(PyObject *self, PyObject *other) {
    jchar a, b;
    if (convert_to_jchar(self, &a) && convert_to_jchar(other, &b))
        return jchar_FromValue(a + b);
    return (jcharObject*)Py_NotImplemented;
}
static jcharObject* jchar_sub(PyObject *self, PyObject *other) {
    jchar a, b;
    if (convert_to_jchar(self, &a) && convert_to_jchar(other, &b))
        return jchar_FromValue(a - b);
    return (jcharObject*)Py_NotImplemented;
}
static jcharObject* jchar_mul(PyObject *self, PyObject *other) {
    jchar a, b;
    if (convert_to_jchar(self, &a) && convert_to_jchar(other, &b))
        return jchar_FromValue(a * b);
    return (jcharObject*)Py_NotImplemented;
}
static jcharObject* jchar_mod(PyObject *self, PyObject *other) {
    jchar a, b;
    if (convert_to_jchar(self, &a) && convert_to_jchar(other, &b))
        return jchar_FromValue(a % b);
    INC_RETURN_NOTIMPLEMENTED(jcharObject*);
}
static PyObject* jchar_divmod(PyObject *self, PyObject *other) {
    PyObject *result = PyTuple_New(2);
    jcharObject *div, *mod;
    if (result) {
        jchar a, b;
        if (!convert_to_jchar(self, &a) || !convert_to_jchar(other, &b)) {
            Py_DECREF(result);
            Py_INCREF(Py_NotImplemented);
            return Py_NotImplemented;
        }
        div = jchar_FromValue(a / b);
        mod = jchar_FromValue(a % b);
        PyTuple_SetItem(result, 0, div);
        PyTuple_SetItem(result, 1, mod);
    }
    return result;
}
static jcharObject* jchar_pow(PyObject *base, PyObject *exp, PyObject *mod) {
    jchar a, b, c;
    jcharObject *result;
    if (mod == Py_None) {
        if (convert_to_jchar(base, &a) && convert_to_jchar(exp, &b))
            return jchar_FromValue(pow(a, b));
    } else {
        if (convert_to_jchar(base, &a) && convert_to_jchar(exp, &b), convert_to_jchar(mod, &c))
            return jchar_FromValue((jchar)pow(a, b) % c);
    }
    INC_RETURN_NOTIMPLEMENTED(jcharObject*);
}
static bool jchar_bool(jcharObject *self) {
    return jchar_Val(self);
}
static jcharObject* jchar_invert(jcharObject *self) {
    return jchar_FromValue(~jchar_Val(self));
}
static jcharObject* jchar_lshift(PyObject *self, PyObject *other) {
    jchar a, b;
    if (convert_to_jchar(self, &a) && convert_to_jchar(other, &b))
        return jchar_FromValue(a << b);
    INC_RETURN_NOTIMPLEMENTED(jcharObject*);
}
static jcharObject* jchar_rshift(PyObject *self, PyObject *other) {
    jchar a, b;
    if (convert_to_jchar(self, &a) && convert_to_jchar(other, &b))
        return jchar_FromValue(a >> b);
    INC_RETURN_NOTIMPLEMENTED(jcharObject*);
}
static jcharObject* jchar_and(PyObject *self, PyObject *other) {
    jchar a, b;
    if (convert_to_jchar(self, &a) && convert_to_jchar(other, &b))
        return jchar_FromValue(a & b);
    INC_RETURN_NOTIMPLEMENTED(jcharObject*);
}
static jcharObject* jchar_xor(PyObject *self, PyObject *other) {
    jchar a, b;
    if (convert_to_jchar(self, &a) && convert_to_jchar(other, &b))
        return jchar_FromValue(a ^ b);
    INC_RETURN_NOTIMPLEMENTED(jcharObject*);
}
static jcharObject* jchar_or(PyObject *self, PyObject *other) {
    jchar a, b;
    if (convert_to_jchar(self, &a) && convert_to_jchar(other, &b))
        return jchar_FromValue(a | b);
    INC_RETURN_NOTIMPLEMENTED(jcharObject*);
}
static PyObject* jchar_long(jcharObject *self) {
    return PyLong_FromLong(jchar_Val(self));
}
static PyObject* jchar_float(jcharObject *self) {
    return PyFloat_FromDouble(jchar_Val(self));
}
static jcharObject* jchar_div(PyObject *self, PyObject *other) {
    jchar a, b;
    if (convert_to_jchar(self, &a) && convert_to_jchar(other, &b))
        return jchar_FromValue(a / b);
    INC_RETURN_NOTIMPLEMENTED(jcharObject*);
}

static PyObject* jchar_richcompare(jcharObject* self, PyObject *other, int op) {
    jchar a, b;
    if (convert_to_jchar(self, &a) && convert_to_jchar(other, &b))
        Py_RETURN_RICHCOMPARE(a, b, op);
    INC_RETURN_NOTIMPLEMENTED(jcharObject*);
}
static jcharObject* jchar_alloc(PyTypeObject *type, Py_ssize_t nitems) {
    jcharObject *obj = (jcharObject*)PyType_GenericAlloc(type, nitems);
    for (Py_ssize_t i=0; i<nitems+1; i++)
        obj[i].desc = (descfunc)jchar_desc;
    return obj;
}
static jcharObject* jchar_jchar(PyObject *x) {
    if (jchar_Check(x)) {
        INC_RETURN_TYPE(x, jcharObject*);
    } else if (PyLong_Check(x)) {
        return jchar_FromValue(PyLong_AsLong(x));
    } else if (PyUnicode_Check(x)) {
        Py_ssize_t length = PyBytes_Size(x);
        if (length != 1) {
            PyErr_Format(PyExc_TypeError, "argument length must be 1, not %zd", length);
            return NULL;
        }
        return jchar_FromValue(PyBytes_AsString(x)[0]);
    }
    _BadArgument("jchar", "argument", "int or one-character-bytes", x);
    return NULL;
}
static jcharObject* jchar_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x = NULL;
    if (!PyArg_UnpackTuple(args, "jchar", 0, 1, &x))
        return NULL;
    if (x == NULL)
        return jchar_FromValue(0);
    return jchar_jchar(x);
}


static PyNumberMethods jchar_as_number = {
    .nb_add = (binaryfunc)jchar_add,
    .nb_subtract = (binaryfunc)jchar_sub,
    .nb_multiply = (binaryfunc)jchar_mul,
    .nb_remainder = (binaryfunc)jchar_mod,
    .nb_divmod = (binaryfunc)jchar_divmod,
    .nb_power = (ternaryfunc)jchar_pow,
    .nb_bool = (inquiry)jchar_bool,
    .nb_invert = (unaryfunc)jchar_invert,
    .nb_lshift = (binaryfunc)jchar_lshift,
    .nb_rshift = (binaryfunc)jchar_rshift,
    .nb_and = (binaryfunc)jchar_and,
    .nb_xor = (binaryfunc)jchar_xor,
    .nb_or = (binaryfunc)jchar_or,
    .nb_int = (unaryfunc)jchar_long,
    .nb_float = (unaryfunc)jchar_float,
    .nb_floor_divide = (binaryfunc)jchar_div,
    .nb_true_divide = (binaryfunc)jchar_div,
    .nb_index = (unaryfunc)jchar_long
};

PyTypeObject jchar_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jchar",
    .tp_as_number = &jchar_as_number,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "jchar type",
    .tp_richcompare = (richcmpfunc)jchar_richcompare,
    .tp_base = &jvalue_Type,
    .tp_alloc = (allocfunc)jchar_alloc,
    .tp_new = (newfunc)jchar_new,
};


jcharObject *jchar_FromValue(jchar value) {
    PyTypeObject *type = &jchar_Type;
    jcharObject *self = (jcharObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jchar_Val(self) = value;
    return self;
}