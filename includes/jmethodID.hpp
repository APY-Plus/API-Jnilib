#ifndef __JMETHODID_H__
#define __JMETHODID_H__

#include "jnilib_conf.hpp"

#define jmethodID_Val(x) (((jmethodIDObject*)(x))->_jmethodID)
#define jmethodID_Sig(x) (((jmethodIDObject*)(x))->sig)
#define jmethodID_RetSig(x) (((jmethodIDObject*)(x))->ret_sig)
#define jmethodID_Check(x) (Py_TYPE(x) == &jmethodID_Type)

struct jmethodIDObject : PyObject {
    jmethodID _jmethodID;
    const char *sig;
    const char *ret_sig;
};

extern PyTypeObject jmethodID_Type;

jmethodIDObject* jmethodID_FromValue(jmethodID, const char*);

#endif /* __JMETHODID_H__ */