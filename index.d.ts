declare module 'react-native-mobilepay'{

    //FUNCTIONS

    //setup functions
    export function setup(merchantId: any, country: any): any
    export function setup(merchantId: any, country: any, merchantUrlScheme: any): any
    export function setCaptureType(type: any): any
    export function setCountry(type: any): any

    //install check functions
    export function isMobilePayInstalledDenmark(): any
    export function isMobilePayInstalledNorway(): any
    export function isMobilePayInstalledFinland(): any

    //timer/delay functions
    export function setTimeoutSeconds(seconds: any): any
    export function setReturnSeconds(seconds:any): any

    //create payment function
    export function createPayment(orderId: any, amount: any): any

    // --------------------------------------------------------------------------------------

    //TYPES

    //capture types
    export const CAPTURE_TYPE_CAPTURE: any
    export const CAPTURE_TYPE_RESERVE: any

    //country constants
    export const COUNTRY_DENMARK: any
    export const COUNTRY_NORWAY: any
    export const COUNTRY_FINLAND: any

}