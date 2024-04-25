public class Main {

    static{
        System.loadLibrary("scanFiles");
    }

    public static native String scanNativeFiles();

    public static void main(String[] args) {
        System.out.println("Hello world!");
    }
}