//
//  VTDemoView.m
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


#import "VTDemoView.h"

@interface VTDemoView ()

@end

@implementation VTDemoView

@synthesize MainScrollView;
@synthesize MainView;
@synthesize TheDevice;
@synthesize DeviceName;
@synthesize DeviceInDataMode;
@synthesize DeviceIsFullyConnected;
@synthesize DeviceBatteryLevel;
@synthesize DeviceDescription;
@synthesize DeviceModuleA;
@synthesize DeviceModuleB;
@synthesize DeviceButtonPressed;
@synthesize PeripheralName;
@synthesize PeripheralUUID;
@synthesize DeviceConnected;

// ============== Kore Streaming
@synthesize KoreAccX;
@synthesize KoreAccY;
@synthesize KoreAccZ;
@synthesize KoreGyroX;
@synthesize KoreGyroY;
@synthesize KoreGyroZ;
@synthesize KoreMagX;
@synthesize KoreMagY;
@synthesize KoreMagZ;
@synthesize KoreQ0;
@synthesize KoreQ1;
@synthesize KoreQ2;
@synthesize KoreQ3;

// ============== Therma Streaming
@synthesize Therma;

// ============== Clima Streaming
@synthesize ClimaTemp;
@synthesize ClimaHumid;
@synthesize ClimaPres;
@synthesize CLimaLight;

// ============== Luma Streaming


#pragma mark - Init
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Grab all potential delegates
    [self grabNodeDelegates];
    
    // Adjust scroll view size
    [self adjustScrollViewSize];
    
}

// Used to setup everything once a device has connected
// Used when nodeDeviceDidConnect is fired
- (void)baseInit
{
    NSLog(@"Base init");
    // Setup the device we are working with
    if ([[VTNodeController allConnectedNodeDevices] count] > 0) {
        self.TheDevice = [[VTNodeController allConnectedNodeDevices] objectAtIndex:0];
        [self setupDeviceInfoDisplay];
    }
}

// Forces the scroll view to expand to the size of its contained content
- (void)adjustScrollViewSize
{
    NSLog(@"Adjust scroll size: %f x %f", self.MainView.bounds.size.width, self.MainView.bounds.size.height);
    [self.MainScrollView setContentSize:self.MainView.frame.size];
}

// Grabs all relevant node delegates
- (void)grabNodeDelegates
{
    
    [VTNodeController sharedInstance].delegate = self;
    
    for (VTNodeDevice* device in [VTNodeController allNodeDevices]) {
        device.delegate = self;
    }
    
}

// Initalize all of the device labels
- (void)setupDeviceInfoDisplay
{
    // ======== Device Properties ========
    // ======== Valid once a device is found ========
    
    // TheDevice.name == TheDevice.peripheral.name
    [self.DeviceName setText:self.TheDevice.name];
    
    // Device Discription = UUID
    NSString *deviceDescript = [[NSString alloc] initWithFormat:@"%@", self.TheDevice.description];
    [self.DeviceDescription setText:deviceDescript];
    
    // Device is fully connected
    NSString *deviceFullyConnected = [[NSString alloc] initWithFormat:@"%@", (self.TheDevice.isFullyConnected ? @"YES" : @"NO")];
    [self.DeviceIsFullyConnected setText:deviceFullyConnected];
    
    // Device connected
    NSString *deviceConnected = [[NSString alloc] initWithFormat:@"%@", (self.TheDevice.connected ? @"YES" : @"NO")];
    [self.DeviceConnected setText:deviceConnected];
    
    [self.DeviceButtonPressed setText:@"False"];
    
    // ======== Properties that are only valid after requesting node's status ========
    
    // Device battery level - Valid after nodeDeviceDidUpdateBatteryLevel
    [self.DeviceBatteryLevel setText:@"Invalid (-1.000)"];
    
    // Device attached modules - Valid after ndoeDeviceDidUpdateModuleTypes
    [self.DeviceModuleA setText:@"Invalid (NONE)"];
    [self.DeviceModuleB setText:@"Invalid (NONE)"];
    
    // ======== Peripheral Properties ========
    
    // Peripheral Name
    [self.PeripheralName setText:self.TheDevice.peripheral.name];
    
    // Peripheral UUID
    NSString *peripheralUUID = [[NSString alloc] initWithFormat:@"%@", self.TheDevice.peripheral.UUID];
    [self.PeripheralUUID setText:peripheralUUID];
    
    // ======== Kore Streaming ========
    [self.KoreAccX setText:@"Invalid"];
    [self.KoreAccY setText:@"Invalid"];
    [self.KoreAccZ setText:@"Invalid"];
    [self.KoreGyroX setText:@"Invalid"];
    [self.KoreGyroY setText:@"Invalid"];
    [self.KoreGyroZ setText:@"Invalid"];
    [self.KoreMagX setText:@"Invalid"];
    [self.KoreMagY setText:@"Invalid"];
    [self.KoreMagZ setText:@"Invalid"];
    [self.KoreQ0 setText:@"Invalid"];
    [self.KoreQ1 setText:@"Invalid"];
    [self.KoreQ2 setText:@"Invalid"];
    [self.KoreQ3 setText:@"Invalid"];
    
    // ======== Therma Streaming ========
    [self.Therma setText:@"Invalid"];
    
    // ======== Therma Streaming ========
    [self.ClimaTemp setText:@"Invalid"];
    [self.ClimaHumid setText:@"Invalid"];
    [self.ClimaPres setText:@"Invalid"];
    [self.CLimaLight setText:@"Invalid"];
    
}

