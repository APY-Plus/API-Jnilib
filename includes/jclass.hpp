#ifndef __JCLASS_H__
#define __JCLASS_H__

#include "jobject.hpp"

#define jclass_Val(x) ((jclass)jobject_Val(x))
#define jclass_Check(x) PyType_IsSubtype(Py_TYPE(x), &jclass_Type)
#define jclass_CheckExact(x) (Py_TYPE(x) == &jclass_Type)

struct jclassObject : jobjectObject {};

extern PyTypeObject jclass_Type;

jclassObject* jclass_FromValue(jclass);

#endif /* __JCLASS_H__ */