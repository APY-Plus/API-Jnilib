#ifndef __JSTRING_H__
#define __JSTRING_H__

#include "jobject.hpp"

#define jstring_Val(x) ((jstring)jobject_Val(x))
#define jstring_Check(x) PyType_IsSubtype(Py_TYPE(x), &jstring_Type)
#define jstring_CheckExact(x) (Py_TYPE(x) == &jstring_Type)

struct jstringObject : jobjectObject {};

extern PyTypeObject jstring_Type;

jstringObject* jstring_FromValue(jstring);

#endif /* __JSTRING_H__ */