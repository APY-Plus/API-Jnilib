#include "jnienv.hpp"

static PyObject* GetVersion(JNIEnvObject *self) {
    return PyLong_FromLong(JNIEnv_Env(self)->GetVersion());
}

static jclassObject* DefineClass(JNIEnvObject *self, PyObject *args) {
    PyObject *name, *loader, *bufobj;
    if (!PyArg_UnpackTuple(args, "define_class", 3, 3, &name, &loader, &bufobj))
        return NULL;
    if (!PyUnicode_Check(name)) {
        _BadArgument("define_class", "arg 1", "str", name);
        return NULL;
    }
    if (!jobject_Check(loader)) {
        _BadArgument("define_class", "arg 2", "jobject", name);
        return NULL;
    }
    Py_buffer buffer = {NULL, NULL};
    if (!PyObject_GetBuffer(bufobj, &buffer, PyBUF_SIMPLE) != 0)
        return NULL;
    jclass result = JNIEnv_Env(self)->DefineClass(
            PyUnicode_AsUTF8(name), jobject_Val(loader),
            (jbyte*)(buffer.buf), buffer.len);
    PyBuffer_Release(&buffer);
    if (result == NULL)
        INC_RETURN_NONE(jclassObject*);
    return jclass_FromValue(result);
}
static jclassObject* FindClass(JNIEnvObject *self, PyObject *args) {
    PyObject *name;
    if (!PyArg_UnpackTuple(args, "find_class", 1, 1, &name))
        return NULL;
    if (!PyUnicode_Check(name)) {
        _BadArgument("find_class", "argument", "str", name);
        return NULL;
    }
    jclass result = JNIEnv_Env(self)->FindClass(PyUnicode_AsUTF8(name));
    if (result == NULL)
        INC_RETURN_NONE(jclassObject*);
    return jclass_FromValue(result);
}
static jclassObject* GetSuperclass(JNIEnvObject *self, PyObject *args) {
    PyObject *sub;
    if (!PyArg_UnpackTuple(args, "get_superclass", 1, 1, &sub))
        return NULL;
    if (!jclass_Check(sub)) {
        _BadArgument("get_superclass", "argument", "jclass", sub);
        return NULL;
    }
    jclass result = JNIEnv_Env(self)->GetSuperclass(jclass_Val(sub));
    if (result == NULL)
        INC_RETURN_NONE(jclassObject*);
    return jclass_FromValue(result);
}
static PyObject* IsAssignableFrom(JNIEnvObject *self, PyObject *args) {
    PyObject *sub, *sup;
    if (!PyArg_UnpackTuple(args, "is_assignable_from", 2, 2, &sub, &sup))
        return NULL;
    if (!jclass_Check(sub)) {
        _BadArgument("is_assignable_from", "arg 1", "jclass", sub);
        return NULL;
    }
    if (!jclass_Check(sup)) {
        _BadArgument("is_assignable_from", "arg 2", "jclass", sup);
        return NULL;
    }
    jboolean result = JNIEnv_Env(self)->IsAssignableFrom(jclass_Val(sub), jclass_Val(sup));
    return PyBool_FromLong(result);
}

static PyObject* Throw(JNIEnvObject *self, PyObject *args) {
    PyObject *obj;
    if (!PyArg_UnpackTuple(args, "throw", 1, 1, &obj))
        return NULL;
    if (!jthrowable_Check(obj)) {
        _BadArgument("throw", "argument", "jthrowable", obj);
        return NULL;
    }
    jint result = JNIEnv_Env(self)->Throw(jthrowable_Val(obj));
    return PyBool_FromLong(result == 0);
}
static PyObject* ThrowNew(JNIEnvObject *self, PyObject* args) {
    PyObject *clazz, *msg;
    if (!PyArg_UnpackTuple(args, "throw_new", 2, 2, &clazz, &msg))
    return NULL;
    if (!jclass_Check(clazz)) {
        _BadArgument("throw_new", "arg 1", "jclass", clazz);
        return NULL;
    }
    if (!PyUnicode_Check(msg)) {
        _BadArgument("throw_new", "arg 2", "str", msg);
        return NULL;
    }
    jint result = JNIEnv_Env(self)->ThrowNew(jclass_Val(clazz), PyUnicode_AsUTF8(msg));
    return PyBool_FromLong(result == 0);
}
static jthrowableObject* ExceptionOccurred(JNIEnvObject *self, PyObject *args) {
    if (!PyArg_UnpackTuple(args, "exception_occurred", 0, 0))
        return NULL;
    jthrowable result = JNIEnv_Env(self)->ExceptionOccurred();
    if (result == NULL)
        INC_RETURN_NONE(jthrowableObject*);
    return jthrowable_FromValue(result);
}
static PyObject* ExceptionDescribe(JNIEnvObject *self, PyObject *args) {
    if (!PyArg_UnpackTuple(args, "exception_describe", 0, 0))
        return NULL;
    JNIEnv_Env(self)->ExceptionDescribe();
    Py_RETURN_NONE;
}
static PyObject* ExceptionClear(JNIEnvObject *self, PyObject *args) {
    if (!PyArg_UnpackTuple(args, "exception_clear", 0, 0))
        return NULL;
    JNIEnv_Env(self)->ExceptionClear();
    Py_RETURN_NONE;
}
static PyObject* ExceptionCheck(JNIEnvObject *self, PyObject *args) {
    if (!PyArg_UnpackTuple(args, "exception_check", 0, 0))
        return NULL;
    jboolean result = JNIEnv_Env(self)->ExceptionCheck();
    return PyBool_FromLong(result);
}
static PyObject* FatalError(JNIEnvObject *self, PyObject *args) {
    PyObject *msg;
    if (!PyArg_UnpackTuple(args, "fatal_error", 1, 1, &msg))
        return NULL;
    if (!PyUnicode_Check(msg)) {
        _BadArgument("fatal_error", "argument", "str", msg);
        return NULL;
    }
    JNIEnv_Env(self)->FatalError(PyUnicode_AsUTF8(msg));
    Py_RETURN_NONE;
}

static jobjectObject* NewGlobalRef(JNIEnvObject* self, PyObject* args) {
    PyObject *lobj;
    if (!PyArg_UnpackTuple(args, "new_global_ref", 1, 1, &lobj))
        return NULL;
    if (!jobject_Check(lobj)) {
        _BadArgument("new_global_ref", "argument", "jobject", lobj);
        return NULL;
    }
    jobject result = JNIEnv_Env(self)->NewGlobalRef(jobject_Val(lobj));
    if (result == NULL)
        INC_RETURN_NONE(jobjectObject*);
    return jobject_FromValue(result);
}
static PyObject* DeleteGlobalRef(JNIEnvObject* self, PyObject* args) {
    PyObject *gref;
    if (!PyArg_UnpackTuple(args, "delete_global_ref", 1, 1, &gref))
        return NULL;
    if (!jobject_Check(gref)) {
        _BadArgument("delete_global_ref", "argument", "jobject", gref);
        return NULL;
    }
    JNIEnv_Env(self)->DeleteGlobalRef(jobject_Val(gref));
    Py_RETURN_NONE;
}
static jobjectObject* NewLocalRef(JNIEnvObject *self, PyObject* args) {
    PyObject *ref;
    if(!PyArg_UnpackTuple(args, "new_local_ref", 1, 1, &ref))
        return NULL;
    if(!jobject_Check(ref)) {
        _PyArg_BadArgument("new_local_ref", "argument", "jobject", ref);
        return NULL;
    }
    jobject result = JNIEnv_Env(self)->NewLocalRef(jobject_Val(ref));
    if (result == NULL)
        INC_RETURN_NONE(jobjectObject*);
    return jobject_FromValue(result);
}
static PyObject* DeleteLocalRef(JNIEnvObject* self, PyObject* args) {
    PyObject *obj;
    if (!PyArg_UnpackTuple(args, "delete_local_ref", 1, 1, &obj))
        return NULL;
    if (!jobject_Check(obj)) {
        _BadArgument("delete_local_ref", "argument", "jobject", obj);
        return NULL;
    }
    JNIEnv_Env(self)->DeleteLocalRef(jobject_Val(obj));
    Py_RETURN_NONE;
}
static PyObject* EnsureLocalCapacity(JNIEnvObject *self, PyObject *args) {
    PyObject *capacity;
    if(!PyArg_UnpackTuple(args, "ensure_local_capacity", 1, 1, &capacity))
        return NULL;
    if(!PyLong_Check(capacity)) {
        _PyArg_BadArgument("ensure_local_capacity", "argument", "int", capacity);
        return NULL;
    }
    jint result = JNIEnv_Env(self)->EnsureLocalCapacity(PyLong_AsLong(capacity));
    return PyBool_FromLong(result == 0);
}
static PyObject* PushLocalFrame(JNIEnvObject *self, PyObject *args) {
    PyObject *capacity;
    if (!PyArg_UnpackTuple(args, "push_local_frame", 1, 1, &capacity))
        return NULL;
    if (!PyLong_Check(capacity)) {
        _BadArgument("push_local_frame", "argument", "int", capacity);
        return NULL;
    }
    jint jcapacity = PyLong_AsLong(capacity);
    jint result = JNIEnv_Env(self)->PushLocalFrame(jcapacity);
    return PyLong_FromLong(result);
}
static jobjectObject* PopLocalFrame(JNIEnvObject *self, PyObject *args) {
    PyObject *result;
    if (!PyArg_UnpackTuple(args, "pop_local_frame", 1, 1, &result))
        return NULL;
    if (!jobject_Check(result)) {
        _BadArgument("pop_local_frame", "argument", "jobject", result);
        return NULL;
    }
    jobject result2 = JNIEnv_Env(self)->PopLocalFrame(jobject_Val(result));
    if (result2 == NULL)
        INC_RETURN_NONE(jobjectObject*);
    return jobject_FromValue(result2);
}

