#include "jthrowable.hpp"

static jthrowableObject* jthrowable_jthrowable(PyObject *x) {
    if (jthrowable_CheckExact(x))
        INC_RETURN_TYPE(x, jthrowableObject*);
    else if (jobject_Check(x))
        return jthrowable_FromValue(jthrowable_Val(x));
    _BadArgument("jthrowable", "argument", "jthrowable", x);
    return NULL;
}
static jthrowableObject* jthrowable_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x;
    if (!PyArg_UnpackTuple(args, "jthrowable", 1, 1, &x))
        return NULL;
    return jthrowable_jthrowable(x);
}

PyTypeObject jthrowable_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jthrowable",
    .tp_basicsize = sizeof(jthrowableObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "jthrowable type",
    .tp_base = &jobject_Type,
    .tp_new = (newfunc)jthrowable_new,
};

jthrowableObject* jthrowable_FromValue(jthrowable value) {
    PyTypeObject *type = &jthrowable_Type;
    jthrowableObject *self = (jthrowableObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jobject_Val(self) = value;
    return self;
}