#pragma mark - Node Device Delegate
// If a device disconnects jump back to the root view controller
- (void)nodeDeviceDidDisconnect:(VTNodeDevice *)device
{
    NSLog(@"Node Device Did Disconnect");
    
    [self disconnectAllDevices];
    
    // Jump back to the root view controller
    [self.navigationController popToRootViewControllerAnimated:TRUE];
}

// Update device information about device once it connects
- (void)nodeDeviceDidConnect:(VTNodeDevice *)device
{
    NSLog(@"Device Did Connect");
    device.delegate = self;
    self.TheDevice = device;
    
    [self baseInit];
}

- (void)nodeDeviceButtonPushed:(VTNodeDevice *)device
{
    [self.DeviceButtonPressed setText:@"True"];
}

- (void)nodeDeviceButtonReleased:(VTNodeDevice *)device
{
    [self.DeviceButtonPressed setText:@"False"];   
}

// ====================================================
// The following functions are fired after a
// requestStatus command is sent to NODE
// ====================================================

// Fired after a request Status message is sent to NODE
- (void)nodeDeviceDidUpdateBatteryLevel:(VTNodeDevice *)device withReading:(float)reading
{
    // reading == self.TheDevice.batteryLevel
    NSLog(@"Device did update battery level");
    NSString *deviceBattery = [[NSString alloc] initWithFormat:@"%f", reading];
    [self.DeviceBatteryLevel setText:deviceBattery];
}

// Fired after a request Status message is sent to NODE
- (void)nodeDeviceDidUpdateModuleTypes:(VTNodeDevice *)device typeA:(uint8_t)typeA typeB:(uint8_t)typeB
{
    NSLog(@"Device did update module types");
    
    switch (typeA) {
        case MODULE_TYPE_CLIMA:
            [self.DeviceModuleA setText:@"Clima"];
            break;
        case MODULE_TYPE_IR_THERMO:
            [self.DeviceModuleA setText:@"Therma"];
            break;
        case MODULE_TYPE_LUMA:
            [self.DeviceModuleA setText:@"Luma"];
            break;
        case MODULE_TYPE_NONE:
            [self.DeviceModuleA setText:@"None"];
            break;
        case MODULE_TYPE_OXA:
            [self.DeviceModuleA setText:@"OXA"];
            break;
        case MODULE_TYPE_VERA:
            [self.DeviceModuleA setText:@"Vera"];
            break;
        default:
            [self.DeviceModuleA setText:@"Error"];
            break;
    }
    
    switch (typeB) {
        case MODULE_TYPE_CLIMA:
            [self.DeviceModuleB setText:@"Clima"];
            break;
        case MODULE_TYPE_IR_THERMO:
            [self.DeviceModuleB setText:@"Therma"];
            break;
        case MODULE_TYPE_LUMA:
            [self.DeviceModuleB setText:@"Luma"];
            break;
        case MODULE_TYPE_NONE:
            [self.DeviceModuleB setText:@"None"];
            break;
        case MODULE_TYPE_OXA:
            [self.DeviceModuleB setText:@"OXA"];
            break;
        case MODULE_TYPE_VERA:
            [self.DeviceModuleB setText:@"Vera"];
            break;
        default:
            [self.DeviceModuleB setText:@"Error"];
            break;
    }
}

