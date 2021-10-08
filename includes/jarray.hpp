#ifndef __JARRAY_H__
#define __JARRAY_H__

#include "jobject.hpp"

#define jarray_Val(x) ((jarray)jobject_Val(x))
#define jarray_Cast(x) ((jarrayObject*)(x))
#define jarray_Type(x) (jarray_Cast(x)->type)
#define jarray_Check(x) PyType_IsSubtype(Py_TYPE(x), &jarray_Type)
#define jarray_CheckExact(x) (Py_TYPE(x) == &jarray_Type)

#define jbooleanArray_Val(x) ((jbooleanArray)jobject_Val(x))
#define jbyteArray_Val(x) ((jbyteArray)jobject_Val(x))
#define jcharArray_Val(x) ((jcharArray)jobject_Val(x))
#define jshortArray_Val(x) ((jshortArray)jobject_Val(x))
#define jintArray_Val(x) ((jintArray)jobject_Val(x))
#define jlongArray_Val(x) ((jlongArray)jobject_Val(x))
#define jfloatArray_Val(x) ((jfloatArray)jobject_Val(x))
#define jdoubleArray_Val(x) ((jdoubleArray)jobject_Val(x))

struct jarrayObject : PyObject {
    PyTypeObject *type;
};

extern PyTypeObject jarray_Type;

jarrayObject* jarray_FromValue(jarray, PyTypeObject*);

#endif /* __JARRAY_H__ */