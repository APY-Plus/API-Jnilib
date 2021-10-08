import threading
from jnilib import *
from typing import cast
from time import sleep

def test():
    t1 = threading.current_thread()
    print('[py]python thread:', t1)
    print('[py]print something')
    env, code = get_env_code()
    print('[py]getenv result:', code, env)

    if not env:
        env, code = attach_thread_code()
        print('[py]attach result:', code, env)

    print('[py]python thread:', threading.current_thread())

    class_Thread = env.find_class('java/lang/Thread')
    Thread_currentThread = env.get_static_method_id(class_Thread, 'currentThread',
                                                    '()Ljava/lang/Thread;')
    Thread_toString = env.get_method_id(class_Thread, 'toString',
                                        '()Ljava/lang/String;')
    Thread_isDaemon = env.get_method_id(class_Thread, 'isDaemon', '()Z')

    thread = cast(jobject, env.call_static_method(class_Thread, Thread_currentThread))
    desc = cast(jstring, env.call_method(thread, Thread_toString))
    desc = env.get_string(desc)
    daemon = env.call_method(thread, Thread_isDaemon)

    print('[py]java thread:', desc, daemon)
    code = detach_thread_code()
    print('[py]detach result:', code)

t1 = threading.Thread(target=test, daemon=False)
t1.start()
# t1.join()
