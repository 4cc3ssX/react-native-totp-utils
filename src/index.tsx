import { NativeModules, Platform } from 'react-native';
import type { IGenerateOTPOptions, IValidateOTPOptions } from './types';

const LINKING_ERROR =
  `The package 'react-native-totp-utils' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n';

const TotpUtilsModule = NativeModules.TotpUtils;

const TotpUtils = TotpUtilsModule
  ? TotpUtilsModule
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR);
        },
      }
    );

TotpUtils.install();

const g = global as any;

export enum Constants {
  DEFAULT_DIGITS = 6,
  DEFAULT_TIME_STEP = 30,
  DEFAULT_WINDOW = 1,
  DEFAULT_LENGTH = 20,
}

export const defaultOptions = {
  digits: Constants.DEFAULT_DIGITS,
  timeStep: Constants.DEFAULT_TIME_STEP,
  window: Constants.DEFAULT_WINDOW,
};

/**
 * Generates a secret key for TOTP.
 * @returns {string} The generated secret key.
 */
export function generateSecretKey(): string {
  return g.totpUtilsGenerateSecretKey();
}

/**
 * Generates a TOTP (Time-Based One-Time Password) using the provided secret key.
 * @param {string} secretKey - The secret key used for TOTP generation.
 * @param {IGenerateOTPOptions} options - The number of digits in the generated OTP.
 * @returns {string} The generated TOTP.
 */
export function generateTOTP(
  secretKey: string,
  options: IGenerateOTPOptions = defaultOptions
): string {
  // overwrite undefined options with default
  options = {
    ...defaultOptions,
    ...options,
  };
  return g.totpUtilsGenerateTOTP(secretKey, options.digits, options.timeStep);
}

/**
 * Validates a TOTP against the provided secret key and OTP.
 * @param {string} secretKey - The secret key used for TOTP validation.
 * @param {string} otp - The OTP to validate.
 * @param {IValidateOTPOptions} options - The number of digits in the OTP.
 * @returns {boolean} True if the OTP is valid, false otherwise.
 */
export function validateTOTP(
  secretKey: string,
  otp: string,
  options: IValidateOTPOptions = {}
): boolean {
  // overwrite undefined options with default
  options = {
    ...defaultOptions,
    ...options,
  };
  return g.totpUtilsValidateTOTP(
    secretKey,
    otp,
    options.digits,
    options.timeStep,
    options.window
  );
}

const RNTOTP = {
  generateSecretKey,
  generateTOTP,
  validateTOTP,
};

export * from './utils';
export default RNTOTP;
