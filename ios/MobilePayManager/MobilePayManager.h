//
//  MobilePayManager.h
//
//  Created by Troels Richter on 3/20/14.
//  Copyright (c) 2014 Trifork A/S All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreImage/CoreImage.h>

#import "MobilePayPayment.h"
#import "MobilePaySuccessfulPayment.h"
#import "MobilePayCancelledPayment.h"

typedef NS_ENUM(NSInteger, ErrorCode) {
    // Unknown error occurred
    ErrorCodeUnknown = 0,
    // Invalid parameters sent to MobilePay app
    ErrorCodeInvalidParameters = 1,
    // VerifyMerchant request failed - validation af merchant failed.
    ErrorCodeMerchantValidationFailed = 2,
    // MobilePay app is out of date and should be updated
    ErrorCodeUpdateApp = 3,
    // Merchant is not valid
    ErrorCodeMerchantNotValid = 4,
    // Hmac parameter is not valid
    ErrorCodeHMACNotValid = 5,
    // MobilePay timeout, the purchase took more than 5 minutes
    ErrorCodeTimeOut = 6,
    // MobilePay amount limits exceeded. Open MobilePay 'Beløbsgrænser' to see your status.
    ErrorCodeLimitsExceeded = 7,
    // Timeout set in merchant app exceeded
    ErrorCodeMerchantTimeout = 8,
    // Invalid signature
    ErrorCodeInvalidSignature = 9,
    // MobilePay SDK version is outdated
    ErrorCodeSDKIsOutdated = 10,
    // The given OrderId is already used. An OrderId has to be unique.
    ErrorCodeOrderIdAlreadyUsed = 11,
    // The payment was rejected because the user is chosen for fraud validation.
    ErrorCodePaymentRejectedFraud = 12,
}DEPRECATED_MSG_ATTRIBUTE("Use 'typedef NS_ENUM(NSInteger, MobilePayErrorCode)' instead");

typedef NS_ENUM(NSInteger, MobilePayErrorCode) {
    // Unknown error occurred
    MobilePayErrorCodeUnknown = 0,
    // Invalid parameters sent to MobilePay app
    MobilePayErrorCodeInvalidParameters = 1,
    // VerifyMerchant request failed - validation af merchant failed.
    MobilePayErrorCodeMerchantValidationFailed = 2,
    // MobilePay app is out of date and should be updated
    MobilePayErrorCodeUpdateApp = 3,
    // Merchant is not valid
    MobilePayErrorCodeMerchantNotValid = 4,
    // Hmac parameter is not valid
    MobilePayErrorCodeHMACNotValid = 5,
    // MobilePay timeout, the purchase took more than 5 minutes
    MobilePayErrorCodeTimeOut = 6,
    // MobilePay amount limits exceeded. Open MobilePay 'Beløbsgrænser' to see your status.
    MobilePayErrorCodeLimitsExceeded = 7,
    // Timeout set in merchant app exceeded
    MobilePayErrorCodeMerchantTimeout = 8,
    // Invalid signature
    MobilePayErrorCodeInvalidSignature = 9,
    // MobilePay SDK version is outdated
    MobilePayErrorCodeSDKIsOutdated = 10,
    // The given OrderId is already used. An OrderId has to be unique.
    MobilePayErrorCodeOrderIdAlreadyUsed = 11,
    // The payment was rejected because the user is chosen for fraud validation.
    MobilePayErrorCodePaymentRejectedFraud = 12,
};


typedef NS_ENUM(NSInteger, MobilePayCaptureType)
{
    MobilePayCaptureType_Capture = 0,          // True for capture
    MobilePayCaptureType_Reserve = 1,          // False -> Reserve
    MobilePayCaptureType_PartialCapture = 2    // Partial capture
};

typedef NS_ENUM(NSInteger, MobilePayCountry)
{
    MobilePayCountry_Denmark = 0,
    MobilePayCountry_Norway = 1,
    MobilePayCountry_Finland = 2,
};

typedef void(^MobilePayPaymentErrorBlock)(NSError * __nonnull error);
typedef void(^MobilePayCallbackSuccessBlock)(NSString * __nullable orderId, NSString * __nullable transactionId, NSString * __nullable signature);
typedef void(^MobilePayCallbackErrorBlock)(NSString * __nullable orderId, int errorCode, NSString * __nullable errorMessage);
typedef void(^MobilePayCallbackCancelBlock)(NSString * __nullable orderId);
typedef void(^MobilePayPaymentSuccessBlock)(MobilePaySuccessfulPayment * __nullable mobilePaySuccessfulPayment);
typedef void(^MobilePayPaymentCancelledBlock)(MobilePayCancelledPayment * __nullable mobilePayCancelledPayment);
                                           
