//
//  MobilePayPayment.h
//  MobilePayManager
//
//  Created by Thomas Fekete Christensen on 27/07/15.
//  Copyright (c) 2015 DanskeBank A/S. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Contains information about the payment being processed.
 */
@interface MobilePayPayment : NSObject

// Required
@property (nonatomic, strong) NSString *orderId;
@property (nonatomic) float productPrice;


// Optional
@property (nonatomic, strong) NSString *productName DEPRECATED_ATTRIBUTE;
@property (nonatomic, strong) UIImage *productImage DEPRECATED_ATTRIBUTE;
@property (nonatomic, strong) NSString *receiptMessage DEPRECATED_ATTRIBUTE;
@property (nonatomic, strong) NSString *bulkRef;

/**
 * Initialize payment object with required values
 * orderId: Text with a max length of 50 characters. Sent through the purchase flow and returned to your app when the payment is completed so that you are able to deliver the right product.
 * productName: obsolete
 * productPrice: price of the product
 */
- (MobilePayPayment *)initWithOrderId:(NSString *)orderId productPrice:(float)productPrice;

@end
