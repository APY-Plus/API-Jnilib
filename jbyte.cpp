#include "jbyte.hpp"


static PyObject* jbyte_desc(jbyteObject *self) {
    jbyte x = jbyte_Val(self);
    Py_ssize_t newsize = 1;
    switch(x) {
        case '\0': case '\t': case '\n': case '\r':
            newsize = 2;
            break;
        default:
            if (x < ' ' || x >= 0x7f)
                newsize = 4;
    }

    PyObject *result = PyUnicode_New(newsize, 127);
    if (result != NULL) {
        Py_UCS1 *data = PyUnicode_1BYTE_DATA(result);
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
                if (x < ' ' || x >= 0x7f) {
                    *data++ = '\\';
                    *data++ = 'x';
                    *data++ = Py_hexdigits[(x & 0xf0) >> 4];
                    *data++ = Py_hexdigits[x & 0xf];
                } else {
                    *data++ = x;
                }
        }
    }
    return result;
}


static bool convert_to_jbyte(PyObject *obj, jbyte *val) {
    if (jbyte_Check(obj)) {
        *val = jbyte_Val(obj);
    } else if (PyLong_Check(obj)) {
        *val = PyLong_AsLong(obj);
    } else {
        return false;
    }
    return true;
}
static jbyteObject* jbyte_add(PyObject *self, PyObject *other) {
    jbyte a, b;
    if (convert_to_jbyte(self, &a) && convert_to_jbyte(other, &b))
        return jbyte_FromValue(a + b);
    return (jbyteObject*)Py_NotImplemented;
}
static jbyteObject* jbyte_sub(PyObject *self, PyObject *other) {
    jbyte a, b;
    if (convert_to_jbyte(self, &a) && convert_to_jbyte(other, &b))
        return jbyte_FromValue(a - b);
    return (jbyteObject*)Py_NotImplemented;
}
static jbyteObject* jbyte_mul(PyObject *self, PyObject *other) {
    jbyte a, b;
    if (convert_to_jbyte(self, &a) && convert_to_jbyte(other, &b))
        return jbyte_FromValue(a * b);
    return (jbyteObject*)Py_NotImplemented;
}
static jbyteObject* jbyte_mod(PyObject *self, PyObject *other) {
    jbyte a, b;
    if (convert_to_jbyte(self, &a) && convert_to_jbyte(other, &b))
        return jbyte_FromValue(a % b);
    INC_RETURN_NOTIMPLEMENTED(jbyteObject*);
}
static PyObject* jbyte_divmod(PyObject *self, PyObject *other) {
    PyObject *result = PyTuple_New(2);
    jbyteObject *div, *mod;
    if (result) {
        jbyte a, b;
        if (!convert_to_jbyte(self, &a) || !convert_to_jbyte(other, &b)) {
            Py_DECREF(result);
            Py_INCREF(Py_NotImplemented);
            return Py_NotImplemented;
        }
        div = jbyte_FromValue(a / b);
        mod = jbyte_FromValue(a % b);
        PyTuple_SetItem(result, 0, div);
        PyTuple_SetItem(result, 1, mod);
    }
    return result;
}
static jbyteObject* jbyte_pow(PyObject *base, PyObject *exp, PyObject *mod) {
    jbyte a, b, c;
    jbyteObject *result;
    if (mod == Py_None)  {
        if (convert_to_jbyte(base, &a) && convert_to_jbyte(exp, &b))
            return jbyte_FromValue(pow(a, b));
    } else {
        if (convert_to_jbyte(base, &a) && convert_to_jbyte(exp, &b), convert_to_jbyte(mod, &c))
            return jbyte_FromValue((jbyte)pow(a, b) % c);
    }
    INC_RETURN_NOTIMPLEMENTED(jbyteObject*);
}
static bool jbyte_bool(jbyteObject *self) {
    return jbyte_Val(self);
}
static jbyteObject* jbyte_invert(jbyteObject *self) {
    return jbyte_FromValue(~jbyte_Val(self));
}
static jbyteObject* jbyte_lshift(PyObject *self, PyObject *other) {
    jbyte a, b;
    if (convert_to_jbyte(self, &a) && convert_to_jbyte(other, &b))
        return jbyte_FromValue(a << b);
    INC_RETURN_NOTIMPLEMENTED(jbyteObject*);
}
static jbyteObject* jbyte_rshift(PyObject *self, PyObject *other) {
    jbyte a, b;
    if (convert_to_jbyte(self, &a) && convert_to_jbyte(other, &b))
        return jbyte_FromValue(a >> b);
    INC_RETURN_NOTIMPLEMENTED(jbyteObject*);
}
static jbyteObject* jbyte_and(PyObject *self, PyObject *other) {
    jbyte a, b;
    if (convert_to_jbyte(self, &a) && convert_to_jbyte(other, &b))
        return jbyte_FromValue(a & b);
    INC_RETURN_NOTIMPLEMENTED(jbyteObject*);
}
static jbyteObject* jbyte_xor(PyObject *self, PyObject *other) {
    jbyte a, b;
    if (convert_to_jbyte(self, &a) && convert_to_jbyte(other, &b))
        return jbyte_FromValue(a ^ b);
    INC_RETURN_NOTIMPLEMENTED(jbyteObject*);
}
static jbyteObject* jbyte_or(PyObject *self, PyObject *other) {
    jbyte a, b;
    if (convert_to_jbyte(self, &a) && convert_to_jbyte(other, &b))
        return jbyte_FromValue(a | b);
    INC_RETURN_NOTIMPLEMENTED(jbyteObject*);
}
static PyObject* jbyte_long(jbyteObject *self) {
    return PyLong_FromLong(jbyte_Val(self));
}
static PyObject* jbyte_float(jbyteObject *self) {
    return PyFloat_FromDouble(jbyte_Val(self));
}
static jbyteObject* jbyte_div(PyObject *self, PyObject *other) {
    jbyte a, b;
    if (convert_to_jbyte(self, &a) && convert_to_jbyte(other, &b))
        return jbyte_FromValue(a / b);
    INC_RETURN_NOTIMPLEMENTED(jbyteObject*);
}