@interface MobilePayManager : NSObject

+ (MobilePayManager * __nonnull) sharedInstance;

/**
 * @param merchantId: merchant id delivered from DanskeBank MobilePay through your MobilePay business agreement
 * @param urlscheme: urlscheme for your app setup under UrlIdentifier in your info.plist (this needs to be done to enable app switching in general)
 * PLEASE NOTE: This will as a default use the mobilepay:// urlscheme for the Danish MobilePay App, and set country to DK
 */
-(void)setupWithMerchantId:(NSString * __nonnull)merchantId merchantUrlScheme:(NSString * __nonnull)merchantUrlScheme
DEPRECATED_MSG_ATTRIBUTE("Use setupWithMerchantId:(NSString * __nonnull)merchantId merchantUrlScheme:(NSString * __nonnull)merchantUrlScheme country:(Country __nonnull)country instead");

/**
 * @param merchantId: merchant id delivered from DanskeBank MobilePay through your MobilePay business agreement
 * @param urlscheme: urlscheme for your app setup under UrlIdentifier in your info.plist (this needs to be done to enable app switching in general)
 * @param Country: The country / version of MobilePay you wish your app to work with - Denmark (DK - mobilepay:// - which also is the default), Norway (NO - urlscheme: mobilepayno://), Finland (FI - mobilepayfi://)
 */
-(void)setupWithMerchantId:(NSString * __nonnull)merchantId merchantUrlScheme:(NSString * __nonnull)merchantUrlScheme country:(MobilePayCountry)country;


/**
 * @param merchantId: merchant id delivered from DanskeBank MobilePay through your MobilePay business agreement
 * @param urlscheme: urlscheme for your app setup under UrlIdentifier in your info.plist (this needs to be done to enable app switching in general)
 * @param timeoutseconds: seconds that you allow the user to spend in the MobilePay app before returning to the merchant app, if exceeded when you try to swipe in Mobile Pay errorcode 8 is returned. Default is 0 = never timeout
 * @param returnseconds: seconds spend on the MobilePay receipt screen before returning to the merchant app. Default is 5 seconds
 * @param capture: Determines if the payment is a reservation or instant capture - default is Yes for instant capture
 */
-(void) setupWithMerchantId:(NSString * __nonnull)merchantId merchantUrlScheme:(NSString * __nonnull)merchantUrlScheme timeoutSeconds:(int)timeoutSeconds returnSeconds:(int)returnSeconds capture:(BOOL)capture DEPRECATED_MSG_ATTRIBUTE("Use setupWithMerchantId:merchantUrlScheme:timeoutSeconds:returnSeconds:captureType: method instead.");

/**
 * @param merchantId: merchant id delivered from DanskeBank MobilePay through your MobilePay business agreement
 * @param urlscheme: urlscheme for your app setup under UrlIdentifier in your info.plist (this needs to be done to enable app switching in general)
 * @param timeoutseconds: seconds that you allow the user to spend in the MobilePay app before returning to the merchant app, if exceeded when you try to swipe in Mobile Pay errorcode 8 is returned. Default is 0 = never timeout
 * @param returnseconds: seconds spend on the MobilePay receipt screen before returning to the merchant app. Default is 5 seconds
 * @param capture: Determines if the payment is a reservation or instant capture - default is Yes for instant capture
 * @param country: The country / version of MobilePay you wish your app to work with - Denmark (DK - mobilepay:// - which also is the default), Norway (NO - urlscheme: mobilepayno://), Finland (FI - mobilepayfi://)
 */
-(void) setupWithMerchantId:(NSString * __nonnull)merchantId merchantUrlScheme:(NSString * __nonnull)merchantUrlScheme timeoutSeconds:(int)timeoutSeconds returnSeconds:(int)returnSeconds captureType:(MobilePayCaptureType)captureType country:(MobilePayCountry)country;

/**
 * will start the MobilePay payment flow by swithing to the MobilePay app
 *
 * @param orderId: Text with a max length of 50 characters. Sent through the purchase flow and returned to your app when the payment is completed so that you are able to deliver the right product.
 * @param productPrice: price of the product
 * @param receiptMessage: Text with a max length of 66 characters. the message is shown at the bottom of the MobilePay receipt
 * @param errorBlock : An error will occur if mobile pay isn't installed
 */
-(void) beginMobilePaymentWithOrderId:(NSString * __nonnull)orderId productPrice:(float)productPrice receiptMessage:(NSString * __nullable)receiptMessage error:(__nullable MobilePayPaymentErrorBlock)errorBlock DEPRECATED_MSG_ATTRIBUTE("Use beginMobilePaymentWithPayment: method instead.");

