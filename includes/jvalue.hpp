#ifndef __JVALUE_H__
#define __JVALUE_H__

#include "jnilib_conf.hpp"

#define jvalue_Cast(x) ((jvalueObject*)(x))
#define jvalue_Val(x) (jvalue_Cast(x)->_jvalue)
#define jvalue_Check(x) PyType_IsSubtype(Py_TYPE(x), &jvalue_Type)
#define jvalue_CheckExact(x) (Py_TYPE(x) == &jvalue_Type)

typedef PyObject* (*descfunc)(struct jvalueObject*);

struct jvalueObject : PyObject {
    jvalue _jvalue;
    descfunc desc;
};

extern PyTypeObject jvalue_Type;

jvalueObject* jvalue_FromValue(jvalue);

#endif /* __JVALUE_H__ */