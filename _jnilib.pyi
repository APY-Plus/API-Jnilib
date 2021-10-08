from typing import Tuple, Union


class jvalue(object):
    ...


class jboolean(jvalue):
    ...


class jbyte(jvalue):
    def __neg__(self) -> jbyte:
        ...

    def __invert__(self) -> jbyte:
        ...

    def __lshift__(self, other: jbyte) -> jbyte:
        ...

    def __rshift__(self, other: jbyte) -> jbyte:
        ...


class jchar(jvalue):
    def __neg__(self) -> jchar:
        ...

    def __invert__(self) -> jchar:
        ...

    def __lshift__(self, other: jchar) -> jchar:
        ...

    def __rshift__(self, other: jchar) -> jchar:
        ...


class jshort(jvalue):
    def __neg__(self):
        ...

    def __invert__(self):
        ...

    def __lshift__(self, other):
        ...

    def __rshift__(self, other):
        ...


#TODO jint能不能继承int
class jint(jvalue, int):
    def __neg__(self):
        ...

    def __invert__(self):
        ...

    def __lshift__(self, other):
        ...

    def __rshift__(self, other):
        ...


class jlong(jvalue):
    def __neg__(self):
        ...

    def __invert__(self):
        ...

    def __lshift__(self, other):
        ...

    def __rshift__(self, other):
        ...


class jfloat(jvalue):
    def __neg__(self):
        ...

    def __invert__(self):
        ...

    def __lshift__(self, other):
        ...

    def __rshift__(self, other):
        ...


class jdouble(jvalue):
    def __neg__(self):
        ...

    def __invert__(self):
        ...

    def __lshift__(self, other):
        ...

    def __rshift__(self, other):
        ...


class jobject(jvalue):
    ...


class jclass(jobject):
    ...


class jstring(jobject):
    ...


class jthrowable(jobject):
    ...


class jweak(jobject):
    ...


class jmehthodID(object):
    ...


class jfieldID(object):
    ...


class JNIEnv(object):
    def get_version(self, version: int = ...) -> int:
        ...

    # Class Operations
    #TODO check whether `buf` type is `bytes`
    def define_class(self, name: str, loader: jobject, buf: bytes) -> jclass:
        ...

    def find_class(self, name: str) -> jclass:
        ...

    def get_superclass():
        ...

    def is_assignable_from():
        ...

    # Exceptions
    def throw():
        ...

    def throw_new():
        ...

    def exception_occurred():
        ...

    def exception_describe():
        ...

    def exception_clear():
        ...

    def exception_check():
        ...

    def fatal_error():
        ...

    # Global and Local References
    def new_global_ref():
        ...

    def delete_global_ref():
        ...

    def new_local_ref():
        ...

    def delete_local_ref():
        ...

    def ensure_local_capacity():
        ...

    def push_local_frame():
        ...

    def pop_local_frame():
        ...

    # Weak Global References"
    def new_weak_global_ref():
        ...

    def delete_weak_global_ref():
        ...

    # Object Operations
    def alloc_object():
        ...

    def new_object():
        ...

    def get_object_class():
        ...

    def get_object_reft_type():
        ...

    def is_instance_of():
        ...

    def is_same_object():
        ...

    # Accessing Fields
    def get_field_id():
        ...

    def get_field():
        ...

    def set_field():
        ...

    def get_static_field_id():
        ...

    def get_static_field():
        ...

    def set_static_field():
        ...

    # Calling Methods
    def get_method_id(self, clazz: jclass, name: str, sig: str) -> jmehthodID:
        ...

    def call_method(self, obj: jobject, method: jmehthodID) -> jvalue:
        ...

    def call_nonvirtual_method():
        ...

    def get_static_method_id(self, clazz: jclass, name: str,
                             sig: str) -> jmehthodID:
        ...

    def call_static_method(self, clazz: jclass,
                           methodID: jmehthodID) -> jvalue:
        ...

    # String Operations
    def new_string():
        ...

    def get_string(self, jstr: jstring) -> str:
        ...

    def get_string_region():
        ...

    # Array Operations
    def new_array():
        ...

    def new_object_array():
        ...

    def get_array_elements():
        ...

    def get_object_array_element():
        ...

    def set_array_elements():
        ...


def get_env_code(version: int = ...) -> Tuple[JNIEnv, int]:
    ...


def attach_thread_code() -> Tuple[JNIEnv, int]:
    ...


def detach_thread_code() -> int:
    ...
