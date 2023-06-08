package com.totputils;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactMethod;

public class TotpUtilsModule extends TotpUtilsSpec {
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
    System.loadLibrary("cpp");
  }

  public static native String nativeGenerateSecretKey(double length);

  public static native String nativeGenerateOTP(String secret, double digits, double timeStep);

  public static native Boolean nativeValidateOTP(String secret, String otp, double digits, double timeStep,
      double window);

  // See https://reactnative.dev/docs/native-modules-android
  @ReactMethod
  public void generateSecretKey(double length, Promise promise) {
    promise.resolve(nativeGenerateSecretKey(length));
  }

  @ReactMethod
  public void generateOTP(String secret, double digits, double timeStep, Promise promise) {
    promise.resolve(nativeGenerateOTP(secret, digits, timeStep));
  }

  @ReactMethod
  public void validateOTP(String secret, String otp, double digits, double timeStep, double window, Promise promise) {
    promise.resolve(nativeValidateOTP(secret, otp, digits, timeStep, window));
  }
}
