
/*
     File:       DiscRecordingUI/DREraseSession.h
 
     Contains:   Carbon erase user interface for DiscRecording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef _H_DREraseSession
#define _H_DREraseSession

#ifndef _H_DiscRecording
#import <DiscRecording/DiscRecording.h>
#endif

#ifndef __CARBON__
#import <Carbon/Carbon.h>
#endif

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*!
	@typedef DREraseSessionRef
	This is the type of a reference to DREraseSession instances.
*/
typedef struct __DREraseSession*	DREraseSessionRef;

/*!
	@function	DREraseSessionGetTypeID
	@abstract	Returns the type identifier of all DREraseSession instances.
	@result		A Core Foundation type ID.
*/
extern CFTypeID
DREraseSessionGetTypeID()									AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@function	DREraseSessionCreate
	@abstract	Creates a new erase session.
	@result		A reference to a new DREraseSession.
*/
extern DREraseSessionRef
DREraseSessionCreate()										AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@function	DREraseSessionSetErase
	@abstract	Sets the erase object for this session.
	@param		eraseSession	The erase session. If this parameter is not a valid
								DREraseSessionRef, the behavior is undefined. 
	@param		erase			The erase to use for the session. If this parameter is not a valid
								DREraseRef, the behavior is undefined. 
*/
extern void
DREraseSessionSetErase(
	DREraseSessionRef	eraseSession,
	DREraseRef			erase)								AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@function	DREraseSessionGetErase
	@abstract	Returns the erase object for this session.
	@param		eraseSession	The erase session. If this parameter is not a valid
								DREraseSessionRef, the behavior is undefined. 
	@result		A reference to the erase object for the session. If the setup dialog has not been run or
				a burn object has not been set with DREraseSessionSetErase, this function returns NULL.
*/
extern DREraseRef
DREraseSessionGetErase(
	DREraseSessionRef	eraseSession)						AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*??????????????????????????????????????????????????????????????????????????????????????????????????????*/
/*	? Dialog Result Codes
/*??????????????????????????????????????????????????????????????????????????????????????????????????????*/
/*!
	@enum		Erase Session Dialog Result Codes
	@discussion	Return codes for the erase session setup dialog.
	@constant	kDREraseSessionOK		Value returned by the setup dialog when the user has confirmed the erase setup.
	@constant	kDREraseSessionCancel	Value returned by the setup dialog when the user has canceled the erase setup.
*/
enum {
	kDREraseSessionOK				= 1,
	kDREraseSessionCancel			= 0
};


/*??????????????????????????????????????????????????????????????????????????????????????????????????????*/
/*	? Setup Dialog Options
/*??????????????????????????????????????????????????????????????????????????????????????????????????????*/
/*!
	@enum		DREraseSessionSetupDialogOptions struct version
*/
enum {
	kEraseSessionSetupDialogOptionsCurrentVersion      = 1
};

/*!
	@enum		Erase Setup Dialog Option Flags
	@constant	kEraseSessionSetupDialogDefaultOptions	Use defaults for all the options
	@constant	kEraseSessionSetupDialogDontHandleReservations	Session does not handle media reservations. Application handles them itself
*/
enum {
	kEraseSessionSetupDialogDefaultOptions			= 0x00000000,	/* use defaults for all the options */
	kEraseSessionSetupDialogDontHandleReservations	= 0x00000001,	/* Don't handle media reservations. Application handles them itself */
};
/*!
	@typedef 	DREraseSessionSetupDialogOptionFlags
	@abstract	Specifies setup dialog configuration options.
*/
typedef UInt32 DREraseSessionSetupDialogOptionFlags;

/*!
	@struct 	DREraseSessionSetupDialogOptions
	@abstract	Options passed into the setup dialog to configure it.
	@field		version				Identifies the version of this structure.
	@field		dialogOptionFlags	One of several constants defined by the DREraseSessionSetupDialogOptionFlags 
									data type as described in ?Erase Setup Dialog Option Flags?.
*/
struct DREraseSessionSetupDialogOptions {
	UInt32										version;
	DREraseSessionSetupDialogOptionFlags		dialogOptionFlags;		/* option flags for affecting the dialog's behavior */
};
typedef struct DREraseSessionSetupDialogOptions	DREraseSessionSetupDialogOptions;


/*??????????????????????????????????????????????????????????????????????????????????????????????????????*/
/*	? Setup Dialog Callbacks
/*??????????????????????????????????????????????????????????????????????????????????????????????????????*/
/*!
	@enum		DREraseSessionSetupCallbacks struct version
*/
enum {
	kDREraseSessionSetupCallbacksCurrentVersion	= 1
};

