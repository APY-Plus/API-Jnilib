#include "jfieldID.hpp"

static void jfieldID_dealloc(jfieldIDObject *self) {
    free((void*)jfieldID_Sig(self));
    Py_TYPE(self)->tp_free(self);
}
static jfieldIDObject* jfieldID_jfieldID(PyObject *x) {
    if (jfieldID_Check(x))
        INC_RETURN_TYPE(x, jfieldIDObject*);
    _BadArgument("jfieldID", "argument", "jfieldID", x);
    return NULL;
}
static jfieldIDObject* jfieldID_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x;
    if (!PyArg_ParseTuple(args, "jfieldID", 1, 1, &x))
        return NULL;
    return jfieldID_jfieldID(x);
}

PyTypeObject jfieldID_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jfieldID",
    .tp_basicsize = sizeof(jfieldIDObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)jfieldID_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "jfieldID type",
    .tp_new = (newfunc)jfieldID_new,
};

jfieldIDObject* jfieldID_FromValue(jfieldID value, const char *sig) {
    PyTypeObject *type = &jfieldID_Type;
    jfieldIDObject *self = (jfieldIDObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        jfieldID_Val(self) = value;
        jfieldID_Sig(self) = strdup(sig);
    }
    return self;
}