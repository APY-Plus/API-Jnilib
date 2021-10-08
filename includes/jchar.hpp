#ifndef __JCHAR_H__
#define __JCHAR_H__

#include "jvalue.hpp"

#define jchar_Val(x) (jvalue_Val(x).c)
#define jchar_Check(x) (Py_TYPE(x) == &jchar_Type)

struct jcharObject : public jvalueObject {};

extern PyTypeObject jchar_Type;

jcharObject* jchar_FromValue(jchar);

#endif /* __JCHAR_H__ */