/**
 * will start the MobilePay payment flow by swithing to the MobilePay app
 *
 * @param orderId: Text with a max length of 50 characters. Sent through the purchase flow and returned to your app when the payment is completed so that you are able to deliver the right product.
 * @param productName: obsolete
 * @param productPrice: price of the product
 * @param productImage: image of the product (only supported for a few merchants with a special agreement with MobilePay)
 * @param receiptMessage: Text with a max length of 66 characters. the message is shown at the bottom of the MobilePay receipt
 * @param errorBlock : An error will occur if mobile pay isn't installed
 */
-(void) beginMobilePaymentWithOrderId:(NSString * __nonnull)orderId productName:(NSString * __nullable)productName productPrice:(float)productPrice productImage:(UIImage * __nullable)productImage receiptMessage:(NSString * __nullable)receiptMessage error:(__nullable MobilePayPaymentErrorBlock)errorBlock DEPRECATED_MSG_ATTRIBUTE("Use beginMobilePaymentWithPayment: method instead.");

/**
 * will start the MobilePay payment flow by swithing to the MobilePay app
 *
 * @param payment: payment object for creating order in mobilepay
 */
-(void) beginMobilePaymentWithPayment:(MobilePayPayment * __nonnull)payment error:(__nullable MobilePayPaymentErrorBlock)errorBlock;

/**
 *  This method handles all callbacks coming from MobilePay after having app switced to it.
 *
 *  @discussion
 *  This method must be added to your AppDelegate in:
 *  @code
 *  - (BOOL)application:(nonnull UIApplication *)app openURL:(nonnull NSURL *)url options:(nonnull NSDictionary<NSString *,id> *)options
 *  @endcode
 *  or
 *  @code
 *  - (BOOL)application:(nonnull UIApplication *)application openURL:(nonnull NSURL *)url sourceApplication:(nullable NSString *)sourceApplication annotation:(nonnull id)annotation
 *  @endcode
 *  if you are developing with a deployment target prior to iOS 9.
 *
 * @param url : the callback url provided by the AppDelegate method
 * @param success:
 * orderId: the SDK has validated that the orderId is the same as the one sent to MobilePay
 * transactionId: MobilePay transactionId that can be found in the MobilePay activity list
 * signature: this is the payment signature that the SDK validates against to ensure the payment authenticity
 * @param error:
 * errorCodes:
 *  1 = Invalid parameters sent to MobilePay app.
 *  2 = VerifyMerchant request failed - validation af merchant failed.
 *  3 = MobilePay app is out of date and should be updated
 *  4 = Merchant is not valid
 *  5 = Hmac parameter is not valid
 *  6 = MobilePay timeout, the purchase took more than 5 minutes
 *  7 = MobilePay amount limits exceeded. Open MobilePay 'Beløbsgrænser' to see your status.
 *  8 = Timeout set in merchant app exceeded
 *  9 = Invalid signature
 * 10 = MobilePay SDK version is outdated
 * 11 = The given OrderId is already used. An OrderId has to be unique.
 * 12 = The payment was rejected because the user is chosen for fraud validation.
 * @param cancel :
 * orderId: the SDK has validated that the orderId is the same as the one sent to MobilePay
 *
 * Most of there errors are technical errors (1,2,4,5,9,10,11) that must be presented as a generic error message without details to the user, where others SHOULD BE HANDLED BY YOUR APP (3,6,7,8,12) to guide the user in the right direction.
 */

-(void)handleMobilePayPaymentWithUrl:(NSURL * __nonnull)url success:(__nullable MobilePayPaymentSuccessBlock)successfulBlock error:(__nullable MobilePayPaymentErrorBlock)errorBlock cancel:(__nullable MobilePayPaymentCancelledBlock)cancelBlock;


/**
 * Deprecated method - please use method above
 */
-(void)handleMobilePayCallbacksWithUrl:(NSURL * __nonnull)url success:(__nonnull MobilePayCallbackSuccessBlock)successBlock error:(__nullable MobilePayCallbackErrorBlock)errorBlock cancel:(__nullable MobilePayCallbackCancelBlock)cancelBlock DEPRECATED_MSG_ATTRIBUTE("Use 'handleMobilePayPaymentWithUrl:(NSURL * __nonnull)url success:(__nullable MobilePayPaymentSuccessBlock)successfulBlock error:(__nullable MobilePayPaymentErrorBlock)errorBlock cancel:(__nullable MobilePayPaymentCancelledBlock)cancelBlock' method instead");


