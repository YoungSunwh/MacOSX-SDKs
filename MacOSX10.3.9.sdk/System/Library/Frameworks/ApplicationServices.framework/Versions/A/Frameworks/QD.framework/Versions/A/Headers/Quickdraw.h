/*
     File:       QD/Quickdraw.h
 
     Contains:   Interface to Quickdraw Graphics
 
     Version:    Quickdraw-150.7~2
 
     Copyright:  ? 1985-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QUICKDRAW__
#define __QUICKDRAW__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __COREGRAPHICS__
#include <CoreGraphics/CoreGraphics.h>
#endif

#ifndef __QUICKDRAWTEXT__
#include <QD/QuickdrawText.h>
#endif

#ifndef __CMTYPES__
#include <ColorSync/CMTypes.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

enum {
  invalColReq                   = -1    /*invalid color table request*/
};

enum {
                                        /* transfer modes */
  srcCopy                       = 0,    /*the 16 transfer modes*/
  srcOr                         = 1,
  srcXor                        = 2,
  srcBic                        = 3,
  notSrcCopy                    = 4,
  notSrcOr                      = 5,
  notSrcXor                     = 6,
  notSrcBic                     = 7,
  patCopy                       = 8,
  patOr                         = 9,
  patXor                        = 10,
  patBic                        = 11,
  notPatCopy                    = 12,
  notPatOr                      = 13,
  notPatXor                     = 14,
  notPatBic                     = 15,   /* Special Text Transfer Mode */
  grayishTextOr                 = 49,
  hilitetransfermode            = 50,
  hilite                        = 50,   /* Arithmetic transfer modes */
  blend                         = 32,
  addPin                        = 33,
  addOver                       = 34,
  subPin                        = 35,
  addMax                        = 37,
  adMax                         = 37,
  subOver                       = 38,
  adMin                         = 39,
  ditherCopy                    = 64,   /* Transparent mode constant */
  transparent                   = 36
};

enum {
  italicBit                     = 1,
  ulineBit                      = 2,
  outlineBit                    = 3,
  shadowBit                     = 4,
  condenseBit                   = 5,
  extendBit                     = 6
};

enum {
                                        /* QuickDraw color separation constants */
  normalBit                     = 0,    /*normal screen mapping*/
  inverseBit                    = 1,    /*inverse screen mapping*/
  redBit                        = 4,    /*RGB additive mapping*/
  greenBit                      = 3,
  blueBit                       = 2,
  cyanBit                       = 8,    /*CMYBk subtractive mapping*/
  magentaBit                    = 7,
  yellowBit                     = 6,
  blackBit                      = 5
};

enum {
  blackColor                    = 33,   /* colors expressed in these mappings */
  whiteColor                    = 30,
  redColor                      = 205,
  greenColor                    = 341,
  blueColor                     = 409,
  cyanColor                     = 273,
  magentaColor                  = 137,
  yellowColor                   = 69
};

enum {
  picLParen                     = 0,    /* standard picture comments */
  picRParen                     = 1
};

/* gdType values */
enum {
  clutType                      = 0,    /* lookup table */
  fixedType                     = 1,    /* fixed table - now unused */
  directType                    = 2     /* direct values */
};

/* gdFlags bits. Bits 1..10 are legacy, and currently unused */
enum {
  gdDevType                     = 0,    /* 0 = monochrome 1 = color */
  interlacedDevice              = 2,
  hwMirroredDevice              = 4,
  roundedDevice                 = 5,
  hasAuxMenuBar                 = 6,
  burstDevice                   = 7,
  ext32Device                   = 8,
  ramInit                       = 10,
  mainScreen                    = 11,   /* 1 if main screen */
  allInit                       = 12,   /* 1 if all devices initialized */
  screenDevice                  = 13,   /* 1 if screen device */
  noDriver                      = 14,   /* 1 if no driver for this GDevice */
  screenActive                  = 15    /* 1 if in use*/
};

enum {
  hiliteBit                     = 7,    /* flag bit in LMGet/SetHiliteMode */
  pHiliteBit                    = 0     /* flag bit in LMGet/SetHiliteMode when used with BitClr */
};

/* miscellaneous constants */
enum {
  defQDColors                   = 127,  /* (legacy - now unused) */
  RGBDirect                     = 16,   /* 16 & 32 bits/pixel pixelType value */
  baseAddr32                    = 4     /* pmVersion value: pixmap base address is 32-bit address */
};

enum {
  sysPatListID                  = 0,
  iBeamCursor                   = 1,
  crossCursor                   = 2,
  plusCursor                    = 3,
  watchCursor                   = 4
};

enum {
  kQDGrafVerbFrame              = 0,
  kQDGrafVerbPaint              = 1,
  kQDGrafVerbErase              = 2,
  kQDGrafVerbInvert             = 3,
  kQDGrafVerbFill               = 4
};

#if OLDROUTINENAMES
enum {
  frame                         = kQDGrafVerbFrame,
  paint                         = kQDGrafVerbPaint,
  erase                         = kQDGrafVerbErase,
  invert                        = kQDGrafVerbInvert,
  fill                          = kQDGrafVerbFill
};

#endif  /* OLDROUTINENAMES */

typedef SInt8                           GrafVerb;
enum {
  chunky                        = 0,
  chunkyPlanar                  = 1,
  planar                        = 2
};

typedef SInt8                           PixelType;
typedef short                           Bits16[16];

/***************   IMPORTANT NOTE REGARDING Pattern  **************************************
   Patterns were originally defined as:
   
        C:          typedef unsigned char Pattern[8];
        Pascal:     Pattern = PACKED ARRAY [0..7] OF 0..255;
        
   The old array definition of Pattern would cause 68000 based CPU's to crash in certain circum-
   stances. The new struct definition is safe, but may require source code changes to compile.
    
*********************************************************************************************/
struct Pattern {
  UInt8               pat[8];
};
typedef struct Pattern                  Pattern;
/*
 ConstPatternParam is no longer needed.  It was first created when Pattern was an array.
 Now that Pattern is a struct, it is more straight forward to just add the "const" qualifier
 on the parameter type (e.g. "const Pattern * pat" instead of "ConstPatternParam pat").
*/
typedef const Pattern *                 ConstPatternParam;
typedef Pattern *                       PatPtr;
typedef PatPtr *                        PatHandle;
typedef SignedByte                      QDByte;
typedef QDByte *                        QDPtr;
typedef QDPtr *                         QDHandle;
typedef short                           QDErr;
enum {
  singleDevicesBit              = 0,
  dontMatchSeedsBit             = 1,
  allDevicesBit                 = 2
};

enum {
  singleDevices                 = 1 << singleDevicesBit,
  dontMatchSeeds                = 1 << dontMatchSeedsBit,
  allDevices                    = 1 << allDevicesBit
};

typedef unsigned long                   DeviceLoopFlags;
/*
    PrinterStatusOpcode.  For communication with downloading and printing services.
*/
typedef SInt32                          PrinterStatusOpcode;
enum {
  kPrinterFontStatus            = 0,
  kPrinterScalingStatus         = 1
};

struct PrinterFontStatus {
  SInt32              oResult;
  SInt16              iFondID;
  Style               iStyle;
};
typedef struct PrinterFontStatus        PrinterFontStatus;
struct PrinterScalingStatus {
  Point               oScalingFactors;
};
typedef struct PrinterScalingStatus     PrinterScalingStatus;
struct BitMap {
  Ptr                 baseAddr;
  short               rowBytes;
  Rect                bounds;
};
typedef struct BitMap                   BitMap;
typedef BitMap *                        BitMapPtr;
typedef BitMapPtr *                     BitMapHandle;
struct Cursor {
  Bits16              data;
  Bits16              mask;
  Point               hotSpot;
};
typedef struct Cursor                   Cursor;
typedef Cursor *                        CursPtr;
typedef CursPtr *                       CursHandle;
struct PenState {
  Point               pnLoc;
  Point               pnSize;
  short               pnMode;
  Pattern             pnPat;
};
typedef struct PenState                 PenState;
#if !OPAQUE_TOOLBOX_STRUCTS
struct MacRegion {
  unsigned short      rgnSize;                /* size in bytes; don't rely on it */
  Rect                rgnBBox;                /* enclosing rectangle; in Carbon use GetRegionBounds */
};
typedef struct MacRegion                MacRegion;
/*
   The type name "Region" has a name space collision on Win32.
   Use MacRegion to be cross-platfrom safe.
*/
typedef MacRegion                       Region;
typedef MacRegion *                     RgnPtr;
typedef RgnPtr *                        RgnHandle;
#else
typedef struct OpaqueRgnHandle*         RgnHandle;
#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

