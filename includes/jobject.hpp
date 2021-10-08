#ifndef __JOBJECT_H__
#define __JOBJECT_H__

#include "jvalue.hpp"

#define jobject_Val(x) (jvalue_Val(x).l)
#define jobject_Check(x) PyType_IsSubtype(Py_TYPE(x), &jobject_Type)
#define jobject_CheckExact(x) (Py_TYPE(x) == &jobject_Type)

struct jobjectObject : jvalueObject {};

extern PyTypeObject jobject_Type;

jobjectObject* jobject_FromValue(jobject);

#endif /* __JOBJECT_H__ */