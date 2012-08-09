//
//  libNode.h
//
//  Created by Wade Gasior on 4/26/12.
//  Copyright (c) 2012 Variable Technologies. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "nBlue.h"

#define MODULE_TYPE_NONE            0xff
#define MODULE_TYPE_LUMA            0x00
#define MODULE_TYPE_CLIMA           0x01
#define MODULE_TYPE_IR_THERMO       0x02
#define MODULE_TYPE_OXA             0x03
#define MODULE_TYPE_VERA            0x04

////////////////////////////////////////////////////////////////////////////////
/** This class represents a three-axis sensor reading. */
@interface VTSensorReading : NSObject
/** The x axis reading */
@property (readonly, nonatomic) int16_t x;
/** The y axis reading */
@property (readonly, nonatomic) int16_t y;
/** The z axis reading */
@property (readonly, nonatomic) int16_t z;

/** Returns a VTSensorReading object initialized with the three provided values.
 
    @param xVal The x axis value for the new reading
    @param yVal The y axis value for the new reading
    @param zVal The z axis value for the new reading
    @return A VTSensorReading initalized with the given values.
 */
-(id) initWithXValue: (int16_t)xVal y: (int16_t)yVal z: (int16_t)zVal;
@end

////////////////////////////////////////////////////////////////////////////////
/** This class represents a quaternion. */
@interface VTQuatReading : NSObject

/** q0 element of quaternion */
@property (readonly, nonatomic) float q0;
/** q1 element of quaternion */
@property (readonly, nonatomic) float q1;
/** q2 element of quaternion */
@property (readonly, nonatomic) float q2;
/** q3 element of quaternion */
@property (readonly, nonatomic) float q3;

/** Returns a VTQuatReading object intialized with the four provided values.
 
 @param q0 q0 element of quaternion
 @param q1 q1 element of quaternion
 @param q2 q2 element of quaternion
 @param q3 q3 element of quaternion
 @return A VTQuatReading object intialized with the provided values
 */
-(id) initWithQ0:(float)q0 q1:(float)q1 q2:(float)q2 q3:(float)q3;
@end

////////////////////////////////////////////////////////////////////////////////
@class VTNodeDevice;

/** The delegate for the VTNodeDevice class*/
@protocol NodeDeviceDelegate <NSObject>
@required
/** Invoked when a connection is established with the Node device 
 @param device The VTNodeDevice for which the connection was established
 */
-(void) nodeDeviceDidConnect:(VTNodeDevice *) device;
/**
 Invoked when the connection with a Node device is lost.
 @param device The VTNodeDevice from which the connection was lost
 */
-(void) nodeDeviceDidDisconnect:(VTNodeDevice *) device;
@optional

/** Invoked when a Node device changes its data mode
 
 @param device The VTNodeDevice that updated its data mode
 @param mode The new mode
 */
-(void) nodeDeviceDidUpdateDataMode: (VTNodeDevice *)device withMode:(DeviceMode)mode;

/** Invoked when a Node device communicates a gyroscope reading
    
    @param device The device that communicated its Gyro reading
    @param reading A VTSensorReading object containing the gyroscope reading
 */
-(void) nodeDeviceDidUpdateGyroReading: (VTNodeDevice *) device withReading: (VTSensorReading*)reading;

/** Invoked when a Node device communicates an accelerometer reading
    
    @param device The device that communicated an accelerometer reading
    @param reading A VTSensorReading object containing the accelerometer reading
 */
-(void) nodeDeviceDidUpdateAccReading: (VTNodeDevice *) device withReading: (VTSensorReading*)reading;

/** Invoked when a Node device communicates a magnetometer reading
 
 @param device The device that communicated a magnetometer reading
 @param reading A VTSensorReading object containing the magnetometer reading
 */
-(void) nodeDeviceDidUpdateMagReading: (VTNodeDevice *) device withReading: (VTSensorReading*)reading;

/** Invoked when a Node device communicates an ambient temperature reading from an attached Clima module
 
 @param device The device that communicated an ambient temperature reading
 @param reading The ambient temperature in degrees celsius
 */
