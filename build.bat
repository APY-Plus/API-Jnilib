@echo off
echo ---Compiling C---
g++ -LD:/X_Tu/Python/Python310 -lpython310 ^
    -ID:/X_Tu/Java/jdk1.8/include ^
    -ID:/X_Tu/Java/jdk1.8/include/win32 ^
    -ID:/X_Tu/Python/Python310/include ^
    -Iincludes -shared -o jnilib.dll ^
    jnilib.cpp jnienv.cpp jvalue.cpp jboolean.cpp jbyte.cpp jchar.cpp jshort.cpp ^
    jint.cpp jlong.cpp jfloat.cpp jdouble.cpp jmethodID.cpp jfieldID.cpp ^
    jobject.cpp jclass.cpp jthrowable.cpp jweak.cpp jstring.cpp jarray.cpp jobjectArray.cpp
copy jnilib.dll _jnilib.pyd

echo ---Compiling Java---
javac Test.java
echo ---Running---
java -cp . Test
