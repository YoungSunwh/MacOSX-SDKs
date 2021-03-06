/* CoreGraphics - CGDisplayConfiguration.h
   Copyright (c) 2002-2009 Apple Inc.
   All rights reserved. */

#ifndef CGDISPLAYCONFIGURATION_H_
#define CGDISPLAYCONFIGURATION_H_

#include <IOKit/IOKitLib.h>
#include <CoreGraphics/CGDirectDisplay.h>

/* The display reconfiguration process:
   - Call `CGBeginDisplayConfiguration' to start.
   - Make all desired changes for all displays.
   - Commit the changes using `CGPerformDisplayConfiguration', or cancel
     with `CGCancelDisplayConfiguration'.

   The resulting layout will be adjusted to remove gaps or overlaps from the
   requested layout, if needed. */

typedef struct _CGDisplayConfigRef *CGDisplayConfigRef;

/* Begin a new set of display configuration changes. This function creates a
   display configuration which provides a context for a set of display
   configuration changes. Use `CGCompleteDisplayConfiguration' to apply the
   changes in a single transaction. */

CG_EXTERN CGError CGBeginDisplayConfiguration(CGDisplayConfigRef *config)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Configure the origin of a display in global display coordinates.

   The new origin of the display is placed as close as possible to the
   requested location, without overlapping or leaving a gap between
   displays.

   Any display whose origin is not explicitly set in a reconfiguration will
   be repositioned to a location as close as possible to its current
   location without overlapping or leaving a gap between displays.

   Note that setting the origin of a display which is mirroring another
   display will remove that display from any mirroring set. */

CG_EXTERN CGError CGConfigureDisplayOrigin(CGDisplayConfigRef config,
  CGDirectDisplayID display, int32_t x, int32_t y)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Configure the display mode of a display. The "options" field is reserved
   for future expansion; pass NULL for now.

   A display mode is a set of properties such as width, height, pixel depth,
   and refresh rate, and options such as stretched LCD panel filling.

   If you use this function to change the mode of a display in a mirroring
   set, Quartz may adjust the bounds, resolutions, and depth of the other
   displays in the set to a safe mode, with matching depth and the smallest
   enclosing size. */

CG_EXTERN CGError CGConfigureDisplayWithDisplayMode(CGDisplayConfigRef config,
  CGDirectDisplayID display, CGDisplayModeRef mode, CFDictionaryRef options)
  CG_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);

/* Enable or disable stereo operation for a display.

   Note that the system normally detects the presence of a stereo window,
   and will automatically switch a display containing a stereo window to
   stereo operation. This function provides a mechanism to force a display
   to stereo operation, and to set options (such as blue line sync signal)
   when in stereo operation.

   When in stereo operation, a display may need to generate a special stereo
   sync signal as part of the video output. The sync signal consists of a
   blue line which occupies the first 25% of the last scanline for the left
   eye view, and the first 75% of the last scanline for the right eye view.
   The remainder of the scanline is black. To force the display to generate
   this sync signal, pass true for `forceBlueLine'; otherwise, pass false.

   Returns `kCGErrorSuccess' on success, or `kCGErrorRangeCheck' if the
   display does not support the stereo operation settings requested.

   On success, the display resolution, mirroring mode, and available display
   modes may change due to hardware-specific capabilities and limitations.
   You should check these settings to verify that they are appropriate for
   your application. */