-(void) nodeDeviceDidUpdateClimaTempReading: (VTNodeDevice *) device withReading: (float) reading;

/** Invoked when a Node device communicates a humidity reading from an attached Clima module
 
 @param device The device that communicated the reading
 @param reading The relative humidity level (in percent)
 
 */
-(void) nodeDeviceDidUpdateClimaHumidityReading: (VTNodeDevice *) device withReading: (float) reading;

/** Invoked when a Node device communicates a barometric pressure reading from an attached Clima module
 
 @param device The device that communicated the reading
 @param reading The barometric pressure level in kPa
 
 */
-(void) nodeDeviceDidUpdateClimaPressureReading: (VTNodeDevice *) device withReading: (float) reading;

/** Invoked when a Node device communicates an ambient light level reading from an attached Clima module
 
 @param device The device that communicated the reading
 @param reading The ambient light level in lux
 
 */
-(void) nodeDeviceDidUpdateClimaLightReading: (VTNodeDevice *) device withReading: (float) reading;

/** Invoked when a Node device communicates a temperature reading from an attached IR Therma module
 
 @param device The device that communicated the reading
 @param reading The reading in degrees celsius
 */
-(void) nodeDeviceDidUpdateIRThermoReading: (VTNodeDevice *) device withReading: (float) reading;

/** Invoked when a Node device communicates its current orientation in quaternion format
 
 @param device The device that communicated its orientation
 @param reading A VTQuatReading object containing a four-dimensional quaternion value that represents the device's orientation
 */
-(void) nodeDeviceDidUpdateQuatReading: (VTNodeDevice *) device withReading: (VTQuatReading *)reading;

/** Invoked when a Node device communicates its current battery level
 
 @param device The device that communicated its battery level
 @param reading The current battery level expressed as a number between 0 (empty) and 1 (full)
 */
-(void) nodeDeviceDidUpdateBatteryLevel: (VTNodeDevice *) device withReading: (float) reading;

/** Invoked when a Node device communicates that its hardware button has been depressed.
 
 @param device The device that communicated the event
 */
-(void) nodeDeviceButtonPushed: (VTNodeDevice *) device;

/** Invoked when a Node device communicates that its hardware button has been released.
 
 @param device The device that communicated the event
 */
-(void) nodeDeviceButtonReleased: (VTNodeDevice *) device;

/** Invoked when a Node device has communicated which modules it has attached
 
 @param device The device that communicated its module types
 @param typeA The code of the module attached to port A (for codes, see defines at top of libNode.h)
 @param typeB The code of the module attached to port B (for codes, see defines at top of libNode.h)
 */
-(void) nodeDeviceDidUpdateModuleTypes: (VTNodeDevice *) device typeA: (uint8_t) typeA typeB: (uint8_t) typeB;
@end

/** The VTNodeDevice class is used to interact with a Node device
 */
@interface VTNodeDevice : BRDevice

/** The delegate object you want to receive events generated by this device */
@property (strong, nonatomic) NSObject<NodeDeviceDelegate> *delegate;
/** The (personalized) name of the Node device*/
@property (nonatomic, readonly) NSString *name;
/** True if the Node device is in data mode (valid only after nodeDeviceDidUpdateDataMode has been invoked, which occurs sometime after a connection is established) */
@property (nonatomic) bool deviceInDataMode;
/** The CBPeripheral object associated with this Node device*/
@property (strong, nonatomic) CBPeripheral *peripheral;
/** The type of module attached to port A (see top of libNode.h for codes) 
 
 Only valid after nodeDeviceDidUpdateModuleTypes has been invoked
 */
@property (nonatomic) uint8_t module_a_type;
/** The type of module attached to port B (see top of libNode.h for codes) 
 
 Only valid after nodeDeviceDidUpdateModuleTypes has been invoked
 */
@property (nonatomic) uint8_t module_b_type;
/** True if the Node device is fully connected and ready to accept commands or data */
@property (nonatomic) bool isFullyConnected;
/** The current battery level expressed as a number between 0 (empty) and 1 (full)
 
 Only valid after nodeDeviceDidUpdateBatteryLevel has been invoked.
 */
@property (nonatomic) float batteryLevel;

