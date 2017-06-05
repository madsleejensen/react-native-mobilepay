# react-native-mobilepay

## Installation

1. `npm i --save react-native-mobilepay`
2. `react-native link react-native-mobilepay`

### iOS

The AppSwitch SDK supports three countries, which corresponds to respective versions of the MobilePay app, and each app has a distinct url scheme:

- MobilePay Denmark: `mobilepay://`
- MobilePay Norway: `mobilepayno://`
- MobilePay Finland: `mobilepayfi://`

#### 1. Enable AppSwitch Open your info.plist find "URL types" entry and add a "URL Identifier" entry with a value matching your bundle identifier fx. "com.trifork.MobilePayFruitShop".

Then add a **"URL Schemes"** Item with a name matching your app. In this example we use **"fruitshop"**, and you should not add this to your production app - this is just an example! This is the part that enables opening your app from an url.

![add urlscheme to info.plist](https://github.com/MobilePayDev/MobilePay-AppSwitch-SDK/raw/master/doc/wiki/images/ios/xcode_add_url_scheme_to_info_plist.png)

In this case you are now able to open a browser on your iPhone and type in **"fruitshop://"** and your app will open.

As of Xcode 7 and iOS9 SDK you must also whitelist the MobilePay URL scheme for the SDK (your merchant app) in order for it to be able to open the MobilePay app. This must be added to your info.plist - see the below screenshot.

![whitelist urlscheme in info.plist](https://github.com/MobilePayDev/MobilePay-AppSwitch-SDK/raw/master/doc/wiki/images/ios/xcode_whitelist_urlschemes.png)

#### 2. Open AppDelegate.m and paste the following
```objc
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {


  if ([[RNMobilePayHandler sharedInstance] handleMobilePayPaymentWithUrl:url]) {
    return true;
  }

  return false;
}
```

####
for more information see https://github.com/MobilePayDev/MobilePay-AppSwitch-SDK


## Examples

```javascript
import MobilePay from 'react-native-mobilepay'

// constants are provided to determine if mobilepay is available on user's phone.

if (MobilePay.isMobilePayInstalledDenmark) {
  console.log('MobilePay is available for Denmark')
}

if (MobilePay.isMobilePayInstalledNorway) {
  console.log('MobilePay is available for Norway')
}

if (MobilePay.isMobilePayInstalledFinland) {
  console.log('MobilePay is available for Finland')
}
```
### setup configurations
```javascript
import MobilePay from 'react-native-mobilepay'

const merchantId = 'APPDK0000000000'
const country = MobilePay.COUNTRY_DENMARK
const merchantUrlScheme = 'fruitshop' // last argument is only used for iOS. (send empty string if only building for android)

MobilePay.setup(merchantId, country, merchantUrlScheme)
```

### request a payment
```javascript
import MobilePay from 'react-native-mobilepay'

const orderId = 'order-1234'
const amount = 150

MobilePay.createPayment(orderId, amount).then(
  result => {
    if (!result.isCancelled) {
      console.log(`payment successful order-id: ${result.orderId} transaction-id: ${result.transactionId}`)
    } else {
      console.log(`payment was cancelled`)
    }
  },
  error => {
    console.log('payment failed', error)
  }
)
```

### additional configurations
```javascript
// change country to Norway
MobilePay.setCountry(MobilePay.COUNTRY_NORWAY)
// or Finland
MobilePay.setCountry(MobilePay.COUNTRY_FINLAND)

// seconds that you allow the user to spend in the MobilePay app before returning to the merchant app, if exceeded when you try to swipe in Mobile Pay errorcode 8 is returned. Default is 0 = never timeout
MobilePay.setTimeoutSeconds(60)

// seconds spend on the MobilePay receipt screen before returning to the merchant app.
MobilePay.setReturnSeconds(10)

MobilePay.setCaptureType(MobilePay.CAPTURE_TYPE_CAPTURE)
MobilePay.setCaptureType(MobilePay.CAPTURE_TYPE_RESERVE)
```
