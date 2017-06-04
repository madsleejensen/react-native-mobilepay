//
// Created by Mads Lee Jensen on 04/06/2017.
// Copyright (c) 2017 Facebook. All rights reserved.
//

#import "RNMobilePay.h"
#import "MobilePayManager.h"
#import "RNMobilePayHandler.h"


@implementation RNMobilePay {
}

RCT_EXPORT_MODULE();

// only allow code to be run on main-queue
- (dispatch_queue_t)methodQueue
{
  return dispatch_get_main_queue();
}

RCT_EXPORT_METHOD(createPayment:(NSString *)orderId productPrice:(float)productPrice resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject)
{
    [[RNMobilePayHandler sharedInstance] createPayment:orderId productPrice:productPrice resolve:resolve reject:reject];
}

RCT_EXPORT_METHOD(setTimeoutSeconds:(int)seconds)
{
    [[MobilePayManager sharedInstance] setTimeoutSeconds:seconds];
}

RCT_EXPORT_METHOD(setReturnSeconds:(int)seconds)
{
    [[MobilePayManager sharedInstance] setReturnSeconds:seconds];
}

RCT_EXPORT_METHOD(setCountry:(MobilePayCountry)county)
{
    [[MobilePayManager sharedInstance] setCountry:county];
}

RCT_EXPORT_METHOD(setCaptureType:(MobilePayCaptureType)captureType)
{
    [[MobilePayManager sharedInstance] setCaptureType:captureType];
}

RCT_EXPORT_METHOD(setMerchantId:(NSString *)merchantId)
{
    [[MobilePayManager sharedInstance] setMerchantId:merchantId];
}

- (NSDictionary *)constantsToExport {
    return @{
      @"isMobilePayInstalledDenmark": @([[MobilePayManager sharedInstance] isMobilePayInstalled:MobilePayCountry_Denmark]),
      @"isMobilePayInstalledNorway": @([[MobilePayManager sharedInstance] isMobilePayInstalled:MobilePayCountry_Norway]),
      @"isMobilePayInstalledFinland": @([[MobilePayManager sharedInstance] isMobilePayInstalled:MobilePayCountry_Finland]),
    };
}

@end
