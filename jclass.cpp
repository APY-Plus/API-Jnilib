#include "jclass.hpp"

// static PyObject* jclass_desc(jclassObject *self) {
//     //TODO display class path
//     return PyUnicode_FromFormat("at %p", self);
// }

// static jclassObject* jclass_alloc(PyTypeObject *type, Py_ssize_t nitems) {
//     jclassObject *obj = (jclassObject*)PyType_GenericAlloc(type, nitems);
//     for (Py_ssize_t i=0; i<nitems+1; i++)
//         obj[i].desc = (descfunc)jclass_desc;
//     return obj;
// }
static jclassObject* jclass_jclass(PyObject *x) {
    if (jclass_CheckExact(x))
        INC_RETURN_TYPE(x, jclassObject*);
    else if (jobject_Check(x))
        return jclass_FromValue(jclass_Val(x));
    _BadArgument("jclass", "argument", "jclass", x);
    return NULL;
}
static jclassObject* jclass_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    PyObject *x;
    if (!PyArg_UnpackTuple(args, "jclass", 1, 1, &x))
        return NULL;
    return jclass_jclass(x);
}

PyTypeObject jclass_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jclass",
    .tp_basicsize = sizeof(jclassObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "jclass type",
    .tp_base = &jobject_Type,
    // .tp_alloc = (allocfunc)jclass_alloc,
    .tp_new = (newfunc)jclass_new,
};

jclassObject* jclass_FromValue(jclass value) {
    PyTypeObject *type = &jclass_Type;
    jclassObject *self = (jclassObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jobject_Val(self) = value;
    return self;
}