- (void)nodeDeviceDidUpdateDataMode:(VTNodeDevice *)device withMode:(DeviceMode)mode
{
    NSLog(@"nodeDeviceDidUpdateDataMode");
    [self.DeviceInDataMode setText:((mode == 1) ? @"DeviceInDataMode" : @"DeviceInRemoteCommand")];
}

/*
  _    __  ______   ______   ______ 
 | |  / / / |  | \ | |  | \ | |     
 | |-< <  | |  | | | |__| | | |---- 
 |_|  \_\ \_|__|_/ |_|  \_\ |_|____ 
 
*/

// ====================================================
// The following functions are fired after a call to:
//
// - (void)setStreamModeAcc:(bool)aMode Gyro:(bool)gMode Mag:(bool)mMode
// or
// - (void)setStreamModeAcc:(bool)aMode Gyro:(bool)gMode Mag:(bool)mMode withPeriod:(uint8_t)p withLifetime:(uint8_t)life
//
// ====================================================

- (void)nodeDeviceDidUpdateGyroReading:(VTNodeDevice *)device withReading:(VTSensorReading*)reading
{
    NSString *xReading = [[NSString alloc] initWithFormat:@"%.2f", reading.x];
    [self.KoreGyroX setText:xReading];
    
    NSString *yReading = [[NSString alloc] initWithFormat:@"%.2f", reading.y];
    [self.KoreGyroY setText:yReading];
    
    NSString *zReading = [[NSString alloc] initWithFormat:@"%.2f", reading.z];
    [self.KoreGyroZ setText:zReading];
}

- (void)nodeDeviceDidUpdateAccReading:(VTNodeDevice *)device withReading:(VTSensorReading*)reading;
{
    NSString *xReading = [[NSString alloc] initWithFormat:@"%.2f", reading.x];
    [self.KoreAccX setText:xReading];
    
    NSString *yReading = [[NSString alloc] initWithFormat:@"%.2f", reading.y];
    [self.KoreAccY setText:yReading];
    
    NSString *zReading = [[NSString alloc] initWithFormat:@"%.2f", reading.z];
    [self.KoreAccZ setText:zReading];
}

- (void)nodeDeviceDidUpdateMagReading:(VTNodeDevice *)device withReading:(VTSensorReading*)reading;
{
    NSString *xReading = [[NSString alloc] initWithFormat:@"%.2f", reading.x];
    [self.KoreMagX setText:xReading];
    
    NSString *yReading = [[NSString alloc] initWithFormat:@"%.2f", reading.y];
    [self.KoreMagY setText:yReading];
    
    NSString *zReading = [[NSString alloc] initWithFormat:@"%.2f", reading.z];
    [self.KoreMagZ setText:zReading];
}

- (void)nodeDeviceDidUpdateQuatReading:(VTNodeDevice *)device withReading:(VTQuatReading *)reading
{
    NSString *q0Reading = [[NSString alloc] initWithFormat:@"%.2f", reading.q0];
    [self.KoreQ0 setText:q0Reading];
    
    NSString *q1Reading = [[NSString alloc] initWithFormat:@"%.2f", reading.q1];
    [self.KoreQ1 setText:q1Reading];
    
    NSString *q2Reading = [[NSString alloc] initWithFormat:@"%.2f", reading.q2];
    [self.KoreQ2 setText:q2Reading];
    
    NSString *q3Reading = [[NSString alloc] initWithFormat:@"%.2f", reading.q3];
    [self.KoreQ3 setText:q3Reading];
}