static jweakObject* NewWeakGlobalRef(JNIEnvObject *self, PyObject *args) {
    PyObject *obj;
    if (!PyArg_UnpackTuple(args, "new_weak_global_ref", 1, 1, &obj))
        return NULL;
    if (!jobject_Check(obj)) {
        _BadArgument("new_weak_global_ref", "argument", "jobject", obj);
        return NULL;
    }
    jweak result = JNIEnv_Env(self)->NewWeakGlobalRef(jobject_Val(self));
    if (result == NULL)
        INC_RETURN_NONE(jweakObject*);
    return jweak_FromValue(result);
}
static PyObject* DeleteWeakGlobalRef(JNIEnvObject *self, PyObject *args) {
    PyObject *ref;
    if (!PyArg_UnpackTuple(args, "delete_weak_global_ref", 1, 1, &ref))
        return NULL;
    if (!jweak_Check(ref)) {
        _BadArgument("delete_weak_global_ref", "argument", "jweak", ref);
        return NULL;
    }
    JNIEnv_Env(self)->DeleteWeakGlobalRef(jweak_Val(ref));
    Py_RETURN_NONE;
}

//TODO think the position of this function in the framework
static jvalue* jnilib_ConvertArgs(PyObject *args, const char *fname, int num, ...) {
    Py_ssize_t len = PyTuple_Size(args);
    if(len < num) {
        PyErr_Format(
            PyExc_TypeError,
            "%.200s expected at least %zd argument%s, got %zd",
            fname, num, num == 1 ? "" : "s", len);
        return NULL;
    }

    va_list vargs;
    va_start(vargs, num);
    for(int i=0; i<num; i++) {
        PyObject **arg = va_arg(vargs, PyObject**);
        *arg = PyTuple_GET_ITEM(args, i);
    }
    va_end(vargs);

    jvalue *jargs = (jvalue*)malloc((len-num) * sizeof(jvalue));
    if(jargs == NULL) {
        PyErr_SetString(PyExc_MemoryError, "Unable to allloc args for jni function");
        return NULL;
    }
    for(Py_ssize_t i=num; i<len; i++) {
        PyObject *item = PyTuple_GetItem(args, i);
        if(!jvalue_Check(item)) {
            PyErr_Format(
                PyExc_TypeError,
                "%.200s() arguments must be jvalue since arg %zd, but arg %zd got %.50s",
                fname, num+1, i, Py_TYPE(item)->tp_name);
            free(jargs);
            return NULL;
        }
        jargs[i-num] = jvalue_Val(item);
    }
    return jargs;
}
static jobjectObject* AllocObject(JNIEnvObject *self, PyObject *args) {
    PyObject *clazz;
    if(!PyArg_UnpackTuple(args, "alloc_object", 1, 1, &clazz))
        return NULL;
    if(!jclass_Check(clazz)) {
        _PyArg_BadArgument("alloc_object", "argument", "jclass", clazz);
        return NULL;
    }
    jobject result = JNIEnv_Env(self)->AllocObject(jclass_Val(clazz));
    if (result == NULL)
        INC_RETURN_NONE(jobjectObject*);
    return jobject_FromValue(result);
}
static jobjectObject* NewObject(JNIEnvObject *self, PyObject *args) {
    PyObject *clazz, *methodID;
    jvalue *jargs = jnilib_ConvertArgs(args, "new_object", 2, &clazz, &methodID);
    if(jargs == NULL)
        return NULL;
    if(!jclass_Check(clazz)) {
        _PyArg_BadArgument("new_object", "arg 1", "jclass", clazz);
        return NULL;
    }
    if(!jmethodID_Check(methodID)) {
        _PyArg_BadArgument("new_object", "arg 2", "jmethodID", methodID);
        return NULL;
    }
    jobject result = JNIEnv_Env(self)->NewObjectA(
            jclass_Val(clazz), jmethodID_Val(methodID), jargs);
    free(jargs);
    if (result == NULL)
        INC_RETURN_NONE(jobjectObject*);
    return jobject_FromValue(result);
}
static jclassObject* GetObjectClass(JNIEnvObject *self, PyObject *args) {
    PyObject *obj;
    if(!PyArg_UnpackTuple(args, "get_object_class", 1, 1, &obj))
        return NULL;
    if(!jobject_Check(obj)) {
        _PyArg_BadArgument("get_object_class", "argument", "jobject", obj);
        return NULL;
    }
    jclass result = JNIEnv_Env(self)->GetObjectClass(jobject_Val(obj));
    return jclass_FromValue(result);
}
static PyObject* GetObjectRefType(JNIEnvObject *self, PyObject *args) {
    PyObject *obj;
    if (!PyArg_UnpackTuple(args, "get_object_ref_type", 1, 1, &obj))
        return NULL;
    if (!jobject_Check(obj)) {
        _BadArgument("get_object_reft_type", "argument", "jobject", obj);
        return NULL;
    }
    jobjectRefType result = JNIEnv_Env(self)->GetObjectRefType(jobject_Val(obj));
    return PyLong_FromLong(result);
}
static PyObject* IsInstanceOf(JNIEnvObject *self, PyObject *args) {
    PyObject *obj, *clazz;
    if(!PyArg_UnpackTuple(args, "is_instance_of", 2, 2, &obj, &clazz))
        return NULL;
    if(!jobject_Check(obj)) {
        _PyArg_BadArgument("is_instance_of", "arg 1", "jobject", obj);
        return NULL;
    }
    if(!jclass_Check(clazz)) {
        _PyArg_BadArgument("is_instance_of", "arg 2", "jclass", clazz);
        return NULL;
    }
    jboolean result = JNIEnv_Env(self)->IsInstanceOf(jobject_Val(obj), jclass_Val(clazz));
    return PyBool_FromLong(result);
}
static PyObject* IsSameObject(JNIEnvObject *self, PyObject *args) {
    PyObject *obj1, *obj2;
    if(!PyArg_UnpackTuple(args, "is_same_object", 2, 2, &obj1, &obj2))
        return NULL;
    if(!jobject_Check(obj1)) {
        _PyArg_BadArgument("is_same_object", "arg 1", "jobject", obj1);
        return NULL;
    }
    if(!jobject_Check(obj2)) {
        _PyArg_BadArgument("is_same_object", "arg 2", "jobject", obj2);
        return NULL;
    }
    jboolean result = JNIEnv_Env(self)->IsSameObject(jobject_Val(obj1), jobject_Val(obj2));
    return PyBool_FromLong(result);
}

