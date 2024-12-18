> [!IMPORTANT]
> ## MOVED TO NEW REPOSITORY
> This library is no longer maintained and moved to new repository [react-native-nitro-totp](https://github.com/4cc3ssX/react-native-nitro-totp).

# react-native-totp-utils

A full-featured Time-Based One-Time Password (TOTP) library for React Native, providing functions for generating and validating OTP codes.

## Features

- [X] New Architecture Support
- [X] Written in C++
- [X] Generate Secret Key
- [X] Generate OTP
- [X] Validate OTP
- [X] JSI Implementation

## Installation

Using npm:

```bash
npm install react-native-totp-utils
```

Using yarn:

```bash
yarn add react-native-totp-utils
```

## Usage

```js
import {
  generateOTP,
  generateSecretKey,
  validateOTP,
  formatSecretKey,
  formatOTP,
} from 'react-native-totp-utils';

// ...

const secretKey = generateSecretKey(); // ABCDABCDABCD

const otp = generateOTP(secretKey); // 123456

const isValid = validateOTP(secretKey, otp); // true

const formattedSecretKey = formatSecretKey(secretKey); // ABCD-ABCD-ABCD-ABCD

const formattedOTP = formatOTP(otp); // 123 456
```

## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT

---

Made with [create-react-native-library](https://github.com/callstack/react-native-builder-bob)
