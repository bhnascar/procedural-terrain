/************************************************************************************PublicHeader:   OVR.hFilename    :   OVR_DeviceMessages.hContent     :   Definition of messages generated by devicesCreated     :   February 5, 2013Authors     :   Lee CooperCopyright   :   Copyright 2013 Oculus VR, Inc. All Rights reserved.Use of this software is subject to the terms of the Oculus licenseagreement provided at the time of installation or download, or whichotherwise accompanies this software in either electronic or hard copy form.*************************************************************************************/#ifndef OVR_DeviceMessages_h#define OVR_DeviceMessages_h#include "OVR_DeviceConstants.h"#include "OVR_DeviceHandle.h"#include "Kernel/OVR_Math.h"#include "Kernel/OVR_Array.h"#include "Kernel/OVR_Color.h"namespace OVR {class DeviceBase;class DeviceHandle;#define OVR_MESSAGETYPE(devName, msgIndex)   ((Device_##devName << 8) | msgIndex)// MessageType identifies the structure of the Message class; based on the message,// casting can be used to obtain the exact value.enum MessageType{    // Used for unassigned message types.    Message_None            = 0,    // Device Manager Messages    Message_DeviceAdded             = OVR_MESSAGETYPE(Manager, 0),  // A new device is detected by manager.    Message_DeviceRemoved           = OVR_MESSAGETYPE(Manager, 1),  // Existing device has been plugged/unplugged.    // Sensor Messages    Message_BodyFrame               = OVR_MESSAGETYPE(Sensor, 0),   // Emitted by sensor at regular intervals.    // Latency Tester Messages    Message_LatencyTestSamples          = OVR_MESSAGETYPE(LatencyTester, 0),    Message_LatencyTestColorDetected    = OVR_MESSAGETYPE(LatencyTester, 1),    Message_LatencyTestStarted          = OVR_MESSAGETYPE(LatencyTester, 2),    Message_LatencyTestButton           = OVR_MESSAGETYPE(LatencyTester, 3),};//-------------------------------------------------------------------------------------// Base class for all messages.class Message{public:    Message(MessageType type = Message_None,            DeviceBase* pdev = 0) : Type(type), pDevice(pdev)    { }    MessageType Type;    // What kind of message this is.    DeviceBase* pDevice; // Device that emitted the message.};// Sensor BodyFrame notification.// Sensor uses Right-Handed coordinate system to return results, with the following// axis definitions://  - Y Up positive//  - X Right Positive//  - Z Back Positive// Rotations a counter-clockwise (CCW) while looking in the negative direction// of the axis. This means they are interpreted as follows://  - Roll is rotation around Z, counter-clockwise (tilting left) in XY plane.//  - Yaw is rotation around Y, positive for turning left.//  - Pitch is rotation around X, positive for pitching up.class MessageBodyFrame : public Message{public:    MessageBodyFrame(DeviceBase* dev)        : Message(Message_BodyFrame, dev), Temperature(0.0f), TimeDelta(0.0f)    {    }    Vector3f Acceleration;   // Acceleration in m/s^2.    Vector3f RotationRate;   // Angular velocity in rad/s^2.    Vector3f MagneticField;  // Magnetic field strength in Gauss.    float    Temperature;    // Temperature reading on sensor surface, in degrees Celsius.    float    TimeDelta;      // Time passed since last Body Frame, in seconds.};// Sent when we receive a device status changes (e.g.:// Message_DeviceAdded, Message_DeviceRemoved).class MessageDeviceStatus : public Message{public:	MessageDeviceStatus(MessageType type, DeviceBase* dev, const DeviceHandle &hdev)		: Message(type, dev), Handle(hdev) { }	DeviceHandle Handle;};//-------------------------------------------------------------------------------------// ***** Latency Tester// Sent when we receive Latency Tester samples.class MessageLatencyTestSamples : public Message{public:    MessageLatencyTestSamples(DeviceBase* dev)        : Message(Message_LatencyTestSamples, dev)    {    }    Array<Color>     Samples;};// Sent when a Latency Tester 'color detected' event occurs.class MessageLatencyTestColorDetected : public Message{public:    MessageLatencyTestColorDetected(DeviceBase* dev)        : Message(Message_LatencyTestColorDetected, dev)    {    }    UInt16      Elapsed;    Color       DetectedValue;    Color       TargetValue;};// Sent when a Latency Tester 'change color' event occurs.class MessageLatencyTestStarted : public Message{public:    MessageLatencyTestStarted(DeviceBase* dev)        : Message(Message_LatencyTestStarted, dev)    {    }    Color    TargetValue;};// Sent when a Latency Tester 'button' event occurs.class MessageLatencyTestButton : public Message{public:    MessageLatencyTestButton(DeviceBase* dev)        : Message(Message_LatencyTestButton, dev)    {    }};} // namespace OVR#endif