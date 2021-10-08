#ifndef __JBOOLEANARRAY_H__
#define __JBOOLEANARRAY_H__

#include "jarray.hpp"
#include "jboolean.hpp"

#define jbooleanArray_Data(x) ((jboolean*)jarray_Data(x))
#define jbooleanArray_Length(x) jarray_Length(x)
#define jbooleanArray_Check(x) PyType_IsSubtype(Py_TYPE(x), &jbooleanArray_Type)
#define jbooleanArray_CheckExact(x) (Py_TYPE(x) == &jbooleanArray_Type)

struct jbooleanArrayObject : jarrayObject {};

extern PyTypeObject jbooleanArray_Type;

jbooleanArrayObject* jbooleanArray_FromValue(jboolean*, jsize);

#endif /* __JBOOLEANARRAY_H__ */