struct Picture {
  short               picSize;
  Rect                picFrame;
};
typedef struct Picture                  Picture;
typedef Picture *                       PicPtr;
typedef PicPtr *                        PicHandle;
struct MacPolygon {
  short               polySize;
  Rect                polyBBox;
  Point               polyPoints[1];
};
typedef struct MacPolygon               MacPolygon;
/*
   The type name "Polygon" has a name space collision on Win32.
   Use MacPolygon to be cross-platfrom safe.
*/
typedef MacPolygon                      Polygon;
typedef MacPolygon *                    PolyPtr;
typedef PolyPtr *                       PolyHandle;
typedef CALLBACK_API( void , QDTextProcPtr )(short byteCount, const void *textBuf, Point numer, Point denom);
typedef CALLBACK_API( void , QDLineProcPtr )(Point newPt);
typedef CALLBACK_API( void , QDRectProcPtr )(GrafVerb verb, const Rect *r);
typedef CALLBACK_API( void , QDRRectProcPtr )(GrafVerb verb, const Rect *r, short ovalWidth, short ovalHeight);
typedef CALLBACK_API( void , QDOvalProcPtr )(GrafVerb verb, const Rect *r);
typedef CALLBACK_API( void , QDArcProcPtr )(GrafVerb verb, const Rect *r, short startAngle, short arcAngle);
typedef CALLBACK_API( void , QDPolyProcPtr )(GrafVerb verb, PolyHandle poly);
typedef CALLBACK_API( void , QDRgnProcPtr )(GrafVerb verb, RgnHandle rgn);
typedef CALLBACK_API( void , QDBitsProcPtr )(const BitMap *srcBits, const Rect *srcRect, const Rect *dstRect, short mode, RgnHandle maskRgn);
typedef CALLBACK_API( void , QDCommentProcPtr )(short kind, short dataSize, Handle dataHandle);
typedef CALLBACK_API( short , QDTxMeasProcPtr )(short byteCount, const void *textAddr, Point *numer, Point *denom, FontInfo *info);
typedef CALLBACK_API( void , QDGetPicProcPtr )(void *dataPtr, short byteCount);
typedef CALLBACK_API( void , QDPutPicProcPtr )(const void *dataPtr, short byteCount);
typedef CALLBACK_API( void , QDOpcodeProcPtr )(const Rect *fromRect, const Rect *toRect, UInt16 opcode, SInt16 version);
/* The following is unused on Mac OS X - ignore it! */
typedef CALLBACK_API_C( OSStatus , QDStdGlyphsProcPtr )(void *dataStream, ByteCount size);
typedef CALLBACK_API( void , QDJShieldCursorProcPtr )(short left, short top, short right, short bottom);
typedef STACK_UPP_TYPE(QDTextProcPtr)                           QDTextUPP;
typedef STACK_UPP_TYPE(QDLineProcPtr)                           QDLineUPP;
typedef STACK_UPP_TYPE(QDRectProcPtr)                           QDRectUPP;
typedef STACK_UPP_TYPE(QDRRectProcPtr)                          QDRRectUPP;
typedef STACK_UPP_TYPE(QDOvalProcPtr)                           QDOvalUPP;
typedef STACK_UPP_TYPE(QDArcProcPtr)                            QDArcUPP;
typedef STACK_UPP_TYPE(QDPolyProcPtr)                           QDPolyUPP;
typedef STACK_UPP_TYPE(QDRgnProcPtr)                            QDRgnUPP;
typedef STACK_UPP_TYPE(QDBitsProcPtr)                           QDBitsUPP;
typedef STACK_UPP_TYPE(QDCommentProcPtr)                        QDCommentUPP;
typedef STACK_UPP_TYPE(QDTxMeasProcPtr)                         QDTxMeasUPP;
typedef STACK_UPP_TYPE(QDGetPicProcPtr)                         QDGetPicUPP;
typedef STACK_UPP_TYPE(QDPutPicProcPtr)                         QDPutPicUPP;
typedef STACK_UPP_TYPE(QDOpcodeProcPtr)                         QDOpcodeUPP;
typedef STACK_UPP_TYPE(QDStdGlyphsProcPtr)                      QDStdGlyphsUPP;
typedef STACK_UPP_TYPE(QDJShieldCursorProcPtr)                  QDJShieldCursorUPP;
struct QDProcs {
  QDTextUPP           textProc;
  QDLineUPP           lineProc;
  QDRectUPP           rectProc;
  QDRRectUPP          rRectProc;
  QDOvalUPP           ovalProc;
  QDArcUPP            arcProc;
  QDPolyUPP           polyProc;
  QDRgnUPP            rgnProc;
  QDBitsUPP           bitsProc;
  QDCommentUPP        commentProc;
  QDTxMeasUPP         txMeasProc;
  QDGetPicUPP         getPicProc;
  QDPutPicUPP         putPicProc;
};
typedef struct QDProcs                  QDProcs;
typedef QDProcs *                       QDProcsPtr;
/*
 *  NewQDTextUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDTextUPP
NewQDTextUPP(QDTextProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDLineUPP
NewQDLineUPP(QDLineProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDRectUPP
NewQDRectUPP(QDRectProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDRRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDRRectUPP
NewQDRRectUPP(QDRRectProcPtr userRoutine)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDOvalUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDOvalUPP
NewQDOvalUPP(QDOvalProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDArcUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDArcUPP
NewQDArcUPP(QDArcProcPtr userRoutine)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDPolyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDPolyUPP
NewQDPolyUPP(QDPolyProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDRgnUPP
NewQDRgnUPP(QDRgnProcPtr userRoutine)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDBitsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDBitsUPP
NewQDBitsUPP(QDBitsProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDCommentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDCommentUPP
NewQDCommentUPP(QDCommentProcPtr userRoutine)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDTxMeasUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDTxMeasUPP
NewQDTxMeasUPP(QDTxMeasProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDGetPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDGetPicUPP
NewQDGetPicUPP(QDGetPicProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDPutPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDPutPicUPP
NewQDPutPicUPP(QDPutPicProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDOpcodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDOpcodeUPP
NewQDOpcodeUPP(QDOpcodeProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDStdGlyphsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDStdGlyphsUPP
NewQDStdGlyphsUPP(QDStdGlyphsProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQDJShieldCursorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDJShieldCursorUPP
NewQDJShieldCursorUPP(QDJShieldCursorProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDTextUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDTextUPP(QDTextUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDLineUPP(QDLineUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDRectUPP(QDRectUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDRRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDRRectUPP(QDRRectUPP userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDOvalUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDOvalUPP(QDOvalUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDArcUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDArcUPP(QDArcUPP userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDPolyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDPolyUPP(QDPolyUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDRgnUPP(QDRgnUPP userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDBitsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDBitsUPP(QDBitsUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDCommentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDCommentUPP(QDCommentUPP userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDTxMeasUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDTxMeasUPP(QDTxMeasUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDGetPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDGetPicUPP(QDGetPicUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDPutPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDPutPicUPP(QDPutPicUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDOpcodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDOpcodeUPP(QDOpcodeUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDStdGlyphsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDStdGlyphsUPP(QDStdGlyphsUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDJShieldCursorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDJShieldCursorUPP(QDJShieldCursorUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDTextUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDTextUPP(
  short         byteCount,
  const void *  textBuf,
  Point         numer,
  Point         denom,
  QDTextUPP     userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDLineUPP(
  Point      newPt,
  QDLineUPP  userUPP)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDRectUPP(
  GrafVerb      verb,
  const Rect *  r,
  QDRectUPP     userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDRRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDRRectUPP(
  GrafVerb      verb,
  const Rect *  r,
  short         ovalWidth,
  short         ovalHeight,
  QDRRectUPP    userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDOvalUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDOvalUPP(
  GrafVerb      verb,
  const Rect *  r,
  QDOvalUPP     userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDArcUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDArcUPP(
  GrafVerb      verb,
  const Rect *  r,
  short         startAngle,
  short         arcAngle,
  QDArcUPP      userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDPolyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDPolyUPP(
  GrafVerb    verb,
  PolyHandle  poly,
  QDPolyUPP   userUPP)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDRgnUPP(
  GrafVerb   verb,
  RgnHandle  rgn,
  QDRgnUPP   userUPP)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDBitsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDBitsUPP(
  const BitMap *  srcBits,
  const Rect *    srcRect,
  const Rect *    dstRect,
  short           mode,
  RgnHandle       maskRgn,
  QDBitsUPP       userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDCommentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDCommentUPP(
  short         kind,
  short         dataSize,
  Handle        dataHandle,
  QDCommentUPP  userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDTxMeasUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern short
InvokeQDTxMeasUPP(
  short         byteCount,
  const void *  textAddr,
  Point *       numer,
  Point *       denom,
  FontInfo *    info,
  QDTxMeasUPP   userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDGetPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDGetPicUPP(
  void *       dataPtr,
  short        byteCount,
  QDGetPicUPP  userUPP)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDPutPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDPutPicUPP(
  const void *  dataPtr,
  short         byteCount,
  QDPutPicUPP   userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDOpcodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDOpcodeUPP(
  const Rect *  fromRect,
  const Rect *  toRect,
  UInt16        opcode,
  SInt16        version,
  QDOpcodeUPP   userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDStdGlyphsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeQDStdGlyphsUPP(
  void *          dataStream,
  ByteCount       size,
  QDStdGlyphsUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDJShieldCursorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDJShieldCursorUPP(
  short               left,
  short               top,
  short               right,
  short               bottom,
  QDJShieldCursorUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

#if !OPAQUE_TOOLBOX_STRUCTS
struct GrafPort {
  short               device;                 /* not available in Carbon*/
  BitMap              portBits;               /* in Carbon use GetPortBitMapForCopyBits or IsPortColor*/
  Rect                portRect;               /* in Carbon use Get/SetPortBounds*/
  RgnHandle           visRgn;                 /* in Carbon use Get/SetPortVisibleRegion*/
  RgnHandle           clipRgn;                /* in Carbon use Get/SetPortClipRegion*/
  Pattern             bkPat;                  /* not available in Carbon all GrafPorts are CGrafPorts*/
  Pattern             fillPat;                /* not available in Carbon all GrafPorts are CGrafPorts*/
  Point               pnLoc;                  /* in Carbon use GetPortPenLocation or MoveTo*/
  Point               pnSize;                 /* in Carbon use Get/SetPortPenSize*/
  short               pnMode;                 /* in Carbon use Get/SetPortPenMode*/
  Pattern             pnPat;                  /* not available in Carbon all GrafPorts are CGrafPorts*/
  short               pnVis;                  /* in Carbon use GetPortPenVisibility or Show/HidePen*/
  short               txFont;                 /* in Carbon use GetPortTextFont or TextFont*/
  StyleField          txFace;                 /* in Carbon use GetPortTextFace or TextFace*/
                                              /*StyleField occupies 16-bits, but only first 8-bits are used*/
  short               txMode;                 /* in Carbon use GetPortTextMode or TextMode*/
  short               txSize;                 /* in Carbon use GetPortTextSize or TextSize*/
  Fixed               spExtra;                /* in Carbon use GetPortSpExtra or SpaceExtra*/
  long                fgColor;                /* not available in Carbon */
  long                bkColor;                /* not available in Carbon*/
  short               colrBit;                /* not available in Carbon*/
  short               patStretch;             /* not available in Carbon*/
  Handle              picSave;                /* in Carbon use IsPortPictureBeingDefined*/
  Handle              rgnSave;                /* not available in Carbon*/
  Handle              polySave;               /* not available in Carbon*/
  QDProcsPtr          grafProcs;              /* not available in Carbon all GrafPorts are CGrafPorts*/
};
typedef struct GrafPort                 GrafPort;
typedef GrafPort *                      GrafPtr;
/*
 *  This set of definitions "belongs" in Windows.
 *  But, there is a circularity in the headers where Windows includes Controls and
 *  Controls includes Windows. To break the circle, the information
 *  needed by Controls is moved from Windows to Quickdraw.
 */
typedef GrafPtr                         WindowPtr;
typedef WindowPtr                       DialogPtr;
#else
typedef struct OpaqueWindowPtr*         WindowPtr;
typedef struct OpaqueDialogPtr*         DialogPtr;
typedef struct OpaqueGrafPtr*           GrafPtr;
#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

typedef WindowPtr                       WindowRef;
/* DragConstraint constants to pass to DragGray,DragTheRgn, or ConstrainedDragRgn*/
typedef UInt16                          DragConstraint;
enum {
  kNoConstraint                 = 0,
  kVerticalConstraint           = 1,
  kHorizontalConstraint         = 2
};


typedef CALLBACK_API( void , DragGrayRgnProcPtr )(void);
/*
 *  Here ends the list of things that "belong" in Windows.
 */


struct RGBColor {
  unsigned short      red;                    /*magnitude of red component*/
  unsigned short      green;                  /*magnitude of green component*/
  unsigned short      blue;                   /*magnitude of blue component*/
};
typedef struct RGBColor                 RGBColor;
typedef RGBColor *                      RGBColorPtr;
typedef RGBColorPtr *                   RGBColorHdl;
typedef CALLBACK_API( Boolean , ColorSearchProcPtr )(RGBColor *rgb, long *position);
typedef CALLBACK_API( Boolean , ColorComplementProcPtr )(RGBColor * rgb);
typedef STACK_UPP_TYPE(DragGrayRgnProcPtr)                      DragGrayRgnUPP;
typedef STACK_UPP_TYPE(ColorSearchProcPtr)                      ColorSearchUPP;
typedef STACK_UPP_TYPE(ColorComplementProcPtr)                  ColorComplementUPP;
/*
 *  NewDragGrayRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DragGrayRgnUPP
NewDragGrayRgnUPP(DragGrayRgnProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewColorSearchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ColorSearchUPP
NewColorSearchUPP(ColorSearchProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewColorComplementUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ColorComplementUPP
NewColorComplementUPP(ColorComplementProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDragGrayRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragGrayRgnUPP(DragGrayRgnUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeColorSearchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeColorSearchUPP(ColorSearchUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeColorComplementUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeColorComplementUPP(ColorComplementUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDragGrayRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDragGrayRgnUPP(DragGrayRgnUPP userUPP)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeColorSearchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeColorSearchUPP(
  RGBColor *      rgb,
  long *          position,
  ColorSearchUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeColorComplementUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeColorComplementUPP(
  RGBColor *          rgb,
  ColorComplementUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

struct ColorSpec {
  short               value;                  /*index or other value*/
  RGBColor            rgb;                    /*true color*/
};
typedef struct ColorSpec                ColorSpec;
typedef ColorSpec *                     ColorSpecPtr;
typedef ColorSpec                       CSpecArray[1];
struct ColorTable {
  long                ctSeed;                 /*unique identifier for table*/
  short               ctFlags;                /*high bit: 0 = PixMap; 1 = device*/
  short               ctSize;                 /*number of entries in CTTable*/
  CSpecArray          ctTable;                /*array [0..0] of ColorSpec*/
};
typedef struct ColorTable               ColorTable;
typedef ColorTable *                    CTabPtr;
typedef CTabPtr *                       CTabHandle;
struct xColorSpec {
  short               value;                  /*index or other value*/
  RGBColor            rgb;                    /*true color*/
  short               xalpha;
};
typedef struct xColorSpec               xColorSpec;
typedef xColorSpec *                    xColorSpecPtr;
typedef xColorSpec                      xCSpecArray[1];
struct MatchRec {
  unsigned short      red;
  unsigned short      green;
  unsigned short      blue;
  long                matchData;
};
typedef struct MatchRec                 MatchRec;
/*
    QuickTime 3.0 makes PixMap data structure available on non-Mac OS's.
    In order to implement PixMap in these alternate environments, the PixMap
    had to be extended. The pmReserved field was changed to pmExt which is
    a Handle to extra info.  The planeBytes field was changed to pixelFormat.
    
    In OS X, Quickdraw also uses the new PixMap data structure.
*/
#ifndef OLDPIXMAPSTRUCT
#if TARGET_API_MAC_OS8
#define OLDPIXMAPSTRUCT 1
#else
#define OLDPIXMAPSTRUCT 0
#endif  /* TARGET_API_MAC_OS8 */

#endif  /* !defined(OLDPIXMAPSTRUCT) */


#if OLDPIXMAPSTRUCT
   #define GETPIXMAPPIXELFORMAT(pm)        ( (pm)->pixelSize )
#else
  #define GETPIXMAPPIXELFORMAT(pm)        ( ((pm)->pixelFormat != 0) ? (pm)->pixelFormat : (pm)->pixelSize )
#endif


#if TARGET_OS_MAC && TARGET_API_MAC_OS8
    #define NON_MAC_PIXEL_FORMATS   0
