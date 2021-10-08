#ifndef __JOBJECTARRAY_H__
#define __JOBJECTARRAY_H__

#include "jarray.hpp"

#define jobjectArray_Val(x) ((jobjectArray)jobject_Val(x))
#define jobjectArray_Check(x) PyType_IsSubtype(Py_TYPE(x), &jarray_Type)
#define jobjectArray_CheckExact(x) (Py_TYPE(x) == &jobjectArray_Type)

struct jobjectArrayObject : jarrayObject {};

extern PyTypeObject jobjectArray_Type;

jobjectArrayObject* jobjectArray_FromValue(jobjectArray);

#endif /* __JOBJECTARRAY_H__ */