static PyObject* jbyte_richcompare(jbyteObject* self, PyObject* other, int op) {
    jbyte a, b;
    if (convert_to_jbyte(self, &a) && convert_to_jbyte(other, &b))
        Py_RETURN_RICHCOMPARE(a, b, op);
    INC_RETURN_NOTIMPLEMENTED(jbyteObject*);
}
static jbyteObject* jbyte_alloc(PyTypeObject *type, Py_ssize_t nitems) {
    jbyteObject *obj = (jbyteObject*)PyType_GenericAlloc(type, nitems);
    for (Py_ssize_t i=0; i<nitems+1; i++)
        obj[i].desc = (descfunc)jbyte_desc;
    return obj;
}
static jbyteObject* jbyte_jbyte(PyObject *x) {
    if (jbyte_Check(x)) {
        INC_RETURN_TYPE(x, jbyteObject*);
    } else if (PyLong_Check(x)) {
        return jbyte_FromValue(PyLong_AsLong(x));
    } else if (PyUnicode_Check(x)) {
        Py_ssize_t length = PyBytes_Size(x);
        if (length != 1) {
            PyErr_Format(PyExc_TypeError, "argument length must be 1, not %zd", length);
            return NULL;
        }
        return jbyte_FromValue(PyBytes_AsString(x)[0]);
    }
    _BadArgument("jbyte", "argument", "int or one-character-bytes", x);
    return NULL;
}
static jbyteObject* jbyte_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x = NULL;
    if (!PyArg_UnpackTuple(args, "jbyte", 0, 1, &x))
        return NULL;
    if (x == NULL)
        return jbyte_FromValue(0);
    return jbyte_jbyte(x);
}


static PyNumberMethods jbyte_as_number = {
    .nb_add = (binaryfunc)jbyte_add,
    .nb_subtract = (binaryfunc)jbyte_sub,
    .nb_multiply = (binaryfunc)jbyte_mul,
    .nb_remainder = (binaryfunc)jbyte_mod,
    .nb_divmod = (binaryfunc)jbyte_divmod,
    .nb_power = (ternaryfunc)jbyte_pow,
    .nb_bool = (inquiry)jbyte_bool,
    .nb_invert = (unaryfunc)jbyte_invert,
    .nb_lshift = (binaryfunc)jbyte_lshift,
    .nb_rshift = (binaryfunc)jbyte_rshift,
    .nb_and = (binaryfunc)jbyte_and,
    .nb_xor = (binaryfunc)jbyte_xor,
    .nb_or = (binaryfunc)jbyte_or,
    .nb_int = (unaryfunc)jbyte_long,
    .nb_float = (unaryfunc)jbyte_float,
    .nb_floor_divide = (binaryfunc)jbyte_div,
    .nb_true_divide = (binaryfunc)jbyte_div,
    .nb_index = (unaryfunc)jbyte_long
};


PyTypeObject jbyte_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jbyte",
    .tp_as_number = &jbyte_as_number,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "jbyte type",
    .tp_richcompare = (richcmpfunc)jbyte_richcompare,
    .tp_base = &jvalue_Type,
    .tp_alloc = (allocfunc)jbyte_alloc,
    .tp_new = (newfunc)jbyte_new,
};


jbyteObject *jbyte_FromValue(jbyte value) {
    PyTypeObject *type = &jbyte_Type;
    jbyteObject *self = (jbyteObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jbyte_Val(self) = value;
    return self;
}