#else
    #define NON_MAC_PIXEL_FORMATS   1
#endif

/* pixel formats*/
enum {
  k1MonochromePixelFormat       = 0x00000001, /* 1 bit indexed*/
  k2IndexedPixelFormat          = 0x00000002, /* 2 bit indexed*/
  k4IndexedPixelFormat          = 0x00000004, /* 4 bit indexed*/
  k8IndexedPixelFormat          = 0x00000008, /* 8 bit indexed*/
  k16BE555PixelFormat           = 0x00000010, /* 16 bit BE rgb 555 (Mac)*/
  k24RGBPixelFormat             = 0x00000018, /* 24 bit rgb */
  k32ARGBPixelFormat            = 0x00000020, /* 32 bit argb    (Mac)*/
  k1IndexedGrayPixelFormat      = 0x00000021, /* 1 bit indexed gray*/
  k2IndexedGrayPixelFormat      = 0x00000022, /* 2 bit indexed gray*/
  k4IndexedGrayPixelFormat      = 0x00000024, /* 4 bit indexed gray*/
  k8IndexedGrayPixelFormat      = 0x00000028 /* 8 bit indexed gray*/
};


/* values for PixMap.pixelFormat*/
enum {
  k16LE555PixelFormat           = 'L555', /* 16 bit LE rgb 555 (PC)*/
  k16LE5551PixelFormat          = '5551', /* 16 bit LE rgb 5551*/
  k16BE565PixelFormat           = 'B565', /* 16 bit BE rgb 565*/
  k16LE565PixelFormat           = 'L565', /* 16 bit LE rgb 565*/
  k24BGRPixelFormat             = '24BG', /* 24 bit bgr */
  k32BGRAPixelFormat            = 'BGRA', /* 32 bit bgra    (Matrox)*/
  k32ABGRPixelFormat            = 'ABGR', /* 32 bit abgr    */
  k32RGBAPixelFormat            = 'RGBA', /* 32 bit rgba    */
  kYUVSPixelFormat              = 'yuvs', /* YUV 4:2:2 byte ordering 16-unsigned = 'YUY2'*/
  kYUVUPixelFormat              = 'yuvu', /* YUV 4:2:2 byte ordering 16-signed*/
  kYVU9PixelFormat              = 'YVU9', /* YVU9 Planar    9*/
  kYUV411PixelFormat            = 'Y411', /* YUV 4:1:1 Interleaved  16*/
  kYVYU422PixelFormat           = 'YVYU', /* YVYU 4:2:2 byte ordering   16*/
  kUYVY422PixelFormat           = 'UYVY', /* UYVY 4:2:2 byte ordering   16*/
  kYUV211PixelFormat            = 'Y211', /* YUV 2:1:1 Packed   8*/
  k2vuyPixelFormat              = '2vuy' /* UYVY 4:2:2 byte ordering   16*/
};


struct PixMap {
  Ptr                 baseAddr;               /*pointer to pixels*/
  short               rowBytes;               /*offset to next line*/
  Rect                bounds;                 /*encloses bitmap*/
  short               pmVersion;              /*pixMap version number*/
  short               packType;               /*defines packing format*/
  long                packSize;               /*length of pixel data*/
  Fixed               hRes;                   /*horiz. resolution (ppi)*/
  Fixed               vRes;                   /*vert. resolution (ppi)*/
  short               pixelType;              /*defines pixel type*/
  short               pixelSize;              /*# bits in pixel*/
  short               cmpCount;               /*# components in pixel*/
  short               cmpSize;                /*# bits per component*/
#if OLDPIXMAPSTRUCT
  long                planeBytes;             /*offset to next plane*/
  CTabHandle          pmTable;                /*color map for this pixMap*/
  long                pmReserved;
#else
  OSType                          pixelFormat;                /*fourCharCode representation*/
    CTabHandle                      pmTable;                    /*color map for this pixMap*/
  void*                           pmExt;                      /*Handle to pixMap extension*/
#endif
};
typedef struct PixMap                   PixMap;
typedef PixMap *                        PixMapPtr;
typedef PixMapPtr *                     PixMapHandle;
struct PixPat {
  short               patType;                /*type of pattern*/
  PixMapHandle        patMap;                 /*the pattern's pixMap*/
  Handle              patData;                /*pixmap's data*/
  Handle              patXData;               /*expanded Pattern data*/
  short               patXValid;              /*flags whether expanded Pattern valid*/
  Handle              patXMap;                /*Handle to expanded Pattern data*/
  Pattern             pat1Data;               /*old-Style pattern/RGB color*/
};
typedef struct PixPat                   PixPat;
typedef PixPat *                        PixPatPtr;
typedef PixPatPtr *                     PixPatHandle;
struct CCrsr {
  short               crsrType;               /*type of cursor*/
  PixMapHandle        crsrMap;                /*the cursor's pixmap*/
  Handle              crsrData;               /*cursor's data*/
  Handle              crsrXData;              /*expanded cursor data*/
  short               crsrXValid;             /*depth of expanded data (0 if none)*/
  Handle              crsrXHandle;            /*future use*/
  Bits16              crsr1Data;              /*one-bit cursor*/
  Bits16              crsrMask;               /*cursor's mask*/
  Point               crsrHotSpot;            /*cursor's hotspot*/
  long                crsrXTable;             /*private*/
  long                crsrID;                 /*private*/
};
typedef struct CCrsr                    CCrsr;
typedef CCrsr *                         CCrsrPtr;
typedef CCrsrPtr *                      CCrsrHandle;
struct GammaTbl {
  short               gVersion;               /*gamma version number*/
  short               gType;                  /*gamma data type*/
  short               gFormulaSize;           /*Formula data size*/
  short               gChanCnt;               /*number of channels of data*/
  short               gDataCnt;               /*number of values/channel*/
  short               gDataWidth;             /*bits/corrected value (data packed to next larger byte size)*/
  short               gFormulaData[1];        /*data for formulas followed by gamma values*/
};
typedef struct GammaTbl                 GammaTbl;
typedef GammaTbl *                      GammaTblPtr;
typedef GammaTblPtr *                   GammaTblHandle;
struct ITab {
  long                iTabSeed;               /*copy of CTSeed from source CTable*/
  short               iTabRes;                /*bits/channel resolution of iTable*/
  Byte                iTTable[1];             /*byte colortable index values*/
};
typedef struct ITab                     ITab;
typedef ITab *                          ITabPtr;
typedef ITabPtr *                       ITabHandle;
struct SProcRec {
  Handle              nxtSrch;                /*SProcHndl Handle to next SProcRec*/
  ColorSearchUPP      srchProc;               /*search procedure proc ptr*/
};
typedef struct SProcRec                 SProcRec;
typedef SProcRec *                      SProcPtr;
typedef SProcPtr *                      SProcHndl;
struct CProcRec {
  Handle              nxtComp;                /*CProcHndl Handle to next CProcRec*/
  ColorComplementUPP  compProc;               /*complement procedure proc ptr*/
};
typedef struct CProcRec                 CProcRec;
typedef CProcRec *                      CProcPtr;
typedef CProcPtr *                      CProcHndl;
/*
    QuickTime 3.0 makes GDevice data structure available on non-Mac OS's.
    In order to implement GDevice in these alternate environments, the GDevice
    had to be extended. The gdReserved field was changed to gdExt which is
    a Handle to extra info.  
*/
#ifndef OLDGDEVICESTRUCT
#if TARGET_API_MAC_OS8
#define OLDGDEVICESTRUCT 1
#else
#define OLDGDEVICESTRUCT 0
#endif  /* TARGET_API_MAC_OS8 */

#endif  /* !defined(OLDGDEVICESTRUCT) */

typedef struct GDevice                  GDevice;
typedef GDevice *                       GDPtr;
typedef GDPtr *                         GDHandle;
struct GDevice {
  short               gdRefNum;               /*driver's unit number*/
  short               gdID;                   /*client ID for search procs*/
  short               gdType;                 /*fixed/CLUT/direct*/
  ITabHandle          gdITable;               /*Handle to inverse lookup table*/
  short               gdResPref;              /*preferred resolution of GDITable*/
  SProcHndl           gdSearchProc;           /*search proc list head*/
  CProcHndl           gdCompProc;             /*complement proc list*/
  short               gdFlags;                /*grafDevice flags word*/
  PixMapHandle        gdPMap;                 /*describing pixMap*/
  long                gdRefCon;               /*reference value*/
  GDHandle            gdNextGD;               /*GDHandle Handle of next gDevice*/
  Rect                gdRect;                 /* device's bounds in global coordinates*/
  long                gdMode;                 /*device's current mode*/
  short               gdCCBytes;              /*depth of expanded cursor data*/
  short               gdCCDepth;              /*depth of expanded cursor data*/
  Handle              gdCCXData;              /*Handle to cursor's expanded data*/
  Handle              gdCCXMask;              /*Handle to cursor's expanded mask*/
#if OLDGDEVICESTRUCT
  long                gdReserved;             /*future use. MUST BE 0*/
#else
  Handle                          gdExt;                      /*QuickTime 3.0 private info*/
#endif
};

struct GrafVars {
  RGBColor            rgbOpColor;             /*color for addPin  subPin and average*/
  RGBColor            rgbHiliteColor;         /*color for hiliting*/
  Handle              pmFgColor;              /*palette Handle for foreground color*/
  short               pmFgIndex;              /*index value for foreground*/
  Handle              pmBkColor;              /*palette Handle for background color*/
  short               pmBkIndex;              /*index value for background*/
  short               pmFlags;                /*flags for Palette Manager*/
};
typedef struct GrafVars                 GrafVars;
typedef GrafVars *                      GVarPtr;
typedef GVarPtr *                       GVarHandle;

#if !OPAQUE_TOOLBOX_STRUCTS
typedef struct CGrafPort                CGrafPort;
typedef CGrafPort *                     CGrafPtr;
#else
typedef GrafPtr                         CGrafPtr;
#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

typedef CALLBACK_API_C( OSStatus , QDPrinterStatusProcPtr )(PrinterStatusOpcode opcode, CGrafPtr currentPort, void *printerStatus);
typedef STACK_UPP_TYPE(QDPrinterStatusProcPtr)                  QDPrinterStatusUPP;

struct CQDProcs {
  QDTextUPP           textProc;
  QDLineUPP           lineProc;
  QDRectUPP           rectProc;
  QDRRectUPP          rRectProc;
  QDOvalUPP           ovalProc;
  QDArcUPP            arcProc;
  QDPolyUPP           polyProc;
  QDRgnUPP            rgnProc;
  QDBitsUPP           bitsProc;
  QDCommentUPP        commentProc;
  QDTxMeasUPP         txMeasProc;
  QDGetPicUPP         getPicProc;
  QDPutPicUPP         putPicProc;
  QDOpcodeUPP         opcodeProc;
  UniversalProcPtr    newProc1;               /* this is the StdPix bottleneck -- see ImageCompression.h */
  QDStdGlyphsUPP      glyphsProc;             /* unused on Mac OS X */
  QDPrinterStatusUPP  printerStatusProc;      /* was newProc3;  now used to communicate status between Printing code and System imaging code */
  UniversalProcPtr    newProc4;
  UniversalProcPtr    newProc5;
  UniversalProcPtr    newProc6;
};
typedef struct CQDProcs                 CQDProcs;
typedef CQDProcs *                      CQDProcsPtr;
#if !OPAQUE_TOOLBOX_STRUCTS
struct CGrafPort {
  short               device;                 /* not available in Carbon*/
  PixMapHandle        portPixMap;             /* in Carbon use GetPortPixMap*/
  short               portVersion;            /* in Carbon use IsPortColor*/
  Handle              grafVars;               /* not available in Carbon*/
  short               chExtra;                /* in Carbon use GetPortChExtra*/
  short               pnLocHFrac;             /* in Carbon use Get/SetPortFracHPenLocation*/
  Rect                portRect;               /* in Carbon use Get/SetPortBounds*/
  RgnHandle           visRgn;                 /* in Carbon use Get/SetPortVisibleRegion*/
  RgnHandle           clipRgn;                /* in Carbon use Get/SetPortClipRegion*/
  PixPatHandle        bkPixPat;               /* in Carbon use GetPortBackPixPat or BackPixPat*/
  RGBColor            rgbFgColor;             /* in Carbon use GetPortForeColor or RGBForeColor*/
  RGBColor            rgbBkColor;             /* in Carbon use GetPortBackColor or RGBBackColor*/
  Point               pnLoc;                  /* in Carbon use GetPortPenLocation or MoveTo*/
  Point               pnSize;                 /* in Carbon use Get/SetPortPenSize*/
  short               pnMode;                 /* in Carbon use Get/SetPortPenMode*/
  PixPatHandle        pnPixPat;               /* in Carbon use Get/SetPortPenPixPat*/
  PixPatHandle        fillPixPat;             /* in Carbon use GetPortFillPixPat*/
  short               pnVis;                  /* in Carbon use GetPortPenVisibility or Show/HidePen*/
  short               txFont;                 /* in Carbon use GetPortTextFont or TextFont*/
  StyleField          txFace;                 /* in Carbon use GetPortTextFace or TextFace*/
                                              /*StyleField occupies 16-bits, but only first 8-bits are used*/
  short               txMode;                 /* in Carbon use GetPortTextMode or TextMode*/
  short               txSize;                 /* in Carbon use GetPortTextSize or TextSize*/
  Fixed               spExtra;                /* in Carbon use GetPortSpExtra or SpaceExtra*/
  long                fgColor;                /* not available in Carbon*/
  long                bkColor;                /* not available in Carbon*/
  short               colrBit;                /* not available in Carbon*/
  short               patStretch;             /* not available in Carbon*/
  Handle              picSave;                /* in Carbon use IsPortPictureBeingDefined*/
  Handle              rgnSave;                /* in Carbon use IsPortRegionBeingDefined*/
  Handle              polySave;               /* in Carbon use IsPortPolyBeingDefined*/
  CQDProcsPtr         grafProcs;              /* in Carbon use Get/SetPortGrafProcs*/
};

