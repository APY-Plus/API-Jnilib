from time import sleep
from threading import Thread


def test():
    sleep(3)
    print('[py]new thread over')

t1 = Thread(target=test, daemon=False)
t1.start()
print('[py]main thread over')
