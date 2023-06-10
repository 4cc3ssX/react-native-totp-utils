package com.totputils;

import android.util.Log;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.JavaScriptContextHolder;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.module.annotations.ReactModule;

@ReactModule(name = TotpUtilsModule.NAME)
public class TotpUtilsModule extends ReactContextBaseJavaModule {
  public static final String NAME = "TotpUtils";

  TotpUtilsModule(ReactApplicationContext context) {
    super(context);
  }

  @Override
  @NonNull
  public String getName() {
    return NAME;
  }

  static {
    try {
      System.loadLibrary("cpp");
    } catch (Exception ignored) {

    }
  }

  private native void nativeInstall(long jsi);

  public void installLib(JavaScriptContextHolder reactContext) {

    if (reactContext.get() != 0) {
      this.nativeInstall(
        reactContext.get()
      );
    } else {
      Log.e("TotpUtilsModule", "JSI Runtime is not available in debug mode");
    }

  }
}