#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

#if OPAQUE_TOOLBOX_STRUCTS
typedef WindowPtr                       CWindowPtr;
#else
typedef CGrafPtr                        CWindowPtr;
#endif  /* OPAQUE_TOOLBOX_STRUCTS */

struct ReqListRec {
  short               reqLSize;               /*request list size*/
  short               reqLData[1];            /*request list data*/
};
typedef struct ReqListRec               ReqListRec;
struct OpenCPicParams {
  Rect                srcRect;
  Fixed               hRes;
  Fixed               vRes;
  short               version;
  short               reserved1;
  long                reserved2;
};
typedef struct OpenCPicParams           OpenCPicParams;
enum {
  kCursorImageMajorVersion      = 0x0001,
  kCursorImageMinorVersion      = 0x0000
};

struct CursorImageRec {
  UInt16              majorVersion;
  UInt16              minorVersion;
  PixMapHandle        cursorPixMap;
  BitMapHandle        cursorBitMask;
};
typedef struct CursorImageRec           CursorImageRec;
typedef CursorImageRec *                CursorImagePtr;
typedef CALLBACK_API( void , DeviceLoopDrawingProcPtr )(short depth, short deviceFlags, GDHandle targetDevice, long userData);
typedef STACK_UPP_TYPE(DeviceLoopDrawingProcPtr)                DeviceLoopDrawingUPP;
/*
 *  NewQDPrinterStatusUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  NewDeviceLoopDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DeviceLoopDrawingUPP
NewDeviceLoopDrawingUPP(DeviceLoopDrawingProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQDPrinterStatusUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeDeviceLoopDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDeviceLoopDrawingUPP(DeviceLoopDrawingUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQDPrinterStatusUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeDeviceLoopDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDeviceLoopDrawingUPP(
  short                 depth,
  short                 deviceFlags,
  GDHandle              targetDevice,
  long                  userData,
  DeviceLoopDrawingUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

#if !OPAQUE_TOOLBOX_STRUCTS || !TARGET_API_MAC_CARBON
struct QDGlobals {
  char                privates[76];
  long                randSeed;               /* in Carbon use GetQDGlobalsRandomSeed*/
  BitMap              screenBits;             /* in Carbon use GetQDGlobalsScreenBits*/
  Cursor              arrow;                  /* in Carbon use GetQDGlobalsArrow*/
  Pattern             dkGray;                 /* in Carbon use GetQDGlobalsDarkGray*/
  Pattern             ltGray;                 /* in Carbon use GetQDGlobalsLightGray*/
  Pattern             gray;                   /* in Carbon use GetQDGlobalsGray*/
  Pattern             black;                  /* in Carbon use GetQDGlobalsBlack*/
  Pattern             white;                  /* in Carbon use GetQDGlobalsWhite*/
  GrafPtr             thePort;                /* in Carbon use GetQDGlobalsThePort*/
};
typedef struct QDGlobals                QDGlobals;
typedef QDGlobals *                     QDGlobalsPtr;
typedef QDGlobalsPtr *                  QDGlobalsHdl;
extern QDGlobals qd;

#endif  /* !OPAQUE_TOOLBOX_STRUCTS || !TARGET_API_MAC_CARBON */


/*
 *  InitGraf()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  OpenPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  InitPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  ClosePort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/*
    General comments about thread-safety of Quickdraw
    -------------------------------------------------
    
    The original design and implementation principles of Quickdraw seriously
    conflict with the goal of making Quickdraw thread-safe. Many Quickdraw
    functions rely on globals instead of explicit parameters. Even though the 
    current port (and the current GDevice) are being maintained per-thread,
    a simple call like "MoveTo(x, y)" just doesn't make sense with preemptive threads,
    if two different threads use the same port. More serious obstacles are hiding
    in picture recording and drawing, or region and polygon recording, or in the
    presence of custom grafProcs bottleneck procedures. Finally, the global QDError
    cannot be maintained per thread, because its pervasive access would cause intolerable
    performance penalties.
    Currently, nearly all Quickdraw API calls are marked thread-unsafe, even those that
    seem to work reliably in pthreads, with some plausible precautions. (Note that
    the absence of crashes in test runs does not guarantee thread-safety!).
    As the work on making portions of Quickdraw thread-safe progresses, the thread-safe
    attributes will be updated. 

*/
/*
   These are Carbon only routines. They do nothing at all on
   Mac OS 9, but work flawlessly on Mac OS X.
*/
/*
 *  LockPortBits()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
LockPortBits(GrafPtr port)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UnlockPortBits()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
UnlockPortBits(GrafPtr port)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Break a region up into rectangles.*/

enum {
  kQDParseRegionFromTop         = (1 << 0),
  kQDParseRegionFromBottom      = (1 << 1),
  kQDParseRegionFromLeft        = (1 << 2),
  kQDParseRegionFromRight       = (1 << 3),
  kQDParseRegionFromTopLeft     = kQDParseRegionFromTop | kQDParseRegionFromLeft,
  kQDParseRegionFromBottomRight = kQDParseRegionFromBottom | kQDParseRegionFromRight
};

typedef SInt32                          QDRegionParseDirection;
enum {
  kQDRegionToRectsMsgInit       = 1,
  kQDRegionToRectsMsgParse      = 2,
  kQDRegionToRectsMsgTerminate  = 3
};

typedef CALLBACK_API_C( OSStatus , RegionToRectsProcPtr )(UInt16 message, RgnHandle rgn, const Rect *rect, void *refCon);
typedef STACK_UPP_TYPE(RegionToRectsProcPtr)                    RegionToRectsUPP;
/*
 *  NewRegionToRectsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern RegionToRectsUPP
NewRegionToRectsUPP(RegionToRectsProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeRegionToRectsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeRegionToRectsUPP(RegionToRectsUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeRegionToRectsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeRegionToRectsUPP(
  UInt16            message,
  RgnHandle         rgn,
  const Rect *      rect,
  void *            refCon,
  RegionToRectsUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  QDRegionToRects()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDRegionToRects(
  RgnHandle                rgn,
  QDRegionParseDirection   dir,
  RegionToRectsUPP         proc,
  void *                   userData)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if TARGET_OS_WIN32
/*
 *  GetPortHWND()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetHWNDPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


#define GetPortHWND(port)  (HWND)GetPortNativeWindow(port)
#define GetHWNDPort(theHWND) GetNativeWindowPort(theHWND)
/*
 *  GetPortHDC()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetPortHBITMAP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetPortHPALETTE()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetPortHFONT()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetDIBFromPICT()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetPICTFromDIB()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


#endif  /* TARGET_OS_WIN32 */

