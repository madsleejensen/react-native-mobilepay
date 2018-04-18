package dk.madslee.mobilepay;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;

import com.facebook.react.bridge.*;
import dk.danskebank.mobilepay.sdk.CaptureType;
import dk.danskebank.mobilepay.sdk.Country;
import dk.danskebank.mobilepay.sdk.MobilePay;
import dk.danskebank.mobilepay.sdk.ResultCallback;
import dk.danskebank.mobilepay.sdk.model.FailureResult;
import dk.danskebank.mobilepay.sdk.model.Payment;
import dk.danskebank.mobilepay.sdk.model.SuccessResult;

import java.math.BigDecimal;
import java.util.HashMap;
import java.util.Map;

public class RNMobilePayModule extends ReactContextBaseJavaModule {

    private static final int MOBILEPAY_PAYMENT_REQUEST_CODE = 1001;
    private boolean mHasBeenSetup = false;
    private String mMerchantId = "APPDK0000000000";
    private Country mCountry = Country.DENMARK;
    private int mReturnSeconds = 1;
    private int mTimeoutSeconds = 90;
    private CaptureType mCaptyreType = CaptureType.CAPTURE;
    private Promise mPaymentPromise;
    private Payment mPayment;

    private final ActivityEventListener mActivityEventListener = new BaseActivityEventListener() {
        @Override
        public void onActivityResult(Activity activity, int requestCode, int resultCode, Intent data) {
            if (requestCode == MOBILEPAY_PAYMENT_REQUEST_CODE) {
                MobilePay.getInstance().handleResult(resultCode, data, new ResultCallback() {
                    @Override
                    public void onSuccess(SuccessResult result) {
                        // The payment succeeded - you can deliver the product.
                        WritableMap map = Arguments.createMap();
                        map.putBoolean("isCancelled", false);
                        map.putString("orderId", result.getOrderId());
                        map.putString("transactionId", result.getTransactionId());
                        map.putString("transactionSignature", result.getSignature());
                        map.putDouble("amountWithdrawnFromCard", result.getAmountWithdrawnFromCard().doubleValue());

                        mPaymentPromise.resolve(map);

                        cleanUp();
                    }
                    @Override
                    public void onFailure(FailureResult result) {
                        // The payment failed - show an appropriate error message to the user. Consult the MobilePay class documentation for possible error codes.
                        mPaymentPromise.reject(Integer.toString(result.getErrorCode()), result.getErrorMessage());

                        cleanUp();
                    }
                    @Override
                    public void onCancel() {
                        // The payment was cancelled.

                        WritableMap map = Arguments.createMap();
                        map.putBoolean("isCancelled", true);
                        map.putString("orderId", mPayment.getOrderId());

                        mPaymentPromise.resolve(map);

                        cleanUp();
                    }
                });
            }
        }
    };

    public RNMobilePayModule(ReactApplicationContext reactContext) {
        super(reactContext);

        reactContext.addActivityEventListener(mActivityEventListener);
    }

    private void cleanUp() {
        mPaymentPromise = null;
        mPayment = null;
    }

    @Override
    public String getName() {
        return "RNMobilePay";
    }

    @ReactMethod
    public void setup(String merchantId, String country, String merchantUrlScheme) {
        mMerchantId = merchantId;

        setCountry(country);

        mHasBeenSetup = true;
    }

    @ReactMethod
    public void createPayment(String orderId, Double productPrice, Promise promise) {
        if (!mHasBeenSetup) {
            promise.reject("-1", "MobilePay has not been setup. Please call setup(merchantId, country, merchantUrlScheme) first.");
        }

        // seems theres a bug in mobilepay SDK 1.8.1 where calling isMobilePayInstalled(..., country) will override the setup country.
        // to workaround we instead store all the config vars, and before each payment we initialize the mobilepay instance from scratch.
        MobilePay.getInstance().init(mMerchantId, mCountry);
        MobilePay.getInstance().setCaptureType(mCaptyreType);
        MobilePay.getInstance().setReturnSeconds(mReturnSeconds);
        MobilePay.getInstance().setTimeoutSeconds(mTimeoutSeconds);

        mPaymentPromise = promise;

        mPayment = new Payment();
        mPayment.setProductPrice(new BigDecimal(productPrice));
        mPayment.setOrderId(orderId);

        // Create a payment Intent using the Payment object from above.
        Intent paymentIntent = MobilePay.getInstance().createPaymentIntent(mPayment);

        // We now jump to MobilePay to complete the transaction. Start MobilePay and wait for the result using an unique result code of your choice.
        getCurrentActivity().startActivityForResult(paymentIntent, MOBILEPAY_PAYMENT_REQUEST_CODE);
    }

    @ReactMethod
    public void setTimeoutSeconds(int seconds) {
        mTimeoutSeconds = seconds;
    }

    @ReactMethod
    public void setReturnSeconds(int seconds) {
        mReturnSeconds = seconds;
    }

    @ReactMethod
    public void setCaptureType(String captureType) {
        mCaptyreType = CaptureType.valueOf(captureType);
    }

    @ReactMethod
    public void setCountry(String country) {
        mCountry = Country.valueOf(country);
    }

    @ReactMethod
    public void setMerchantId(String merchantId) {
        mMerchantId = merchantId;
    }

    @ReactMethod
    public void isMobilePayInstalled(String country, final Callback successCb, final Callback failureCb) {
        try {
            Country mobilePayCountry = Country.valueOf(country);
            successCb.invoke(MobilePay.getInstance().isMobilePayInstalled(getReactApplicationContext(), mobilePayCountry));
        } catch (Exception e) {
            failureCb.invoke(e.toString());
        }
    }

    @Override
    public Map<String, Object> getConstants() {
        final Map<String, Object> constants = new HashMap<>();

        constants.put("CAPTURE_TYPE_CAPTURE", CaptureType.CAPTURE.name());
        constants.put("CAPTURE_TYPE_RESERVE", CaptureType.RESERVE.name());
        constants.put("CAPTURE_TYPE_PARTIALCAPTURE", CaptureType.PARTIAL_CAPTURE.name());

        constants.put("COUNTRY_DENMARK", Country.DENMARK.name());
        constants.put("COUNTRY_NORWAY", Country.NORWAY.name());
        constants.put("COUNTRY_FINLAND", Country.FINLAND.name());

        return constants;
    }


}
