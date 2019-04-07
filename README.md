# VirtualPlunger

Fixes the Z-Axis issue for arduino-based controllerboards (e.g. Pincontrol) in combination with x360ce.

# Installation

1. Install  http://vjoystick.sourceforge.net/site/index.php/download-a-install/download
2. Reboot
3. Download the latest release and put the two files **VirtualPlunger.exe** and **vJoyInterface.dll** into a separate folder (e.g. c:\VirtualPlunger)
4. Run VirtualPlunger.exe
5. Configure **vJoy** and **x360ce** as described in the following pictures
6. Make sure **VirtualPlunger.exe** starts automatically after login or before each launch of a Pinball FX-table.

![Step 1](https://github.com/1amcord/VirtualPlunger/blob/master/res/devicemanager_1.png)

![Step 2](https://github.com/1amcord/VirtualPlunger/blob/master/res/devicemanager_2.png)

![Step 3](https://github.com/1amcord/VirtualPlunger/blob/master/res/x360ce_1_options.PNG)

![Step 4](https://github.com/1amcord/VirtualPlunger/blob/master/res/x360ce_2_controller1.PNG)

![Step 5](https://github.com/1amcord/VirtualPlunger/blob/master/res/x360ce_3_controller1_right_thumb.PNG)

![Step 6](https://github.com/1amcord/VirtualPlunger/blob/master/res/x360ce_4_controller2.PNG)

# Debug

<<<<<<< HEAD
4. Avoid conflict with Plunger in Virtual Pinball
- Add this to the Launch-Script for Pinball FX3 to start VirtualPlunger.exe in Pinball FX3 only:
```bat
rem Start VirtualPlunger.exe if not already running
set PATH_TO_VIRTUALPLUNGER=c:\VirtualPlunger 
set VIRTUALPLUNGER=VirtualPlunger.exe
tasklist /nh /fi "imagename eq %VIRTUALPLUNGER%" | find /i "%VIRTUALPLUNGER%" > nul || (start "" "%PATH_TO_VIRTUALPLUNGER%\%VIRTUALPLUNGER%")
```
- Add this to the Launch-Script for Visual Pinball to stop VirtualPlunger.exe in Visual Pinball:
```bat
rem stop VirtualPlunger.exe if running
taskkill /F /IM VirtualPlunger.exe```
=======
Run VirtualPlunger.exe with /debug to get a window that shows Z-Axis values.
>>>>>>> ab61563510d947b0c5ff7353c4528e752ce1c74e

# Idea

This program makes usage of these two examples : http://vjoystick.sourceforge.net/site/index.php/download-a-install https://github.com/walbourn/directx-sdk-samples/tree/master/DirectInput/Joystick

A virtual device for the Z-Axis is created as input for x360ce.
