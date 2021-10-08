#include "jobject.hpp"

static PyObject* jobject_desc(jobjectObject *self) {
    //TODO display class path
    return PyUnicode_FromFormat("at %p", self);
}

static bool convert_to_jobject(PyObject *obj, jobject *val) {
    if (!jobject_Check(obj))
        return false;
    *val = jobject_Val(obj);
    return true;
}
static jobjectObject* jobject_alloc(PyTypeObject *type, Py_ssize_t nitems) {
    jobjectObject *obj = (jobjectObject*)PyType_GenericAlloc(type, nitems);
    for (Py_ssize_t i=0; i<nitems+1; i++)
        obj[i].desc = (descfunc)jobject_desc;
    return obj;
}
static jobjectObject* jobject_jobject(PyObject *x) {
    //TODO should not assign it but copy it
    if (jobject_CheckExact(x))
        INC_RETURN_TYPE(x, jobjectObject*);
    else if (jobject_Check(x))
        return jobject_FromValue(jobject_Val(x));
    _BadArgument("jobject", "argument", "jobject", x);
    return NULL;
}
static jobjectObject* jobject_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x;
    if (!PyArg_UnpackTuple(args, "jobject", 1, 1, &x))
        return NULL;
    return jobject_jobject(x);
}

PyTypeObject jobject_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jobject",
    .tp_basicsize = sizeof(jobjectObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "jobject type",
    .tp_base = &jvalue_Type,
    .tp_alloc = (allocfunc)jobject_alloc,
    .tp_new = (newfunc)jobject_new,
};

jobjectObject* jobject_FromValue(jobject value) {
    PyTypeObject *type = &jobject_Type;
    jobjectObject *self = (jobjectObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jobject_Val(self) = value;
    return self;
}
