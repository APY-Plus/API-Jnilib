public class Test {
    static {
        System.loadLibrary("jnilib");
    }

    public static native void init();

    public static native void mode1(String fname);

    public static native void mode2();

    public static void mode1_test() {
        Thread thread = new Thread(() -> {
            mode1("test.py");
        });
        thread.start();
    }

    public static void mode2_test() {
        Thread thread = new Thread(() -> {
            mode2();
        });
        thread.start();
    }

    public static void main(String[] args) throws Exception {
        init();
        mode1_test();

        Thread.sleep(1000);
        System.out.println("[java]java over");
    }
}