/** Returns a VTNodeDevice object initialized with the given delegate and peripheral 
 
 @param delegate The delegate object you want to receive events generated by this device
 @param device The CBPeripheral object with which to associate the object
 
 @return A VTNodeDevice object initalized with the given delegate and peripheral
 */
-(id) initWithDelegate:(NSObject<NodeDeviceDelegate> *)delegate withDevice:(CBPeripheral *)device;

/** Attempts to establish a connection with the device.
 
 If successful, the nodeDeviceDidConnect callback will be invoked. 
*/
-(void) connect;

/** Disconects from the Node device.
 
  The nodeDeviceDidDisconnect callback will be invoked when the connection is broken.
 */
-(void) disconnect;

/** Connect if disconnected, and disconnect if connected.
 
 The apropriate delegate callback will be invoked when a connection is broken or established.
 */
-(void) toggleConnection;

/** Send an AT.S command to a Node device (note: use sendData for sending Node commands)
 
 @param str The command to send
*/
-(void) sendCommand:(NSString *)str;
/** Send a Node command to a Node device 
 
 @param str The command to send
 */
-(void) sendData:(NSString *)str;
/** Disable all data streaming modes for the device */
-(void) disableAllStreaming;

/** Enable or disable KORE streaming using the default period (20ms) and duration (infinite)
 
 @param aMode set to YES to stream accelerometer readings
 @param gMode set to YES to stream gyroscope readings
 @param mMode set to YES to stream magnetometer readings
 
 */
-(void) setStreamModeAcc: (bool)aMode Gyro:(bool)gMode Mag:(bool)mMode;

/** Enable or disable KORE streaming using a specified period and duration
 
 p and life are only valid if at least one mode param (aMode, gMode, or mMode) is set to YES
 
 @param aMode set to YES to stream accelerometer readings
 @param gMode set to YES to stream gyroscope readings
 @param mMode set to YES to stream magnetometer readings
 @param p The period between readings in units of 10ms
 @param life The number of readings to collect (0 for infinite)
 
 */
-(void) setStreamModeAcc: (bool)aMode Gyro:(bool)gMode Mag:(bool)mMode withPeriod:(uint8_t)p withLifetime:(uint8_t)life;

/** Enable or disable IR Therma module streaming using the default period (100ms) and duration (infinite) with the spotting LED powered on

 @param irMode set to YES to stream IR Therma readings
 
 */
-(void) setStreamModeIRThermo: (bool)irMode;

/** Enable or disable IR Therma module streaming using the default period (100ms) and duration (infinite)
 
 @param irMode set to YES to stream IR Therma readings
 @param ledMode set to YES to enabled the spotting LED
 
 */
-(void) setStreamModeIRThermo: (bool)irMode withLedPower:(bool)ledMode;

/** Enable of disable IR Thermo module streaming using a specified period and duration
 
 @param irMode set to YES to stream IR Therma readings
 @param ledMode set to YES to enabled the spotting LED
 @param p The period between readings in units of 10ms
 @param life The number of readings to collect (0 for infinite)
 
 */
-(void) setStreamModeIRThermo: (bool)irMode withLedPower:(bool)ledMode withPeriod:(uint8_t)p withLifetime:(uint8_t)life;

/** Enable or disable streaming of orientation data using the default period (10ms) and duration (infinite)
 
 @param qMode Set to YES to enable streaming of quaternion data
 */
-(void) setStreamModeOriQuat:(bool)qMode;

/** Enable or disable streaming of clima data using default period (250 ms) and duration (infinite) 
 
 @param tempPressureMode Set to YES to enable streaming of ambient temperature and pressure readings
 @param humidityMode Set to YES to enable streaming of relative humidity readings
 @param lpMode Set to YES to enable streaming of ambient light and proximity
 */
-(void) setStreamModeClimaTP: (bool) tempPressureMode Humidity: (bool)humidityMode LightProximity:(bool)lpMode;

/** Enable or disable streaming of clima data using specified period and duration
 
 @param tempPressureMode Set to YES to enable streaming of ambient temperature and pressure readings
 @param humidityMode Set to YES to enable streaming of relative humidity readings
 @param lpMode Set to YES to enable streaming of ambient light and proximity
 @param p The period between readings in units of 10ms
 @param life The number of readings to collect (0 for infinite)
 */
