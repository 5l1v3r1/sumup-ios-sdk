//
//  SMPCheckoutRequest.h
//  SumupSDK
//
//  Created by Lukas Mollidor on 23.01.14.
//  Copyright (c) 2014 SumUp Payments Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 * Currency codes to be used in checkout (ISO 4217 code).
 * Other currency codes are permissible in the request object,
 * but are likely not to be accepted during the checkout.
 */

extern NSString *const SMPCurrencyCodeBRL;
extern NSString *const SMPCurrencyCodeCHF;
extern NSString *const SMPCurrencyCodeEUR;
extern NSString *const SMPCurrencyCodeGBP;
extern NSString *const SMPCurrencyCodePLN;

typedef NS_OPTIONS (NSUInteger, SMPPaymentOptions) {
    SMPPaymentOptionAny = 0,
    SMPPaymentOptionCardReader = 1 << 0,
    SMPPaymentOptionMobilePayment = 1 << 1,
};

/// Encapsulates all information that is necessary during a checkout with the SumUp.
@interface SMPCheckoutRequest : NSObject

/**
 \abstract Creates a new checkout request.
 
 \param totalAmount The total amount to be charged to a customer. Cannot be nil.
 \param title An optional title to be displayed in the merchant's history and on customer receipts.
 \param currencyCode Currency Code in which the total should be charged (ISO 4217 code, see SMPCurrencyCode). Cannot be nil, has to match the currency of the merchant logged in.
 \param options Payment options to choose a payment type(card reader, mobile payment...)
 
 \discussion Be careful when creating the NSDecimalNumber to not
 falsely use the NSNumber class creator methods.
 Use SMPPaymentOptionAny to not put restrictions on the desired payment types.
 
 \returns A new request object or nil if totalAmount or currencyCode are nil.
 */
+ (SMPCheckoutRequest *)requestWithTotal:(NSDecimalNumber *)totalAmount
                                   title:(NSString *)title
                            currencyCode:(NSString *)currencyCode
                          paymentOptions:(SMPPaymentOptions)paymentOptions;

/**
 \abstract Creates a new checkout request.
 
 \param totalAmount The total amount to be charged to a customer. Cannot be nil.
 \param title An optional title to be displayed in the merchant's history and on customer receipts.
 \param currencyCode Currency Code in which the total should be charged (ISO 4217 code, see SMPCurrencyCode). Cannot be nil, has to match the currency of the merchant logged in. Use [[[SumupSDK currentMerchant] currencyCode].
 
 \discussion Be careful when creating the NSDecimalNumber to not
 falsely use the NSNumber class creator methods.
 
 \returns A new request object or nil if totalAmount or currencyCode are nil.
 */
+ (SMPCheckoutRequest *)requestWithTotal:(NSDecimalNumber *)totalAmount
                                   title:(NSString *)title
                            currencyCode:(NSString *)currencyCode;

/// The total amount to be charged to a customer.
@property (strong, readonly) NSDecimalNumber *totalAmount;

/// A title to be displayed in the merchant's history and on customer receipts.
@property (strong, readonly) NSString *title;

/// Currency Code in which the total should be charged (ISO 4217 code, see SMPCurrencyCode). Cannot be nil.
@property (strong, readonly) NSString *currencyCode;

/// Payment options to choose a payment type
@property (assign, readonly) SMPPaymentOptions paymentOptions;

/**
 *  An (optional) ID to be associated with this transaction.
 *  See https://sumup.com/integration#transactionReportingAPIs
 *  on how to retrieve a transaction using this ID.
 *  This ID has to be unique in the scope of a SumUp merchant account and its sub-accounts.
 *  It must not be longer than 128 characters and can only contain printable ASCII characters.
 */
@property (strong) NSString *foreignTransactionID;

@end
