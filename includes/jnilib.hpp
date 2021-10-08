#ifndef __JNILIB_H__
#define __JNILIB_H__

// #include "jnilib_conf.hpp"
#include "jnienv.hpp"

extern "C" {

PyMODINIT_FUNC PyInit_jnilib(void);
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void *reserved);
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved);
JNIEXPORT void JNICALL Java_Test_init(JNIEnv*, jclass);
JNIEXPORT void JNICALL Java_Test_fini(JNIEnv*, jclass);
JNIEXPORT void JNICALL Java_Test_mode1(JNIEnv*, jclass, jstring fname);
JNIEXPORT void JNICALL Java_Test_mode2(JNIEnv*, jclass);

}

#endif /* __JNILIB_H__ */