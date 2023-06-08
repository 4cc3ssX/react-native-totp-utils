import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  generateSecretKey(length: number): Promise<string>;
  generateOTP(
    secret: string,
    digits: number,
    timeStep: number
  ): Promise<string>;
  validateOTP(
    secret: string,
    otp: string,
    digits: number,
    timeStep: number,
    window: number
  ): Promise<boolean>;
}

export default TurboModuleRegistry.getEnforcing<Spec>('TotpUtils');