CG_EXTERN CGError CGConfigureDisplayStereoOperation(CGDisplayConfigRef config,
  CGDirectDisplayID display, boolean_t stereo, boolean_t forceBlueLine)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Make a display a mirror of a master display.

   Pass `kCGNullDirectDisplay' for the master display to disable mirroring.
   Pass `CGMainDisplayID()' for the master display to mirror the main
   display.

   Display mirroring and display matte generation are implemented either in
   hardware (preferred) or software, at the discretion of the device driver.

   - Hardware mirroring

     With hardware mirroring enabled, all drawing is directed to the primary
     display --- see CGDisplayPrimaryDisplay.

     If the device driver selects hardware matte generation, the display
     bounds and rowbytes values are adjusted to reflect the active drawable
     area.

   - Software mirroring

     In this form of mirroring, identical content is drawn into each display
     in the mirroring set. Applications that use the window system need not
     be concerned about mirroring, as the window system takes care of all
     flushing of window content to the appropriate displays.

     Applications that draw directly to the display, as with display
     capture, must make sure to draw the same content to all mirrored
     displays in a software mirror set. When drawing to software mirrored
     displays using a full screen OpenGL context (not drawing through a
     window), you should create shared OpenGL contexts for each display and
     re-render for each display.

     You can use the function `CGGetActiveDisplayList' to determine which
     displays are active, or drawable. This automatically gives your
     application the correct view of the current displays. */

CG_EXTERN CGError CGConfigureDisplayMirrorOfDisplay(CGDisplayConfigRef config,
  CGDirectDisplayID display, CGDirectDisplayID master)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Cancel a set of display configuration changes. On return, the
   configuration is cancelled and is no longer valid. */

CG_EXTERN CGError CGCancelDisplayConfiguration(CGDisplayConfigRef config)
  CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Complete a set of display configuration changes. On return, the
   configuration is no longer valid.

   A configuration change can apply for the life of an application, the life
   of a login session, or permanently. If a request is made to make a change
   permanent, and the change cannot be supported by Mac OS X user interface,
   then the configuration change lasts only for the current login session.

   A permanent configuration change also becomes the current session's
   configuration.

   When the system reverts configurations at app termination, the
   configuration reverts to the session or permanent configuration setting.

   When the system reverts configurations at session termination, the
   configuration reverts to the permanent configuration setting.

   This operation may fail if an unsupported display mode is requested, or
   if another app is running in full-screen mode. */

enum {
  kCGConfigureForAppOnly = 0,
  kCGConfigureForSession = 1,
  kCGConfigurePermanently = 2
};
typedef uint32_t CGConfigureOption;

CG_EXTERN CGError CGCompleteDisplayConfiguration(CGDisplayConfigRef config,
  CGConfigureOption option) CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

/* Restore the permanent display configuration settings for the current
   user. */

CG_EXTERN void CGRestorePermanentDisplayConfiguration(void)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Display changes are reported via a callback mechanism.

   Callbacks are invoked when the app is listening for events, on the event
   processing thread, or from within the display reconfiguration function
   when in the program that is driving the reconfiguration.

   Callbacks should avoid changing display configurations, and should not
   raise exceptions or perform a non-local return such as calling longjmp().

   Before display reconfiguration, a callback fires to inform applications
   of a configuration change. The callback runs once for each on-line
   display. The flag is set to `kCGDisplayBeginConfigurationFlag'. This
   callback does not carry other per-display information, as details of how
   a reconfiguration affects a particular device rely on device-specific
   behaviors which may not be exposed by a device driver.

   After display reconfiguration, at the time the callback function is
   invoked, all display state reported by CoreGraphics, QuickDraw, and the
   Carbon Display Manager API will be up to date. This callback runs after
   the Carbon Display Manager notification callbacks. The callback runs once
   for each added, removed, and currently on-line display. Note that in the
   case of removed displays, calls into the CoreGraphics API with the
   removed display ID will fail. */

enum {
  kCGDisplayBeginConfigurationFlag	= (1 << 0),
  kCGDisplayMovedFlag			= (1 << 1),
  kCGDisplaySetMainFlag			= (1 << 2),
  kCGDisplaySetModeFlag			= (1 << 3),
  kCGDisplayAddFlag			= (1 << 4),
  kCGDisplayRemoveFlag			= (1 << 5),
  kCGDisplayEnabledFlag			= (1 << 8),
  kCGDisplayDisabledFlag		= (1 << 9),
  kCGDisplayMirrorFlag			= (1 << 10),
  kCGDisplayUnMirrorFlag		= (1 << 11),
  kCGDisplayDesktopShapeChangedFlag	= (1 << 12)
};
typedef uint32_t CGDisplayChangeSummaryFlags;

/* A client-supplied callback function that???s invoked whenever the
   configuration of a local display is changed. */

typedef void(*CGDisplayReconfigurationCallBack)(CGDirectDisplayID display,
  CGDisplayChangeSummaryFlags flags, void *userInfo);

/* Register a display reconfiguration callback procedure. The `userInfo'
   argument is passed back to the callback procedure each time it is
   invoked. */

CG_EXTERN CGError CGDisplayRegisterReconfigurationCallback(
  CGDisplayReconfigurationCallBack callback, void *userInfo)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

/* Remove a display reconfiguration callback procedure. */

CG_EXTERN CGError CGDisplayRemoveReconfigurationCallback(
  CGDisplayReconfigurationCallBack callback, void *userInfo)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

/* Specialized configuration changes should be done outside of the scope of
   a `CGBeginDisplayConfiguration'/`CGCompleteDisplayConfiguration' pair, as
   they may alter things such as the available display modes which a normal
   reconfiguration sequence might assume are invariant. */

