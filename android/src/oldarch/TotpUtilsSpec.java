package com.totputils;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.Promise;

abstract class TotpUtilsSpec extends ReactContextBaseJavaModule {
  TotpUtilsSpec(ReactApplicationContext context) {
    super(context);
  }

  public abstract void generateSecretKey(double keyLength, Promise promise);

  public abstract void generateOTP(String secret, double digits, double timeStep, Promise promise);

  public abstract void validateOTP(String secret, String otp, double digits, double timeStep, double window,
      Promise promise);
}
