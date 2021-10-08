#ifndef __JSHORT_H__
#define __JSHORT_H__

#include "jvalue.hpp"

#define jshort_Val(x) (jvalue_Val(x).s)
#define jshort_Check(x) (Py_TYPE(x) == &jshort_Type)

struct jshortObject : jvalueObject {};

extern PyTypeObject jshort_Type;

jshortObject* jshort_FromValue(jshort);


#endif /* __JSHORT_H__ */