-(void) setStreamModeClimaTP: (bool) tempPressureMode Humidity: (bool)humidityMode LightProximity:(bool)lpMode withPeriod:(uint8_t)p withLifetime:(uint8_t)life;

/** Turn on or off LEDs on the LUMA module
 
 There are eight LEDs on the LUMA module. Each LED is controlled by a single bit of a 1-byte value.
 To turn all LEDs off, mode should be set to 0.
 To turn all LEDs on, mode should be set to 255.
 To turn on LEDs 0 and 4, the value 0b00010001 (17) should be used
 
 @param mode A value between 0 and 255 that sets the LED level for LUMA
 */
-(void) setLumaMode: (unsigned char)mode;

/** Request that the Node device communicate its battery level and attached module types
 
 nodeDeviceDidUpdateModuleTypes and nodeDeviceDidUpdateBatteryLevel will be invoked
 
 */
-(void) requestStatus;

/**
 Put the Node device into magnetometer calibration mode. 
 
 The device will disconnect. The device should be spun along each axis during calibration.
 */
-(void) requestMagnetometerCalibration;

/**
 Put the Node device into gyroscope calibration mode. 
 
 The device will disconnect. The device should be placed on a flat surface and kept very still during calibration.
 */
-(void) requestGyroscopeCalibration;

//-(void) requestClima;
//-(void) requestIRThermometer;

/** Request a single color reading from the VERA module.
 @param _level The LED level to be used during the reading.There are eight LEDs on the LUMA module. Each LED is controlled by a single bit of a 1-byte value.
    To turn all LEDs off, mode should be set to 0.
    To turn all LEDs on, mode should be set to 255.
    To turn on LEDs 0 and 4, the value 0b00010001 (17) should be used
 */
 
-(void) requestVeraWithLightLevel: (uint8_t) _level;

/** Compares two VTNodeDevice objects
 
 @param anotherDevice The other VTNodeDevice
 @return A NSComparisonResult object containing the result of the comparison
 
 */
- (NSComparisonResult)compareWithDeviceID:(VTNodeDevice*)anotherDevice;
@end

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

/** Delegate protocol for the VTNodeController class */
@protocol NodeControllerDelegate <NSObject>
@optional
/** Invoked when a new Node is discovered during scanning
 @param device A VTNodeDevice object representing the discovered Node device
 */
-(void) nodeDeviceFound:(VTNodeDevice *) device;
/** Invoked when the VTNodeController shared instance is ready to be used.
 
 Once this is invoked, it is safe to begin scanning for Node devices
 */
-(void) nodeControllerReady;

@end

/** This class is used to find and manage Node devices */
@interface VTNodeController : NSObject <nBlueDelegate>

/** The delegate object you want to receive events generated by the controller  */
@property (strong, nonatomic) NSObject<NodeControllerDelegate> *delegate;

/** Returns the global shared instance of the VTNodeController class
 
 @return An object that is the global shared instance of the VTNodeController class
 */
+(VTNodeController *)sharedInstance;

/** Returns an array of all known Node devices (all Nodes that have been discovered during scanning)
 
 @return An array of all discovered Node devices
 */
+(NSArray *)allNodeDevices;

/** Returns an array of all Node devices that are currently connected.
 
 @return An array of all Node devices currently connected.
 
 */
+(NSArray *)allConnectedNodeDevices;

/** Initiates scanning for Node devices.
 
 @param to The duration of the scan in seconds
 
 When a Node device is found, nodeDeviceFound is invoked */
+(void) scanForNodeDevicesWithTimeout: (int) to;

/** Cancels an in-progress scan */
+(void) stopScan;

/** Fetches a Node device at a given index from the array of all known Node devices
 
 @param idx The index of the device to fetch
 @return A VTNodeDevice object that is the object stored at the given array index
 */
+(VTNodeDevice *)getNodeDevice: (int) idx;

/** Clears the list of known Node devices */
+(void)forgetAllDevices;
@end

