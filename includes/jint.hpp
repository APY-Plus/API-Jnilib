#ifndef __JINT_H__
#define __JINT_H__

#include "jvalue.hpp"

#define jint_Val(x) (jvalue_Val(x).i)
#define jint_Check(x) (Py_TYPE(x) == &jint_Type)

struct jintObject : jvalueObject {};

extern PyTypeObject jint_Type;

jintObject* jint_FromValue(jint);


#endif /* __JINT_H__ */