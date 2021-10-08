#include "jnilib.hpp"

JavaVM *G_VM;

static PyMethodDef _jnilib_methods[] = {
    {"attach_thread_code", AttachCurrentThread, METH_VARARGS, "nothing"},
    {"detach_thread_code", DetachCurrentThread, METH_VARARGS, "nothing"},
    {"get_env_code", GetEnv, METH_VARARGS, "nothing"},
    {NULL}
};

static PyModuleDef _jnilib_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "_jnilib",
    .m_doc = "nothing",
    .m_size = -1,
    .m_methods = _jnilib_methods,
};


PyMODINIT_FUNC PyInit__jnilib(void) {
    if (PyType_Ready(&jvalue_Type) < 0)
        return NULL;
    PyObject *module = PyModule_Create(&_jnilib_module);
    if (module) {

        #define INIT_TYPE(TYPE, NAME) \
            if (PyType_Ready(&TYPE) < 0) \
                return NULL; \
            Py_INCREF(&TYPE); \
            if (PyModule_AddObject(module, NAME, (PyObject*)&TYPE) < 0) { \
                Py_DECREF(&TYPE); \
                Py_DECREF(module); \
                return NULL; \
            }

        INIT_TYPE(jvalue_Type, "jvalue");
        INIT_TYPE(jboolean_Type, "jboolean");
        INIT_TYPE(jbyte_Type, "jbyte");
        INIT_TYPE(jchar_Type, "jchar");
        INIT_TYPE(jshort_Type, "jshort");
        INIT_TYPE(jint_Type, "jint");
        INIT_TYPE(jlong_Type, "jlong");
        INIT_TYPE(jfloat_Type, "jfloat");
        INIT_TYPE(jdouble_Type, "jdouble");
        INIT_TYPE(jobject_Type, "jobject");
        INIT_TYPE(jclass_Type, "jclass");
        INIT_TYPE(jstring_Type, "jstring");
        INIT_TYPE(jthrowable_Type, "jthrowable");
        INIT_TYPE(jweak_Type, "jweak");
        INIT_TYPE(jmethodID_Type, "jmehthodID");
        INIT_TYPE(jfieldID_Type, "jfieldID");

        INIT_TYPE(JNIEnv_Type, "JNIEnv");
    }
    return module;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void *reserved) {
    G_VM = vm;
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void *reserved) {
    Py_Finalize();
}

JNIEXPORT void JNICALL Java_Test_init(JNIEnv*, jclass) {
    PyImport_AppendInittab("_jnilib", PyInit__jnilib);
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('.')");
}

JNIEXPORT void JNICALL Java_Test_fini(JNIEnv*, jclass) {
    Py_Finalize();
}


JNIEXPORT void JNICALL Java_Test_mode1(JNIEnv *env, jclass, jstring j_fname) {
    PyThreadState *state = Py_NewInterpreter();
    const char *fname = env->GetStringUTFChars(j_fname, NULL);
    PyObject *py_fname = PyUnicode_FromString(fname);
    FILE *fp = _Py_fopen_obj(py_fname, "rb");
    PyRun_SimpleFileEx(fp, fname, 1);
    Py_DECREF(py_fname);
    Py_EndInterpreter(state);
}

JNIEXPORT void JNICALL Java_Test_mode2(JNIEnv*, jclass) {
    int res = PyRun_InteractiveLoop(stdin, "<stdin>");
    printf("[c]loop res: %d\n", res);
}