/*!
	@typedef	DREraseSessionDeviceCheckProcPtr
	@abstract	Callback used for checking the suitability of a device.
	@discussion This callback is called whenever a new device appears. It's purpose is to allow the
				application to filter out devices which do not support the operation to be performed. for
				example, a device may filter our CD-R/W's if it is a DVD creation appliacation.
	@param		eraseSession	The erase session object.
	@param		device			The device to examine.
	@result		A Boolean value indicating the suitability of the device.
*/
typedef CALLBACK_API( Boolean , DREraseSessionDeviceCheckProcPtr )(DREraseSessionRef eraseSession, DRDeviceRef device);

/*!
	@typedef	DREraseSessionMediaCheckProcPtr
	@abstract	Callback used for checking the suitability of media in a device.
	@discussion This callback is called whenever the state of the media has changed. It's purpose is to allow the
				application to determine if the media is suitable for the operation to be performed. For example,
				the application an check to see if there is enough space on the media for the data to be written.
	@param		eraseSession	The erase session object.
	@param		device			The device containing the media to examine.
	@param		prompt			A pointer to a CFStringRef. An application may return a custom message to display in the 
								setup dialog.
	@result		A Boolean value indicating the suitability of the media.
*/
typedef CALLBACK_API( Boolean , DREraseSessionMediaCheckProcPtr )(DREraseSessionRef eraseSession, DRDeviceRef device, CFStringRef* prompt);

/*!
	@typedef	DREraseSessionDeviceSelectionNotificationProcPtr
	@abstract	Callback used to notify the application of a new device selected.
	@param		eraseSession	The erase session object.
	@param		device			The newly selected device.
*/
typedef CALLBACK_API( void , DREraseSessionDeviceSelectionNotificationProcPtr )(DREraseSessionRef eraseSession, DRDeviceRef selectedDevice);

/*!
	@struct		DREraseSessionSetupCallbacks
	@abstract	Callback functions passed to the setup dialog.
	@field		version					Identifies the version of this structure.
	@field		deviceShouldBeTarget	Pointer to a DREraseSessionDeviceCheckProcPtr. The value of this field may be NULL.
	@field		containsSuitableMedia	Pointer to a DREraseSessionMediaCheckProcPtr. The value of this field may be NULL.
	@field		deviceSelectionChanged	Pointer to a DREraseSessionDeviceSelectionNotificationProcPtr. The value of this field may be NULL.
*/
struct DREraseSessionSetupCallbacks {
	UInt32												version;
	DREraseSessionDeviceCheckProcPtr					deviceShouldBeTarget;
	DREraseSessionMediaCheckProcPtr						containsSuitableMedia;
	DREraseSessionDeviceSelectionNotificationProcPtr	deviceSelectionChanged;
};
typedef struct DREraseSessionSetupCallbacks	DREraseSessionSetupCallbacks;


/*!
	@function	DREraseSessionSetupDialog
	@abstract	Presents the setup interface as a modal dialog.
	@discussion	This function present the user with a modal dialog that allows them to configure an erase to their custom
				settings. These include: the device to use and the type of erase to perform.
				and others. The function does not return until the user dismissed the dialog.
	@param		eraseSession	The erase session object
	@param		options			A pointer to a structure of type DREraseSessionSetupDialogOptions. 
								This pointer may be NULL if no custom configuration is required.
	@param		setupCallbacks	A pointer to a structure of type DREraseSessionSetupCallbacks. 
								This pointer may be NULL if no custom behavior is desired.
	@param		resultCode		A pointer to a SInt8 to hold the result code for the setup dialog.
								May be one of the constants defined by "Erase Session Dalog Result Codes".
	@result		An OSStatus.
*/
extern SInt8
DREraseSessionSetupDialog(
	DREraseSessionRef					eraseSession,
	DREraseSessionSetupDialogOptions*	options,
	DREraseSessionSetupCallbacks*		setupCallbacks)			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*??????????????????????????????????????????????????????????????????????????????????????????????????????*/
/*	? Progress Dialog Callbacks
/*??????????????????????????????????????????????????????????????????????????????????????????????????????*/
/*!
	@enum		kDREraseProgressSetupCallbacksCurrentVersion struct version
*/
enum {
	kDREraseProgressSetupCallbacksCurrentVersion	= 1
};

/*!
	@typedef	DREraseSessionProgressBeginNotificationProcPtr
	@abstract	Callback notifying the application the erase progress is about to begin.
	@discussion	This callback is called when the erase progress is about to be displayed. This allows the application
				to do things such as disable the quit menu item, or the close menu for a document window.
	@param		eraseSession	The erase session object.
*/
typedef CALLBACK_API( void , DREraseSessionProgressBeginNotificationProcPtr )(DREraseSessionRef eraseSession);

