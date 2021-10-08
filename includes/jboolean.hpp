#ifndef __JBOOLEAN_H__
#define __JBOOLEAN_H__

#include "jvalue.hpp"

#define jboolean_Val(x) (jvalue_Val(x).z)
#define jboolean_Check(x) (Py_TYPE(x) == &jboolean_Type)

struct jbooleanObject: jvalueObject {};

extern PyTypeObject jboolean_Type;

jbooleanObject* jboolean_FromValue(jboolean);

#endif /* __JBOOLEAN_H__ */