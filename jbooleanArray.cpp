#include "jbooleanArray.hpp"

static jbooleanArrayObject* jbooleanArray_jbooleanArray(PyObject *x) {
    if (jbooleanArray_CheckExact(x)) {
        INC_RETURN_TYPE(x, jbooleanArrayObject*);
    } else if (PySequence_Check(x)) {
        jsize length = PySequence_Length(x);
        jboolean *data = (jboolean*)malloc(length * sizeof(jboolean));
        for (jsize i=0; i<length; i++) {
            PyObject *item = PySequence_ITEM(x, i);
            if (item == NULL) {
                free(data);
                return NULL;
            }
            data[i] = PyObject_IsTrue(item);
            Py_DECREF(item);
        }
        return jbooleanArray_FromValue(data, length);
    }
    _BadArgument("jbooleanArray", "argument", "jbooleanArray or an iterable object", x);
    return NULL;
}
static jbooleanArrayObject* jbooleanArray_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    Py_ssize_t length = PyTuple_Size(args);
    if (length == 1 && PySequence_Check(PyTuple_GET_ITEM(args, 0))) {
        
    }
}

PyTypeObject jbooleanArray_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jbooleanArray",
    .tp_basicsize = sizeof(jbooleanArrayObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "jbooleanArray type",
    .tp_new = (newfunc)jbooleanArray_new,
};

jbooleanArrayObject* jbooleanArray_FromValue(jboolean *data, jsize length) {
    PyTypeObject *type = &jbooleanArray_Type;
    jbooleanArrayObject *self = (jbooleanArrayObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        jarray_Data(self) = data;
        jarray_Length(self) = length;
        Py_INCREF(&jboolean_Type);
        jarray_Type(self) = &jboolean_Type;
        jarray_TypeSize(self) = sizeof(jboolean);
    }
}