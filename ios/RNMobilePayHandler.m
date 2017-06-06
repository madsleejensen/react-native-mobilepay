//
// Created by Mads Lee Jensen on 04/06/2017.
// Copyright (c) 2017 Facebook. All rights reserved.
//

#import "RNMobilePayHandler.h"
#import "MobilePayManager.h"

@implementation RNMobilePayHandler {
    RCTPromiseResolveBlock _resolveBlock;
    RCTPromiseRejectBlock _rejectBlock;

    BOOL _hasBeenSetup;
    NSString *_merchantId;
    MobilePayCountry _country;
    NSString *_merchantUrlScheme;
}

+ (instancetype)sharedInstance {
    static RNMobilePayHandler *sharedInstance = nil;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        sharedInstance = [[RNMobilePayHandler alloc] init];
    });
    
    return sharedInstance;
}

-(instancetype)init {
    self = [super init];
    if (self) {
        _merchantId = @"APPDK0000000000";
        _country = MobilePayCountry_Denmark;
        _merchantUrlScheme = @"";
    }
    
    return self;
}

-(void)setup:(NSString *)merchantId country:(MobilePayCountry)country merchantUrlScheme:(NSString *)merchantUrlScheme {
    _merchantId = merchantId;
    _country = country;
    _merchantUrlScheme = merchantUrlScheme;
    
    _hasBeenSetup = true;
}

-(void)setCountry:(MobilePayCountry)country {
    _country = country;
}

-(void)setMerchantId:(NSString *)merchantId {
    _merchantId = merchantId;
}

- (void)createPayment:(NSString *)orderId productPrice:(float)productPrice resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject
{
    if (!_hasBeenSetup) {
        reject(@"-1", @"MobilePay has not been setup. Please call setup(merchantId, country, merchantUrlScheme) first.", nil);
        return;
    }
    
    [[MobilePayManager sharedInstance] setupWithMerchantId:_merchantId merchantUrlScheme:_merchantUrlScheme country:_country];
    
    MobilePayPayment *payment = [[MobilePayPayment alloc] initWithOrderId:orderId productPrice:productPrice];

    _resolveBlock = [resolve copy];
    _rejectBlock = [reject copy];

    [[MobilePayManager sharedInstance] beginMobilePaymentWithPayment:payment error:^(NSError * _Nonnull error) {
        NSLog(@"beginMobilePaymentWithPayment - error %@", error);
        
        [self handleOnError:error];
        [self cleanupHandlers];
    }];
}

- (bool)handleMobilePayPaymentWithUrl:(NSURL *)url
{
    if (![url.absoluteString hasPrefix:_merchantUrlScheme]) {
        return false;
    }
    
    [[MobilePayManager sharedInstance] handleMobilePayPaymentWithUrl:url success:^(MobilePaySuccessfulPayment * _Nullable mobilePaySuccessfulPayment) {
        NSString *orderId = mobilePaySuccessfulPayment.orderId;
        NSString *transactionId = mobilePaySuccessfulPayment.transactionId;
        NSString *amountWithdrawnFromCard = [NSString stringWithFormat:@"%f",mobilePaySuccessfulPayment.amountWithdrawnFromCard];
        NSLog(@"MobilePay purchase succeeded: Your have now paid for order with id '%@' and MobilePay transaction id '%@' and the amount withdrawn from the card is: '%@'", orderId, transactionId,amountWithdrawnFromCard);

        _resolveBlock(@{
            @"isCancelled": @NO,
            @"orderId": orderId,
            @"amountWithdrawnFromCard": amountWithdrawnFromCard,
            @"transactionId": transactionId,
            @"transactionSignature": mobilePaySuccessfulPayment.signature
        });

        [self cleanupHandlers];
    } error:^(NSError * _Nonnull error) {
        NSDictionary *dict = error.userInfo;
        NSString *errorMessage = [dict valueForKey:NSLocalizedFailureReasonErrorKey];
        NSLog(@"MobilePay purchase failed:  Error code '%li' and message '%@'",(long)error.code,errorMessage);

        //TODO: show an appropriate error message to the user. Check MobilePayManager.h for a complete description of the error codes

        //An example of using the MobilePayErrorCode enum
        //if (error.code == MobilePayErrorCodeUpdateApp) {
        //    NSLog(@"You must update your MobilePay app");
        //}

        [self handleOnError:error];
        [self cleanupHandlers];

    } cancel:^(MobilePayCancelledPayment * _Nullable mobilePayCancelledPayment) {
        NSLog(@"MobilePay purchase with order id '%@' cancelled by user", mobilePayCancelledPayment.orderId);

        _resolveBlock(@{
            @"isCancelled": @YES,
            @"orderId": mobilePayCancelledPayment.orderId,
        });

        [self cleanupHandlers];
    }];
    
    return true;
}

- (void)handleOnError:(NSError *)error {
    if (_rejectBlock) {
       _rejectBlock([NSString stringWithFormat:@"%d", error.code], error.localizedDescription, error);
    }
}

- (void)cleanupHandlers {
    _rejectBlock = nil;
    _resolveBlock = nil;
}

@end