/*
 _______  _    _   ______  ______   _________   ______  
   | |   | |  | | | |     | |  | \ | | | | | \ | |  | | 
   | |   | |--| | | |---- | |__| | | | | | | | | |__| | 
   |_|   |_|  |_| |_|____ |_|  \_\ |_| |_| |_| |_|  |_| 
 
 */
 
// ====================================================
// The following function is fired after a call to:
//
// - (void)setStreamModeIRThermo:(bool)irMode;
// or
// - (void)setStreamModeIRThermo:(bool)irMode withLedPower:(bool)ledMode;
// or
// - (void)setStreamModeIRThermo:(bool)irMode withLedPower:(bool)ledMode withPeriod:(uint8_t)p withLifetime:(uint8_t)life;
//
// ====================================================

- (void)nodeDeviceDidUpdateIRThermoReading:(VTNodeDevice *)device withReading:(float)reading
{
    NSString *thermaReading = [[NSString alloc] initWithFormat:@"%f", reading];
    [self.Therma setText:thermaReading];
}

/*
  ______  _       _____  _________   ______  
 | |     | |       | |  | | | | | \ | |  | | 
 | |     | |   _   | |  | | | | | | | |__| | 
 |_|____ |_|__|_| _|_|_ |_| |_| |_| |_|  |_| 
 
*/
 
// ====================================================
// The following functions are fired after a call to:
//
// - (void)setStreamModeClimaTP:(bool)tempPressureMode Humidity:(bool)humidityMode LightProximity:(bool)lpMode;
// or
// - (void)setStreamModeClimaTP:(bool)tempPressureMode Humidity:(bool)humidityMode LightProximity:(bool)lpMode withPeriod:(uint8_t)p withLifetime:(uint8_t)life;
//
// ====================================================

- (void)nodeDeviceDidUpdateClimaTempReading:(VTNodeDevice *)device withReading:(float)reading
{
    NSString *climaTempReading = [[NSString alloc] initWithFormat:@"%f", reading];
    [self.ClimaTemp setText:climaTempReading];
}

- (void)nodeDeviceDidUpdateClimaHumidityReading:(VTNodeDevice *)device withReading:(float)reading
{
    NSString *climaHumidReading = [[NSString alloc] initWithFormat:@"%f", reading];
    [self.ClimaHumid setText:climaHumidReading];
}

- (void)nodeDeviceDidUpdateClimaPressureReading:(VTNodeDevice *)device withReading:(float)reading
{
    NSString *climaPresReading = [[NSString alloc] initWithFormat:@"%f", reading];
    [self.ClimaPres setText:climaPresReading];
}

- (void)nodeDeviceDidUpdateClimaLightReading:(VTNodeDevice *)device withReading:(float)reading
{
    NSString *climaLightReading = [[NSString alloc] initWithFormat:@"%f", reading];
    [self.CLimaLight setText:climaLightReading];
}


#pragma mark - Button Actions
- (IBAction)requestNodeStatus:(id)sender
{
    NSLog(@"Requesting status");
    [self.TheDevice requestStatus];
}

- (IBAction)streamAcGyMa:(id)sender
{
    if ([sender isKindOfClass:[UIButton class]]) {
        UIButton *koreButton = sender;
        
        if (koreButton.selected == TRUE) {
            koreButton.selected = FALSE;
            NSLog(@"Stop Stream Acc, Gyro, Mag");
            [self.TheDevice setStreamModeAcc:FALSE Gyro:FALSE Mag:FALSE];
        }
        else {
            koreButton.selected = TRUE;
            NSLog(@"Stream Acc, Gyro, Mag");
            [self.TheDevice setStreamModeAcc:TRUE Gyro:TRUE Mag:TRUE];
        }
    }
}