/*
 *  [Mac]SetPort()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacSetPort SetPort
#endif
extern void 
MacSetPort(GrafPtr port)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPort()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetPort(GrafPtr * port)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDSwapPort()
 *  
 *  Summary:
 *    Combines a GetPort(&savePort); SetPort(newPort) sequence.
 *  
 *  Discussion:
 *    On X, the GetPort/SetPort calls act on per-thread globals, and
 *    cost more processor cycles than in the past, where they were
 *    simple memory accessors. To optimize, use the QDSwapPort call
 *    which combines both, and returns a Boolean indicating if the port
 *    actually did change. Typical usage: portChanged =
 *    QDSwapPort(newPort, &savePort); // some drawing into newPort if
 *    (portChanged) QDSwapPort(savePort, NULL);
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inNewPort:
 *      The new port to be set.
 *    
 *    outOldPort:
 *      Receives the previous port. Can be NULL.
 *  
 *  Result:
 *    A Boolean indicating whether the port was changed, i.e.
 *    (inNewPort != *outOldPort)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
QDSwapPort(
  CGrafPtr    inNewPort,
  CGrafPtr *  outOldPort)                                     AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  GrafDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GrafDevice(short device)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortBits()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPortBits(const BitMap * bm)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PortSize()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PortSize(
  short   width,
  short   height)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MovePortTo()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MovePortTo(
  short   leftGlobal,
  short   topGlobal)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetOrigin()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetOrigin(
  short   h,
  short   v)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetClip()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetClip(RgnHandle rgn)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetClip()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetClip(RgnHandle rgn)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ClipRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ClipRect(const Rect * r)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BackPat()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
BackPat(const Pattern * pat)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InitCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InitCursor(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]SetCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacSetCursor SetCursor
#endif
extern void 
MacSetCursor(const Cursor * crsr)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HideCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HideCursor(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]ShowCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacShowCursor ShowCursor
#endif
extern void 
MacShowCursor(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ObscureCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ObscureCursor(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HidePen()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HidePen(void)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ShowPen()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ShowPen(void)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPen()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetPen(Point * pt)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPenState()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetPenState(PenState * pnState)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPenState()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPenState(const PenState * pnState)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PenSize()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PenSize(
  short   width,
  short   height)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PenMode()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PenMode(short mode)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PenPat()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PenPat(const Pattern * pat)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PenNormal()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PenNormal(void)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MoveTo()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MoveTo(
  short   h,
  short   v)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Move()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Move(
  short   dh,
  short   dv)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]LineTo()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacLineTo LineTo
#endif
extern void 
MacLineTo(
  short   h,
  short   v)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Line()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Line(
  short   dh,
  short   dv)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ForeColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ForeColor(long color)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BackColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
BackColor(long color)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ColorBit()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ColorBit(short whichBit)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]SetRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacSetRect SetRect
#endif
extern void 
MacSetRect(
  Rect *  r,
  short   left,
  short   top,
  short   right,
  short   bottom)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]OffsetRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacOffsetRect OffsetRect
#endif
extern void 
MacOffsetRect(
  Rect *  r,
  short   dh,
  short   dv)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]InsetRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacInsetRect InsetRect
#endif
extern void 
MacInsetRect(
  Rect *  r,
  short   dh,
  short   dv)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SectRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
SectRect(
  const Rect *  src1,
  const Rect *  src2,
  Rect *        dstRect)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]UnionRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacUnionRect UnionRect
#endif
extern void 
MacUnionRect(
  const Rect *  src1,
  const Rect *  src2,
  Rect *        dstRect)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]EqualRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacEqualRect EqualRect
#endif
extern Boolean 
MacEqualRect(
  const Rect *  rect1,
  const Rect *  rect2)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EmptyRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
EmptyRect(const Rect * r)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]FrameRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacFrameRect FrameRect
#endif
extern void 
MacFrameRect(const Rect * r)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PaintRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PaintRect(const Rect * r)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EraseRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EraseRect(const Rect * r)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]InvertRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacInvertRect InvertRect
#endif
extern void 
MacInvertRect(const Rect * r)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]FillRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacFillRect FillRect
#endif
extern void 
MacFillRect(
  const Rect *     r,
  const Pattern *  pat)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FrameOval()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FrameOval(const Rect * r)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PaintOval()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PaintOval(const Rect * r)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EraseOval()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EraseOval(const Rect * r)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InvertOval()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InvertOval(const Rect * r)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FillOval()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillOval(
  const Rect *     r,
  const Pattern *  pat)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FrameRoundRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FrameRoundRect(
  const Rect *  r,
  short         ovalWidth,
  short         ovalHeight)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PaintRoundRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PaintRoundRect(
  const Rect *  r,
  short         ovalWidth,
  short         ovalHeight)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EraseRoundRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EraseRoundRect(
  const Rect *  r,
  short         ovalWidth,
  short         ovalHeight)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InvertRoundRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InvertRoundRect(
  const Rect *  r,
  short         ovalWidth,
  short         ovalHeight)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FillRoundRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillRoundRect(
  const Rect *     r,
  short            ovalWidth,
  short            ovalHeight,
  const Pattern *  pat)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FrameArc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FrameArc(
  const Rect *  r,
  short         startAngle,
  short         arcAngle)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PaintArc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PaintArc(
  const Rect *  r,
  short         startAngle,
  short         arcAngle)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EraseArc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EraseArc(
  const Rect *  r,
  short         startAngle,
  short         arcAngle)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InvertArc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InvertArc(
  const Rect *  r,
  short         startAngle,
  short         arcAngle)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FillArc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillArc(
  const Rect *     r,
  short            startAngle,
  short            arcAngle,
  const Pattern *  pat)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern RgnHandle 
NewRgn(void)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
OpenRgn(void)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CloseRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CloseRgn(RgnHandle dstRgn)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BitMapToRegion()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
BitMapToRegion(
  RgnHandle       region,
  const BitMap *  bMap)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HandleToRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
HandleToRgn(
  Handle      oldRegion,
  RgnHandle   region)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RgnToHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
RgnToHandle(
  RgnHandle   region,
  Handle      flattenedRgnDataHdl)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  DisposeRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeRgn(RgnHandle rgn)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]CopyRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacCopyRgn CopyRgn
#endif
extern void 
MacCopyRgn(
  RgnHandle   srcRgn,
  RgnHandle   dstRgn)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetEmptyRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetEmptyRgn(RgnHandle rgn)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]SetRectRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacSetRectRgn SetRectRgn
#endif
extern void 
MacSetRectRgn(
  RgnHandle   rgn,
  short       left,
  short       top,
  short       right,
  short       bottom)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RectRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RectRgn(
  RgnHandle     rgn,
  const Rect *  r)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]OffsetRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacOffsetRgn OffsetRgn
#endif
extern void 
MacOffsetRgn(
  RgnHandle   rgn,
  short       dh,
  short       dv)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InsetRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InsetRgn(
  RgnHandle   rgn,
  short       dh,
  short       dv)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SectRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SectRgn(
  RgnHandle   srcRgnA,
  RgnHandle   srcRgnB,
  RgnHandle   dstRgn)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]UnionRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacUnionRgn UnionRgn
#endif
extern void 
MacUnionRgn(
  RgnHandle   srcRgnA,
  RgnHandle   srcRgnB,
  RgnHandle   dstRgn)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DiffRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DiffRgn(
  RgnHandle   srcRgnA,
  RgnHandle   srcRgnB,
  RgnHandle   dstRgn)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]XorRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacXorRgn XorRgn
#endif
extern void 
MacXorRgn(
  RgnHandle   srcRgnA,
  RgnHandle   srcRgnB,
  RgnHandle   dstRgn)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RectInRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
RectInRgn(
  const Rect *  r,
  RgnHandle     rgn)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]EqualRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacEqualRgn EqualRgn
#endif
extern Boolean 
MacEqualRgn(
  RgnHandle   rgnA,
  RgnHandle   rgnB)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EmptyRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
EmptyRgn(RgnHandle rgn)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]FrameRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacFrameRgn FrameRgn
#endif
extern void 
MacFrameRgn(RgnHandle rgn)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]PaintRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacPaintRgn PaintRgn
#endif
extern void 
MacPaintRgn(RgnHandle rgn)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EraseRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EraseRgn(RgnHandle rgn)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]InvertRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacInvertRgn InvertRgn
#endif
extern void 
MacInvertRgn(RgnHandle rgn)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]FillRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacFillRgn FillRgn
#endif
extern void 
MacFillRgn(
  RgnHandle        rgn,
  const Pattern *  pat)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ScrollRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ScrollRect(
  const Rect *  r,
  short         dh,
  short         dv,
  RgnHandle     updateRgn)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CopyBits()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CopyBits(
  const BitMap *  srcBits,
  const BitMap *  dstBits,
  const Rect *    srcRect,
  const Rect *    dstRect,
  short           mode,
  RgnHandle       maskRgn)       /* can be NULL */            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SeedFill()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SeedFill(
  const void *  srcPtr,
  void *        dstPtr,
  short         srcRow,
  short         dstRow,
  short         height,
  short         words,
  short         seedH,
  short         seedV)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CalcMask()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CalcMask(
  const void *  srcPtr,
  void *        dstPtr,
  short         srcRow,
  short         dstRow,
  short         height,
  short         words)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CopyMask()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CopyMask(
  const BitMap *  srcBits,
  const BitMap *  maskBits,
  const BitMap *  dstBits,
  const Rect *    srcRect,
  const Rect *    maskRect,
  const Rect *    dstRect)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenPicture()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PicHandle 
OpenPicture(const Rect * picFrame)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PicComment()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PicComment(
  short    kind,
  short    dataSize,
  Handle   dataHandle)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ClosePicture()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ClosePicture(void)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDGetPictureBounds()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Rect * 
QDGetPictureBounds(
  PicHandle   picH,
  Rect *      outRect)                                        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  DrawPicture()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DrawPicture(
  PicHandle     myPicture,
  const Rect *  dstRect)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KillPicture()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
KillPicture(PicHandle myPicture)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenPoly()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PolyHandle 
OpenPoly(void)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ClosePoly()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ClosePoly(void)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KillPoly()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
KillPoly(PolyHandle poly)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OffsetPoly()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
OffsetPoly(
  PolyHandle   poly,
  short        dh,
  short        dv)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FramePoly()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FramePoly(PolyHandle poly)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PaintPoly()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PaintPoly(PolyHandle poly)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ErasePoly()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ErasePoly(PolyHandle poly)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InvertPoly()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InvertPoly(PolyHandle poly)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FillPoly()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillPoly(
  PolyHandle       poly,
  const Pattern *  pat)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPt()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPt(
  Point *  pt,
  short    h,
  short    v)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LocalToGlobal()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LocalToGlobal(Point * pt)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GlobalToLocal()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GlobalToLocal(Point * pt)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Random()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
Random(void)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StuffHex()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StuffHex(
  void *             thingPtr,
  ConstStr255Param   s)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]GetPixel()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacGetPixel GetPixel
#endif
extern Boolean 
MacGetPixel(
  short   h,
  short   v)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ScalePt()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ScalePt(
  Point *       pt,
  const Rect *  srcRect,
  const Rect *  dstRect)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MapPt()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MapPt(
  Point *       pt,
  const Rect *  srcRect,
  const Rect *  dstRect)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MapRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MapRect(
  Rect *        r,
  const Rect *  srcRect,
  const Rect *  dstRect)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MapRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MapRgn(
  RgnHandle     rgn,
  const Rect *  srcRect,
  const Rect *  dstRect)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MapPoly()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MapPoly(
  PolyHandle    poly,
  const Rect *  srcRect,
  const Rect *  dstRect)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetStdProcs()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetStdProcs(QDProcs * procs)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdRect(
  GrafVerb      verb,
  const Rect *  r)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdRRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdRRect(
  GrafVerb      verb,
  const Rect *  r,
  short         ovalWidth,
  short         ovalHeight)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdOval()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdOval(
  GrafVerb      verb,
  const Rect *  r)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdArc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdArc(
  GrafVerb      verb,
  const Rect *  r,
  short         startAngle,
  short         arcAngle)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdPoly()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdPoly(
  GrafVerb     verb,
  PolyHandle   poly)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdRgn(
  GrafVerb    verb,
  RgnHandle   rgn)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdBits()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdBits(
  const BitMap *  srcBits,
  const Rect *    srcRect,
  const Rect *    dstRect,
  short           mode,
  RgnHandle       maskRgn)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdComment()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdComment(
  short    kind,
  short    dataSize,
  Handle   dataHandle)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdGetPic()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdGetPic(
  void *  dataPtr,
  short   byteCount)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdPutPic()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdPutPic(
  const void *  dataPtr,
  short         byteCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdOpcode()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
StdOpcode(
  const Rect *  fromRect,
  const Rect *  toRect,
  UInt16        opcode,
  SInt16        version)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddPt()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AddPt(
  Point    src,
  Point *  dst)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EqualPt()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
EqualPt(
  Point   pt1,
  Point   pt2)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]PtInRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacPtInRect PtInRect
#endif
extern Boolean 
MacPtInRect(
  Point         pt,
  const Rect *  r)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Pt2Rect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Pt2Rect(
  Point   pt1,
  Point   pt2,
  Rect *  dstRect)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PtToAngle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PtToAngle(
  const Rect *  r,
  Point         pt,
  short *       angle)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SubPt()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SubPt(
  Point    src,
  Point *  dst)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PtInRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
PtInRgn(
  Point       pt,
  RgnHandle   rgn)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdLine()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdLine(Point newPt)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenCPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  InitCPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  CloseCPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  NewPixMap()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PixMapHandle 
NewPixMap(void)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposePixMap()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposePixMap(PixMapHandle pm)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CopyPixMap()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CopyPixMap(
  PixMapHandle   srcPM,
  PixMapHandle   dstPM)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewPixPat()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PixPatHandle 
NewPixPat(void)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposePixPat()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposePixPat(PixPatHandle pp)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CopyPixPat()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CopyPixPat(
  PixPatHandle   srcPP,
  PixPatHandle   dstPP)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PenPixPat()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PenPixPat(PixPatHandle pp)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  BackPixPat()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
BackPixPat(PixPatHandle pp)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPixPat()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PixPatHandle 
GetPixPat(short patID)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MakeRGBPat()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MakeRGBPat(
  PixPatHandle      pp,
  const RGBColor *  myColor)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FillCRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillCRect(
  const Rect *   r,
  PixPatHandle   pp)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FillCOval()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillCOval(
  const Rect *   r,
  PixPatHandle   pp)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FillCRoundRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillCRoundRect(
  const Rect *   r,
  short          ovalWidth,
  short          ovalHeight,
  PixPatHandle   pp)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FillCArc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillCArc(
  const Rect *   r,
  short          startAngle,
  short          arcAngle,
  PixPatHandle   pp)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FillCRgn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillCRgn(
  RgnHandle      rgn,
  PixPatHandle   pp)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FillCPoly()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillCPoly(
  PolyHandle     poly,
  PixPatHandle   pp)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RGBForeColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RGBForeColor(const RGBColor * color)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RGBBackColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RGBBackColor(const RGBColor * color)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetCPixel()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetCPixel(
  short             h,
  short             v,
  const RGBColor *  cPix)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortPix()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPortPix(PixMapHandle pm)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetCPixel()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetCPixel(
  short       h,
  short       v,
  RGBColor *  cPix)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetForeColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetForeColor(RGBColor * color)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetBackColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetBackColor(RGBColor * color)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SeedCFill()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SeedCFill(
  const BitMap *   srcBits,
  const BitMap *   dstBits,
  const Rect *     srcRect,
  const Rect *     dstRect,
  short            seedH,
  short            seedV,
  ColorSearchUPP   matchProc,
  long             matchData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CalcCMask()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CalcCMask(
  const BitMap *    srcBits,
  const BitMap *    dstBits,
  const Rect *      srcRect,
  const Rect *      dstRect,
  const RGBColor *  seedRGB,
  ColorSearchUPP    matchProc,
  long              matchData)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenCPicture()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PicHandle 
OpenCPicture(const OpenCPicParams * newHeader)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
OpColor(const RGBColor * color)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HiliteColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HiliteColor(const RGBColor * color)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeCTable()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeCTable(CTabHandle cTable)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetCTable()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern CTabHandle 
GetCTable(short ctID)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetCCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern CCrsrHandle 
GetCCursor(short crsrID)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetCCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetCCursor(CCrsrHandle cCrsr)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AllocCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AllocCursor(void)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeCCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeCCursor(CCrsrHandle cCrsr)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* GetCIcon(), PlotCIcon(), and DisposeCIcon() moved to Icons.h*/

/*
 *  SetStdCProcs()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetStdCProcs(CQDProcs * procs)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMaxDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
GetMaxDevice(const Rect * globalRect)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetCTSeed()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
GetCTSeed(void)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDeviceList()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
GetDeviceList(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMainDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
GetMainDevice(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetNextDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
GetNextDevice(GDHandle curDevice)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TestDeviceAttribute()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
TestDeviceAttribute(
  GDHandle   gdh,
  short      attribute)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDeviceAttribute()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetDeviceAttribute(
  GDHandle   gdh,
  short      attribute,
  Boolean    value)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InitGDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InitGDevice(
  short      qdRefNum,
  long       mode,
  GDHandle   gdh)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewGDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
NewGDevice(
  short   refNum,
  long    mode)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeGDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeGDevice(GDHandle gdh)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetGDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetGDevice(GDHandle gd)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetGDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
GetGDevice(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Color2Index()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
Color2Index(const RGBColor * myColor)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Index2Color()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Index2Color(
  long        index,
  RGBColor *  aColor)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InvertColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InvertColor(RGBColor * myColor)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RealColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
RealColor(const RGBColor * color)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetSubTable()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetSubTable(
  CTabHandle   myColors,
  short        iTabRes,
  CTabHandle   targetTbl)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MakeITable()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MakeITable(
  CTabHandle   cTabH,
  ITabHandle   iTabH,
  short        res)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddSearch()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AddSearch(ColorSearchUPP searchProc)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddComp()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AddComp(ColorComplementUPP compProc)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DelSearch()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DelSearch(ColorSearchUPP searchProc)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DelComp()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DelComp(ColorComplementUPP compProc)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetClientID()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetClientID(short id)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ProtectEntry()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ProtectEntry(
  short     index,
  Boolean   protect)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ReserveEntry()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ReserveEntry(
  short     index,
  Boolean   reserve)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetEntries()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetEntries(
  short        start,
  short        count,
  CSpecArray   aTable)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SaveEntries()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SaveEntries(
  CTabHandle    srcTable,
  CTabHandle    resultTable,
  ReqListRec *  selection)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RestoreEntries()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RestoreEntries(
  CTabHandle    srcTable,
  CTabHandle    dstTable,
  ReqListRec *  selection)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDError()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
QDError(void)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CopyDeepMask()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CopyDeepMask(
  const BitMap *  srcBits,
  const BitMap *  maskBits,
  const BitMap *  dstBits,
  const Rect *    srcRect,
  const Rect *    maskRect,
  const Rect *    dstRect,
  short           mode,
  RgnHandle       maskRgn)        /* can be NULL */           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DeviceLoop()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DeviceLoop(
  RgnHandle              drawingRgn,
  DeviceLoopDrawingUPP   drawingProc,
  long                   userData,
  DeviceLoopFlags        flags)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  GetMaskTable()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr 
GetMaskTable(void)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  GetPattern()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PatHandle 
GetPattern(short patternID)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]GetCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacGetCursor GetCursor
#endif
extern CursHandle 
MacGetCursor(short cursorID)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPicture()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PicHandle 
GetPicture(short pictureID)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DeltaPoint()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
DeltaPoint(
  Point   ptA,
  Point   ptB)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ShieldCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ShieldCursor(
  const Rect *  shieldRect,
  Point         offsetPt)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ScreenRes()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ScreenRes(
  short *  scrnHRes,
  short *  scrnVRes)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetIndPattern()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetIndPattern(
  Pattern *  thePat,
  short      patternListID,
  short      index)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ptinrect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  pt2rect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  pttoangle()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  ptinrgn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  addpt()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  subpt()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  equalpt()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  stuffhex()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  stdline()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  shieldcursor()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  deltapoint()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
