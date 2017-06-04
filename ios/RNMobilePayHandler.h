//
// Created by Mads Lee Jensen on 04/06/2017.
// Copyright (c) 2017 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <React/RCTBridgeModule.h>


@interface RNMobilePayHandler : NSObject

+ (instancetype)sharedInstance;
- (void)handleMobilePayPaymentWithUrl:(NSURL *)url;
- (void)createPayment:(NSString *)orderId productPrice:(float)productPrice resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

@end
