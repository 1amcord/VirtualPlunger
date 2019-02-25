// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VJOYINTERFACE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VJOYINTERFACE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef VJOYINTERFACE_EXPORTS
#define VJOYINTERFACE_API __declspec(dllexport)
#else
#define VJOYINTERFACE_API __declspec(dllimport)
#endif

#ifdef STATIC
#undef VJOYINTERFACE_API
#define VJOYINTERFACE_API
#endif

///////////////////////////// vJoy device (collection) status ////////////////////////////////////////////
#ifndef VJDSTAT
#define VJDSTAT
enum VjdStat  /* Declares an enumeration data type */
{
	VJD_STAT_OWN,	// The  vJoy Device is owned by this application.
	VJD_STAT_FREE,	// The  vJoy Device is NOT owned by any application (including this one).
	VJD_STAT_BUSY,	// The  vJoy Device is owned by another application. It cannot be acquired by this application.
	VJD_STAT_MISS,	// The  vJoy Device is missing. It either does not exist or the driver is down.
	VJD_STAT_UNKN	// Unknown
}; 

/* Error codes for some of the functions */
#define NO_HANDLE_BY_INDEX				 -1
#define BAD_PREPARSED_DATA				 -2
#define NO_CAPS				 			 -3
#define BAD_N_BTN_CAPS				 	 -4
#define BAD_CALLOC				 	 	 -5
#define BAD_BTN_CAPS				 	 -6
#define BAD_BTN_RANGE				 	 -7
#define BAD_N_VAL_CAPS				 	 -8
#define BAD_ID_RANGE				 	 -9
#define NO_SUCH_AXIS				 	 -10
#define BAD_DEV_STAT				 	 -11
#define NO_DEV_EXIST				 	 -12
#define NO_FILE_EXIST				 	 -13

/* Registry Constants */
#define REG_PARAM		L"SYSTEM\\CurrentControlSet\\services\\vjoy\\Parameters"
#define REG_PARAM_DEV0	L"SYSTEM\\CurrentControlSet\\services\\vjoy\\Parameters\\Device0"
#define REG_PARAM_DEV	L"SYSTEM\\CurrentControlSet\\services\\vjoy\\Parameters\\Device"
#define REG_DEVICE		L"Device"
#define REG_INIT		L"Init"
#define BTN_INIT		L"BTNS"

/* Environment Variables */
#define INTERFACE_LOG_LEVEL "VJOYINTERFACELOGLEVEL"
#define INTERFACE_LOG_FILE  "VJOYINTERFACELOGFILE"
#define INTERFACE_DEF_LOG_FILE	"vJoyInterface.log"

/* Compatibility definitions */
#define FFB_EFF_CONST 	FFB_EFF_REPORT
#define PFFB_EFF_CONST 	PFFB_EFF_REPORT
#define Ffb_h_Eff_Const Ffb_h_Eff_Report

// Device Axis/POVs/Buttons
struct DEVCTRLS {
	BOOL Init;
	BOOL	Rudder;
	BOOL	Aileron;
	BOOL	AxisX;
	BOOL	AxisY;
	BOOL	AxisZ;
	BOOL	AxisXRot;
	BOOL	AxisYRot;
	BOOL	AxisZRot;
	BOOL	Slider;
	BOOL	Dial;
	BOOL	Wheel;
	BOOL	AxisVX;
	BOOL	AxisVY;
	BOOL	AxisVZ;
	BOOL	AxisVBRX;
	BOOL	AxisVBRY;
	BOOL	AxisVBRZ;
	INT		nButtons;	
	INT		nDescHats;
	INT		nContHats;
};

struct DeviceStat {
	HANDLE h;								// Handle to the PDO interface that represents the virtual device
	VjdStat stat;							// Status of the device
	JOYSTICK_POSITION_V2 position;			// Current Position of the device
	HDEVNOTIFY hDeviceNotifyHandle;			// Device Notification Handle
	DEVCTRLS	DeviceControls;				// Structure Holding the data about the device's controls
	PVOID		 pPreParsedData;	// structure contains a top-level collection's preparsed data.
};

struct DEV_INFO {
	BYTE	DeviceID;		// Device ID: Valid values are 1-16
	BYTE	nImplemented;	// Number of implemented device: Valid values are 1-16
	BYTE	isImplemented;	// Is this device implemented?
	BYTE	MaxDevices;		// Maximum number of devices that may be implemented (16)
	BYTE	DriverFFB;		// Does this driver support FFB (False)
	BYTE	DeviceFFB;		// Does this device support FFB (False)
} ;



typedef void (CALLBACK *RemovalCB)(BOOL, BOOL, PVOID);

#endif


