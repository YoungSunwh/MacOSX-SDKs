//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCameraDevice.h
//  ImageCaptureCore
//
//  Copyright (c) 2008 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------
/*!
	@header ICCameraDevice
    ICCameraDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class.
*/

#import <ImageCaptureCore/ICDevice.h>
#import <ImageCaptureCore/ICCameraItem.h>

//------------------------------------------------------------------------------------------------------------------------------
// Constants used to describe capabilities of a camera

/*!
    @const      ICCameraDeviceCanTakePicture
    @abstract   ICCameraDeviceCanTakePicture
    @discussion Indicates that the camera can capture shoot a picture while it is connected.
*/
extern NSString *const ICCameraDeviceCanTakePicture;

/*!
    @const      ICCameraDeviceCanDeleteOneFile
    @abstract   ICCameraDeviceCanDeleteOneFile
    @discussion Indicates that the camera can delete a file at a time while it is connected.
*/
extern NSString *const ICCameraDeviceCanDeleteOneFile;

/*!
    @const      ICCameraDeviceCanDeleteAllFiles
    @abstract   ICCameraDeviceCanDeleteAllFiles
    @discussion Indicates that the camera can delete all files in a single operation while it is connected. 
*/
extern NSString *const ICCameraDeviceCanDeleteAllFiles;

/*!
    @const      ICCameraDeviceCanSyncClock
    @abstract   ICCameraDeviceCanSyncClock
    @discussion Indicates that the camera can synchronize its date and time with that of the host computer.
*/
extern NSString *const ICCameraDeviceCanSyncClock;

/*!
    @const      ICCameraDeviceCanReceiveFile
    @abstract   ICCameraDeviceCanReceiveFile
    @discussion Indicates that the host can upload files to the camera.
*/
extern NSString *const ICCameraDeviceCanReceiveFile;

/*!
    @const      ICCameraDeviceCanAcceptPTPCommands
    @abstract   ICCameraDeviceCanAcceptPTPCommands
    @discussion Indicates that the camera can accept PTP commands.
*/
extern NSString *const ICCameraDeviceCanAcceptPTPCommands;

//------------------------------------------------------------------------------------------------------------------------------
// Allowed keys in the options dictionary used when downloading a file from the camera

/*!
    @const      ICDownloadsDirectoryURL
    @abstract   ICDownloadsDirectoryURL
    @discussion The value for this key should be an NSURL object referencing a writable directory. The downloaded files will be saved in that directory.
*/
extern NSString *const ICDownloadsDirectoryURL;

/*!
    @const      ICSaveAsFilename
    @abstract   ICSaveAsFilename
    @discussion The value for this key should be an NSString object containing the name to be used for the downloaded file.
*/
extern NSString *const ICSaveAsFilename;

/*!
    @const      ICSavedFilename
    @abstract   ICSavedFilename
    @discussion The value for this key will be an NSString object containing the actual name of the saved file. The options dictionary returned in didDownloadFile:error:options:contextInfo: will have this key. 
*/
extern NSString *const ICSavedFilename;

/*!
    @const      ICSavedAncillaryFiles
    @abstract   ICSavedAncillaryFiles
    @discussion The value for this key will be an NSArray object containing names of files associated with the primary file that is downloaded. The options dictionary returned in didDownloadFile:error:options:contextInfo: may have this key.
*/
extern NSString *const ICSavedAncillaryFiles;

/*!
    @const      ICOverwrite
    @abstract   ICOverwrite
    @discussion The value for this key should be an NSNumber object representing a boolean value. If this value is YES, the downloaded file will overwrite an existing file with the same name and extension.
*/
extern NSString *const ICOverwrite;

/*!
    @const      ICDeleteAfterSuccessfulDownload
    @abstract   ICDeleteAfterSuccessfulDownload
    @discussion The value for this key should be an NSNumber object representing a boolean value. If this value is YES, the file will be deleted from the device after it is succcessfully downloaded.
*/
extern NSString *const ICDeleteAfterSuccessfulDownload;

