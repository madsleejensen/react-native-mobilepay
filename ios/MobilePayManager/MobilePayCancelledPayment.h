//
//  MobilePayCancelledPayment.h
//  MobilePayManager
//
//  Created by Lars Elgaard Mikkelsen on 08/12/2015.
//  Copyright © 2015 DanskeBank A/S. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MobilePayCancelledPayment : NSObject

@property (nonatomic, strong, readonly) NSString *orderId;

- (instancetype)initWithOrderId:(NSString *)orderId;

@end
