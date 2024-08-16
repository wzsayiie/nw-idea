package host.low;

import androidx.annotation.Keep;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.HashMap;

public class Low {

    static final int PARAM_REG_COUNT = 8;

    public static boolean[] b = new boolean[PARAM_REG_COUNT];
    public static int    [] i = new int    [PARAM_REG_COUNT];
    public static long   [] l = new long   [PARAM_REG_COUNT];
    public static float  [] f = new float  [PARAM_REG_COUNT];
    public static double [] d = new double [PARAM_REG_COUNT];
    public static String [] s = new String [PARAM_REG_COUNT];
    public static byte[] [] v = new byte   [PARAM_REG_COUNT][];

    public static boolean br;
    public static int     ir;
    public static long    lr;
    public static float   fr;
    public static double  dr;
    public static String  sr;
    public static byte[]  vr;

    public static void registerObject(Object obj) {
        Class<?> cls = obj.getClass();

        for (Method method : cls.getDeclaredMethods()) {
            if (method.getDeclaringClass() != cls) {
                continue;
            }
            if (!method.getReturnType().equals(void.class) || method.getParameterCount() != 0) {
                continue;
            }
            if (!method.isAnnotationPresent(LowMethod.class)) {
                continue;
            }
            if (Modifier.isStatic(method.getModifiers())) {
                continue;
            }

            Runnable lambda = () -> {
                try {
                    method.setAccessible(true);
                    method.invoke(obj);
                } catch (Exception ignore) {
                }
            };

            int id = method.hashCode();
            registerJavaMethod(method.getName(), id);
            _javaLambdas.put(id, lambda);
        }
    }

    //this method will be called by native.
    @Keep
    static void onCall(int id) {
        Runnable lambda = _javaLambdas.get(id);
        if (lambda == null) {
            return;
        }

        readParamsFromNative();
        lambda.run();
        writeReturnToNative();
    }

    static HashMap<Integer, Runnable> _javaLambdas = new HashMap<>();

    static void readParamsFromNative() {
        for (int n = 0; n < PARAM_REG_COUNT; n++) {
            b[n] = getNativeBoolean(n);
            i[n] = getNativeInt    (n);
            l[n] = getNativeLong   (n);
            f[n] = getNativeFloat  (n);
            d[n] = getNativeDouble (n);
            s[n] = getNativeString (n);
            v[n] = getNativeBytes  (n);
        }
    }

    static void writeReturnToNative() {
        setNativeBoolean(-1, br);
        setNativeInt    (-1, ir);
        setNativeLong   (-1, lr);
        setNativeFloat  (-1, fr);
        setNativeDouble (-1, dr);
        setNativeString (-1, sr);
        setNativeBytes  (-1, vr);
    }

    public static void call(String name) {
        writeParamsToNative();
        callNative(name);
        readReturnFromNative();
    }

    static void writeParamsToNative() {
        for (int n = 0; n < PARAM_REG_COUNT; n++) {
            setNativeBoolean(n, b[n]);
            setNativeInt    (n, i[n]);
            setNativeLong   (n, l[n]);
            setNativeFloat  (n, f[n]);
            setNativeDouble (n, d[n]);
            setNativeString (n, s[n]);
            setNativeBytes  (n, v[n]);
        }
    }

    static void readReturnFromNative() {
        br = getNativeBoolean(-1);
        ir = getNativeInt    (-1);
        lr = getNativeLong   (-1);
        fr = getNativeFloat  (-1);
        dr = getNativeDouble (-1);
        sr = getNativeString (-1);
        vr = getNativeBytes  (-1);
    }

    static native void setNativeBoolean(int index, boolean value);
    static native void setNativeInt    (int index, int     value);
    static native void setNativeLong   (int index, long    value);
    static native void setNativeFloat  (int index, float   value);
    static native void setNativeDouble (int index, double  value);
    static native void setNativeString (int index, String  value);
    static native void setNativeBytes  (int index, byte[]  value);

    static native boolean getNativeBoolean(int index);
    static native int     getNativeInt    (int index);
    static native long    getNativeLong   (int index);
    static native float   getNativeFloat  (int index);
    static native double  getNativeDouble (int index);
    static native String  getNativeString (int index);
    static native byte[]  getNativeBytes  (int index);

    static native void registerJavaMethod(String name, int id);

    static native void callNative(String name);
}
