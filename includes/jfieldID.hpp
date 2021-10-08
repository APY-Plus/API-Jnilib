#ifndef __JFIELDID_H__
#define __JFIELDID_H__

#include "jnilib_conf.hpp"

#define jfieldID_Val(x) (((jfieldIDObject*)(x))->_jfieldID)
#define jfieldID_Sig(x) (((jfieldIDObject*)(x))->sig)
#define jfieldID_Check(x) (Py_TYPE(x) == &jfieldID_Type)

struct jfieldIDObject : PyObject {
    jfieldID _jfieldID;
    const char *sig;
};

extern PyTypeObject jfieldID_Type;

jfieldIDObject* jfieldID_FromValue(jfieldID, const char*);

#endif /* __JFIELDID_H__ */