public class PluginScanner {
    static {
        System.loadLibrary("pluginNative");
    }

    public native String scanFiles();
}
