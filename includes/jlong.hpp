#ifndef __JLONG_H__
#define __JLONG_H__

#include "jvalue.hpp"

#define jlong_Val(x) (jvalue_Val(x).j)
#define jlong_Check(x) PyType_IsSubtype((x)->ob_type, &jlong_Type)

struct jlongObject : jvalueObject {};

extern PyTypeObject jlong_Type;

jlongObject* jlong_FromValue(jlong);


#endif /* __JLONG_H__ */