static jfieldIDObject* GetFieldID(JNIEnvObject *self, PyObject *args) {
    PyObject *clazz, *name, *sig;
    if(!PyArg_UnpackTuple(args, "get_field_id", 3, 3, &clazz, &name, &sig))
        return NULL;
    if(!jclass_Check(clazz)) {
        _PyArg_BadArgument("get_field_id", "arg 1", "jclass", clazz);
        return NULL;
    }
    if(!PyUnicode_Check(name)) {
        _PyArg_BadArgument("get_field_id", "arg 2", "str", name);
        return NULL;
    }
    if(!PyUnicode_Check(sig)) {
        _PyArg_BadArgument("get_field_id", "arg 3", "str", sig);
        return NULL;
    }
    jfieldID result = JNIEnv_Env(self)->GetFieldID(
            jclass_Val(clazz), PyUnicode_AsUTF8(name), PyUnicode_AsUTF8(sig));
    if (result == NULL)
        INC_RETURN_NONE(jfieldIDObject*);
    return jfieldID_FromValue(result, PyUnicode_AsUTF8(sig));
}
static jvalueObject* GetField(JNIEnvObject *self, PyObject *args) {
    PyObject *obj, *fieldID;
    if (!PyArg_UnpackTuple(args, "get_field", 2, 2, &obj, &fieldID))
        return NULL;
    if (!jobject_Check(obj)) {
        _BadArgument("get_field", "arg 1", "jobject", obj);
        return NULL;
    }
    if (!jfieldID_Check(fieldID)) {
        _BadArgument("get_field", "arg 2", "jfieldID", fieldID);
        return NULL;
    }
    const char *sig = jfieldID_Sig(fieldID);
    switch (sig[0]) {
        case 'Z': {
            jboolean result = JNIEnv_Env(self)->GetBooleanField(
                    jobject_Val(obj), jfieldID_Val(fieldID));
            return jboolean_FromValue(result);
        }
        case 'B': {
            jbyte result = JNIEnv_Env(self)->GetByteField(
                    jobject_Val(obj), jfieldID_Val(fieldID));
            return jbyte_FromValue(result);
        }
        case 'C': {
            jchar result = JNIEnv_Env(self)->GetCharField(
                    jobject_Val(obj), jfieldID_Val(fieldID));
            return jchar_FromValue(result);
        }
        case 'S': {
            jshort result = JNIEnv_Env(self)->GetShortField(
                    jobject_Val(obj), jfieldID_Val(fieldID));
            return jshort_FromValue(result);
        }
        case 'I': {
            jint result = JNIEnv_Env(self)->GetIntField(
                    jobject_Val(obj), jfieldID_Val(fieldID));
            return jint_FromValue(result);
        }
        case 'J': {
            jlong result = JNIEnv_Env(self)->GetLongField(
                    jobject_Val(obj), jfieldID_Val(fieldID));
            return jlong_FromValue(result);
        }
        case 'F': {
            jfloat result = JNIEnv_Env(self)->GetFloatField(
                    jobject_Val(obj), jfieldID_Val(fieldID));
            return jfloat_FromValue(result);
        }
        case 'D': {
            jdouble result = JNIEnv_Env(self)->GetDoubleField(
                    jobject_Val(obj), jfieldID_Val(fieldID));
            return jdouble_FromValue(result);
        }
        case 'L': {
            jobject result = JNIEnv_Env(self)->GetObjectField(
                    jobject_Val(obj), jfieldID_Val(fieldID));
            if (result == NULL)
                INC_RETURN_NONE(jvalueObject*);
            return jobject_FromValue(result);
        }
        case '[': {
            //TODO implement
        }
        default:
            PyErr_Format(PyExc_TypeError, "Unknown type of this jfieldID: %.50s", sig);
            return NULL;
    }
}
static PyObject* SetField(JNIEnvObject *self, PyObject *args) {
    PyObject *obj, *fieldID, *value;
    if (!PyArg_UnpackTuple(args, "set_field", 3, 3, &obj, &fieldID, &value))
        return NULL;
    if (!jobject_Check(obj)) {
        _BadArgument("set_field", "arg 1", "jobject", obj);
        return NULL;
    }
    if (!jfieldID_Check(fieldID)) {
        _BadArgument("set_field", "arg 2", "jfieldID", fieldID);
        return NULL;
    }
    if (!jvalue_Check(value)) {
        _BadArgument("set_field", "arg 3", "jvalue", value);
        return NULL;
    }
    const char *sig = jfieldID_Sig(fieldID);
    switch (sig[0]) {
        case 'Z':
            JNIEnv_Env(self)->SetBooleanField(
                jobject_Val(obj), jfieldID_Val(fieldID), jboolean_Val(value));
            Py_RETURN_NONE;
        case 'B':
            JNIEnv_Env(self)->SetByteField(
                jobject_Val(obj), jfieldID_Val(fieldID), jbyte_Val(value));
            Py_RETURN_NONE;
        case 'C':
            JNIEnv_Env(self)->SetCharField(
                jobject_Val(obj), jfieldID_Val(fieldID), jchar_Val(value));
            Py_RETURN_NONE;
        case 'S':
            JNIEnv_Env(self)->SetShortField(
                jobject_Val(obj), jfieldID_Val(fieldID), jshort_Val(value));
            Py_RETURN_NONE;
        case 'I':
            JNIEnv_Env(self)->SetIntField(
                jobject_Val(obj), jfieldID_Val(fieldID), jint_Val(value));
            Py_RETURN_NONE;
        case 'J':
            JNIEnv_Env(self)->SetLongField(
                jobject_Val(obj), jfieldID_Val(fieldID), jlong_Val(value));
            Py_RETURN_NONE;
        case 'F':
            JNIEnv_Env(self)->SetFloatField(
                jobject_Val(obj), jfieldID_Val(fieldID), jfloat_Val(value));
            Py_RETURN_NONE;
        case 'D':
            JNIEnv_Env(self)->SetDoubleField(
                jobject_Val(obj), jfieldID_Val(fieldID), jdouble_Val(value));
            Py_RETURN_NONE;
        case 'L':
            JNIEnv_Env(self)->SetObjectField(
                jobject_Val(obj), jfieldID_Val(fieldID), jobject_Val(value));
            Py_RETURN_NONE;
        case '[':
            //TODO implement
        default:
            PyErr_Format(PyExc_TypeError, "Unknown type of this jfieldID: %.50s", sig);
            return NULL;
    }
}
static jfieldIDObject* GetStaticFieldID(JNIEnvObject *self, PyObject *args) {
    PyObject *clazz, *name, *sig;
    if (!PyArg_UnpackTuple(args, "get_static_field_id", 3, 3, &clazz, &name, &sig))
        return NULL;
    if (!jclass_Check(clazz)) {
        _BadArgument("get_static_field_id", "arg 1", "jclass", clazz);
        return NULL;
    }
    if (!PyUnicode_Check(name)) {
        _BadArgument("get_static_field_id", "arg 2", "str", name);
        return NULL;
    }
    if (!PyUnicode_Check(sig)) {
        _BadArgument("get_static_field_id", "arg 3", "str", sig);
        return NULL;
    }
    jfieldID result = JNIEnv_Env(self)->GetStaticFieldID(
            jclass_Val(clazz), PyUnicode_AsUTF8(name), PyUnicode_AsUTF8(sig));
    if (result == NULL)
        INC_RETURN_NONE(jfieldIDObject*);
    return jfieldID_FromValue(result, PyUnicode_AsUTF8(sig));
}
static jvalueObject* GetStaticField(JNIEnvObject *self, PyObject *args) {
    PyObject *clazz, *fieldID;
    if (!PyArg_UnpackTuple(args, "get_field", 2, 2, &clazz, &fieldID))
        return NULL;
    if (!jclass_Check(clazz)) {
        _BadArgument("get_field", "arg 1", "jclass", clazz);
        return NULL;
    }
    if (!jfieldID_Check(fieldID)) {
        _BadArgument("get_field", "arg 2", "jfieldID", fieldID);
        return NULL;
    }
    const char *sig = jfieldID_Sig(fieldID);
    switch (sig[0]) {
        case 'Z': {
            jboolean result = JNIEnv_Env(self)->GetStaticBooleanField(
                    jclass_Val(clazz), jfieldID_Val(fieldID));
            return jboolean_FromValue(result);
        }
        case 'B': {
            jbyte result = JNIEnv_Env(self)->GetStaticByteField(
                    jclass_Val(clazz), jfieldID_Val(fieldID));
            return jbyte_FromValue(result);
        }
        case 'C': {
            jchar result = JNIEnv_Env(self)->GetStaticCharField(
                    jclass_Val(clazz), jfieldID_Val(fieldID));
            return jchar_FromValue(result);
        }
        case 'S': {
            jshort result = JNIEnv_Env(self)->GetStaticShortField(
                    jclass_Val(clazz), jfieldID_Val(fieldID));
            return jshort_FromValue(result);
        }
        case 'I': {
            jint result = JNIEnv_Env(self)->GetStaticIntField(
                    jclass_Val(clazz), jfieldID_Val(fieldID));
            return jint_FromValue(result);
        }
        case 'J': {
            jlong result = JNIEnv_Env(self)->GetStaticLongField(
                    jclass_Val(clazz), jfieldID_Val(fieldID));
            return jlong_FromValue(result);
        }
        case 'F': {
            jfloat result = JNIEnv_Env(self)->GetStaticFloatField(
                    jclass_Val(clazz), jfieldID_Val(fieldID));
            return jfloat_FromValue(result);
        }
        case 'D': {
            jdouble result = JNIEnv_Env(self)->GetStaticDoubleField(
                    jclass_Val(clazz), jfieldID_Val(fieldID));
            return jdouble_FromValue(result);
        }
        case 'L': {
            jobject result = JNIEnv_Env(self)->GetStaticObjectField(
                    jclass_Val(clazz), jfieldID_Val(fieldID));
            if (result == NULL)
                INC_RETURN_NONE(jvalueObject*);
            return jobject_FromValue(result);
        }
        case '[': {
            //TODO implement
        }
        default:
            PyErr_Format(PyExc_TypeError, "Unknown type of this jfieldID: %.50s", sig);
            return NULL;
    }
}
static PyObject* SetStaticField(JNIEnvObject *self, PyObject *args) {
    PyObject *clazz, *fieldID, *value;
    if (!PyArg_UnpackTuple(args, "set_static_field", 3, 3, &clazz, &fieldID, &value))
        return NULL;
    if (!jclass_Check(clazz)) {
        _BadArgument("set_static_field", "arg 1", "jclass", clazz);
        return NULL;
    }
    if (!jfieldID_Check(fieldID)) {
        _BadArgument("set_static_field", "arg 2", "jfieldID", fieldID);
        return NULL;
    }
    if (!jvalue_Check(value)) {
        _BadArgument("set_static_field", "arg 3", "jvalue", value);
        return NULL;
    }
    const char *sig = jfieldID_Sig(fieldID);
    switch (sig[0]) {
        case 'Z':
            JNIEnv_Env(self)->SetStaticBooleanField(
                jclass_Val(clazz), jfieldID_Val(fieldID), jboolean_Val(value));
            Py_RETURN_NONE;
        case 'B':
            JNIEnv_Env(self)->SetStaticByteField(
                jclass_Val(clazz), jfieldID_Val(fieldID), jbyte_Val(value));
            Py_RETURN_NONE;
        case 'C':
            JNIEnv_Env(self)->SetStaticCharField(
                jclass_Val(clazz), jfieldID_Val(fieldID), jchar_Val(value));
            Py_RETURN_NONE;
        case 'S':
            JNIEnv_Env(self)->SetStaticShortField(
                jclass_Val(clazz), jfieldID_Val(fieldID), jshort_Val(value));
            Py_RETURN_NONE;
        case 'I':
            JNIEnv_Env(self)->SetStaticIntField(
                jclass_Val(clazz), jfieldID_Val(fieldID), jint_Val(value));
            Py_RETURN_NONE;
        case 'J':
            JNIEnv_Env(self)->SetStaticLongField(
                jclass_Val(clazz), jfieldID_Val(fieldID), jlong_Val(value));
            Py_RETURN_NONE;
        case 'F':
            JNIEnv_Env(self)->SetStaticFloatField(
                jclass_Val(clazz), jfieldID_Val(fieldID), jfloat_Val(value));
            Py_RETURN_NONE;
        case 'D':
            JNIEnv_Env(self)->SetStaticDoubleField(
                jclass_Val(clazz), jfieldID_Val(fieldID), jdouble_Val(value));
            Py_RETURN_NONE;
        case 'L':
            JNIEnv_Env(self)->SetStaticObjectField(
                jclass_Val(clazz), jfieldID_Val(fieldID), jobject_Val(value));
            Py_RETURN_NONE;
        case '[':
            //TODO implement
        default:
            PyErr_Format(PyExc_TypeError, "Unknown type of this jfieldID: %.50s", sig);
            return NULL;
    }
}

