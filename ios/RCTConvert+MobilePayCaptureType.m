//
//  RCTConvert+MobilePayCaptureType.m
//  RNMobilePay
//
//  Created by Mads Lee Jensen on 05/06/2017.
//  Copyright © 2017 Facebook. All rights reserved.
//

#import "RCTConvert+MobilePayCaptureType.h"

@implementation RCTConvert (MobilePayCaptureType)
RCT_ENUM_CONVERTER(
   	MobilePayCaptureType,
   	(@{
      @"MobilePayCaptureType_Capture": @(MobilePayCaptureType_Capture),
      @"MobilePayCaptureType_Reserve": @(MobilePayCaptureType_Reserve),
      @"MobilePayCaptureType_PartialCapture": @(MobilePayCaptureType_PartialCapture)
  	}), MobilePayCaptureType_Capture, integerValue
)
@end
