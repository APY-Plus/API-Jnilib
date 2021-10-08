#include "jmethodID.hpp"

static void jmethodID_dealloc(jmethodIDObject *self) {
    free((void*)jmethodID_Sig(self));
    free((void*)jmethodID_RetSig(self));
    Py_TYPE(self)->tp_free(self);
}
static jmethodIDObject* jmethodID_jmethodID(PyObject *x) {
    if (jmethodID_Check(x))
        INC_RETURN_TYPE(x, jmethodIDObject*);
    _BadArgument("jmethodID", "argument", "jmethodID", x);
    return NULL;
}
static jmethodIDObject* jmethodID_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x;
    if (!PyArg_ParseTuple(args, "jmethodID", 1, 1, &x))
        return NULL;
    return jmethodID_jmethodID(x);
}

PyTypeObject jmethodID_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jmethodID",
    .tp_basicsize = sizeof(jmethodIDObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)jmethodID_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "jmethodID type",
    .tp_new = (newfunc)jmethodID_new,
};

jmethodIDObject* jmethodID_FromValue(jmethodID value, const char *sig) {
    PyTypeObject *type = &jmethodID_Type;
    jmethodIDObject *self = (jmethodIDObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        jmethodID_Val(self) = value;
        jmethodID_Sig(self) = strdup(sig);
        jmethodID_RetSig(self) = strdup(strrchr(sig, ')') + 1);
        //TODO 当签名不规范时怎么处理
    }
    return self;
}