static jmethodIDObject* GetMethodID(JNIEnvObject *self, PyObject *args) {
    PyObject *clazz, *name, *sig;
    if(!PyArg_UnpackTuple(args, "get_method_id", 3, 3, &clazz, &name, &sig))
        return NULL;
    if(!jclass_Check(clazz)) {
        _PyArg_BadArgument("get_method_id", "arg 1", "jclass", clazz);
        return NULL;
    }
    if(!PyUnicode_Check(name)) {
        _PyArg_BadArgument("get_method_id", "arg 2", "str", name);
        return NULL;
    }
    if(!PyUnicode_Check(sig)) {
        _PyArg_BadArgument("get_method_id", "arg 3", "str", sig);
        return NULL;
    }
    jmethodID result = JNIEnv_Env(self)->GetMethodID(
            jclass_Val(clazz), PyUnicode_AsUTF8(name), PyUnicode_AsUTF8(sig));
    if (result == NULL)
        INC_RETURN_NONE(jmethodIDObject*);
    return jmethodID_FromValue(result, PyUnicode_AsUTF8(sig));
}
static jvalueObject* CallMethod(JNIEnvObject *self, PyObject *args) {
    PyObject *obj, *methodID;
    jvalue *jargs = jnilib_ConvertArgs(args, "call_method", 2, &obj, &methodID);
    if (jargs == NULL)
        return NULL;
    if (!jobject_Check(obj)) {
        _BadArgument("call_method", "arg 1", "jobject", obj);
        return NULL;
    }
    if (!jmethodID_Check(methodID)) {
        _BadArgument("call_method", "arg 2", "jmethodID", methodID);
        return NULL;
    }
    jvalueObject *ret;
    const char *sig = jmethodID_RetSig(methodID);
    switch (sig[0]) {
        case 'Z': {
            jboolean result = JNIEnv_Env(self)->CallBooleanMethod(
                    jobject_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jboolean_FromValue(result);
            break;
        }
        case 'B': {
            jbyte result = JNIEnv_Env(self)->CallByteMethod(
                    jobject_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jbyte_FromValue(result);
            break;
        }
        case 'C': {
            jchar result = JNIEnv_Env(self)->CallCharMethod(
                    jobject_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jchar_FromValue(result);
            break;
        }
        case 'S': {
            jshort result = JNIEnv_Env(self)->CallShortMethod(
                    jobject_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jshort_FromValue(result);
            break;
        }
        case 'I': {
            jint result = JNIEnv_Env(self)->CallIntMethod(
                    jobject_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jint_FromValue(result);
            break;
        }
        case 'J': {
            jlong result = JNIEnv_Env(self)->CallLongMethod(
                    jobject_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jlong_FromValue(result);
            break;
        }
        case 'F': {
            jfloat result = JNIEnv_Env(self)->CallFloatMethod(
                    jobject_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jfloat_FromValue(result);
            break;
        }
        case 'D': {
            jdouble result = JNIEnv_Env(self)->CallDoubleMethod(
                    jobject_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jdouble_FromValue(result);
            break;
        }
        case 'L': {
            jobject result = JNIEnv_Env(self)->CallObjectMethod(
                    jobject_Val(obj), jmethodID_Val(methodID), jargs);
            if (result == NULL)
                INC_RETURN_NONE(jvalueObject*);

            if (strcmp(sig, "Ljava/lang/String;") == 0)
                ret = jstring_FromValue((jstring)result);
            else
                ret = jobject_FromValue(result);
            break;
        }
        case '[': {
            //TODO implement
        }
        default:
            PyErr_Format(PyExc_TypeError, "Unknown type of this jfieldID: %.50s", sig);
            return NULL;
    }
    free(jargs);
    return ret;
}
static jvalueObject* CallNonvirtualMethod(JNIEnvObject *self, PyObject *args) {
    PyObject *obj, *clazz, *methodID;
    jvalue *jargs = jnilib_ConvertArgs(args, "call_nonvirtual_method", 3, &obj, &clazz, &methodID);
    if (jargs == NULL)
        return NULL;
    if (!jobject_Check(obj)) {
        _BadArgument("call_nonvirtual_method", "arg 1", "jobject", obj);
        return NULL;
    }
    if (!jclass_Check(clazz)) {
        _BadArgument("call_nonvirtual_method", "arg 2", "jclass", clazz);
        return NULL;
    }
    if (!jmethodID_Check(methodID)) {
        _BadArgument("call_nonvirtual_method", "arg 3", "jmethodID", methodID);
        return NULL;
    }
    jvalueObject *ret;
    const char *sig = jmethodID_RetSig(methodID);
    switch (sig[0]) {
        case 'Z': {
            jboolean result = JNIEnv_Env(self)->CallNonvirtualBooleanMethod(
                    jobject_Val(obj), jclass_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jboolean_FromValue(result);
            break;
        }
        case 'B': {
            jbyte result = JNIEnv_Env(self)->CallNonvirtualByteMethod(
                    jobject_Val(obj), jclass_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jbyte_FromValue(result);
            break;
        }
        case 'C': {
            jchar result = JNIEnv_Env(self)->CallNonvirtualCharMethod(
                    jobject_Val(obj), jclass_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jchar_FromValue(result);
            break;
        }
        case 'S': {
            jshort result = JNIEnv_Env(self)->CallNonvirtualShortMethod(
                    jobject_Val(obj), jclass_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jshort_FromValue(result);
            break;
        }
        case 'I': {
            jint result = JNIEnv_Env(self)->CallNonvirtualIntMethod(
                    jobject_Val(obj), jclass_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jint_FromValue(result);
            break;
        }
        case 'J': {
            jlong result = JNIEnv_Env(self)->CallNonvirtualLongMethod(
                    jobject_Val(obj), jclass_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jlong_FromValue(result);
            break;
        }
        case 'F': {
            jfloat result = JNIEnv_Env(self)->CallNonvirtualFloatMethod(
                    jobject_Val(obj), jclass_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jfloat_FromValue(result);
            break;
        }
        case 'D': {
            jdouble result = JNIEnv_Env(self)->CallNonvirtualDoubleMethod(
                    jobject_Val(obj), jclass_Val(obj), jmethodID_Val(methodID), jargs);
            ret = jdouble_FromValue(result);
            break;
        }
        case 'L': {
            jobject result = JNIEnv_Env(self)->CallNonvirtualObjectMethod(
                    jobject_Val(obj), jclass_Val(obj), jmethodID_Val(methodID), jargs);
            if (result == NULL)
                INC_RETURN_NONE(jvalueObject*);

            if (strcmp(sig, "Ljava/lang/String;") == 0)
                ret = jstring_FromValue((jstring)result);
            else
                ret = jobject_FromValue(result);
            break;
        }
        case '[': {
            //TODO implement
        }
        default:
            PyErr_Format(PyExc_TypeError, "Unknown type of this jfieldID: %.50s", sig);
            return NULL;
    }
    free(jargs);
    return ret;
}
static jmethodIDObject* GetStaticMethodID(JNIEnvObject *self, PyObject *args) {
    PyObject *clazz, *name, *sig;
    if (!PyArg_UnpackTuple(args, "get_static_method_id", 3, 3, &clazz, &name, &sig))
        return NULL;
    if(!jclass_Check(clazz)) {
        _PyArg_BadArgument("get_static_method_id", "arg 1", "jclass", clazz);
        return NULL;
    }
    if(!PyUnicode_Check(name)) {
        _PyArg_BadArgument("get_static_method_id", "arg 2", "str", name);
        return NULL;
    }
    if(!PyUnicode_Check(sig)) {
        _PyArg_BadArgument("get_static_method_id", "arg 3", "str", sig);
        return NULL;
    }
    jmethodID result = JNIEnv_Env(self)->GetStaticMethodID(
            jclass_Val(clazz), PyUnicode_AsUTF8(name), PyUnicode_AsUTF8(sig));
    if (result == NULL)
        INC_RETURN_NONE(jmethodIDObject*);
    return jmethodID_FromValue(result, PyUnicode_AsUTF8(sig));
}
static jvalueObject* CallStaticMethod(JNIEnvObject *self, PyObject *args) {
    PyObject *clazz, *methodID;
    jvalue *jargs = jnilib_ConvertArgs(args, "call_static_method", 2, &clazz, &methodID);
    if (jargs == NULL)
        return NULL;
    if (!jclass_Check(clazz)) {
        _BadArgument("call_static_method", "arg 1", "jclass", clazz);
        return NULL;
    }
    if (!jmethodID_Check(methodID)) {
        _BadArgument("call_static_method", "arg 2", "jmethodID", methodID);
        return NULL;
    }
    jvalueObject *ret;
    const char *sig = jmethodID_RetSig(methodID);
    switch (sig[0]) {
        case 'Z': {
            jboolean result = JNIEnv_Env(self)->CallStaticBooleanMethod(
                    jclass_Val(clazz), jmethodID_Val(methodID), jargs);
            ret = jboolean_FromValue(result);
            break;
        }
        case 'B': {
            jbyte result = JNIEnv_Env(self)->CallStaticByteMethod(
                    jclass_Val(clazz), jmethodID_Val(methodID), jargs);
            ret = jbyte_FromValue(result);
            break;
        }
        case 'C': {
            jchar result = JNIEnv_Env(self)->CallStaticCharMethod(
                    jclass_Val(clazz), jmethodID_Val(methodID), jargs);
            ret = jchar_FromValue(result);
            break;
        }
        case 'S': {
            jshort result = JNIEnv_Env(self)->CallStaticShortMethod(
                    jclass_Val(clazz), jmethodID_Val(methodID), jargs);
            ret = jshort_FromValue(result);
            break;
        }
        case 'I': {
            jint result = JNIEnv_Env(self)->CallStaticIntMethod(
                    jclass_Val(clazz), jmethodID_Val(methodID), jargs);
            ret = jint_FromValue(result);
            break;
        }
        case 'J': {
            jlong result = JNIEnv_Env(self)->CallStaticLongMethod(
                    jclass_Val(clazz), jmethodID_Val(methodID), jargs);
            ret = jlong_FromValue(result);
            break;
        }
        case 'F': {
            jfloat result = JNIEnv_Env(self)->CallStaticFloatMethod(
                    jclass_Val(clazz), jmethodID_Val(methodID), jargs);
            ret = jfloat_FromValue(result);
            break;
        }
        case 'D': {
            jdouble result = JNIEnv_Env(self)->CallStaticDoubleMethod(
                    jclass_Val(clazz), jmethodID_Val(methodID), jargs);
            ret = jdouble_FromValue(result);
            break;
        }
        case 'L': {
            jobject result = JNIEnv_Env(self)->CallStaticObjectMethod(
                    jclass_Val(clazz), jmethodID_Val(methodID), jargs);
            if (result == NULL)
                INC_RETURN_NONE(jvalueObject*);

            if (strcmp(sig, "Ljava/lang/String;") == 0)
                ret = jstring_FromValue((jstring)result);
            else
                ret = jobject_FromValue(result);
            break;
        }
        case '[': {
            //TODO implement
        }
        default:
            PyErr_Format(PyExc_TypeError, "Unknown type of this jfieldID: %.50s", sig);
            return NULL;
    }
    free(jargs);
    return ret;
}

static jstringObject* NewString(JNIEnvObject *self, PyObject *args) {
    PyObject *utf;
    if (!PyArg_UnpackTuple(args, "new_string", 1, 1, &utf))
        return NULL;
    if (!PyUnicode_Check(utf)) {
        _BadArgument("new_string", "argument", "str", utf);
        return NULL;
    }
    jstring result = JNIEnv_Env(self)->NewStringUTF(PyUnicode_AsUTF8(utf));
    return jstring_FromValue(result);
}
static PyObject* GetString(JNIEnvObject *self, PyObject *args) {
    PyObject *str;
    if (!PyArg_UnpackTuple(args, "get_string", 1, 1, &str))
        return NULL;
    if (!jstring_Check(str)) {
        _BadArgument("get_string", "argument", "jstring", str);
        return NULL;
    }
    const char *result = JNIEnv_Env(self)->GetStringUTFChars(jstring_Val(str), NULL);
    PyObject *ret = PyUnicode_FromString(result);
    JNIEnv_Env(self)->ReleaseStringUTFChars(jstring_Val(str), result);
    return ret;
}
static PyObject* GetStringRegion(JNIEnvObject *self, PyObject *args) {
    PyObject *str, *start, *len;
    if (!PyArg_UnpackTuple(args, "get_string_region", 3, 3, &str, &start, &len))
        return NULL;
    if (!jstring_Check(str)) {
        _BadArgument("get_string_region", "arg 1", "jstring", str);
        return NULL;
    }
    if (!PyLong_Check(start)) {
        _BadArgument("get_string_region", "arg 2", "int", start);
        return NULL;
    }
    if (!PyLong_Check(len)) {
        _BadArgument("get_string_region", "arg 3", "int", len);
        return NULL;
    }
    long jlen = PyLong_AsLong(len);
    char *buf = (char*)malloc(jlen * sizeof(char));
    JNIEnv_Env(self)->GetStringUTFRegion(jstring_Val(str), PyLong_AsLong(start), jlen, buf);
    PyObject *ret = PyUnicode_FromString(buf);
    free(buf);
    return ret;
}

static jarrayObject* NewArray(JNIEnvObject *self, PyObject *args) {
    PyObject *length;
    PyTypeObject *type;
    if (!PyArg_UnpackTuple(args, "new_array", 2, 2, &type, &length))
        return NULL;
    if (!PyType_Check(type) || PyType_IsSubtype(type, &jvalue_Type)) {
        _BadArgument("new_array", "arg 1", "type", (PyObject*)type);
        return NULL;
    }
    if (!PyLong_Check(length)) {
        _BadArgument("new_array", "arg 2", "int", length);
        return NULL;
    }
    jarray result;
    jsize len = PyLong_AsLong(length);
    if (type == &jboolean_Type) {
        result = JNIEnv_Env(self)->NewBooleanArray(len);
    } else if (type == &jbyte_Type) {
        result = JNIEnv_Env(self)->NewByteArray(len);
    } else if (type == &jchar_Type) {
        result = JNIEnv_Env(self)->NewCharArray(len);
    } else if (type == &jshort_Type) {
        result = JNIEnv_Env(self)->NewShortArray(len);
    } else if (type == &jint_Type) {
        result = JNIEnv_Env(self)->NewIntArray(len);
    } else if (type == &jlong_Type) {
        result = JNIEnv_Env(self)->NewLongArray(len);
    } else if (type == &jfloat_Type) {
        result = JNIEnv_Env(self)->NewFloatArray(len);
    } else if (type == &jdouble_Type) {
        result = JNIEnv_Env(self)->NewDoubleArray(len);
    } else if (PyType_IsSubtype(type, &jobject_Type)) {
        PyErr_SetString(PyExc_TypeError, "This function does not support jobject, please use new_object_array");
        return NULL;
    } else {
        PyErr_Format(PyExc_TypeError, "Unknown type: %.50s", type->tp_name);
        return NULL;
    }
    if (result == NULL)
        INC_RETURN_NONE(jarrayObject*);
    return jarray_FromValue(result, type);
}
static jarrayObject* NewObjectArray(JNIEnvObject *self, PyObject *args) {
    PyObject *len, *clazz, *init;
    if (!PyArg_UnpackTuple(args, "new_object_array", 3, 3, &len, &clazz, &init))
        return NULL;
    if (!PyLong_Check(len)) {
        _BadArgument("new_object_array", "arg 1", "int", len);
        return NULL;
    }
    if (!jclass_Check(clazz)) {
        _BadArgument("new_object_array", "arg 2", "jclass", clazz);
        return NULL;
    }
    if (!jobject_Check(init)) {
        _BadArgument("new_object_array", "arg 3", "jobject", init);
        return NULL;
    }
    jobjectArray result = JNIEnv_Env(self)->NewObjectArray(
            PyLong_AsLong(len), jclass_Val(clazz), jobject_Val(init));
    return jobjectArray_FromValue(result);
}
static inline PyObject* array_from_data(const char *type, void *data, jsize length) {
    PyObject *module_array = PyImport_ImportModule("array");
    if (module_array == NULL)
        return NULL;
    PyObject *buffer = PyBytes_FromStringAndSize((char*)data, length);
    if (buffer == NULL)
        return NULL;
    PyObject *array = PyObject_CallMethod(module_array, "sO", type, buffer);
    Py_DECREF(buffer);
    Py_DECREF(module_array);
    return array;
}
static PyObject* GetArrayElements(JNIEnvObject *self, PyObject *args) {
    PyObject *array;
    if (!PyArg_UnpackTuple(args, "get_array_elements", 1, 1, &array))
        return NULL;
    if (!jarray_Check(array)) {
        _BadArgument("get_array_elements", "argument", "jarray", array);
        return NULL;
    }
    PyObject *ret = NULL;
    PyTypeObject *type = jarray_Type(array);
    jsize length = JNIEnv_Env(self)->GetArrayLength(jarray_Val(array));
    if (type == &jboolean_Type) {
        jboolean *result = JNIEnv_Env(self)->GetBooleanArrayElements(jbooleanArray_Val(array), NULL);
        ret = array_from_data("Z", result, length);
        JNIEnv_Env(self)->ReleaseBooleanArrayElements(jbooleanArray_Val(array), result, JNI_ABORT);
    } else if (type == &jbyte_Type) {
        jbyte *result = JNIEnv_Env(self)->GetByteArrayElements(jbyteArray_Val(array), NULL);
        ret = array_from_data("B", result, length);
        JNIEnv_Env(self)->ReleaseByteArrayElements(jbyteArray_Val(array), result, JNI_ABORT);
    } else if (type == &jchar_Type) {
        jchar *result = JNIEnv_Env(self)->GetCharArrayElements(jcharArray_Val(array), NULL);
        ret = array_from_data("C", result, length);
        JNIEnv_Env(self)->ReleaseCharArrayElements(jcharArray_Val(array), result, JNI_ABORT);
    } else if (type == &jshort_Type) {
        jshort *result = JNIEnv_Env(self)->GetShortArrayElements(jshortArray_Val(array), NULL);
        ret = array_from_data("S", result, length);
        JNIEnv_Env(self)->ReleaseShortArrayElements(jshortArray_Val(array), result, JNI_ABORT);
    } else if (type == &jint_Type) {
        jint *result = JNIEnv_Env(self)->GetIntArrayElements(jintArray_Val(array), NULL);
        ret = array_from_data("I", result, length);
        JNIEnv_Env(self)->ReleaseIntArrayElements(jintArray_Val(array), result, JNI_ABORT);
    } else if (type == &jlong_Type) {
        jlong *result = JNIEnv_Env(self)->GetLongArrayElements(jlongArray_Val(array), NULL);
        ret = array_from_data("J", result, length);
        JNIEnv_Env(self)->ReleaseLongArrayElements(jlongArray_Val(array), result, JNI_ABORT);
    } else if (type == &jfloat_Type) {
        jfloat *result = JNIEnv_Env(self)->GetFloatArrayElements(jfloatArray_Val(array), NULL);
        ret = array_from_data("F", result, length);
        JNIEnv_Env(self)->ReleaseFloatArrayElements(jfloatArray_Val(array), result, JNI_ABORT);
    } else if (type == &jdouble_Type) {
        jdouble *result = JNIEnv_Env(self)->GetDoubleArrayElements(jdoubleArray_Val(array), NULL);
        ret = array_from_data("D", result, length);
        JNIEnv_Env(self)->ReleaseDoubleArrayElements(jdoubleArray_Val(array), result, JNI_ABORT);
    } else if (PyType_IsSubtype(type, &jobject_Type)) {
        PyErr_SetString(PyExc_TypeError, "This function does not support jobject, please use get_object_array_element");
    } else {
        PyErr_Format(PyExc_TypeError, "Unknown type: %.50s", type->tp_name);
    }
    return ret;
}
static jobjectObject* GetObjectArrayElement(JNIEnvObject *self, PyObject *args) {
    PyObject *array, *index;
    if (!PyArg_UnpackTuple(args, "get_object_array_element", 2, 2, &array, &index))
        return NULL;
    if (!jobjectArray_Check(array)) {
        _BadArgument("get_object_array_element", "arg 1", "jobjectArray", array);
        return NULL;
    }
    if (!PyLong_Check(index)) {
        _BadArgument("get_object_array_element", "arg 2", "int", index);
        return NULL;
    }
    jobject result = JNIEnv_Env(self)->GetObjectArrayElement(
            jobjectArray_Val(array), PyLong_AsLong(index));
    return jobject_FromValue(result);
}
static inline bool pyarray_Check(PyObject *x) {
    PyObject *module_array = PyImport_ImportModule("array");
    if (module_array == NULL)
        return false;
    PyObject *dict = PyModule_GetDict(module_array);
    if (dict == NULL)
        return false;
    PyTypeObject *array_Type = (PyTypeObject*)PyDict_GetItemString(dict, "array");
    if (array_Type == NULL)
        return false;
    Py_DECREF(module_array);
    return PyType_IsSubtype(Py_TYPE(x), array_Type);
}
static inline void* pyarray_Buffer(PyObject *x) {
    return PyObject_CallMethod(x, "tobytes", "");
}
static PyObject* SetArrayElements(JNIEnvObject *self, PyObject *args) {
    PyObject *jarray_obj, *array;
    if (!PyArg_UnpackTuple(args, "set_array_elements", 2, 2, &jarray_obj, &array))
        return NULL;
    if (!jarray_Check(jarray_obj)) {
        _BadArgument("set_array_elements", "arg 1", "jarray", jarray_obj);
        return NULL;
    }
    if (!pyarray_Check(array)) {
        _BadArgument("set_array_elements", "arg 2", "array", array);
        return NULL;
    }
    void *buf = pyarray_Buffer(array);
    PyTypeObject *type = jarray_Type(array);
    jsize length = JNIEnv_Env(self)->GetArrayLength(jarray_Val(jarray_obj));
    if (type == &jboolean_Type) {
        JNIEnv_Env(self)->SetBooleanArrayRegion(
                    jbooleanArray_Val(array), 0, length, (jboolean*)pyarray_Buffer(array));
    } else if (type == &jbyte_Type) {
        JNIEnv_Env(self)->SetByteArrayRegion(
                    jbyteArray_Val(array), 0, length, (jbyte*)pyarray_Buffer(array));
    } else if (type == &jchar_Type) {
        JNIEnv_Env(self)->SetCharArrayRegion(
                    jcharArray_Val(array), 0, length, (jchar*)pyarray_Buffer(array));
    } else if (type == &jshort_Type) {
        JNIEnv_Env(self)->SetShortArrayRegion(
                    jshortArray_Val(array), 0, length, (jshort*)pyarray_Buffer(array));
    } else if (type == &jint_Type) {
        JNIEnv_Env(self)->SetIntArrayRegion(
                    jintArray_Val(array), 0, length, (jint*)pyarray_Buffer(array));
    } else if (type == &jlong_Type) {
        JNIEnv_Env(self)->SetLongArrayRegion(
                    jlongArray_Val(array), 0, length, (jlong*)pyarray_Buffer(array));
    } else if (type == &jfloat_Type) {
        JNIEnv_Env(self)->SetFloatArrayRegion(
                    jfloatArray_Val(array), 0, length, (jfloat*)pyarray_Buffer(array));
    } else if (type == &jdouble_Type) {
        JNIEnv_Env(self)->SetDoubleArrayRegion(
                    jdoubleArray_Val(array), 0, length, (jdouble*)pyarray_Buffer(array));
    } else if (PyType_IsSubtype(type, &jobject_Type)) {
        PyErr_SetString(PyExc_TypeError, "This function does not support jobject, please use get_object_array_element");
        return NULL;
    } else {
        PyErr_Format(PyExc_TypeError, "Unknown type: %.50s", type->tp_name);
        return NULL;
    }
    Py_RETURN_NONE;
}

// static jmethodIDObject* FromReflectedMethod(JNIEnvObject *self, PyObject *args) {
//     PyObject *method;
//     if (!PyArg_UnpackTuple(args, "from_reflected_method", 1, 1, &method))
//         return NULL;
//     if (!jobject_Check(method)) {
//         _BadArgument("from_reflected_method", "argument", "jobject", method);
//         return NULL;
//     }
//     jmethodID result = JNIEnv_Env(self)->FromReflectedMethod(jobject_Val(method));
//     return jmethodID_FromValue(result);
// }
// static jfieldIDObject* FromReflectedField(JNIEnvObject *self, PyObject *args) {
//     PyObject *field;
//     if (!PyArg_UnpackTuple(args, "from_reflected_field", 1, 1, &field))
//         return NULL;
//     if (!jobject_Check(field)) {
//         _BadArgument("from_reflected_field", "argument", "jobject", field);
//         return NULL;
//     }
//     jfieldID result = JNIEnv_Env(self)->FromReflectedField(jobject_Val(field));
//     return jfieldID_FromValue(result);
// }
// static jobjectObject* ToReflectedMethod(JNIEnvObject *self, PyObject *args) {
//     PyObject *cls, *methodID, *isStatic;
//     if (!PyArg_UnpackTuple(args, "to_reflected_method", 3, 3, &cls, &methodID, &isStatic))
//         return NULL;
//     if (!jclass_Check(cls)) {
//         _BadArgument("to_reflected_method", "arg 1", "jclass", cls);
//         return NULL;
//     }
//     if (!jmethodID_Check(methodID)) {
//         _BadArgument("to_reflected_method", "arg 2", "jmethodID", methodID);
//         return NULL;
//     }
//     jobject result = JNIEnv_Env(self)->ToReflectedMethod(
//             jclass_Val(cls),  jmethodID_Val(methodID), PyObject_IsTrue(isStatic));
//     return jobject_FromValue(result);
// }
// static jobjectObject* ToReflectedField(JNIEnvObject *self, PyObject *args) {
//     PyObject *cls, *fieldID, *isStatic;
//     if (!PyArg_UnpackTuple(args, "to_reflected_field", 3, 3, &cls, &fieldID, &isStatic))
//         return NULL;
//     if (!jclass_Check(cls)) {
//         _BadArgument("to_reflected_field", "arg 1", "jclass", cls);
//         return NULL;
//     }
//     if (!jfieldID_Check(fieldID)) {
//         _BadArgument("to_reflected_field", "arg 2", "jfieldID", fieldID);
//         return NULL;
//     }
//     jobject result = JNIEnv_Env(self)->ToReflectedField(
//             jclass_Val(cls), jfieldID_Val(fieldID), PyObject_IsTrue(isStatic));
//     return jobject_FromValue(result);
// }
// static PyObject* IsSameObject(JNIEnvObject *self, PyObject *args) {
//     PyObject *obj1, *obj2;
//     if(!PyArg_UnpackTuple(args, "IsSameObject", 2, 2, &obj1, &obj2))
//         return NULL;
//     if(!jobject_Check(obj1)) {
//         _PyArg_BadArgument("is_same_object", "arg 1", "jobject", obj1);
//         return NULL;
//     }
//     if(!jobject_Check(obj2)) {
//         _PyArg_BadArgument("is_same_object", "arg 2", "jobject", obj2);
//         return NULL;
//     }
//     jboolean result = JNIEnv_Env(self)->IsSameObject(
//             jobject_Val(obj1), jobject_Val(obj2));
//     return PyBool_FromLong(result);
// }

// static PyObject* IsInstanceOf(JNIEnvObject *self, PyObject *args) {
//     PyObject *obj, *clazz;
//     if(!PyArg_UnpackTuple(args, "is_instance_of", 2, 2, &obj, &clazz))
//         return NULL;
//     if(!jobject_Check(obj)) {
//         _PyArg_BadArgument("is_instance_of", "arg 1", "jobject", obj);
//         return NULL;
//     }
//     if(!jclass_Check(clazz)) {
//         _PyArg_BadArgument("is_instance_of", "arg 2", "jclass", clazz);
//         return NULL;
//     }
//     jboolean result = JNIEnv_Env(self)->IsInstanceOf(jobject_Val(obj), jclass_Val(clazz));
//     return PyBool_FromLong(result);
// }

static PyMethodDef JNIEnv_methods[] = {
    //Version Information
    {"get_version", (PyCFunction)GetVersion, METH_NOARGS, "nothing"},
    //Class Operations
    {"define_class", (PyCFunction)DefineClass, METH_VARARGS, "nothing"},
    {"find_class", (PyCFunction)FindClass, METH_VARARGS, "nothing"},
    {"get_superclass", (PyCFunction)GetSuperclass, METH_VARARGS, "nothing"},
    {"is_assignable_from", (PyCFunction)IsAssignableFrom, METH_VARARGS, "nothing"},
    //Exceptions
    {"throw", (PyCFunction)Throw, METH_VARARGS, "nothing"},
    {"throw_new", (PyCFunction)ThrowNew, METH_VARARGS, "nothing"},
    {"exception_occurred", (PyCFunction)ExceptionOccurred, METH_VARARGS, "nothing"},
    {"exception_describe", (PyCFunction)ExceptionDescribe, METH_VARARGS, "nothing"},
    {"exception_clear", (PyCFunction)ExceptionClear, METH_VARARGS, "nothing"},
    {"exception_check", (PyCFunction)ExceptionCheck, METH_VARARGS, "nothing"},
    {"fatal_error", (PyCFunction)FatalError, METH_VARARGS, "nothing"},
    //Global and Local References
    {"new_global_ref", (PyCFunction)NewGlobalRef, METH_VARARGS, "nothing"},
    {"delete_global_ref", (PyCFunction)DeleteGlobalRef, METH_VARARGS, "nothing"},
    {"new_local_ref", (PyCFunction)NewLocalRef, METH_VARARGS, "nothing"},
    {"delete_local_ref", (PyCFunction)DeleteLocalRef, METH_VARARGS, "nothing"},
    {"ensure_local_capacity", (PyCFunction)EnsureLocalCapacity, METH_VARARGS, "nothing"},
    {"push_local_frame", (PyCFunction)PushLocalFrame, METH_VARARGS, "nothing"},
    {"pop_local_frame", (PyCFunction)PopLocalFrame, METH_VARARGS, "nothing"},
    //Weak Global References"
    {"new_weak_global_ref", (PyCFunction)NewWeakGlobalRef, METH_VARARGS, "nothing"},
    {"delete_weak_global_ref", (PyCFunction)DeleteWeakGlobalRef, METH_VARARGS, "nothing"},
    //Object Operations
    {"alloc_object", (PyCFunction)AllocObject, METH_VARARGS, "nothing"},
    {"new_object", (PyCFunction)NewObject, METH_VARARGS, "nothing"},
    {"get_object_class", (PyCFunction)GetObjectClass, METH_VARARGS, "nothing"},
    {"get_object_reft_type", (PyCFunction)GetObjectRefType, METH_VARARGS, "nothing"},
    {"is_instance_of", (PyCFunction)IsInstanceOf, METH_VARARGS, "nothing"},
    {"is_same_object", (PyCFunction)IsSameObject, METH_VARARGS, "nothing"},
    //Accessing Fields
    {"get_field_id", (PyCFunction)GetFieldID, METH_VARARGS, "nothing"},
    {"get_field", (PyCFunction)GetField, METH_VARARGS, "nothing"},
    {"set_field", (PyCFunction)SetField, METH_VARARGS, "nothing"},
    {"get_static_field_id", (PyCFunction)GetStaticFieldID, METH_VARARGS, "nothing"},
    {"get_static_field", (PyCFunction)GetStaticField, METH_VARARGS, "nothing"},
    {"set_static_field", (PyCFunction)SetStaticField, METH_VARARGS, "nothing"},
    //Calling Methods
    {"get_method_id", (PyCFunction)GetMethodID, METH_VARARGS, "nothing"},
    {"call_method", (PyCFunction)CallMethod, METH_VARARGS, "nothing"},
    {"call_nonvirtual_method", (PyCFunction)CallNonvirtualMethod, METH_VARARGS, "nothing"},
    {"get_static_method_id", (PyCFunction)GetStaticMethodID, METH_VARARGS, "nothing"},
    {"call_static_method", (PyCFunction)CallStaticMethod, METH_VARARGS, "nothing"},
    //String Operations
    {"new_string", (PyCFunction)NewString, METH_VARARGS, "nothing"},
    {"get_string", (PyCFunction)GetString, METH_VARARGS, "nothing"},
    {"get_string_region", (PyCFunction)GetStringRegion, METH_VARARGS, "nothing"},
    // Array Operations
    {"new_array", (PyCFunction)NewArray, METH_VARARGS, "nothing"},
    {"new_object_array", (PyCFunction)NewObjectArray, METH_VARARGS, "nothing"},
    {"get_array_elements", (PyCFunction)GetArrayElements, METH_VARARGS, "nothing"},
    {"get_object_array_element", (PyCFunction)GetObjectArrayElement, METH_VARARGS, "nothing"},
    {"set_array_elements", (PyCFunction)SetArrayElements, METH_VARARGS, "nothing"},

    // {"from_reflected_method", (PyCFunction)FromReflectedMethod, METH_VARARGS, "nothing"},
    // {"from_reflected_field", (PyCFunction)FromReflectedField, METH_VARARGS, "nothing"},
    // {"to_reflected_method", (PyCFunction)ToReflectedMethod, METH_VARARGS, "nothing"},
    // {"to_reflected_field", (PyCFunction)ToReflectedField, METH_VARARGS, "nothing"},

    {NULL}
};

PyTypeObject JNIEnv_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "JNIEnv",
    .tp_basicsize = sizeof(JNIEnvObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "JNIEnv type",
    .tp_methods = JNIEnv_methods,
};

PyObject* AttachCurrentThread(PyObject*, PyObject*) {
    //TODO support the thrid argument `JavaVMAttachArgs *thr_args`
    JNIEnv *env;
    jint jni_code = G_VM->AttachCurrentThread((void**)&env, NULL);
    PyObject *result = PyTuple_New(2);
    PyTuple_SET_ITEM(result, 0, JNIEnv_FromEnv(env));
    PyTuple_SET_ITEM(result, 1, PyLong_FromLong(jni_code));
    return result;
}
PyObject* DetachCurrentThread(PyObject*, PyObject*) {
    jint jni_code = G_VM->DetachCurrentThread();
    return PyLong_FromLong(jni_code);
}
PyObject* GetEnv(PyObject*, PyObject *args) {
    PyObject *version = NULL;
    if (!PyArg_UnpackTuple(args, "get_env", 0, 1, &version))
        return NULL;
    jint jversion = JNI_VERSION_1_6;
    if (version != NULL)
        jversion = PyLong_AsLong(version);
    JNIEnv *env = NULL;
    jint jni_code = G_VM->GetEnv((void**)&env, jversion);
    PyObject *result = PyTuple_New(2);
    PyTuple_SET_ITEM(result, 0, JNIEnv_FromEnv(env));
    PyTuple_SET_ITEM(result, 1, PyLong_FromLong(jni_code));
    return result;
}

JNIEnvObject* JNIEnv_FromEnv(JNIEnv *env) {
    if (!env)
        INC_RETURN_NONE(JNIEnvObject*);
    PyTypeObject *type = &JNIEnv_Type;
    JNIEnvObject *self = (JNIEnvObject*)type->tp_alloc(type, 0);
    if (self != NULL)
        JNIEnv_Env(self) = env;
    return self;
}