public class Main {

    static{
        System.loadLibrary("pluginNative");
    }

    public static native String scanFiles();

    public static void main(String[] args) {
        PluginScanner scanner = new PluginScanner();
        String toPrint = scanner.scanFiles();
        System.out.println(toPrint);
    }
}