/**
 *Checks if url can be opened, and it will only for check for the appstore version of MobilePay
 *
 *Currently the mobilepay app is available in three countries, and each 'Country' has it's own urlscheme:
 *
 *Denmark: mobilepay://
 *Norway: mobilepayno://
 *Finland: mobilepayfi://
 *
 * When running iOS9 SDK / Xcode7 you need to whitelist the MobilePay URL, before you can use this method.
 *
 *if you want to check for the Danish version of MobilePay, then add the following:
 * <key>LSApplicationQueriesSchemes</key>
 * <array>
 * <string>mobilepay</string>
 * <string>yourotherurlschemes</string>
 * </array>
 *
 *if you want to check for the Norwegian version of MobilePay, then add the following:
 * <key>LSApplicationQueriesSchemes</key>
 * <array>
 * <string>mobilepayno</string>
 * <string>yourotherurlschemes</string>
 * </array>
 *
 *if you want to check for the Finish version of MobilePay, then add the following:
 * <key>LSApplicationQueriesSchemes</key>
 * <array>
 * <string>mobilepayfi</string>
 * <string>yourotherurlschemes</string>
 * </array>
 */
-(BOOL)isMobilePayInstalled:(MobilePayCountry)country;

/**
 * capture: Determines if the payment is a reservation or instant capture - default is Yes for instant capture
 */
@property (nonatomic) BOOL capture DEPRECATED_MSG_ATTRIBUTE("Use captureType property instead.");

/**
 * capture: Determines if the payment is a reservation, instant capture or  - default is "Capture" for instant capture
 */
@property (nonatomic) MobilePayCaptureType captureType;

/**
 * Country
 */
@property (nonatomic) MobilePayCountry country;

/**
 * ErrorCode
 */
@property (nonatomic, readonly) ErrorCode errorCode DEPRECATED_MSG_ATTRIBUTE("Use MobilePayErrorCode instead.");

/**
 * ErrorCode
 */
@property (nonatomic, readonly) MobilePayErrorCode mobilePayErrorCode;

/**
 * The version of the SDK
 */
@property (nonatomic, readonly) NSString * __nonnull sdkVersion;

/**
 * merchant id delivered from DanskeBank MobilePay through your MobilePay business agreement
 */
@property (nonatomic) NSString * __nullable merchantId;

/**
 * a time limit you set for which the user must have swiped in MobilePay to confirm the purchase. if exceeded errorcode 8 is returned. Default is 0 = never timeout
 */
@property (nonatomic) int timeoutSeconds;

/**
 * seconds spend on the MobilePay receipt screen before returning to the merchant app - Default is 1 second
 */
@property (nonatomic) int returnSeconds;

/**
 * checks if mobilepay:// url can be opened, and it will only for check for the appstore version of MobilePay
 * 
 * When running iOS9 SDK / Xcode7 you need to whitelist the MobilePay URL, before you can use this method.
 *
 * <key>LSApplicationQueriesSchemes</key>
 * <array>
 * <string>mobilepay</string>
 * <string>yourotherurlschemes</string>
 * </array>
 */
@property (nonatomic, readonly) BOOL isMobilePayInstalled DEPRECATED_MSG_ATTRIBUTE("Use isMobilePayInstalled:(MobilePayCountry)country instead.");

/*
 * the urls for the different versions of MobilePay in AppStore
 */
@property (nonatomic, readonly) NSString * __nonnull mobilePayAppStoreLinkDK;

@property (nonatomic, readonly) NSString * __nonnull mobilePayAppStoreLinkNO;

@property (nonatomic, readonly) NSString * __nonnull mobilePayAppStoreLinkFI;

/**
 * isAppSwitchInProgress = YES after calling beginMobilePaymentWithOrderId and set to NO after calling handleMobilePayCallbacksWithUrl
 */
@property (nonatomic, readonly) BOOL isAppSwitchInProgress;

/**
 * returns the version of signature. This can be used to make specific logic for each version, which can be useful for example when validating different signatures
 */
@property (nonatomic, readonly) NSString * __nonnull signatureVersion;

/**
 * ServerCallbackUrl is deprecated.
 */
-(void)setServerCallbackUrl:(NSString * __nonnull)serverCallbackUrl DEPRECATED_MSG_ATTRIBUTE("ServerCallbackUrl is deprecated, setting this property will have no effect.");

/**
 * for internal development purpose only
 */
-(void)setCertificate:(NSString * __nonnull)certificate;
/**
 * for internal development purpose only
 */
-(void)setMobilePayUrlScheme:(NSString * __nonnull)mobilePayUrlScheme;


@end
