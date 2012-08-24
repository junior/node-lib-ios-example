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
@property (readonly, nonatomic) float x;
/** The y axis reading */
@property (readonly, nonatomic) float y;
/** The z axis reading */
@property (readonly, nonatomic) float z;

/** Returns a VTSensorReading object initialized with the three provided values.
 
    @param xVal The x axis value for the new reading
    @param yVal The y axis value for the new reading
    @param zVal The z axis value for the new reading
    @return A VTSensorReading initalized with the given values.
 */
-(id) initWithXValue: (float)xVal y: (float)yVal z: (float)zVal;
@end

////////////////////////////////////////////////////////////////////////////////
/** This class represents a set of yaw, pitch, and roll values */
@interface VTYprReading : NSObject
/** The yaw value */
@property (readonly, nonatomic) float yaw;
/** The pitch value **/
@property (readonly, nonatomic) float pitch;
/** The roll value **/
@property (readonly, nonatomic) float roll;
/** Returns a VTYprReading object initialized with the three provided values. 
    
    @param yaw The yaw value for the new object
    @param pitch The pitch value for the new object
    @param roll The roll value for the new object
    @return A VTYprReading object initialized with the provided values.
 */
-(id) initWithYaw: (float)yaw pitch:(float)pitch roll:(float)roll;
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
/** This class represents a color reading from the Vera module. */
@interface VTRGBCReading : NSObject
/** The clear channel */
@property (readonly, nonatomic) uint16_t clear;
/** The red channel */
@property (readonly, nonatomic) uint16_t red;
/** The green channel */
@property (readonly, nonatomic) uint16_t green;
/** The blue channel */
@property (readonly, nonatomic) uint16_t blue;

/** Returns a VTRGBCReading object initialized with the four provided values.
 
 @param clear Clear channel value of new object
 @param red Red channel value of new object
 @param green Green channel value of new object
 @param blue Blue channel value of new object
 @return A VTRGBCReading object initialized with the provided values
 */
-(id) initWithClear:(uint16_t)clear red:(uint16_t)red green:(uint16_t)green blue:(uint16_t)blue;

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

/** Invoked when a Node device communicates an OXA module reading
 @param device The Node device that communicated the reading
 @param reading The reading
 */
-(void) nodeDeviceDidUpdateOxaReading: (VTNodeDevice *) device withReading: (float) reading;

/** Invoked when a Node device communicates an OXA module reading
 @param device The Node device that communicated the reading
 @param reading The reading
 */
-(void) nodeDeviceDidUpdateOxaTempReading: (VTNodeDevice *) device withReading: (int16_t) reading;

/** Invoked when a Node device communicates a temperature reading from an attached IR Therma module
 
 @param device The device that communicated the reading
 @param reading The reading in degrees celsius
 */
-(void) nodeDeviceDidUpdateIRThermoReading: (VTNodeDevice *) device withReading: (float) reading;

/** Invoked when a Node device communicates its current yaw, pitch and roll
 
 @param device The device that communicated its yaw, pitch and roll
 @param reading A VTYprReading object containing the yaw pitch and roll communicated
 */
-(void) nodeDeviceDidUpdateYprReading: (VTNodeDevice *) device withReading: (VTYprReading *)reading;

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

/** Invoked when a Node device has communicated a color reading from an attached Vera module
 
 @param device The device that communicated the reading
 @param reading A VTRGBCReading object containing the color values read
 */
-(void) nodeDeviceDidUpdateVeraReading: (VTNodeDevice *) device withReading: (VTRGBCReading *) reading;
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
-(void) setStreamModeAcc: (bool)aMode Gyro:(bool)gMode Mag:(bool)mMode withPeriod:(uint16_t)p withLifetime:(uint16_t)life;

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
-(void) setStreamModeIRThermo: (bool)irMode withLedPower:(bool)ledMode withPeriod:(uint16_t)p withLifetime:(uint16_t)life;

/** Enable or disable streaming of OXA readings. 
 
 @param oxaMode Set to YES to enable OXA readings
 @param p The period between readings in units of 10ms
 @param life The number of readings to collect (0 for infinite)
 */
-(void) setStreamModeOxa:(bool)oxaMode withPeriod:(uint16_t)p withLifetime:(uint16_t)life;

/** Enable or disable streaming of orientation data using the default period (10ms) and duration (infinite)
 
 @param yprMode Set to YES to enable streaming of yaw, pitch, and roll data
 @param qMode Set to YES to enable streaming of quaternion data
 */