//--------------------------------------------------------------------------------------------------------- Forward Declarations

@class ICCameraDevice;

//------------------------------------------------------------------------------------------------------- ICCameraDeviceDelegate
/*! 
  @protocol ICCameraDeviceDelegate  <ICDeviceDelegate>
  @abstract A delegate of ICCameraDevice must conform to ICCameraDeviceDelegate protocol.
  @discussion The ICCameraDeviceDelegate protocol inherits from the ICDeviceDelegate protocol.
*/

@protocol ICCameraDeviceDelegate  <ICDeviceDelegate>

@optional

/*! 
  @method cameraDevice:didAddItem:
  @abstract This message is sent when an object is added to the device.
  @discussion The object may be an instance of ICCameraFolder or ICCameraFile class.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didAddItem:(ICCameraItem*)item;

/*! 
  @method cameraDevice:didRemoveItem:
  @abstract This message is sent when an object is removed from the device.
  @discussion The object may be an instance of ICCameraFolder or ICCameraFile class.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didRemoveItem:(ICCameraItem*)item;

/*! 
  @method cameraDeviceDidChangeCapability:
  @abstract This message is sent when the capability of a device changes.
  @discussion This usually happens when the device module takes control or yields control of the device.
*/
- (void)cameraDeviceDidChangeCapability:(ICCameraDevice*)camera;

/*! 
  @method cameraDevice:didReceiveThumbnailForItem:
  @abstract This message is sent when the thumbnail requested for an item on a device is available.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didReceiveThumbnailForItem:(ICCameraItem*)item;

/*! 
  @method cameraDevice:didReceiveMetadataForItem:
  @abstract This message is sent when the metadata requested for an item on a device is available.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didReceiveMetadataForItem:(ICCameraItem*)item;

/*! 
  @method cameraDevice:didReceivePTPEvent:
  @abstract This message is sent to the delegate to convey a PTP event.
*/
- (void)cameraDevice:(ICCameraDevice*)camera didReceivePTPEvent:(NSData*)eventData;

@end

//--------------------------------------------------------------------------------------------------------------- ICCameraDevice
/*!
	@class ICCameraDevice
    @abstract ICCameraDevice is a concrete subclass of ICDevice class. ICDeviceBrowser creates instances of this class.
*/

@interface ICCameraDevice : ICDevice
{
@private
    id _cameraProperties;
}

/*!
    @property batteryLevelAvailable
    @abstract Indicates if the device has reported battery charge level???.

*/
@property(readonly)   BOOL            batteryLevelAvailable;

/*!
    @property batteryLevel
    @abstract ???Indicates the battery charge level. Its value ranges from 0 to 100.

*/
@property(readonly)   NSUInteger      batteryLevel;

/*!
    @property contentCatalogPercentCompleted
    @abstract ???Indicates the percentage of content cataloging completed on the device. Its value ranges from 0 to 100.

*/
@property(readonly)   NSUInteger      contentCatalogPercentCompleted;

/*!
    @property contents
    @abstract ???Contents of the camera. The structure of the elements in this array will reflect the folder structure of the storage reported by the camera. Each item in this array will correspond to a storage on the camera.

*/
@property(readonly)   NSArray*        contents;

/*!
    @property mediaFiles
    @abstract ???The property mediaFiles represents all image, movie and audio files on the camera. These files are returned as a single array without regard to the folder hierarchy used to store these files on the camera.

*/
@property(readonly)   NSArray*        mediaFiles;

/*!
    @property timeOffset
    @abstract Indicates the time offset, in seconds, between the camera's clock and the computer's clock???. This value is positive if the camera's clock is ahead of the computer's clock. This property should be ignored if the camera's capabilities property does not contain ICCameraDeviceCanSyncClock.

*/
@property(readonly)   NSTimeInterval  timeOffset;

