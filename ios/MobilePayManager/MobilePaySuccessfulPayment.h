//
//  MobilePaySuccessfulPayment.h
//  MobilePayManager
//
//  Created by Lars Elgaard Mikkelsen on 23/09/15.
//  Copyright © 2015 DanskeBank A/S. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MobilePaySuccessfulPayment : NSObject

@property (nonatomic, strong, readonly) NSString *orderId;
@property (nonatomic, strong, readonly) NSString *transactionId;
@property (nonatomic, strong, readonly) NSString *signature;
@property (nonatomic, readonly) float productPrice;
@property (nonatomic, readonly) float amountWithdrawnFromCard;

- (instancetype)initWithOrderId:(NSString *)orderId transactionId:(NSString *)transactionId signature:(NSString *)signature productPrice:(float)productPrice amountWithdrawnFromCard:(float)amountWithdrawnFromCard;

@end