/* Immediately enable or disable stereo operation for a display.

   Note that the system normally detects the presence of a stereo window,
   and will automatically switch a display containing a stereo window to
   stereo operation. This function provides a mechanism to force a display
   to stereo operation, and to set options (such as blue line sync signal)
   when in stereo operation.

   When in stereo operation, a display may need to generate a special stereo
   sync signal as part of the video output. The sync signal consists of a
   blue line which occupies the first 25% of the last scanline for the left
   eye view, and the first 75% of the last scanline for the right eye view.
   The remainder of the scanline is black. To force the display to generate
   this sync signal, pass true for `forceBlueLine'; otherwise, pass false.

   Returns `kCGErrorSuccess' on success, or `kCGErrorRangeCheck' if the
   display does not support the stereo operation settings requested.

   On success, the display resolution, mirroring mode, and available display
   modes may change due to hardware-specific capabilities and limitations.
   You should check these settings to verify that they are appropriate for
   your application. */

CG_EXTERN CGError CGDisplaySetStereoOperation(CGDirectDisplayID display,
  boolean_t stereo, boolean_t forceBlueLine, CGConfigureOption option)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Return true if the display is connected, awake, and available for
   drawing; false otherwise. */

CG_EXTERN boolean_t CGDisplayIsActive(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return true if the display is asleep (and is therefore not drawable);
   false otherwise. */

CG_EXTERN boolean_t CGDisplayIsAsleep(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return true if the display is connected or online; false otherwise. */

CG_EXTERN boolean_t CGDisplayIsOnline(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return true if the display is the current main display; false
   otherwise. */

CG_EXTERN boolean_t CGDisplayIsMain(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return true if the display is built-in, such as the internal display in
   portable systems; false otherwise. */

CG_EXTERN boolean_t CGDisplayIsBuiltin(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return true if the display is in a mirroring set; false otherwise. */

CG_EXTERN boolean_t CGDisplayIsInMirrorSet(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return true if the display is always in a mirroring set and cannot be
   unmirrored; false otherwise. */

CG_EXTERN boolean_t CGDisplayIsAlwaysInMirrorSet(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return true if the display is in a hardware mirroring set; false
   otherwise. */

CG_EXTERN boolean_t CGDisplayIsInHWMirrorSet(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* For a secondary display in a mirror set, return the display being
   mirrored (the primary display), or `kCGNullDirectDisplay' if the display
   is the primary display or if the display is unmirrored. */

CG_EXTERN CGDirectDisplayID CGDisplayMirrorsDisplay(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return true if the display is using OpenGL acceleration; false
   otherwise. */

CG_EXTERN boolean_t CGDisplayUsesOpenGLAcceleration(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return true if the display is running in a stereo graphics mode; false
   otherwise. */

CG_EXTERN boolean_t CGDisplayIsStereo(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA); /* 10.4.3 and later. */

/* Return the primary display in a hardware mirror set, or `display' if the
   display is not hardware-mirrored. */

CG_EXTERN CGDirectDisplayID CGDisplayPrimaryDisplay(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return the logical unit number of a display. */

CG_EXTERN uint32_t CGDisplayUnitNumber(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return the vendor number of a display's monitor. */

CG_EXTERN uint32_t CGDisplayVendorNumber(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return the model number of a display's monitor. */

CG_EXTERN uint32_t CGDisplayModelNumber(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return the serial number of a display's monitor. */

CG_EXTERN uint32_t CGDisplaySerialNumber(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return the IOKit service port of a display. */

CG_EXTERN io_service_t CGDisplayIOServicePort(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);

/* Return the width and height of a display in millimeters.

   If 'display' is not a valid display ID, the size returned has a width and
   height of 0.

   If Extended Display Identification Data (EDID) for the display device is
   not available, the size is estimated based on the device width and height
   in pixels from `CGDisplayBounds', with an assumed resolution of 2.835
   pixels/mm, or 72 DPI, a reasonable guess for displays predating EDID
   support. */

CG_EXTERN CGSize CGDisplayScreenSize(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

/* Return the rotation angle of a display in degrees clockwise.

   A display rotation of 90?? implies the display is rotated clockwise 90??,
   such that what was the physical bottom of the display is now the left
   side, and what was the physical top is now the right side.

   If `display' is not a valid display ID, the rotation returned is 0. */

CG_EXTERN double CGDisplayRotation(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* Return the color space of a display. */

CG_EXTERN CGColorSpaceRef CGDisplayCopyColorSpace(CGDirectDisplayID display)
  CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* These functions are deprecated; do not use them. */

CG_EXTERN CGError CGConfigureDisplayMode(CGDisplayConfigRef config,
  CGDirectDisplayID display, CFDictionaryRef mode)
  CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_6,
    __IPHONE_NA, __IPHONE_NA);

#endif /* CGDISPLAYCONFIGURATION_H_ */