/*!
	@typedef	DREraseSessionProgressFinishNotificationProcPtr
	@abstract	Callback notifying the application the erase progress is has finished.
	@discussion	This callback is called when the erase progress has been removed from view. This allows the application
				to do things such as re-enable the quit menu item, or the close menu for a document window.
	@param		eraseSession	The erase session object.
*/
typedef CALLBACK_API( void , DREraseSessionProgressFinishNotificationProcPtr )(DREraseSessionRef eraseSession);

/*!
	@typedef	DREraseSessionProgressFinishNotificationProcPtr
	@abstract	Callback notifying the application the erase progress is has finished.
	@discussion	This callback is called when the erase operation completes, either successfully or with an error.
				This function can be used by the application to present it's own custom end-of-erase handling. If the 
				application wants to present it's own end-of-erase notification, it can do so from this callback. If it
				does, it can return a false return value to prevent the erase session from presenting it's own notification.
	@param		eraseSession	The erase session object.
	@param		erase		The erase instance that just finished.
	@result		A Boolean value controlling the display of the erase session's error dialog.
*/
typedef CALLBACK_API( Boolean , DREraseSessionEraseCompleteProcPtr )(DREraseSessionRef eraseSession, DREraseRef erase);

/*!
	@struct		DREraseSessionProgressCallbacks
	@abstract	Callback functions passed to the progress dialog.
	@field		version					Identifies the version of this structure.
	@field		deviceShouldBeTarget	Pointer to a DREraseSessionProgressBeginNotificationProcPtr. The value of this field may be NULL.
	@field		containsSuitableMedia	Pointer to a DREraseSessionProgressFinishNotificationProcPtr. The value of this field may be NULL.
	@field		deviceSelectionChanged	Pointer to a DREraseSessionEraseCompleteProcPtr. The value of this field may be NULL.
*/
struct DREraseSessionProgressCallbacks {
	UInt32											version;
	DREraseSessionProgressBeginNotificationProcPtr	progressWillBegin;
	DREraseSessionProgressFinishNotificationProcPtr	progressDidFinish;
	DREraseSessionEraseCompleteProcPtr				eraseDidFinish;
};
typedef struct DREraseSessionProgressCallbacks	DREraseSessionProgressCallbacks;


/*??????????????????????????????????????????????????????????????????????????????????????????????????????*/
/*	? Progress Dialog Options
/*??????????????????????????????????????????????????????????????????????????????????????????????????????*/
/*!
	@enum		DREraseSessionProgressDialogOptions struct version
*/
enum {
	kEraseSessionProgressDialogOptionsCurrentVersion      = 1
};

/*!
	@enum		Erase Progress Dialog Option Flags
	@constant	kEraseSessionProgressDialogDefaultOptions	Use defaults for all the options
*/
enum {
	kEraseSessionProgressDialogDefaultOptions			= 0x00000000	/* use defaults for all the options */
};

/*!
	@typedef 	DREraseSessionProgressDialogOptionFlags
	@abstract	Specifies progress dialog configuration options.
*/
typedef UInt32 DREraseSessionProgressDialogOptionFlags;

/*!
	@struct 	DREraseSessionProgressDialogOptions
	@abstract	Options passed into the progress dialog to configure it.
	@field		version				Identifies the version of this structure.
	@field		dialogOptionFlags	One of several constants defined by the DREraseSessionProgressDialogOptionFlags 
									data type as described in ?Erase Progress Dialog Option Flags?.
	@field		description			A CFStringRef that defines a custom description to be used for the dialog.
									If you do not provide this string (passing NULL), the normal description is used.
*/
struct DREraseSessionProgressDialogOptions {
	UInt32									version;
	DREraseSessionProgressDialogOptionFlags	dialogOptionFlags;		/* option flags for affecting the dialog's behavior */
	CFStringRef								description;			/* optional description of the erase */
};
typedef struct DREraseSessionProgressDialogOptions	DREraseSessionProgressDialogOptions;


/*!
	@function	DREraseSessionBeginProgressDialog
	@abstract	Presents the progress interface as a non-modal dialog.
	@discussion	This function present the user with a non-modal dialog that shows the erase progress.
	@param		eraseSession	The erase session object
	@param		options			A pointer to a structure of type DREraseSessionSetupDialogOptions. 
	@param		progressCallbacks	A pointer to a structure of type DREraseSessionProgressCallbacks. 
									This pointer may be NULL if no custom behavior is desired.
	@result		An OSStatus.
*/
extern void
DREraseSessionBeginProgressDialog(
	DREraseSessionRef						eraseSession,
	DREraseSessionProgressDialogOptions*	options,
	DREraseSessionProgressCallbacks*		progressCallbacks)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#ifdef __cplusplus
}
#endif

#endif /* _H_DREraseSession */
