
package dk.madslee.mobilepay;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Callback;

public class RNMobilePayModule extends ReactContextBaseJavaModule {

  private final ReactApplicationContext reactContext;

  public RNMobilePayModule(ReactApplicationContext reactContext) {
    super(reactContext);
    this.reactContext = reactContext;
  }

  @Override
  public String getName() {
    return "RNMobilePay";
  }
}