#ifndef __JTHROWABLE_H__
#define __JTHROWABLE_H__

#include "jobject.hpp"

#define jthrowable_Val(x) ((jthrowable)jobject_Val(x))
#define jthrowable_Check(x) PyType_IsSubtype(Py_TYPE(x), &jthrowable_Type)
#define jthrowable_CheckExact(x) (Py_TYPE(x) == &jthrowable_Type)

struct jthrowableObject : jobjectObject {};

extern PyTypeObject jthrowable_Type;

jthrowableObject* jthrowable_FromValue(jthrowable);

#endif /* __JTHROWABLE_H__ */