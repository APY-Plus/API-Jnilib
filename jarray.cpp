#include "jarray.hpp"

static void jarray_dealloc(jarrayObject *self) {
    Py_DECREF(jarray_Type(self));
    Py_TYPE(self)->tp_free(self);
}
// static jarrayObject* jarray_jarray(PyObject *x) {
//     if (jarray_CheckExact(x))
//         INC_RETURN_TYPE(x, jarrayObject*);
//     else if (jobject_Check(x))
//         return jarray_FromValue(jarray_Val(x));
//     _BadArgument("jarray", "argument", "jarray", x);
//     return NULL;
// }
// static jarrayObject* jarray_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
//     PyObject *x;
//     if (!PyArg_UnpackTuple(args, "jarray", 1, 1, &x))
//         return NULL;
//     return jarray_jarray(x);
// }

PyTypeObject jarray_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jarray",
    .tp_basicsize = sizeof(jarrayObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)jarray_dealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "jarray type",
    .tp_base = &jobject_Type,
    // .tp_new = (newfunc)jarray_new,
};

jarrayObject* jarray_FromValue(jarray value, PyTypeObject *type_obj) {
    PyTypeObject *type = &jarray_Type;
    jarrayObject *self = (jarrayObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        jobject_Val(self) = value;
        Py_INCREF(type_obj);
        jarray_Type(self) = type_obj;
    }
    return self;
}
