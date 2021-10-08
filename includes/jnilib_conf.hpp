#ifndef __JNILIB_CONF_H__
#define __JNILIB_CONF_H__

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <jni.h>

#define INC_RETURN(x) return Py_INCREF(x), x
#define INC_RETURN_TYPE(x, type) return Py_INCREF(x), (type)(x)
#define INC_RETURN_NONE(type) INC_RETURN_TYPE(Py_None, type)
#define INC_RETURN_NOTIMPLEMENTED(type) INC_RETURN_TYPE(Py_NotImplemented, type)


extern JavaVM *G_VM;   //Global JavaVM

inline void _BadArgument(const char *fname, const char *displayname,
                   const char *expected, PyObject *arg) {
    PyErr_Format(PyExc_TypeError,
                 "%.200s() %.200s must be %.50s, not %.50s",
                 fname, displayname, expected,
                 arg == Py_None ? "None" : arg->ob_type->tp_name);
}

bool SafeEnv_Head(JNIEnv **env);
//  {
//     jint jni_code = G_VM->GetEnv(env, JNI_VERSION_1_6);
//     switch (jni_code) {
//         case JNI_EDETACHED: {

//         }
//         case JNI_OK: {

//         }
//         default: {

//         }
//     }
// }

#endif /* __JNILIB_CONF_H__ */