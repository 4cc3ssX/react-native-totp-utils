import type {
  IGenerateOTPOptions,
  IGenerateSecretKeyOptions,
  IValidateOTPOptions,
} from './types';

const g = global as any;

export enum Constants {
  DEFAULT_DIGITS = 6,
  DEFAULT_TIME_STEP = 30,
  DEFAULT_SECRET_KEY_LENGTH = 16,
  DEFAULT_WINDOW = 1,
}

export const defaultOptions = {
  digits: Constants.DEFAULT_DIGITS,
  timeStep: Constants.DEFAULT_TIME_STEP,
  window: Constants.DEFAULT_WINDOW,
  length: Constants.DEFAULT_SECRET_KEY_LENGTH,
};

/**
 * Generates a secret key for TOTP.
 * @param {IGenerateSecretKeyOptions} options - The length of the secret key.
 * @returns {string} The generated secret key.
 */
export function generateSecretKey(
  options: IGenerateSecretKeyOptions = defaultOptions
): string {
  options = {
    ...defaultOptions,
    ...options,
  };
  return g.totpUtilsGenerateSecretKey(options.length);
}

/**
 * Generates a TOTP (Time-Based One-Time Password) using the provided secret key.
 * @param {string} secretKey - The secret key used for TOTP generation.
 * @param {IGenerateOTPOptions} options - The number of digits in the generated OTP.
 * @returns {string} The generated TOTP.
 */
export function generateOTP(
  secretKey: string,
  options: IGenerateOTPOptions = defaultOptions
): string {
  // overwrite undefined options with default
  options = {
    ...defaultOptions,
    ...options,
  };
  return g.totpUtilsGenerateOTP(secretKey, options.digits, options.timeStep);
}

/**
 * Validates a TOTP against the provided secret key and OTP.
 * @param {string} secretKey - The secret key used for TOTP validation.
 * @param {string} otp - The OTP to validate.
 * @param {IValidateOTPOptions} options - The number of digits in the OTP.
 * @returns {boolean} True if the OTP is valid, false otherwise.
 */
export function validateOTP(
  secretKey: string,
  otp: string,
  options: IValidateOTPOptions = {}
): boolean {
  // overwrite undefined options with default
  options = {
    ...defaultOptions,
    ...options,
  };
  return g.totpUtilsValidateOTP(
    secretKey,
    otp,
    options.digits,
    options.timeStep,
    options.window
  );
}

const RNTOTP = {
  generateSecretKey,
  generateOTP,
  validateOTP,
};

export * from './utils';
export default RNTOTP;
