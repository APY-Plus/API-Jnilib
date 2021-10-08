#include "jstring.hpp"

static jstringObject* jstring_jstring(PyObject *x) {
    if (jstring_CheckExact(x))
        INC_RETURN_TYPE(x, jstringObject*);
    else if (jobject_Check(x))
        return jstring_FromValue(jstring_Val(x));
    _BadArgument("jstring", "argument", "jstring", x);
    return NULL;
}
static jstringObject* jstring_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x;
    if (!PyArg_UnpackTuple(args, "jstring", 1, 1, &x))
        return NULL;
    return jstring_jstring(x);
}

PyTypeObject jstring_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jstring",
    .tp_basicsize = sizeof(jstringObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "jstring type",
    .tp_base = &jobject_Type,
    .tp_new = (newfunc)jstring_new,
};

jstringObject* jstring_FromValue(jstring value) {
    PyTypeObject *type = &jstring_Type;
    jstringObject *self = (jstringObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jobject_Val(self) = value;
    return self;
}