-(void) setStreamModeOriYpr: (bool)yprMode QuatMode:(bool)qMode;

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
-(void) setStreamModeClimaTP: (bool) tempPressureMode Humidity: (bool)humidityMode LightProximity:(bool)lpMode withPeriod:(uint16_t)p withLifetime:(uint16_t)life;

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

/** Starts the Node buzzer buzzing at a provided frequency for 60ms.
 
 @param frequency The frequency with witch to buzz the buzzer. Valid between 100-4000.
 */
-(void) buzzerBeep:(uint16_t)frequency;

/** Starts the Node buzzer buzzing at a provided frequency for a provided length of time
 
 @param frequency The frequency with witch to buzz the buzzer. valid between 100-4000.
 @param duration The length to buzz the buzzer for. Increases in increments of 10ms (1 = 10ms). A duration of 0 will buzz the buzzer indefinietly
*/
-(void) buzzerStart:(uint16_t)frequency duration:(uint16_t)duration;

/** Stops any buzzing by the buzzer
 
*/
-(void) buzzerStop;

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

/** Request a single color reading from the VERA module.
 @param _level The LED level to be used during the reading.There are eight LEDs on the LUMA module. Each LED is controlled by a single bit of a 1-byte value.
    To turn all LEDs off, mode should be set to 0.
    To turn all LEDs on, mode should be set to 255.
    To turn on LEDs 0 and 4, the value 0b00010001 (17) should be used
 @param gain Gain setting for color sensor (0-3 to choose from 1x, 4x, 16x and 64x)
 @param prescaler Prescaler setting for color sensor (0-6 to choose from divide by 1, 2, 4, 8, 16, 32, 64)
 @param integrationTime Integration time to use for color sensor (0-2 for 12ms, 100ms, and 400ms respectively)
 
 For maximum sensitivity, use gain of 3 (64x), prescaler of 0 (divide by 1), and integration time of 2 (400ms)
 */ 
-(void) requestVeraWithLightLevel:(uint8_t) _level withGainSetting: (uint8_t)gain withPrescaler:(uint8_t)prescaler withIntegrationTime:(uint8_t)integrationTime;

/** Compares two VTNodeDevice objects
 
 @param anotherDevice The other VTNodeDevice
 @return A NSComparisonResult object containing the result of the comparison
 
 */
- (NSComparisonResult)compareWithDeviceID:(VTNodeDevice*)anotherDevice;


/** Controls power of Node's LEDs
 
    Each of the leds take an unsigned char with a range from 0-255. With 0 being the led is completely off.
    And 255 being the led is completely on.
 
    @param aBluePwr The brightness of the first blue led.
    @param bBluePwr The brightness of the second blue led.
    @param aRedPwr The brightness of the first red led.
    @param bRedPwr The brightness of the second red led.
 */
-(void) setLedABlue:(uint8_t)aBluePwr BBlue:(uint8_t)bBluePwr ARed:(uint8_t)aRedPwr BRed:(uint8_t)bRedPwr;

/** Turns on the four leds (two at each end) for a given duration
 
     Each of the leds take an unsigned char with a range from 0-255. With 0 being the led is completely off.
     And 255 being the led is completely on.
     
     @param led1B The brightness of the first blue led.
     @param led2B The brightness of the second blue led.
     @param led1R The brightness of the first red led.
     @param led2R The brightness of the second red led.
     @param duration The duration to keep the leds on for - in increments of 10ms. (1=10ms)
 */
-(void) ledsOn:(unsigned char)led1B led2B:(unsigned char)led2B led1R:(unsigned char)led1R led2R:(unsigned char)led2R duration:(uint16_t)duration;

/** Turns on the four leds (two at each end) for a given duration with a given pulse frequency
 
     Each of the leds take an unsigned char with a range from 0-255. With 0 being the led is completely off.
     And 255 being the led is completely on.
 
     When pulsing the leds go from 0 to their set brightness and then back to 0 when pulsing up/down.
     
     @param led1B The brightness of the first blue led.
     @param led2B The brightness of the second blue led.
     @param led1R The brightness of the first red led.
     @param led2R The brightness of the second red led.
     @param duration The duration to keep the leds on for - in increments of 10ms. (1=10ms)
     @param pulseFrequency The time interval between a full cycle of the leds (On->off) - in increments of 10ms. (1=10ms)
 */
-(void) ledsPulse:(unsigned char)led1B led2B:(unsigned char)led2B led1R:(unsigned char)led1R led2R:(unsigned char)led2R duration:(uint16_t)duration pulseFrequency:(uint16_t)pulseFrequency;

/** Turns off the four leds
 
 */
-(void) ledsOff;
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

