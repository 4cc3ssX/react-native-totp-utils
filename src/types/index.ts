export interface IGenerateOTPOptions {
  /**
   * The time step in seconds.
   * @type {number}
   */
  timeStep?: number;
  /**
   * The number of digits in the OTP.
   * @type {number}
   */
  digits?: number;
}

export interface IGenerateSecretKeyOptions {
  /**
   * Generates a random secret key of the specified length.
   * @type {number}
   */
  length?: number;
}

export interface IValidateOTPOptions extends IGenerateOTPOptions {
  /**
   * The window of time to allow for OTP validation, in steps.
   * @type {number}
   * @default 1
   */
  window?: number;
}
