package host.ui;

import android.app.Activity;
import android.os.Bundle;
import host.low.Low;

public class HostActivity extends Activity {
    static {
        System.loadLibrary("main");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Low.registerObject(this);
    }
}
