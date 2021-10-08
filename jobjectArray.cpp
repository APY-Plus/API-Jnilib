#include "jobjectArray.hpp"

static jobjectArrayObject* jobjectArray_jobjectArray(PyObject *x) {
    if (jobjectArray_CheckExact(x))
        INC_RETURN_TYPE(x, jobjectArrayObject*);
    else if (jobject_Check(x))
        return jobjectArray_FromValue(jobjectArray_Val(x));
    _BadArgument("jobjectArray", "argument", "jobject", x);
    return NULL;
}
static jobjectArrayObject* jobjectArray_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x;
    if (!PyArg_UnpackTuple(args, "jobjectArray", 1, 1, &x))
        return NULL;
    return jobjectArray_jobjectArray(x);
}

PyTypeObject jobjectArray_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jobjectArray",
    .tp_basicsize = sizeof(jobjectArrayObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "jobjectArray type",
    .tp_base = &jarray_Type,
};

jobjectArrayObject* jobjectArray_FromValue(jobjectArray value) {
    PyTypeObject *type = &jobjectArray_Type;
    jobjectArrayObject *self = (jobjectArrayObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        jobject_Val(self) = value;
        Py_INCREF(&jobjectArray_Type);
        jarray_Type(self) = &jobjectArray_Type;
    }
    return self;
} 