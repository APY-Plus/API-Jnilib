#ifndef __JNIENV_H__
#define __JNIENV_H__

#include "jnilib_conf.hpp"
#include "jvalue.hpp"
#include "jboolean.hpp"
#include "jbyte.hpp"
#include "jchar.hpp"
#include "jshort.hpp"
#include "jint.hpp"
#include "jlong.hpp"
#include "jfloat.hpp"
#include "jdouble.hpp"
#include "jobject.hpp"
#include "jclass.hpp"
#include "jmethodID.hpp"
#include "jfieldID.hpp"
#include "jthrowable.hpp"
#include "jweak.hpp"
#include "jstring.hpp"
#include "jarray.hpp"
#include "jobjectArray.hpp"

#define JNIEnv_Env(x) (((JNIEnvObject*)(x))->_env)

struct JNIEnvObject : PyObject {
    JNIEnv *_env;
};

extern PyTypeObject JNIEnv_Type;

PyObject* AttachCurrentThread(PyObject*, PyObject*);
PyObject* DetachCurrentThread(PyObject*, PyObject*);
PyObject* GetEnv(PyObject*, PyObject*);

JNIEnvObject* JNIEnv_FromEnv(JNIEnv*);

#endif /* __JNIENV__ */