deltapoint(
  Point *  ptA,
  Point *  ptB)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if OLDROUTINENAMES
#define DisposPixMap(pm) DisposePixMap(pm)
#define DisposPixPat(pp) DisposePixPat(pp)
#define DisposCTable(cTable) DisposeCTable(cTable)
#define DisposCCursor(cCrsr) DisposeCCursor(cCrsr)
#define DisposGDevice(gdh) DisposeGDevice(gdh)
#endif  /* OLDROUTINENAMES */

/*
    From ToolUtils.i
*/
/*
 *  PackBits()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PackBits(
  Ptr *   srcPtr,
  Ptr *   dstPtr,
  short   srcBytes)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UnpackBits()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
UnpackBits(
  Ptr *   srcPtr,
  Ptr *   dstPtr,
  short   dstBytes)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SlopeFromAngle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fixed 
SlopeFromAngle(short angle)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AngleFromSlope()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
AngleFromSlope(Fixed slope)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* New transfer modes */
enum {
  colorXorXFer                  = 52,
  noiseXFer                     = 53,
  customXFer                    = 54
};

/* Custom XFer flags */
enum {
  kXFer1PixelAtATime            = 0x00000001, /* 1 pixel passed to custom XFer proc*/
  kXFerConvertPixelToRGB32      = 0x00000002 /* All color depths converted to 32 bit RGB*/
};

struct CustomXFerRec {
  UInt32              version;
  void *              srcPixels;
  void *              destPixels;
  void *              resultPixels;
  UInt32              refCon;
  UInt32              pixelSize;
  UInt32              pixelCount;
  Point               firstPixelHV;
  Rect                destBounds;
};
typedef struct CustomXFerRec            CustomXFerRec;
typedef CustomXFerRec *                 CustomXFerRecPtr;
typedef CALLBACK_API( void , CustomXFerProcPtr )(CustomXFerRecPtr info);
/*
 *  GetPortCustomXFerProc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
GetPortCustomXFerProc(
  CGrafPtr             port,
  CustomXFerProcPtr *  proc,
  UInt32 *             flags,
  UInt32 *             refCon)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortCustomXFerProc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
SetPortCustomXFerProc(
  CGrafPtr            port,
  CustomXFerProcPtr   proc,
  UInt32              flags,
  UInt32              refCon)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



enum {
  kCursorComponentsVersion      = 0x00010001
};

enum {
  kCursorComponentType          = 'curs'
};

/* Cursor Component capabilities flags */
enum {
  cursorDoesAnimate             = 1L << 0,
  cursorDoesHardware            = 1L << 1,
  cursorDoesUnreadableScreenBits = 1L << 2
};

/* Cursor Component output mode flags */
enum {
  kRenderCursorInHardware       = 1L << 0,
  kRenderCursorInSoftware       = 1L << 1
};

/* Cursor Component Info */
struct CursorInfo {
  long                version;                /* use kCursorComponentsVersion */
  long                capabilities;
  long                animateDuration;        /* approximate time between animate tickles */
  Rect                bounds;
  Point               hotspot;
  long                reserved;               /* must set to zero */

};
typedef struct CursorInfo               CursorInfo;
/* Cursor Component Selectors */
enum {
  kCursorComponentInit          = 0x0001,
  kCursorComponentGetInfo       = 0x0002,
  kCursorComponentSetOutputMode = 0x0003,
  kCursorComponentSetData       = 0x0004,
  kCursorComponentReconfigure   = 0x0005,
  kCursorComponentDraw          = 0x0006,
  kCursorComponentErase         = 0x0007,
  kCursorComponentMove          = 0x0008,
  kCursorComponentAnimate       = 0x0009,
  kCursorComponentLastReserved  = 0x0050
};

/*
 *  OpenCursorComponent()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
OpenCursorComponent(
  Component            c,
  ComponentInstance *  ci)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CloseCursorComponent()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
CloseCursorComponent(ComponentInstance ci)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetCursorComponent()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
SetCursorComponent(ComponentInstance ci)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CursorComponentChanged()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
CursorComponentChanged(ComponentInstance ci)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CursorComponentSetData()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
CursorComponentSetData(
  ComponentInstance   ci,
  long                data)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Quickdraw-specific ColorSync matching */
/*
 *  CWMatchPixMap()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CWMatchPixMap(
  CMWorldRef            cw,
  PixMap *              myPixMap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CWCheckPixMap()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CWCheckPixMap(
  CMWorldRef            cw,
  PixMap *              myPixMap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  BitMap *              resultBitMap)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NCMBeginMatching()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
NCMBeginMatching(
  CMProfileRef   src,
  CMProfileRef   dst,
  CMMatchRef *   myRef)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMEndMatching()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
CMEndMatching(CMMatchRef myRef)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NCMDrawMatchedPicture()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
NCMDrawMatchedPicture(
  PicHandle      myPicture,
  CMProfileRef   dst,
  Rect *         myRect)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMEnableMatchingComment()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
CMEnableMatchingComment(Boolean enableIt)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NCMUseProfileComment()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
NCMUseProfileComment(
  CMProfileRef   prof,
  UInt32         flags)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Available in CarbonLib... */
/*
 *  IsValidPort()
 *  
 *  Summary:
 *    Attempts to detect invalid ports
 *  
 *  Discussion:
 *    A grafPort structure contains many nested Handles. An attempt to
 *    guarantee that they are all valid is prohibitively costly. Since
 *    10.1, IsValidPort only compares the CGrafPtr parameter against
 *    the list of grafPorts maintained internally by Quickdraw. The
 *    function returns true if it is found, false otherwise. This is
 *    enough to detect ports belonging to windows that have been
 *    closed, or GWorlds that have been deallocated.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    port:
 *      The CGrafPtr in question.
 *  
 *  Result:
 *    If false, port is definitely invalid. If true, port is probably
 *    valid (unless memory has been clobbered)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsValidPort(CGrafPtr port)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* GrafPort */
/* Getters */
/*
 *  GetPortPixMap()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern PixMapHandle 
GetPortPixMap(CGrafPtr port)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortBitMapForCopyBits()
 *  
 *  Discussion:
 *    GetPortBitMapForCopyBits is provided for the specific purpose of
 *    using the return value as a parameter to CopyBits. The return
 *    value can be used as the srcBits or dstBits parameter to CopyBits
 *    regardless of whether the port is color. If the port parameter is
 *    a color port, however, the returned BitMapPtr does not actually
 *    point to a BitMap; it points to the PixMapHandle and other fields
 *    in the CGrafPort structure. You should not dereference the
 *    BitMapPtr or otherwise depend on its contents unless you've
 *    confirmed that this port is a non-color port.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0.2 and later
 */
extern const BitMap * 
GetPortBitMapForCopyBits(CGrafPtr port)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortBounds()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Rect * 
GetPortBounds(
  CGrafPtr   port,
  Rect *     rect)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortForeColor()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern RGBColor * 
GetPortForeColor(
  CGrafPtr    port,
  RGBColor *  foreColor)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortBackColor()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern RGBColor * 
GetPortBackColor(
  CGrafPtr    port,
  RGBColor *  backColor)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortOpColor()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern RGBColor * 
GetPortOpColor(
  CGrafPtr    port,
  RGBColor *  opColor)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortHiliteColor()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern RGBColor * 
GetPortHiliteColor(
  CGrafPtr    port,
  RGBColor *  hiliteColor)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortGrafProcs()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern CQDProcsPtr 
GetPortGrafProcs(CGrafPtr port)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortTextFont()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPortTextFont(CGrafPtr port)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortTextFace()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Style 
GetPortTextFace(CGrafPtr port)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortTextMode()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPortTextMode(CGrafPtr port)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortTextSize()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPortTextSize(CGrafPtr port)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortChExtra()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPortChExtra(CGrafPtr port)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortFracHPenLocation()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPortFracHPenLocation(CGrafPtr port)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortSpExtra()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Fixed 
GetPortSpExtra(CGrafPtr port)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortPenVisibility()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPortPenVisibility(CGrafPtr port)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortVisibleRegion()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern RgnHandle 
GetPortVisibleRegion(
  CGrafPtr    port,
  RgnHandle   visRgn)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortClipRegion()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern RgnHandle 
GetPortClipRegion(
  CGrafPtr    port,
  RgnHandle   clipRgn)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortBackPixPat()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern PixPatHandle 
GetPortBackPixPat(
  CGrafPtr       port,
  PixPatHandle   backPattern)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortPenPixPat()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern PixPatHandle 
GetPortPenPixPat(
  CGrafPtr       port,
  PixPatHandle   penPattern)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortFillPixPat()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern PixPatHandle 
GetPortFillPixPat(
  CGrafPtr       port,
  PixPatHandle   fillPattern)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortPenSize()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Point * 
GetPortPenSize(
  CGrafPtr   port,
  Point *    penSize)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortPenMode()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern SInt32 
GetPortPenMode(CGrafPtr port)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPortPenLocation()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Point * 
GetPortPenLocation(
  CGrafPtr   port,
  Point *    penLocation)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IsPortRegionBeingDefined()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Boolean 
IsPortRegionBeingDefined(CGrafPtr port)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IsPortPictureBeingDefined()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Boolean 
IsPortPictureBeingDefined(CGrafPtr port)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IsPortPolyBeingDefined()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.3 and later
 */
extern Boolean 
IsPortPolyBeingDefined(CGrafPtr port)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IsPortOffscreen()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Boolean 
IsPortOffscreen(CGrafPtr port)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IsPortColor()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0.2 and later
 */