- (IBAction)streamQuat:(id)sender {
    if ([sender isKindOfClass:[UIButton class]]) {
        UIButton *quatButton = sender;
        
        if (quatButton.selected == TRUE) {
            quatButton.selected = FALSE;
            NSLog(@"Stop stream quat");
            [self.TheDevice setStreamModeOriYpr:FALSE QuatMode:FALSE];
        }
        else {
            quatButton.selected = TRUE;
            NSLog(@"Stream Quat");
            [self.TheDevice setStreamModeOriYpr:FALSE QuatMode:TRUE];
        }
    }
}

- (IBAction)streamTherma:(id)sender {
    if ([sender isKindOfClass:[UIButton class]]) {
        UIButton *thermaButton = sender;
        
        if (thermaButton.selected == TRUE) {
            thermaButton.selected = FALSE;
            NSLog(@"Stop stream therma");
            [self.TheDevice setStreamModeIRThermo:FALSE];
        }
        else {
            thermaButton.selected = TRUE;
            NSLog(@"Stream therma");
            [self.TheDevice setStreamModeIRThermo:TRUE];
        }
    }
}

- (IBAction)streamClima:(id)sender {
    if ([sender isKindOfClass:[UIButton class]]) {
        UIButton *climaButton = sender;
        
        if (climaButton.selected == TRUE) {
            climaButton.selected = FALSE;
            NSLog(@"Stop stream clima");
            [self.TheDevice setStreamModeClimaTP:FALSE Humidity:FALSE LightProximity:FALSE];
        }
        else {
            climaButton.selected = TRUE;
            NSLog(@"Stream clima");
            [self.TheDevice setStreamModeClimaTP:TRUE Humidity:TRUE LightProximity:TRUE];
        }
    }
}

- (IBAction)eanbleLuma:(id)sender {
    
    if ([sender isKindOfClass:[UIButton class]]) {
        UIButton *lumaButton = sender;
        
        if (lumaButton.selected == TRUE) {
            lumaButton.selected = FALSE;
            NSLog(@"Disable Luma");
            [self.TheDevice setLumaMode:0];
        }
        else {
            lumaButton.selected = TRUE;
            NSLog(@"Enable Luma");
            
            for (int i = 0; i < 10000; i++) {
                if (i % 40 == 0) {
                    [self.TheDevice setLumaMode:i/40];
                }
            }
            
            [self.TheDevice setLumaMode:255];
            
        }
    }
}

#pragma mark - Transition Handeling
// When returning to the root view: disable all streaming, and disconnect the device
- (void)viewWillDisappear:(BOOL)animated
{
    
    if ([self.navigationController.viewControllers indexOfObject:self]==NSNotFound) {
        [self disconnectAllDevices];
    }
    
    [super viewWillDisappear:animated];
    
}

#pragma mark - Utility
- (void)disconnectAllDevices
{
    for (VTNodeDevice* device in [VTNodeController allConnectedNodeDevices]) {
        [device disableAllStreaming];
        [device disconnect];
    }
}

#pragma mark - Teardown
- (void)viewDidUnload
{
    [self setDeviceName:nil];
    [self setDeviceInDataMode:nil];
    [self setDeviceIsFullyConnected:nil];
    [self setDeviceBatteryLevel:nil];
    [self setDeviceConnected:nil];
    [self setDeviceDescription:nil];
    [self setPeripheralName:nil];
    [self setPeripheralUUID:nil];
    [self setDeviceModuleA:nil];
    [self setDeviceModuleB:nil];
    [self setKoreAccX:nil];
    [self setKoreAccY:nil];
    [self setKoreAccZ:nil];
    [self setKoreGyroX:nil];
    [self setKoreGyroY:nil];
    [self setKoreGyroZ:nil];
    [self setKoreMagX:nil];
    [self setKoreMagY:nil];
    [self setKoreMagZ:nil];
    [self setKoreQ0:nil];
    [self setKoreQ1:nil];
    [self setKoreQ2:nil];
    [self setKoreQ3:nil];
    [self setTherma:nil];
    [self setClimaTemp:nil];
    [self setClimaHumid:nil];
    [self setClimaPres:nil];
    [self setCLimaLight:nil];
    [self setDeviceButtonPressed:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

#pragma mark - Unchanged Functions
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

@end
