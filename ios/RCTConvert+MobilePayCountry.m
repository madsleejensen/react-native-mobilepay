//
//  RCTConvert+MobilePayCountry.m
//  RNMobilePay
//
//  Created by Mads Lee Jensen on 05/06/2017.
//  Copyright © 2017 Facebook. All rights reserved.
//

#import "RCTConvert+MobilePayCountry.h"

@implementation RCTConvert (MobilePayCountry)

RCT_ENUM_CONVERTER(
   	MobilePayCountry,
   	(@{
      @"MobilePayCountry_Denmark": @(MobilePayCountry_Denmark),
      @"MobilePayCountry_Norway": @(MobilePayCountry_Norway),
      @"MobilePayCountry_Finland": @(MobilePayCountry_Finland)
  	}), MobilePayCountry_Denmark, integerValue
)

@end
