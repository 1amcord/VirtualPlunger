# VirtualPlunger
Fix the Z-Axis issue that arduino-based Pincontrol-Controllers have with x360ce program

# Installation Instructions

1. Install  http://vjoystick.sourceforge.net/site/index.php/download-a-install/download
2. Download [VirtualPlunger.exe](https://github.com/1amcord/VirtualPlunger/blob/master/x64/Release/VirtualPlunger.exe) and [vJoyInterface.dll](https://github.com/1amcord/VirtualPlunger/blob/master/x64/Release/vJoyInterface.dll) and put them into separate folder (e.g. c:\VirtualPlunger)
3. Configure x360ce as described in the following pictures

![Step 1](https://github.com/1amcord/VirtualPlunger/blob/master/res/x360ce_1_options.PNG)

![Step 2](https://github.com/1amcord/VirtualPlunger/blob/master/res/x360ce_2_controller1.PNG)

![Step 3](https://github.com/1amcord/VirtualPlunger/blob/master/res/x360ce_3_controller1_right_thumb.PNG)

![Step 4](https://github.com/1amcord/VirtualPlunger/blob/master/res/x360ce_4_controller2.PNG)


# Idea

This program makes usage of these two examples : http://vjoystick.sourceforge.net/site/index.php/download-a-install https://github.com/walbourn/directx-sdk-samples/tree/master/DirectInput/Joystick

A virtual device for the Z-Axis is created as input for x360ce.