extern Boolean 
IsPortColor(CGrafPtr port)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IsPortVisibleRegionEmpty()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.1
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsPortVisibleRegionEmpty(CGrafPtr port)                       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  IsPortClipRegionEmpty()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.1
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsPortClipRegionEmpty(CGrafPtr port)                          AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  SectRegionWithPortClipRegion()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
SectRegionWithPortClipRegion(
  CGrafPtr    port,
  RgnHandle   ioRegion)                                       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  SectRegionWithPortVisibleRegion()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
SectRegionWithPortVisibleRegion(
  CGrafPtr    port,
  RgnHandle   ioRegion)                                       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/* Swappers */
/*
 *  SwapPortPicSaveHandle()
 *  
 *  Summary:
 *    Sets the port's picSave Handle, and returns the previous picSave
 *  
 *  Discussion:
 *    Historically, the picSave field in a GrafPort is != NULL if a
 *    Picture is being defined; and it has been documented that picture
 *    definition can be temporarily suspended by saving the current
 *    picSave Handle and setting picSave to NULL. Restoring the saved
 *    picSave Handle resumes picture definition.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    port:
 *      The port whose picSave field is being swapped.
 *    
 *    inPicSaveHdl:
 *      The picSave Handle to be set.
 *  
 *  Result:
 *    The previous picSave Handle in the port.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern Handle 
SwapPortPicSaveHandle(
  CGrafPtr   port,
  Handle     inPicSaveHdl)                                    AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* Similarly: */
/*
 *  SwapPortPolySaveHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern Handle 
SwapPortPolySaveHandle(
  CGrafPtr   port,
  Handle     inPolySaveHdl)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SwapPortRegionSaveHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern Handle 
SwapPortRegionSaveHandle(
  CGrafPtr   port,
  Handle     inRegionSaveHdl)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/* Setters */
/*
 *  SetPortBounds()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortBounds(
  CGrafPtr      port,
  const Rect *  rect)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortOpColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortOpColor(
  CGrafPtr          port,
  const RGBColor *  opColor)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortGrafProcs()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortGrafProcs(
  CGrafPtr      port,
  CQDProcsPtr   procs)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortTextFont()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
SetPortTextFont(
  CGrafPtr   port,
  short      txFont)                                          AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  SetPortTextSize()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
SetPortTextSize(
  CGrafPtr   port,
  short      txSize)                                          AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  SetPortTextFace()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
SetPortTextFace(
  CGrafPtr         port,
  StyleParameter   face)                                      AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  SetPortTextMode()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
SetPortTextMode(
  CGrafPtr   port,
  short      mode)                                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  SetPortVisibleRegion()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortVisibleRegion(
  CGrafPtr    port,
  RgnHandle   visRgn)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortClipRegion()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortClipRegion(
  CGrafPtr    port,
  RgnHandle   clipRgn)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortPenPixPat()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortPenPixPat(
  CGrafPtr       port,
  PixPatHandle   penPattern)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortFillPixPat()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.2 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.2 and later
 */
extern void 
SetPortFillPixPat(
  CGrafPtr       port,
  PixPatHandle   penPattern)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortBackPixPat()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortBackPixPat(
  CGrafPtr       port,
  PixPatHandle   backPattern)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortPenSize()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortPenSize(
  CGrafPtr   port,
  Point      penSize)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortPenMode()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortPenMode(
  CGrafPtr   port,
  SInt32     penMode)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPortFracHPenLocation()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortFracHPenLocation(
  CGrafPtr   port,
  short      pnLocHFrac)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* PixMap */
/*
 *  GetPixBounds()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Rect * 
GetPixBounds(
  PixMapHandle   pixMap,
  Rect *         bounds)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPixDepth()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPixDepth(PixMapHandle pixMap)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* QDGlobals */
/* Getters */
/*
 *  GetQDGlobalsRandomSeed()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern long 
GetQDGlobalsRandomSeed(void)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetQDGlobalsScreenBits()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern BitMap * 
GetQDGlobalsScreenBits(BitMap * screenBits)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetQDGlobalsArrow()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Cursor * 
GetQDGlobalsArrow(Cursor * arrow)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetQDGlobalsDarkGray()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Pattern * 
GetQDGlobalsDarkGray(Pattern * dkGray)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetQDGlobalsLightGray()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Pattern * 
GetQDGlobalsLightGray(Pattern * ltGray)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetQDGlobalsGray()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Pattern * 
GetQDGlobalsGray(Pattern * gray)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetQDGlobalsBlack()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Pattern * 
GetQDGlobalsBlack(Pattern * black)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetQDGlobalsWhite()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Pattern * 
GetQDGlobalsWhite(Pattern * white)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetQDGlobalsThePort()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern CGrafPtr 
GetQDGlobalsThePort(void)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Setters */
/*
 *  SetQDGlobalsRandomSeed()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetQDGlobalsRandomSeed(long randomSeed)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetQDGlobalsArrow()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetQDGlobalsArrow(const Cursor * arrow)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Regions */
/*
 *  GetRegionBounds()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Rect * 
GetRegionBounds(
  RgnHandle   region,
  Rect *      bounds)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IsRegionRectangular()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Boolean 
IsRegionRectangular(RgnHandle region)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Utilities */
/* To prevent upward dependencies, GetWindowFromPort() is defined in Window Manager interface: */
/*      pascal WindowRef        GetWindowFromPort(CGrafPtr port); */
/* NewPtr/OpenCPort doesn't work with opaque structures */
/*
 *  CreateNewPort()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern CGrafPtr 
CreateNewPort(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposePort()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
DisposePort(CGrafPtr port)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  SetQDError()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0.2 and later
 */
extern void 
SetQDError(OSErr err)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Helpful Carbon-only utilities (finally made public)*/

/*
 *  QDLocalToGlobalPoint()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Point * 
QDLocalToGlobalPoint(
  CGrafPtr   port,
  Point *    point)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDGlobalToLocalPoint()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Point * 
QDGlobalToLocalPoint(
  CGrafPtr   port,
  Point *    point)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDLocalToGlobalRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Rect * 
QDLocalToGlobalRect(
  CGrafPtr   port,
  Rect *     bounds)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDGlobalToLocalRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Rect * 
QDGlobalToLocalRect(
  CGrafPtr   port,
  Rect *     bounds)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDLocalToGlobalRegion()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern RgnHandle 
QDLocalToGlobalRegion(
  CGrafPtr    port,
  RgnHandle   region)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDGlobalToLocalRegion()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern RgnHandle 
QDGlobalToLocalRegion(
  CGrafPtr    port,
  RgnHandle   region)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
   Routines available on Mac OS X to flush buffered window ports...
   These calls do nothing on Mac OS 8/9. QDIsPortBuffered will always return false there.
*/

/*
 *  QDIsPortBuffered()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
QDIsPortBuffered(CGrafPtr port)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDIsPortBufferDirty()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
QDIsPortBufferDirty(CGrafPtr port)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDFlushPortBuffer()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
QDFlushPortBuffer(
  CGrafPtr    port,
  RgnHandle   region)       /* can be NULL */                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDGetDirtyRegion()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDGetDirtyRegion(
  CGrafPtr    port,
  RgnHandle   rgn)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDSetDirtyRegion()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDSetDirtyRegion(
  CGrafPtr    port,
  RgnHandle   rgn)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDAddRectToDirtyRegion()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDAddRectToDirtyRegion(
  CGrafPtr      inPort,
  const Rect *  inBounds)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDAddRegionToDirtyRegion()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDAddRegionToDirtyRegion(
  CGrafPtr    inPort,
  RgnHandle   inRegion)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  CreateCGContextForPort()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateCGContextForPort(
  CGrafPtr        inPort,
  CGContextRef *  outContext)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ClipCGContextToRegion()
 *  
 *  Summary:
 *    Set a CGContext's clip path to the equivalent of a RgnHandle
 *  
 *  Discussion:
 *    The usage model of the clipPath in a CGContext is fundamentally
 *    different from the usage of a clipRgn in a GrafPort (cf.
 *    CoreGraphics documentation). When Quickdraw and CoreGraphics
 *    drawing are being mixed, it is often necessary to convert a QD
 *    clipRgn to a clipPath in CG. In order to produce the expected
 *    outcome in ClipCGContextToRegion, this function needs to reset
 *    any CGContext clipPath, before setting it to the converted
 *    region. Consequently, the previous clipPath in the CGContext is
 *    lost, and cannot be restored in a
 *    CGContextSaveGState/CGContextRestoreGState bracket around the
 *    ClipCGContextToRegion call.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    gc:
 *      The CGContext
 *    
 *    portRect:
 *      A bounding box for the region (needed by conversion to
 *      clipPath). Can be the GrafPort bounds, or the region bounds
 *    
 *    region:
 *      The RgnHandle (usually a clipRgn) to be converted to the
 *      CGContextClip.
 *  
 *  Result:
 *    OSStatus noErr, or a memory error is some internal allocation
 *    failed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ClipCGContextToRegion(
  CGContextRef   gc,
  const Rect *   portRect,
  RgnHandle      region)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SyncCGContextOriginWithPort()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SyncCGContextOriginWithPort(
  CGContextRef   inContext,
  CGrafPtr       port)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDBeginCGContext()
 *  
 *  Summary:
 *    Allow CoreGraphics drawing in a CGrafPort
 *  
 *  Discussion:
 *    So far, CreateCGContextForPort() was used to create a CGContext
 *    for CG drawing from a CGrafPort. However, if the current port is
 *    a printing port, the CreateCGContextForPort fails; consequently,
 *    there was no way to mix Quickdraw and CoreGraphics drawing and
 *    still print it. If, instead, the CoreGraphics drawing is
 *    bracketed by QDBeginCGContext/QDEndCGContext calls, the drawing
 *    will also appear in print. There are some restrictions on the
 *    usage of QDBeginCGContext/QDEndCGContext:
 *    - Between QDBeginCGContext and QDEndCGContext, Quickdraw drawing
 *    is disabled; only CoreGraphics drawing is allowed
 *    - QDBeginCGContext/QDEndCGContext calls can not be nested
 *    - QDEndCGContext releases the CGContext returned from
 *    QDBeginCGContext and sets it to NULL.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inPort:
 *      The current port
 *    
 *    outContext:
 *      The CGContextRef to be used for CG drawing
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDBeginCGContext(
  CGrafPtr        inPort,
  CGContextRef *  outContext)                                 AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  QDEndCGContext()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDEndCGContext(
  CGrafPtr        inPort,
  CGContextRef *  inoutContext)                               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
    They save the pixel data of a region in a packed format for quick save/restore 
    without using a lot of memory to do a large, hollow region, such as the region
    used when drag hiliting (which is where this is used).
*/

