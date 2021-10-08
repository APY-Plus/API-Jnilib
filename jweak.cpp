#include "jweak.hpp"

static jweakObject* jweak_jewak(PyObject *x) {
    if (jweak_CheckExact(x))
        INC_RETURN_TYPE(x, jweakObject*);
    else if (jweak_Check(x))
        return jweak_FromValue(jweak_Val(x));
    _BadArgument("jweak", "argument", "jweak", x);
    return NULL;
}
static jweakObject* jweak_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x;
    if (!PyArg_UnpackTuple(args, "jweak", 1, 1, &x))
        return NULL;
    return jweak_jewak(x);
}

PyTypeObject jweak_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jweak",
    .tp_basicsize = sizeof(jweakObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "jweak type",
    .tp_base = &jobject_Type,
    .tp_new = (newfunc)jweak_new,
};

jweakObject* jweak_FromValue(jweak value) {
    PyTypeObject *type = &jweak_Type;
    jweakObject *self = (jweakObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jobject_Val(self) = value;
    return self;
}