//
//  VTDemoView.h
//  NODE_API_DEMO
//
//  Created by Aaron Boggs on 8/2/12.
//  Copyright (c) 2012 Variable Technologies

//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
//  associated documentation files (the "Software"), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
//  the following conditions:

//  The above copyright notice and this permission notice shall be included in all copies or substantial
//  portions of the Software.

//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
//  LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
//  NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#import <UIKit/UIKit.h>
#import <inttypes.h>
#import "libNode.h"

@interface VTDemoView : UIViewController <NodeControllerDelegate, NodeDeviceDelegate, UINavigationControllerDelegate>

// UI
@property (weak, nonatomic) IBOutlet UIScrollView *MainScrollView;
@property (weak, nonatomic) IBOutlet UIView *MainView;

// Device Information
@property (retain, nonatomic) VTNodeDevice *TheDevice;
@property (weak, nonatomic) IBOutlet UILabel *DeviceName;
@property (weak, nonatomic) IBOutlet UILabel *DeviceInDataMode;
@property (weak, nonatomic) IBOutlet UILabel *DeviceIsFullyConnected;
@property (weak, nonatomic) IBOutlet UILabel *DeviceConnected;
@property (weak, nonatomic) IBOutlet UILabel *DeviceBatteryLevel;
@property (weak, nonatomic) IBOutlet UILabel *DeviceDescription;
@property (weak, nonatomic) IBOutlet UILabel *DeviceModuleA;
@property (weak, nonatomic) IBOutlet UILabel *DeviceModuleB;
@property (weak, nonatomic) IBOutlet UILabel *DeviceButtonPressed;

@property (weak, nonatomic) IBOutlet UILabel *PeripheralName;
@property (weak, nonatomic) IBOutlet UILabel *PeripheralUUID;

// ============== Kore Streaming
@property (weak, nonatomic) IBOutlet UILabel *KoreAccX;
@property (weak, nonatomic) IBOutlet UILabel *KoreAccY;
@property (weak, nonatomic) IBOutlet UILabel *KoreAccZ;

@property (weak, nonatomic) IBOutlet UILabel *KoreGyroX;
@property (weak, nonatomic) IBOutlet UILabel *KoreGyroY;
@property (weak, nonatomic) IBOutlet UILabel *KoreGyroZ;

@property (weak, nonatomic) IBOutlet UILabel *KoreMagX;
@property (weak, nonatomic) IBOutlet UILabel *KoreMagY;
@property (weak, nonatomic) IBOutlet UILabel *KoreMagZ;

@property (weak, nonatomic) IBOutlet UILabel *KoreQ0;
@property (weak, nonatomic) IBOutlet UILabel *KoreQ1;
@property (weak, nonatomic) IBOutlet UILabel *KoreQ2;
@property (weak, nonatomic) IBOutlet UILabel *KoreQ3;

// ============== Therma Streaming
@property (weak, nonatomic) IBOutlet UILabel *Therma;

// ============== Clima Streaming
@property (weak, nonatomic) IBOutlet UILabel *ClimaTemp;
@property (weak, nonatomic) IBOutlet UILabel *ClimaHumid;
@property (weak, nonatomic) IBOutlet UILabel *ClimaPres;
@property (weak, nonatomic) IBOutlet UILabel *CLimaLight;

#pragma mark - Node Device Delegates
- (void)nodeDeviceDidDisconnect:(VTNodeDevice *)device;
- (void)nodeDeviceDidConnect:(VTNodeDevice *)device;

#pragma mark - Node Device Streaming
// KORE
- (void)nodeDeviceDidUpdateGyroReading:(VTNodeDevice *)device withReading:(VTSensorReading*)reading;
- (void)nodeDeviceDidUpdateAccReading:(VTNodeDevice *)device withReading:(VTSensorReading*)reading;
- (void)nodeDeviceDidUpdateMagReading:(VTNodeDevice *)device withReading:(VTSensorReading*)reading;
- (void)nodeDeviceDidUpdateQuatReading:(VTNodeDevice *)device withReading:(VTQuatReading *)reading; // Quaternion Representation

// CLIMA
- (void)nodeDeviceDidUpdateClimaTempReading:(VTNodeDevice *)device withReading:(float)reading;
- (void)nodeDeviceDidUpdateClimaHumidityReading:(VTNodeDevice *)device withReading:(float)reading;
- (void)nodeDeviceDidUpdateClimaPressureReading:(VTNodeDevice *)device withReading:(float)reading;
- (void)nodeDeviceDidUpdateClimaLightReading:(VTNodeDevice *)device withReading:(float)reading;

// THERMA
- (void)nodeDeviceDidUpdateIRThermoReading:(VTNodeDevice *)device withReading:(float)reading;

#pragma mark - Node Device Data Mode Delegate
- (void)nodeDeviceDidUpdateDataMode:(VTNodeDevice *)device withMode:(DeviceMode)mode;

#pragma mark - Node Button Delegate
- (void)nodeDeviceButtonPushed:(VTNodeDevice *)device;
- (void)nodeDeviceButtonReleased:(VTNodeDevice *)device;

#pragma mark - Node Module Delegate
- (void)nodeDeviceDidUpdateModuleTypes:(VTNodeDevice *)device typeA:(uint8_t)typeA typeB:(uint8_t)typeB;

#pragma mark - Node Battery Delegate
- (void)nodeDeviceDidUpdateBatteryLevel:(VTNodeDevice *)device withReading:(float)reading;

#pragma mark - UIButtons
- (IBAction)requestNodeStatus:(id)sender;
- (IBAction)streamAcGyMa:(id)sender;
- (IBAction)streamQuat:(id)sender;
- (IBAction)streamTherma:(id)sender;
- (IBAction)streamClima:(id)sender;
- (IBAction)eanbleLuma:(id)sender;

- (void)viewWillDisappear:(BOOL)animated;

@end
