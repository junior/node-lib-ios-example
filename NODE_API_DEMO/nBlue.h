//
//  nBlue.h
//  nBlue 1.0
//
//  Created by DERIC KRAMER on 1/18/12.
//  Copyright (c) 2012 BlueRadios, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@class BRDevice;

enum {
    BRServiceNone = 0,          //This value should never be used for scan.  It will find no devices
    BRServiceBRSP = 1,          //All BRSP devices
    BRServiceAll = 4294967295   //All BlueRadios devices
}; 
typedef UInt32 BRService;
/**
 Set of methods to be implemented as delegates for nBlue library callbacks.
 */
@protocol nBlueDelegate <NSObject>
@optional
/**
 Method that is called everytime a device is found.  
 @param A CBPeripheral object from the CoreBluetooth.framework that can be used to initialize BRDevice objects
 */
/*!  Typical use case involves checking peripherals to determine what to do. */
-(void) deviceFound:(CBPeripheral*)p;
/**
 Method that is called when scan_nBlue has completed.  
 */
/*!  Use if you need to know when scanning is finished. */
-(void) scanComplete;
/**
 Method is called signifying the completion of a connect request
 @param error
 An NSError object containing the error response if the call to connect failed to connect
 If == nil then no error occured and the device is now connected
 */
/*!  Put code here to handle connect confirmations. */
-(void) didConnect:(CBPeripheral*)p error:(NSError*)error;
/**
 Method that is called when a device is disconnected.  
 @param error
 An NSError object containing the error response if the call to disconnectDevice failed
 If == nil then no error occured and the device is now disconnected
 */
/*!  Put code here to handle disconnect confirmations. */
-(void) didDisconnect:(CBPeripheral*)p error:(NSError*)error;
/**
 Fires when isInitialized == YES.  This is a good place to start scanning, connecting, etc
 */
/*!  Put code here to handle nBlue initialization complete. */
-(void) nBlueReady;

@end

/**
 The manager class for use with BlueRadios BLE modules.  
 */
@interface nBlue : NSObject <CBCentralManagerDelegate, CBPeripheralDelegate> {
}

/**
 The delegate used for all nBlue callbacks.
 */
@property (nonatomic, weak) id <nBlueDelegate> nBlueDelegate;
/**
 A list of peripherals found by the scan_nBlue method.
 */
@property (nonatomic, readonly, strong, getter=getPeripherals) NSArray *peripherals;
/**
 Is set to YES if the device is currently powered on and available to use. (initWithDelegate has been called and has completed)
 */
@property (nonatomic, readonly, getter=initialized) BOOL isInitialized;

/**
 Get the shared nBlue instance
 @return nBlue object as id
 */
+(id) shared_nBlue;
/**
 Get the shared nBlue instance
 @param delegate 
 Will set the nBlueDelegate in the shared instance 
 @return nBlue object as id
 */
+(id) shared_nBlue:(id<nBlueDelegate>)delegate;
/**
Initialize an instance of this class using this funtion
 @param delegate 
    The delegate that will receive nBlue events.
 @return nBlue object as id
 */
-(id) initWithDelegate:(id<nBlueDelegate>)delegate;
/**
 Used to scan for devices.
 @param timeout the desired time (in seconds) to scan for devices.
 @param num a BRService enum value indicating which BlueRadios devices to filter. 
 <br><b>BRServiceNone</b> - This value should never be used.  Will return no devices.
 <br><b>BRServiceBRSP</b> - Devices that support the BRSP service
 <br><b>BRServiceAll</b>  - All BlueRadios devices will be returned in scan
 */
-(void) scan_nBlue:(int)timeout ServiceFilter:(BRService)num;
/**
 Used to stop scanning for devices. (Cancels a previous scan_nBlue call before the specified timeout)
 */
-(void) stopScan_nBlue;
/**
 Get a peripheral that was previously found by a scan_nBlue
 @param uuid 
 A NSString object with the uuid of the peripheral to search for.
 EX: @"00000000-0000-0000-0000-000000000000"
 @return
 The CBPeripheral object found.  Returns NULL if no peripheral found.
 */
-(CBPeripheral*)getPeripheral:(NSString *)uuid;
/**
 Connects to a BRDevice.
 @param d a peripheral that you want to connect to.
 */
-(void) connectDevice:(BRDevice*)d;
/**
 Disconnects a peripheral.
 @param p a peripheral that you want to disconnect.
 */
-(void) disconnectDevice:(BRDevice*)d;
/**
 Disconnects all devices opened by this application
 */
-(void) disconnectAll;
/**
 Gets an array of accepted service UUIDs.
 @param BRService mask used to generate the NSArray
 @return NSArray of CBUUID objects
 */
-(NSArray*)getAcceptedServices:(BRService)serviceFilter;

@end

@class nBlue;
//#import "Utilities.h"

enum {
    DeviceModeData = 1,
    DeviceModeRemoteCommand = 2
};
typedef NSUInteger DeviceMode;

@protocol BRDeviceDelegate <NSObject>
@optional
/**
 Method is called signifying the completion of a connect request
 @param error
 An NSError object containing the error response if the call to connect failed to connect
 If == nil then no error occured and the device is now connected
 */
-(void) didConnect:(NSError*)error;
/**
 Method is called signifying the completion of a disconnect request
 @param error
 An NSError object containing an error response associated with a disconnect.
 */
-(void) didDisconnect:(NSError*)error;
/**
 Method is called everytime data is received from the BLE device.
 @param response
 An NSData object containing the data received.
 */
-(void) deviceResponse:(NSData *)response;
/**
 Method is called everytime the BRSP mode of the device changes
 @param mode
 An DeviceMode indicating what BRSP mode the device is in
 */
-(void) modeChanged:(DeviceMode)mode;

@end

/**
 Represents a base BRDevice.  Inherit from this class to make specialized/custom Devices.
 */
@interface BRDevice : NSObject <CBPeripheralDelegate, BRDeviceDelegate> {
}

/**
 Returns true if the device is connected
 */
@property (nonatomic, readonly, getter=connected) BOOL isConnected;
/**
 A pointer to the CBPeripheral object that is associated with this decice
 */
@property (nonatomic, strong, readonly) CBPeripheral *cbPeripheral;
/**
 The BRSP mode of the device.
 @see -(void) changeBrspMode:(DeviceMode)mode;
 */
@property (nonatomic, readonly) DeviceMode mode;
/**
 The delegate used for all BRDevice callbacks.  Note: Defaults to BRdevice class or child class used to connect
 */
@property (nonatomic, weak) id <BRDeviceDelegate> deviceDelegate;

/**
 Initialize the BRDevice class with this method instead of init
 @param p an initialized peripheral object
 @return self as id
 */
-(id) initWithPeripheral:(CBPeripheral*)p;

/**
 Connects this device.
 @param manager an initialized nBlue manager object
 Note: Can use [nBlue shared_nBlue] to use a shared singleton instance
 */
-(void) connect:(nBlue*)manager;
/**
 Disconnects this device
 */
-(void) disconnect;
/**
 Sends a string to the device
 @param str a string to send to device.
 */
-(void) writeBrsp:(NSString*)str;
/**
 Changes modes of the BRSP service.
 @param mode an int used to set the mode of a device.
 1 = data mode
 2 = remote command mode
 */
-(void) changeBrspMode:(DeviceMode)mode;

@end