#ifndef STATIC
	extern "C" {
#else
namespace vJoyNS {
#endif
	///////////////////////////// vJoy device (collection) Control interface /////////////////////////////////
	/*
		These functions allow writing feeders and other applications that interface with vJoy
		It is assumed that only one vJoy top-device (= Raw PDO) exists.
		This top-level device can have up to 16 siblings (=top-level Reports/collections)
		Each sibling is refered to as a "vJoy Device" and is attributed a unique Report ID (Range: 1-16).

		Naming convetion:
			VJD = vJoy Device
			rID = Report ID
	*/
#pragma warning( push )
#pragma warning( disable : 4995 )
	/////	General driver data
	VJOYINTERFACE_API SHORT __cdecl GetvJoyVersion(void);
	VJOYINTERFACE_API BOOL	__cdecl vJoyEnabled(void);
	VJOYINTERFACE_API PVOID	__cdecl	GetvJoyProductString(void);
	VJOYINTERFACE_API PVOID	__cdecl	GetvJoyManufacturerString(void);
	VJOYINTERFACE_API PVOID	__cdecl	GetvJoySerialNumberString(void);
	VJOYINTERFACE_API BOOL	__cdecl	DriverMatch(WORD * DllVer, WORD * DrvVer);
	VJOYINTERFACE_API VOID	__cdecl	RegisterRemovalCB(RemovalCB cb, PVOID data);
	VJOYINTERFACE_API BOOL	__cdecl	vJoyFfbCap(BOOL * Supported);	// Is this version of vJoy capable of FFB?
	VJOYINTERFACE_API BOOL	__cdecl	GetvJoyMaxDevices(int * n);	// What is the maximum possible number of vJoy devices
	VJOYINTERFACE_API BOOL	__cdecl	GetNumberExistingVJD(int * n);	// What is the number of vJoy devices currently enabled


	/////	vJoy Device properties
	VJOYINTERFACE_API int	__cdecl  GetVJDButtonNumber(UINT rID);	// Get the number of buttons defined in the specified VDJ
	VJOYINTERFACE_API int	__cdecl  GetVJDDiscPovNumber(UINT rID);	// Get the number of descrete-type POV hats defined in the specified VDJ
	VJOYINTERFACE_API int	__cdecl  GetVJDContPovNumber(UINT rID);	// Get the number of descrete-type POV hats defined in the specified VDJ
	VJOYINTERFACE_API BOOL	__cdecl  GetVJDAxisExist(UINT rID, UINT Axis); // Test if given axis defined in the specified VDJ
	VJOYINTERFACE_API BOOL	__cdecl  GetVJDAxisMax(UINT rID, UINT Axis, LONG * Max); // Get logical Maximum value for a given axis defined in the specified VDJ
	VJOYINTERFACE_API BOOL	__cdecl  GetVJDAxisMin(UINT rID, UINT Axis, LONG * Min); // Get logical Minimum value for a given axis defined in the specified VDJ
	VJOYINTERFACE_API enum VjdStat	__cdecl	GetVJDStatus(UINT rID);			// Get the status of the specified vJoy Device.
	// Added in 2.1.6
	VJOYINTERFACE_API BOOL	__cdecl	isVJDExists(UINT rID);					// TRUE if the specified vJoy Device exists																			
	// Added in 2.1.8
	VJOYINTERFACE_API int	__cdecl	GetOwnerPid(UINT rID);					// Reurn owner's Process ID if the specified vJoy Device exists


	/////	Write access to vJoy Device - Basic
	VJOYINTERFACE_API BOOL		__cdecl	AcquireVJD(UINT rID);				// Acquire the specified vJoy Device.
	VJOYINTERFACE_API VOID		__cdecl	RelinquishVJD(UINT rID);			// Relinquish the specified vJoy Device.
	VJOYINTERFACE_API BOOL		__cdecl	UpdateVJD(UINT rID, PVOID pData);	// Update the position data of the specified vJoy Device.

	/////	Write access to vJoy Device - Modifyiers
	// This group of functions modify the current value of the position data
	// They replace the need to create a structure of position data then call UpdateVJD

	//// Reset functions
	VJOYINTERFACE_API BOOL		__cdecl	ResetVJD(UINT rID);			// Reset all controls to predefined values in the specified VDJ
	VJOYINTERFACE_API VOID		__cdecl	ResetAll(void);				// Reset all controls to predefined values in all VDJ
	VJOYINTERFACE_API BOOL		__cdecl	ResetButtons(UINT rID);		// Reset all buttons (To 0) in the specified VDJ
	VJOYINTERFACE_API BOOL		__cdecl	ResetPovs(UINT rID);		// Reset all POV Switches (To -1) in the specified VDJ

	// Write data
	VJOYINTERFACE_API BOOL		__cdecl	SetAxis(LONG Value, UINT rID, UINT Axis);		// Write Value to a given axis defined in the specified VDJ 
	VJOYINTERFACE_API BOOL		__cdecl	SetBtn(BOOL Value, UINT rID, UCHAR nBtn);		// Write Value to a given button defined in the specified VDJ 
	VJOYINTERFACE_API BOOL		__cdecl	SetDiscPov(int Value, UINT rID, UCHAR nPov);	// Write Value to a given descrete POV defined in the specified VDJ 
	VJOYINTERFACE_API BOOL		__cdecl	SetContPov(DWORD Value, UINT rID, UCHAR nPov);	// Write Value to a given continuous POV defined in the specified VDJ 


#pragma warning( pop )
#ifndef STATIC
	} // extern "C"
#else
} // Namespace vJoyNS
#endif
