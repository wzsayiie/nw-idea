#include <jni.h>
#include "ddefer.h"
#include "lcall.h"
#include "lreg.h"

extern "C" JNIEXPORT void JNICALL Java_host_low_Low_setNativeBoolean(JNIEnv *e, jclass c, jint n, jboolean v) { n != -1 ? low::b[n] = v : low::br = v; }
extern "C" JNIEXPORT void JNICALL Java_host_low_Low_setNativeInt    (JNIEnv *e, jclass c, jint n, jint     v) { n != -1 ? low::i[n] = v : low::ir = v; }
extern "C" JNIEXPORT void JNICALL Java_host_low_Low_setNativeLong   (JNIEnv *e, jclass c, jint n, jlong    v) { n != -1 ? low::l[n] = v : low::lr = v; }
extern "C" JNIEXPORT void JNICALL Java_host_low_Low_setNativeFloat  (JNIEnv *e, jclass c, jint n, jfloat   v) { n != -1 ? low::f[n] = v : low::fr = v; }
extern "C" JNIEXPORT void JNICALL Java_host_low_Low_setNativeDouble (JNIEnv *e, jclass c, jint n, jdouble  v) { n != -1 ? low::d[n] = v : low::dr = v; }

extern "C" JNIEXPORT void JNICALL
Java_host_low_Low_setNativeString(JNIEnv *env, jclass cls, jint index, jstring value) {
    std::string &reg = index != -1 ? low::s[index] : low::sr;

    if (value == nullptr) {
        reg.clear();
        return;
    }

    const char *chars = env->GetStringUTFChars(value, nullptr);
    d_defer {
        env->ReleaseStringUTFChars(value, chars);
    };

    reg.assign(chars);
}

extern "C" JNIEXPORT void JNICALL
Java_host_low_Low_setNativeBytes(JNIEnv *env, jclass cls, jint index, jbyteArray value) {
    dash::bytes &reg = index != -1 ? low::v[index] : low::vr;

    if (value == nullptr) {
        reg.reset();
        return;
    }

    jbyte *buf = env->GetByteArrayElements(value, nullptr);
    jsize  len = env->GetArrayLength(value);
    d_defer {
        env->ReleaseByteArrayElements(value, buf, 0);
    };

    reg = dash::make_bytes(buf, len);
}

extern "C" JNIEXPORT jboolean JNICALL Java_host_low_Low_getNativeBoolean(JNIEnv *e, jclass c, jint n) { return n != -1 ? low::b[n] : low::br; }
extern "C" JNIEXPORT jint     JNICALL Java_host_low_Low_getNativeInt    (JNIEnv *e, jclass c, jint n) { return n != -1 ? low::i[n] : low::ir; }
extern "C" JNIEXPORT jlong    JNICALL Java_host_low_Low_getNativeLong   (JNIEnv *e, jclass c, jint n) { return n != -1 ? low::l[n] : low::lr; }
extern "C" JNIEXPORT jfloat   JNICALL Java_host_low_Low_getNativeFloat  (JNIEnv *e, jclass c, jint n) { return n != -1 ? low::f[n] : low::fr; }
extern "C" JNIEXPORT jdouble  JNICALL Java_host_low_Low_getNativeDouble (JNIEnv *e, jclass c, jint n) { return n != -1 ? low::d[n] : low::dr; }

extern "C" JNIEXPORT jstring JNICALL
Java_host_low_Low_getNativeString(JNIEnv *env, jclass cls, jint index) {
    std::string &reg = index != -1 ? low::s[index] : low::sr;

    if (reg.empty()) {
        return nullptr;
    }

    return env->NewStringUTF(reg.c_str());
}

extern "C" JNIEXPORT jbyteArray JNICALL
Java_host_low_Low_getNativeBytes(JNIEnv *env, jclass cls, jint index) {
    dash::bytes &reg = index != -1 ? low::v[index] : low::vr;

    if (reg == nullptr) {
        return nullptr;
    }

    auto buf = (jbyte *)reg->data();
    auto len = (jsize  )reg->size();

    jbyteArray array = env->NewByteArray(len);
    env->SetByteArrayRegion(array, 0, len, buf);
    return array;
}

static JNIEnv   *g_jniEnv    = nullptr;
static jclass    g_javaClass = nullptr;
static jmethodID g_callback  = nullptr;

static void InitCallback(JNIEnv *env, jclass cls) {
    g_jniEnv    = env;
    g_javaClass = (jclass)env->NewGlobalRef(cls);
    g_callback  = env->GetStaticMethodID(g_javaClass, "onCall", "(I)V");

    jclass    methodCls     = env->FindClass("java/lang/reflect/Method");
    jmethodID setAccessible = env->GetMethodID(methodCls, "setAccessible", "(Z)V");
    jobject   methodObj     = env->ToReflectedMethod(g_javaClass, g_callback, JNI_FALSE);

    env->CallVoidMethod(methodObj, setAccessible, JNI_TRUE);
}

static void onCall(int id) {
    g_jniEnv->CallStaticVoidMethod(g_javaClass, g_callback, id);
}

extern "C" JNIEXPORT void JNICALL
Java_host_low_Low_registerJavaMethod(JNIEnv *env, jclass cls, jstring name, jint id) {
    const char *func = env->GetStringUTFChars(name, nullptr);
    d_defer {
        env->ReleaseStringUTFChars(name, func);
    };

    low::set(func, onCall, id);
    InitCallback(env, cls);
}

extern "C" JNIEXPORT void JNICALL
Java_host_low_Low_callNative(JNIEnv *env, jclass cls, jstring name) {
    const char *func = env->GetStringUTFChars(name, nullptr);
    d_defer {
        env->ReleaseStringUTFChars(name, func);
    };

    low::call(func);
}
