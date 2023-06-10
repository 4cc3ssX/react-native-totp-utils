import * as React from 'react';

import { StyleSheet, View, Text } from 'react-native';
import {
  generateOTP,
  generateSecretKey,
  validateOTP,
  formatSecretKey,
  formatOTP,
} from 'react-native-totp-utils';

export default function App() {
  const [secretKey, setSecretKey] = React.useState<string>('');
  const [otp, setOTP] = React.useState<string>('');
  const [isValid, setIsValid] = React.useState<boolean>(false);

  React.useEffect(() => {
    const secret = generateSecretKey();
    console.log(secret);
    // set formatted secret
    setSecretKey(formatSecretKey(secret));
    const totp = generateOTP(secret);
    console.log(totp);
    // set formatted OTP
    setOTP(formatOTP(totp));
    const valid = validateOTP(secret, totp);
    console.log(valid);
    setIsValid(valid);
  }, []);

  return (
    <View style={styles.container}>
      <Text>Secret Key: {secretKey}</Text>
      <Text>OTP: {otp}</Text>
      <Text>Is Valid: {`${isValid}`}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: 'white',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
