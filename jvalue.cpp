#include "jvalue.hpp"

static PyObject* jvalue_desc(jvalueObject *self) {
    return PyUnicode_FromFormat("at %p", self);
}

static PyObject* jvalue_str(jvalueObject *self) {
    PyObject *description = self->desc(self);
    if (description == NULL)
        return NULL;
    PyObject *result = PyUnicode_FromFormat("<%s %S>", Py_TYPE(self)->tp_name, description);
    Py_DECREF(description);
    return result;
}
static jvalueObject* jvalue_alloc(PyTypeObject *type, Py_ssize_t nitems) {
    jvalueObject *obj = (jvalueObject*)PyType_GenericAlloc(type, nitems);
    for (Py_ssize_t i=0; i<nitems+1; i++)
        obj[i].desc = (descfunc)jvalue_desc;
    return obj;
}
static jvalueObject* jvalue_jvalue(PyObject *x) {
    if (jvalue_CheckExact(x))
        INC_RETURN_TYPE(x, jvalueObject*);
    else if (jvalue_Check(x))
        return jvalue_FromValue(jvalue_Val(x));
    _BadArgument("jvalue", "argument", "jvalue", x);
    return NULL;
}
static jvalueObject* jvalue_new(PyTypeObject *self, PyObject *args, PyObject *kwargs) {
    PyObject *x;
    if (!PyArg_UnpackTuple(args, "jvalue", 1, 1, &x))
        return NULL;
    return jvalue_jvalue(x);
}

PyTypeObject jvalue_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "jvalue",
    .tp_basicsize = sizeof(jvalueObject),
    .tp_itemsize = 0,
    .tp_repr = (reprfunc)jvalue_str,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "jvalue type",
    .tp_alloc = (allocfunc)jvalue_alloc,
    .tp_new = (newfunc)jvalue_new,
};

jvalueObject* jvalue_FromValue(jvalue value) {
    PyTypeObject *type = &jvalue_Type;
    jvalueObject *self = (jvalueObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        jvalue_Val(self) = value;
    return self;
}

