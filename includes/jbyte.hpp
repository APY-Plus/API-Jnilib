#ifndef __JBYTE_H__
#define __JBYTE_H__

#include "jvalue.hpp"

#define jbyte_Val(x) (jvalue_Val(x).b)
#define jbyte_Check(x) (Py_TYPE(x) == &jbyte_Type)

struct jbyteObject : jvalueObject {};

extern PyTypeObject jbyte_Type;

jbyteObject* jbyte_FromValue(jbyte);

#endif /* __JBYTE_H__ */