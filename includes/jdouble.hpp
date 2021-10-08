#ifndef __JDOUBLE_H__
#define __JDOUBLE_H__

#include "jvalue.hpp"

#define jdouble_Val(x) (jvalue_Val(x).d)
#define jdouble_Check(x) PyType_IsSubtype((x)->ob_type, &jdouble_Type)

struct jdoubleObject : jvalueObject {};

extern PyTypeObject jdouble_Type;

jdoubleObject* jdouble_FromValue(jdouble);


#endif /* __JDOUBLE_H__ */