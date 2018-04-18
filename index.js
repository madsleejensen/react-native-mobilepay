
import { NativeModules } from 'react-native';

const { RNMobilePay } = NativeModules;

export function isMobilePayInstalled (country) {
	return new Promise((resolve, reject) => {
		RNMobilePay.isMobilePayInstalled(country, resolve, reject);
	});
}

export default RNMobilePay;
