#ifndef __JNILIB_H__
#define __JNILIB_H__

// #include "jnilib_conf.hpp"
#include "jnienv.hpp"

extern "C" {

PyMODINIT_FUNC PyInit_jnilib(void);
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void *reserved);
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved);
JNIEXPORT void JNICALL Java_Test_init(JNIEnv*, jobject);
JNIEXPORT void JNICALL Java_Test_hello1(JNIEnv*, jobject);
JNIEXPORT void JNICALL Java_Test_hello2(JNIEnv*, jobject);

}

#endif /* __JNILIB_H__ */