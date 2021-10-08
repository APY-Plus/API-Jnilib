from types import FunctionType
from typing import ParamSpec

from _jnilib import *

P = ParamSpec('P')

JNI_OK = 0
JNI_ERR = -1
JNI_EDETACHED = -2
JNI_EVERSION = -3
JNI_ENOMEM = -4
JNI_EEXIST = -5
JNI_EINVAL = -6

JNI_VERSION_1_1 = 0x10001
JNI_VERSION_1_2 = 0x10002
JNI_VERSION_1_4 = 0x10004
JNI_VERSION_1_6 = 0x10006
JNI_VERSION_1_8 = 0x10008

JNIInvalidRefType = 0
JNILocalRefType = 1
JNIGlobalRefType = 2
JNIWeakGlobalRefType = 3

jni_codes = {
    JNI_OK: 'JNI_OK',
    JNI_ERR: 'JNI_ERR',
    JNI_EDETACHED: 'JNI_EDETACHED',
    JNI_EVERSION: 'JNI_EVERSION',
    JNI_ENOMEM: 'JNI_ENOMEM',
    JNI_EEXIST: 'JNI_EEXIST',
    JNI_EINVAL: 'JNI_EINVAL'
}


class JNIException(Exception):
    def __init__(self, code: int):
        self.type = jni_codes[code]
        self.message = f'JNI function return the error code {self.type}'


def attach_thread():
    env, code = attach_thread_code()
    if code != JNI_OK:
        raise JNIException(code)
    return env


def detach_thread():
    code = detach_thread_code()
    if code != JNI_OK:
        raise JNIException(code)


def get_env(version: int = JNI_VERSION_1_6) -> JNIEnv:
    env, code = get_env_code(version)
    if code != JNI_OK:
        raise JNIException(code)
    return env


def safe_env(func: FunctionType):
    #TODO 这个函数里的三个jni函数又不要换成对应的上面python函数
    def wrapper(*args: P.args, **kwargs: P.kwargs):
        env, code = get_env_code()
        if code == JNI_EDETACHED:
            env, _ = attach_thread_code()
        func(env, *args, **kwargs)
        if code == JNI_EDETACHED:
            detach_thread_code()

    return wrapper
