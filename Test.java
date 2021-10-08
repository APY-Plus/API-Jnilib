public class Test extends Thread {
    static {
        System.loadLibrary("jnilib");
    }

    public native void init();

    public native void hello1();

    public native void hello2();

    public Test() {
        init();
    }

    public void printThreads() {
        ThreadGroup currentGroup = Thread.currentThread().getThreadGroup();
        int threadNum = currentGroup.activeCount();
        Thread[] threads = new Thread[threadNum];
        currentGroup.enumerate(threads);
        for (int i = 0; i < threadNum; i++)
            System.out.println("线程号：" + i + " = " + threads[i].getName());
    }

    public static void main(String[] args) throws Exception {
        Test test = new Test();
        Thread thread = Thread.currentThread();
        System.out.println("[java]" + thread);
        System.out.println("[java]python start");
        test.hello1();
        System.out.println("[java]python over");
        Thread.sleep(3000);
        System.out.println("[java]java over");
    }
}