typedef struct OpaqueQDRegionBitsRef*   QDRegionBitsRef;
/*
 *  QDSaveRegionBits()
 *  
 *  Summary:
 *    Saves the pixel data of a region in a packed format for quick
 *    restore
 *  
 *  Discussion:
 *    Implemented in CarbonLib, and on Mac OS X in QD proper. Used in
 *    particular for drag hiliting. The packed format doesn't use too
 *    much memory for large hollow regions.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    region:
 *      The RgnHandle corresponding to the pixel data to be saved.
 *  
 *  Result:
 *    The QDRegionBitsRef to be passed later into QDRestoreRegionBits.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern QDRegionBitsRef 
QDSaveRegionBits(RgnHandle region)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  QDRestoreRegionBits()
 *  
 *  Summary:
 *    Restores the pixel data of a region, as returned from
 *    QDSaveRegionBits
 *  
 *  Discussion:
 *    Implemented in CarbonLib, and on Mac OS X in QD proper. Used in
 *    particular for drag hiliting. NOTE: QDRestoreRegionBits also
 *    calls QDDisposeRegionBits on the regionBits passed in - don't
 *    call it again!
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    region:
 *      The RgnHandle corresponding to the regionBits.
 *    
 *    regionBits:
 *      The QDRegionBitsRef returned from a preceding QDSaveRegionBits
 *      call
 *  
 *  Result:
 *    OSStatus noErr, or paramErr if a NULL parameter is passed in
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDRestoreRegionBits(
  RgnHandle         region,
  QDRegionBitsRef   regionBits)                               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  QDDisposeRegionBits()
 *  
 *  Summary:
 *    Disposes of data allocated in QDSaveRegionBits, when the
 *    QDRegionBitsRef needs to be discarded without being passed to
 *    QDRestoreRegionBits.
 *  
 *  Discussion:
 *    Implemented in CarbonLib, and on Mac OS X in QD proper. NOTE: If
 *    the QDRegionBitsRef has been passed to QDRestoreRegionBits, it
 *    has been deallocated already - don't call QDDisposeRegionBits,
 *    then.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    regionBits:
 *      The QDRegionBitsRef returned from a preceding QDSaveRegionBits
 *      call
 *  
 *  Result:
 *    OSStatus noErr, or paramErr if a NULL parameter is passed in
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDDisposeRegionBits(QDRegionBitsRef regionBits)               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/*
   Developers need a way to go from a CGDirectDisplay environment to Quickdraw.
   The following is equivalent to CreateNewPort(), but instead of taking the
   portPixMap from the current GDevice, it uses the GDevice corresponding to
   the CGSDisplayID passed in. If the CGSDisplayID is invalid, the mainDevice
   is used instead.
*/
/*
 *  CreateNewPortForCGDisplayID()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern CGrafPtr 
CreateNewPortForCGDisplayID(UInt32 inCGDisplayID)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   In Mac OS X, developers should be able to turn the WaitCursor (spinning wheel)
   on and off. QDDisplayWaitCursor() keeps track of nested calls.
   Passing FALSE will resume automatic wait cursor operation.
   Call this function only from an application in the foreground.
*/
/*
 *  QDDisplayWaitCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
QDDisplayWaitCursor(Boolean forceWaitCursor)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDSetPatternOrigin()
 *  
 *  Summary:
 *    Sets the pattern origin for the current port.
 *  
 *  Discussion:
 *    When a QuickDraw drawing operation uses a pattern (either a
 *    black&white pattern or a PixPat), the pattern's image is aligned
 *    with port origin, modified by the pattern origin of the port. For
 *    example, if the background pattern is a 10x10 image, and a
 *    rectangle with coordinates (3, 3, 10, 10) is filled with that
 *    pattern, then only the bottom right 7x7 portion of the pattern
 *    image will be drawn into the rectangle. When drawing a pattern,
 *    QuickDraw always starts with the port origin and then adjusts it
 *    by the pattern origin to determine the actual origin point of
 *    pattern drawing. QDSetPatternOrigin can be used to set the
 *    pattern origin relative to the port origin. It is often used in
 *    conjuction with SetOrigin to maintain the pattern alignment at
 *    (0,0) in a window's content area, regardless of the port origin;
 *    for example, after changing the port's origin to (10,10), an
 *    application might change the port's pattern origin to (-10, -10)
 *    so that patterns are still aligned with the window's content area.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    origin:
 *      The new pattern origin of the port.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in NQD 8.5 and later
 */
extern void 
QDSetPatternOrigin(Point origin)                              AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  QDGetPatternOrigin()
 *  
 *  Summary:
 *    Returns the pattern origin of the current port.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    origin:
 *      On exit, contains the current port's pattern origin.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in NQD 8.5 and later
 */
extern void 
QDGetPatternOrigin(Point * origin)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/*
 *  QDIsNamedPixMapCursorRegistered()
 *  
 *  Summary:
 *    Returns whether a named cursor has already been registered.
 *  
 *  Discussion:
 *    The CoreGraphics Scalable Cursor Registry provides support for
 *    cursors based on PixMaps for crsrData and crsrMask, with sizes up
 *    to 64x64 pixels. Such cursors need to be registered via
 *    QDRegisterNamedPixMapCursor, and can then be set by
 *    QDSetNamedPixMapCursor.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    name:
 *      (see below at QDRegisterNamedPixMapCursor)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
QDIsNamedPixMapCursorRegistered(const char name[128])         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
 *  QDRegisterNamedPixMapCursor()
 *  
 *  Summary:
 *    Register a new cursor by name
 *  
 *  Discussion:
 *    In order to set a PixMapCursor, it needs to be registered first
 *    by name. This only succeeds if the system supports Hardware
 *    Cursors (depending on video circuits). There is also the obvious
 *    companion function QDUnregisterNamedPixMapCursor. NOTE: The
 *    original implementation of QDUnregisterNamedPixMapCursor was
 *    misspelled "QDUnregisterNamedPixMapCursur".
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    crsrData:
 *      A PixMapHandle representing the cursor pixels. If the
 *      pixelDepth is 32, the crsrMask PixMapHandle can be NULL; in
 *      this case, the alpha channel in the ARGB PixMap is used as
 *      mask. If a crsrMask is provided, the alpha channel in crsrData
 *      is ignored. The pixelDepth can be any of 1, 2, 4, 8, 16 or 32.
 *    
 *    crsrMask:
 *      A PixMapHandle representing the mask. It is assumed to be in
 *      8-bit deep grayScale format, although other depths are accepted
 *      and converted to 8-bit grayScale (using CopyBits). The
 *      (**crsrMask).bounds rectangle needs to match
 *      (**crsrData).bounds. If the crsrData are 32-bit deep, crsrMask
 *      can be NULL, and the alpha bytes in the crsrData ARGB pixels
 *      are used as mask.
 *    
 *    hotSpot:
 *      The usual cursor hotspot, in coordinates relativ to
 *      (**crsrData).bounds.topLeft.
 *    
 *    name:
 *      A naming convention involving the name of your application and
 *      descriptive cursor names or resource IDs is suggested. Cursor
 *      names are 0-terminated C-strings up to a length of 127. $result
 *              OSStatus: noErr = 0 for success, or (constants from
 *      MacErrors.h): kQDNoColorHWCursorSupport,
 *      kQDCursorAlreadyRegistered, paramErr, memFullErr, or a CGError
 *      as returned internally from CoreGraphics.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDRegisterNamedPixMapCursor(
  PixMapHandle   crsrData,
  PixMapHandle   crsrMask,
  Point          hotSpot,
  const char     name[128])                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QDUnregisterNamedPixMapCursur()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDUnregisterNamedPixMapCursur(const char name[128])           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QDUnregisterNamedPixMapCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDUnregisterNamedPixMapCursor(const char name[128])           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QDSetNamedPixMapCursor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDSetNamedPixMapCursor(const char name[128])                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


enum {
  kQDXArrowCursor               = 0,
  kQDXIBeamCursor               = 1,
  kQDXIBeamXORCursor            = 2,
  kQDXAliasCursor               = 3,
  kQDXCopyCursor                = 4,
  kQDXMoveCursor                = 5,
  kQDXNumberOfSystemCursors     = 6     /* Must be last */
};


typedef UInt32                          QDXSystemCursorID;
/*
 *  QDGetCursorNameForSystemCursor()
 *  
 *  Summary:
 *    Return the name of one of the predefined Mac OS X system cursors
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    cursorID:
 *      UInt32 in the range 0 ... kQDXNumberOfSystemCursors - 1 (see
 *      enum above)
 *  
 *  Result:
 *    const char* name, or NULL if 'cursorID' is out of range
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern const char * 
QDGetCursorNameForSystemCursor(QDXSystemCursorID cursorID)    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




/*
 *  QDSetCursorScale()
 *  
 *  Summary:
 *    Set a scaling factor for the cursor.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    scale:
 *      Must be at least 0.5, and integer values (1.0, 2.0, 3.0, 4.0)
 *      are recommended. The scaling factor is system-wide (applies to
 *      all apps), and is intended for use in such things as assisting
 *      the visually impaired.  The scaling factor is treated as a hint
 *      to the system, and the exact scale applied may be limited by
 *      device driver capabilities and performance considerations.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDSetCursorScale(float scale)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QDGetCursorScale()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDGetCursorScale(float * outScale)                            AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  QDGetCursorData()
 *  
 *  Summary:
 *    Allocate and return a PixMapHandle with the cursor data; also
 *    return the hotSpot. The caller is responsible for calling
 *    DisposePtr((**crsrData).baseAddr) and DisposePixMap(crsrData)
 *    when done with the crsrData returned.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    contextCursor:
 *      A Boolean; if true, return data for the current context cursor,
 *      if false, return data for the currently showing global cursor.
 *    
 *    crsrData:
 *      Allocates a PixMapHandle and pixelData in baseAddr,
 *      corresponding to the cursorData. The pixelData are in 32-bit
 *      ARGB format, with the mask contained in the alpha channel. This
 *      PixMapHandle can be passed as crsrData to
 *      QDRegisterNamedPixMapCursor, above (with crsrMask = NULL). If
 *      the return result indicates an error, NULL is returned.
 *    
 *    hotSpot:
 *      Contains the cursor hotSpot, if successful.
 *  
 *  Result:
 *    noErr if successful, or whatever error is returned from lower
 *    levels otherwise.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDGetCursorData(
  Boolean         contextCursor,
  PixMapHandle *  crsrData,
  Point *         hotSpot)                                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




enum {
  kQDUseDefaultTextRendering    = 0,    /* Sets whatever is specified in system defaults.*/
                                        /* Currently sets kQDUseTrueTypeScalerGlyphs if nothing is specified.*/
  kQDUseTrueTypeScalerGlyphs    = (1 << 0), /* bit 0*/
  kQDUseCGTextRendering         = (1 << 1), /* bit 1*/
  kQDUseCGTextMetrics           = (1 << 2), /* bit 2*/
  kQDSupportedFlags             = kQDUseTrueTypeScalerGlyphs | kQDUseCGTextRendering | kQDUseCGTextMetrics,
  kQDDontChangeFlags            = (long)0xFFFFFFFF /* to request the current state, without changing anything*/
};



/*
 *  QDSwapTextFlags()
 *  
 *  Summary:
 *    Returns current flags and optionally sets new flags.
 *  
 *  Discussion:
 *    Currently, only the flag bits in the enum above are supported.
 *    The typical usage is UInt32 savedFlags =
 *    QDSwapTextFlags(newFlags); // ... draw text under the conditions
 *    of "newFlags" ... (void)QDSwapTextFlags(savedFlags);  // restore
 *    previous setting
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    newFlags:
 *      Use the enums above; example "kQDUseCGTextRendering |
 *      kQDUseCGTextMetrics".
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern UInt32 
QDSwapTextFlags(UInt32 newFlags)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QDSwapPortTextFlags()
 *  
 *  Summary:
 *    Same as QDSwapTextFlags, but per GrafPort.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    port:
 *      Settings per port override any global settings. If port ==
 *      NULL, the current port is used.
 *    
 *    newFlags:
 *      As in QDSwapTextFlags, above.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern UInt32 
QDSwapPortTextFlags(
  CGrafPtr   port,
  UInt32     newFlags)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
 *  QDGetCGDirectDisplayID()
 *  
 *  Summary:
 *    Return the CGDirectDisplayID corresponding to a GDHandle
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inGDevice:
 *      The GDevice handle corresponding to the device for which the
 *      CGDirectDisplayID is requested
 *  
 *  Result:
 *    The CGDirectDisplayID, or 0 if the GDHandle does not represent a
 *    display.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern CGDirectDisplayID 
QDGetCGDirectDisplayID(GDHandle inGDevice)                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* 
    LowMem accessor functions previously in LowMem.h
*/
/*
 *  LMGetScrVRes()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16 
LMGetScrVRes(void)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetScrVRes()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetScrVRes(SInt16 value)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetScrHRes()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16 
LMGetScrHRes(void)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetScrHRes()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetScrHRes(SInt16 value)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetMainDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
LMGetMainDevice(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetMainDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetMainDevice(GDHandle value)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetDeviceList()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
LMGetDeviceList(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetDeviceList()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetDeviceList(GDHandle value)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetQDColors()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
LMGetQDColors(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetQDColors()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetQDColors(Handle value)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetWidthListHand()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
LMGetWidthListHand(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetWidthListHand()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetWidthListHand(Handle value)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetHiliteMode()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8 
LMGetHiliteMode(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetHiliteMode()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetHiliteMode(UInt8 value)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetWidthPtr()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr 
LMGetWidthPtr(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetWidthPtr()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetWidthPtr(Ptr value)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetWidthTabHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
LMGetWidthTabHandle(void)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetWidthTabHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetWidthTabHandle(Handle value)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetLastSPExtra()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt32 
LMGetLastSPExtra(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetLastSPExtra()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetLastSPExtra(SInt32 value)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetLastFOND()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
LMGetLastFOND(void)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetLastFOND()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetLastFOND(Handle value)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetFractEnable()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8 
LMGetFractEnable(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetFractEnable()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetFractEnable(UInt8 value)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetTheGDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
LMGetTheGDevice(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetTheGDevice()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetTheGDevice(GDHandle value)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetHiliteRGB()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMGetHiliteRGB(RGBColor * hiliteRGBValue)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetHiliteRGB()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetHiliteRGB(const RGBColor * hiliteRGBValue)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetCursorNew()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern Boolean 
LMGetCursorNew(void)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetCursorNew()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern void 
LMSetCursorNew(Boolean value)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



















#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __QUICKDRAW__ */