/*! 
  @method filesOfType:
  @abstract This method returns an array of files on the camera of type fileType. 
  @discussion The fileType string is one of the following Uniform Type Identifier strings: kUTTypeImage, kUTTypeMovie, kUTTypeAudio, or kUTTypeData.
*/
- (NSArray*)filesOfType:(NSString*)fileUTType;

/*! 
  @method requestSyncClock
  @abstract Synchronize camera's clock with the computer's clock.
*/
- (void)requestSyncClock;

/*! 
  @method requestTakePicture
  @abstract Capture a new image using the camera.
*/
- (void)requestTakePicture;

/*! 
  @method requestDeleteFiles
  @abstract Deletes files.
*/
- (void)requestDeleteFiles:(NSArray*)files;

/*! 
  @method requestEjectOrDisconnect
  @abstract Eject the media if permitted by the device, or disconnect from a remote device.
*/
- (void)requestEjectOrDisconnect;

/*! 
  @method requestDownloadFile:options:downloadDelegate:didDownloadSelector:contextInfo:
  @abstract Download a file from the camera. Please refer to the top of this header for information about the options.
  @discussion The downloadDelegate passed must not be nil. When this request is completed, the didDownloadSelector of the downloadDelegate object is called.The didDownloadSelector should have the same signature as: - (void)didDownloadFile:(ICCameraFile*)file error:(NSError*)error options:(NSDictionary*)options contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully. 
*/
- (void)requestDownloadFile:(ICCameraFile*)file options:(NSDictionary*)options downloadDelegate:(id)downloadDelegate didDownloadSelector:(SEL)selector contextInfo:(void*)contextInfo;

/*! 
  @method cancelDownload
  @abstract Cancels the current download operation.
*/
- (void)cancelDownload;

/*! 
  @method requestUploadFile:options:uploadDelegate:didUploadSelector:contextInfo:
  @abstract Upload a file at fileURL to the camera. The options dictionary is not used in this version.
  @discussion The uploadDelegate passed must not be nil. When this request is completed, the didUploadSelector of the uploadDelegate object is called. The didUploadSelector should have the same signature as: - (void)didUploadFile:(NSURL*)fileURL error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestUploadFile:(NSURL*)fileURL options:(NSDictionary*)options uploadDelegate:(id)uploadDelegate didUploadSelector:(SEL)selector contextInfo:(void*)contextInfo;

/*! 
  @method requestReadDataFromFile:atOffset:length:readDelegate:didReadDataSelector:contextInfo:
  @abstract This method asynchronously reads data of a specified length from a specified offset.
  @discussion The readDelegate passed must not be nil. When this request is completed, the didReadDataSelector of the readDelegate object is called. The didReadDataSelector should have the same signature as: - (void)didReadData:(NSData*)data fromFile:(ICCameraFile*)file error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestReadDataFromFile:(ICCameraFile*)file atOffset:(off_t)offset length:(off_t)length readDelegate:(id)readDelegate didReadDataSelector:(SEL)selector contextInfo:(void*)contextInfo;

/*! 
  @method requestSendPTPCommand:outData:sendCommandDelegate:sendCommandDelegate:contextInfo:
  @abstract This method asynchronously sends a PTP command to a camera.
  @discussion This should be sent only if the 'capabilities' property contains 'ICCameraDeviceCanAcceptPTPCommands'. All PTP cameras have this capability. The response to this command will be delivered using didSendCommandSelector of sendCommandDelegate. The didSendCommandSelector should have the same signature as: - (void)didSendPTPCommand:(NSData*)command inData:(NSData*)data response:(NSData*)response error:(NSError*)error contextInfo:(void*)contextInfo. The content of error returned should be examined to determine if the request completed successfully.
*/
- (void)requestSendPTPCommand:(NSData*)command outData:(NSData*)data sendCommandDelegate:(id)sendCommandDelegate didSendCommandSelector:(SEL)selector contextInfo:(void*)contextInfo;

@end

//------------------------------------------------------------------------------------------------------------------------------

