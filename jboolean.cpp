#include "jboolean.hpp"


static PyObject* jboolean_desc(jbooleanObject *self) {
    if (jboolean_Val(self)) {
        Py_INCREF(Py_True);
        return Py_True;
    } else {
        Py_INCREF(Py_False);
        return Py_False;
    }
}

static bool jboolean_bool(jbooleanObject *self) {
    return jboolean_Val(self);
}
static jbooleanObject* jboolean_and(jbooleanObject *self, PyObject *other) {
    jboolean a = PyObject_IsTrue(self);
    jboolean b = PyObject_IsTrue(other);
    return jboolean_FromValue(a && b);
}
static jbooleanObject* jboolean_xor(jbooleanObject *self, PyObject *other) {
    jboolean a = PyObject_IsTrue((self));
    jboolean b = PyObject_IsTrue(other);
    return jboolean_FromValue(a ^ b);
}
static jbooleanObject* jboolean_or(jbooleanObject *self, PyObject *other) {
    jboolean a = PyObject_IsTrue((self));
    jboolean b = PyObject_IsTrue(other);
    return jboolean_FromValue(a || b);
}
static PyObject* jboolean_long(jbooleanObject* self) {
    return PyLong_FromLong(jboolean_Val(self));
}

static PyObject* jboolean_richcompare(jbooleanObject *self, PyObject *other, int op) {
    bool a = PyObject_IsTrue(self);
    bool b = PyObject_IsTrue(other);
    Py_RETURN_RICHCOMPARE(a, b, op);
}
static jbooleanObject* jboolean_alloc(PyTypeObject *type, Py_ssize_t nitems) {
    jbooleanObject *obj = (jbooleanObject*)PyType_GenericAlloc(type, nitems);
    for (Py_ssize_t i=0; i<nitems+1; i++)
        obj[i].desc = (descfunc)jboolean_desc;
    return obj;
}
static jbooleanObject* jboolean_jboolean(PyObject* x) {
    return jboolean_FromValue(PyObject_IsTrue(x));
}
static jbooleanObject* jboolean_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x = Py_False;
    if (!PyArg_UnpackTuple(args, "jboolean", 0, 1, &x))
        return NULL;
    return jboolean_jboolean(x);
}


static PyNumberMethods jboolean_as_number = {
    .nb_bool = (inquiry)jboolean_bool,
    .nb_and = (binaryfunc)jboolean_and,
    .nb_xor = (binaryfunc)jboolean_xor,
    .nb_or = (binaryfunc)jboolean_or,
    .nb_int = (unaryfunc)jboolean_long,
    .nb_index = (unaryfunc)jboolean_long,
};

PyTypeObject jboolean_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jboolean",
    .tp_as_number = &jboolean_as_number,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "jboolean type",
    .tp_richcompare = (richcmpfunc)jboolean_richcompare,
    .tp_base = &jvalue_Type,
    .tp_alloc = (allocfunc)jboolean_alloc,
    .tp_new = (newfunc)jboolean_new,
};


jbooleanObject* jboolean_FromValue(jboolean value) {
    PyTypeObject *type = &jboolean_Type;
    jbooleanObject *self = (jbooleanObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jboolean_Val(self) = value;
    return self;
}