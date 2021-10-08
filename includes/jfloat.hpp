#ifndef __JFLOAT_H__
#define __JFLOAT_H__

#include "jvalue.hpp"

#define jfloat_Val(x) (jvalue_Val(x).f)
#define jfloat_Check(x) PyType_IsSubtype((x)->ob_type, &jfloat_Type)

struct jfloatObject : jvalueObject {};

extern PyTypeObject jfloat_Type;

jfloatObject* jfloat_FromValue(jfloat);


#endif /* __JFLOAT_H__ */