/*
     File:       ColorSync/CMApplication.h
 
     Contains:   Color Matching Interfaces
 
     Version:    ColorSync-81~8
 
     Copyright:  ? 1992-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CMAPPLICATION__
#define __CMAPPLICATION__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __CMICCPROFILE__
#include <ColorSync/CMICCProfile.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif

#ifndef __CMTYPES__
#include <ColorSync/CMTypes.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif

#ifndef __CFDICTIONARY__
#include <CoreFoundation/CFDictionary.h>
#endif



#define _DECLARE_CS_QD_API_ 0

#if TARGET_OS_WIN32
#include <windows.h>
#endif



#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

enum {
  kDefaultCMMSignature          = 'appl'
};

/* Macintosh 68K trap word */
enum {
  cmTrap                        = 0xABEE
};


/* PicComment IDs */
enum {
  cmBeginProfile                = 220,
  cmEndProfile                  = 221,
  cmEnableMatching              = 222,
  cmDisableMatching             = 223,
  cmComment                     = 224
};

/* PicComment selectors for cmComment */
enum {
  cmBeginProfileSel             = 0,
  cmContinueProfileSel          = 1,
  cmEndProfileSel               = 2,
  cmProfileIdentifierSel        = 3
};


/* Defines for version 1.0 CMProfileSearchRecord.fieldMask */
enum {
  cmMatchCMMType                = 0x00000001,
  cmMatchApplProfileVersion     = 0x00000002,
  cmMatchDataType               = 0x00000004,
  cmMatchDeviceType             = 0x00000008,
  cmMatchDeviceManufacturer     = 0x00000010,
  cmMatchDeviceModel            = 0x00000020,
  cmMatchDeviceAttributes       = 0x00000040,
  cmMatchFlags                  = 0x00000080,
  cmMatchOptions                = 0x00000100,
  cmMatchWhite                  = 0x00000200,
  cmMatchBlack                  = 0x00000400
};

/* Defines for version 2.0 CMSearchRecord.searchMask */
enum {
  cmMatchAnyProfile             = 0x00000000,
  cmMatchProfileCMMType         = 0x00000001,
  cmMatchProfileClass           = 0x00000002,
  cmMatchDataColorSpace         = 0x00000004,
  cmMatchProfileConnectionSpace = 0x00000008,
  cmMatchManufacturer           = 0x00000010,
  cmMatchModel                  = 0x00000020,
  cmMatchAttributes             = 0x00000040,
  cmMatchProfileFlags           = 0x00000080
};


/* Flags for PostScript-related functions */
enum {
  cmPS7bit                      = 1,
  cmPS8bit                      = 2
};

/* Flags for profile embedding functions */
enum {
  cmEmbedWholeProfile           = 0x00000000,
  cmEmbedProfileIdentifier      = 0x00000001
};

/* Commands for CMFlattenUPP() */
enum {
  cmOpenReadSpool               = 1,
  cmOpenWriteSpool              = 2,
  cmReadSpool                   = 3,
  cmWriteSpool                  = 4,
  cmCloseSpool                  = 5
};

/* Commands for CMAccessUPP() */
enum {
  cmOpenReadAccess              = 1,
  cmOpenWriteAccess             = 2,
  cmReadAccess                  = 3,
  cmWriteAccess                 = 4,
  cmCloseAccess                 = 5,
  cmCreateNewAccess             = 6,
  cmAbortWriteAccess            = 7,
  cmBeginAccess                 = 8,
  cmEndAccess                   = 9
};


/* Use types for CMGet/SetDefaultProfileByUse() */
enum {
  cmInputUse                    = 'inpt',
  cmOutputUse                   = 'outp',
  cmDisplayUse                  = 'dply',
  cmProofUse                    = 'pruf'
};


/* Union of 1.0 2.0, and 4.0 profile header variants */
union CMAppleProfileHeader {
  CMHeader            cm1;
  CM2Header           cm2;
  CM4Header           cm4;
};
typedef union CMAppleProfileHeader      CMAppleProfileHeader;
/* CWConcatColorWorld() definitions */
struct CMConcatProfileSet {
  UInt16              keyIndex;               /* Zero-based */
  UInt16              count;                  /* Min 1 */
  CMProfileRef        profileSet[1];          /* Variable. Ordered from Source -> Dest */
};
typedef struct CMConcatProfileSet       CMConcatProfileSet;
/* NCWConcatColorWorld() definitions */
struct NCMConcatProfileSpec {
  UInt32              renderingIntent;        /* renderingIntent override */
  UInt32              transformTag;           /* transform enumerations defined below */
  CMProfileRef        profile;                /* profile */
};
typedef struct NCMConcatProfileSpec     NCMConcatProfileSpec;
struct NCMConcatProfileSet {
  OSType              cmm;                    /* e.g. 'KCMS', 'appl', ...  uniquely ids the cmm, or 0000 */
  UInt32              flags;                  /* specify quality, lookup only, no gamut checking ... */
  UInt32              flagsMask;              /* which bits of 'flags' to use to override profile */
  UInt32              profileCount;           /* how many ProfileSpecs in the following set */
  NCMConcatProfileSpec  profileSpecs[1];      /* Variable. Ordered from Source -> Dest */
};
typedef struct NCMConcatProfileSet      NCMConcatProfileSet;
enum {
  kNoTransform                  = 0,    /* Not used */
  kUseAtoB                      = 1,    /* Use 'A2B*' tag from this profile or equivalent */
  kUseBtoA                      = 2,    /* Use 'B2A*' tag from this profile or equivalent */
  kUseBtoB                      = 3,    /* Use 'pre*' tag from this profile or equivalent */
                                        /* For typical device profiles the following synonyms may be useful */
  kDeviceToPCS                  = kUseAtoB, /* Device Dependent to Device Independent */
  kPCSToDevice                  = kUseBtoA, /* Device Independent to Device Dependent */
  kPCSToPCS                     = kUseBtoB, /* Independent, through device's gamut */
  kUseProfileIntent             = (long)0xFFFFFFFF /* For renderingIntent in NCMConcatProfileSpec    */
};


/* ColorSync color data types */
struct CMRGBColor {
  UInt16              red;                    /* 0..65535 */
  UInt16              green;
  UInt16              blue;
};
typedef struct CMRGBColor               CMRGBColor;
struct CMCMYKColor {
  UInt16              cyan;                   /* 0..65535 */
  UInt16              magenta;
  UInt16              yellow;
  UInt16              black;
};
typedef struct CMCMYKColor              CMCMYKColor;
struct CMCMYColor {
  UInt16              cyan;                   /* 0..65535 */
  UInt16              magenta;
  UInt16              yellow;
};
typedef struct CMCMYColor               CMCMYColor;
struct CMHLSColor {
  UInt16              hue;                    /* 0..65535. Fraction of circle. Red at 0 */
  UInt16              lightness;              /* 0..65535 */
  UInt16              saturation;             /* 0..65535 */
};
typedef struct CMHLSColor               CMHLSColor;
struct CMHSVColor {
  UInt16              hue;                    /* 0..65535. Fraction of circle. Red at 0 */
  UInt16              saturation;             /* 0..65535 */
  UInt16              value;                  /* 0..65535 */
};
typedef struct CMHSVColor               CMHSVColor;
struct CMLabColor {
  UInt16              L;                      /* 0..65535 maps to 0..100 */
  UInt16              a;                      /* 0..65535 maps to -128..127.996 */
  UInt16              b;                      /* 0..65535 maps to -128..127.996 */
};
typedef struct CMLabColor               CMLabColor;
struct CMLuvColor {
  UInt16              L;                      /* 0..65535 maps to 0..100 */
  UInt16              u;                      /* 0..65535 maps to -128..127.996 */
  UInt16              v;                      /* 0..65535 maps to -128..127.996 */
};
typedef struct CMLuvColor               CMLuvColor;
struct CMYxyColor {
  UInt16              capY;                   /* 0..65535 maps to 0..1 */
  UInt16              x;                      /* 0..65535 maps to 0..1 */
  UInt16              y;                      /* 0..65535 maps to 0..1 */
};
typedef struct CMYxyColor               CMYxyColor;
struct CMGrayColor {
  UInt16              gray;                   /* 0..65535 */
};
typedef struct CMGrayColor              CMGrayColor;
struct CMMultichannel5Color {
  UInt8               components[5];          /* 0..255 */
};
typedef struct CMMultichannel5Color     CMMultichannel5Color;
struct CMMultichannel6Color {
  UInt8               components[6];          /* 0..255 */
};
typedef struct CMMultichannel6Color     CMMultichannel6Color;
struct CMMultichannel7Color {
  UInt8               components[7];          /* 0..255 */
};
typedef struct CMMultichannel7Color     CMMultichannel7Color;
struct CMMultichannel8Color {
  UInt8               components[8];          /* 0..255 */
};
typedef struct CMMultichannel8Color     CMMultichannel8Color;
struct CMNamedColor {
  UInt32              namedColorIndex;        /* 0..a lot */
};
typedef struct CMNamedColor             CMNamedColor;
union CMColor {
  CMRGBColor          rgb;
  CMHSVColor          hsv;
  CMHLSColor          hls;
  CMXYZColor          XYZ;
  CMLabColor          Lab;
  CMLuvColor          Luv;
  CMYxyColor          Yxy;
  CMCMYKColor         cmyk;
  CMCMYColor          cmy;
  CMGrayColor         gray;
  CMMultichannel5Color  mc5;
  CMMultichannel6Color  mc6;
  CMMultichannel7Color  mc7;
  CMMultichannel8Color  mc8;
  CMNamedColor        namedColor;
};
typedef union CMColor                   CMColor;
/* GetIndexedProfile() search definition */
struct CMProfileSearchRecord {
  CMHeader            header;
  UInt32              fieldMask;
  UInt32              reserved[2];
};
typedef struct CMProfileSearchRecord    CMProfileSearchRecord;
typedef CMProfileSearchRecord *         CMProfileSearchRecordPtr;
typedef CMProfileSearchRecordPtr *      CMProfileSearchRecordHandle;
/* CMNewProfileSearch() search definition */
struct CMSearchRecord {
  OSType              CMMType;
  OSType              profileClass;
  OSType              dataColorSpace;
  OSType              profileConnectionSpace;
  UInt32              deviceManufacturer;
  UInt32              deviceModel;
  UInt32              deviceAttributes[2];
  UInt32              profileFlags;
  UInt32              searchMask;
  CMProfileFilterUPP  filter;
};
typedef struct CMSearchRecord           CMSearchRecord;
/* CMMIterateUPP() structure */
struct CMMInfo {
  UInt32              dataSize;               /* Size of this structure - compatibility*/
  OSType              CMMType;                /* Signature, e.g. 'appl', 'HDM ' or 'KCMS'*/
  OSType              CMMMfr;                 /* Vendor, e.g. 'appl'*/
  UInt32              CMMVersion;             /* CMM version number*/
  unsigned char       ASCIIName[32];          /* pascal string - name*/
  unsigned char       ASCIIDesc[256];         /* pascal string - description or copyright*/
  UniCharCount        UniCodeNameCount;       /* count of UniChars in following array*/
  UniChar             UniCodeName[32];        /* the name in UniCode chars*/
  UniCharCount        UniCodeDescCount;       /* count of UniChars in following array*/
  UniChar             UniCodeDesc[256];       /* the description in UniCode chars*/
};
typedef struct CMMInfo                  CMMInfo;
/* GetCWInfo() structures */
struct CMMInfoRecord {
  OSType              CMMType;
  long                CMMVersion;
};
typedef struct CMMInfoRecord            CMMInfoRecord;
struct CMCWInfoRecord {
  UInt32              cmmCount;
  CMMInfoRecord       cmmInfo[2];
};
typedef struct CMCWInfoRecord           CMCWInfoRecord;
/* profile identifier structures */
struct CMProfileIdentifier {
  CM2Header           profileHeader;
  CMDateTime          calibrationDate;
  UInt32              ASCIIProfileDescriptionLen;
  char                ASCIIProfileDescription[1]; /* variable length */
};
typedef struct CMProfileIdentifier      CMProfileIdentifier;
typedef CMProfileIdentifier *           CMProfileIdentifierPtr;
/* colorspace masks */
enum {
  cmColorSpaceSpaceMask         = 0x0000003F,
  cmColorSpacePremulAlphaMask   = 0x00000040,
  cmColorSpaceAlphaMask         = 0x00000080,
  cmColorSpaceSpaceAndAlphaMask = 0x000000FF,
  cmColorSpacePackingMask       = 0x0000FF00,
  cmColorSpaceEncodingMask      = 0x000F0000,
  cmColorSpaceReservedMask      = (long)0xFFF00000
};

/* packing formats */
enum {
  cmNoColorPacking              = 0x0000,
  cmWord5ColorPacking           = 0x0500,
  cmWord565ColorPacking         = 0x0600,
  cmLong8ColorPacking           = 0x0800,
  cmLong10ColorPacking          = 0x0A00,
  cmAlphaFirstPacking           = 0x1000,
  cmOneBitDirectPacking         = 0x0B00,
  cmAlphaLastPacking            = 0x0000,
  cm8_8ColorPacking             = 0x2800,
  cm16_8ColorPacking            = 0x2000,
  cm24_8ColorPacking            = 0x2100,
  cm32_8ColorPacking            = cmLong8ColorPacking,
  cm40_8ColorPacking            = 0x2200,
  cm48_8ColorPacking            = 0x2300,
  cm56_8ColorPacking            = 0x2400,
  cm64_8ColorPacking            = 0x2500,
  cm32_16ColorPacking           = 0x2600,
  cm48_16ColorPacking           = 0x2900,
  cm64_16ColorPacking           = 0x2A00,
  cm32_32ColorPacking           = 0x2700,
  cmLittleEndianPacking         = 0x4000,
  cmReverseChannelPacking       = 0x8000
};

/* channel encoding format */
enum {
  cmSRGB16ChannelEncoding       = 0x00010000 /* used for sRGB64 encoding ( ?3.12 format)*/
};

/* general colorspaces */
enum {
  cmNoSpace                     = 0x0000,
  cmRGBSpace                    = 0x0001,
  cmCMYKSpace                   = 0x0002,
  cmHSVSpace                    = 0x0003,
  cmHLSSpace                    = 0x0004,
  cmYXYSpace                    = 0x0005,
  cmXYZSpace                    = 0x0006,
  cmLUVSpace                    = 0x0007,
  cmLABSpace                    = 0x0008,
  cmReservedSpace1              = 0x0009,
  cmGraySpace                   = 0x000A,
  cmReservedSpace2              = 0x000B,
  cmGamutResultSpace            = 0x000C,
  cmNamedIndexedSpace           = 0x0010,
  cmMCFiveSpace                 = 0x0011,
  cmMCSixSpace                  = 0x0012,
  cmMCSevenSpace                = 0x0013,
  cmMCEightSpace                = 0x0014,
  cmAlphaPmulSpace              = 0x0040,
  cmAlphaSpace                  = 0x0080,
  cmRGBASpace                   = cmRGBSpace + cmAlphaSpace,
  cmGrayASpace                  = cmGraySpace + cmAlphaSpace,
  cmRGBAPmulSpace               = cmRGBASpace + cmAlphaPmulSpace,
  cmGrayAPmulSpace              = cmGrayASpace + cmAlphaPmulSpace
};

/* supported CMBitmapColorSpaces - Each of the following is a */
/* combination of a general colospace and a packing formats. */
/* Each can also be or'd with cmReverseChannelPacking. */
enum {
  cmGray8Space                  = cmGraySpace + cm8_8ColorPacking,
  cmGray16Space                 = cmGraySpace,
  cmGray16LSpace                = cmGraySpace + cmLittleEndianPacking,
  cmGrayA16Space                = cmGrayASpace + cm16_8ColorPacking,
  cmGrayA32Space                = cmGrayASpace,
  cmGrayA32LSpace               = cmGrayASpace + cmLittleEndianPacking,
  cmGrayA16PmulSpace            = cmGrayAPmulSpace + cm16_8ColorPacking,
  cmGrayA32PmulSpace            = cmGrayAPmulSpace,
  cmGrayA32LPmulSpace           = cmGrayAPmulSpace + cmLittleEndianPacking,
  cmRGB16Space                  = cmRGBSpace + cmWord5ColorPacking,
  cmRGB16LSpace                 = cmRGBSpace + cmWord5ColorPacking + cmLittleEndianPacking,
  cmRGB565Space                 = cmRGBSpace + cmWord565ColorPacking,
  cmRGB565LSpace                = cmRGBSpace + cmWord565ColorPacking + cmLittleEndianPacking,
  cmRGB24Space                  = cmRGBSpace + cm24_8ColorPacking,
  cmRGB32Space                  = cmRGBSpace + cm32_8ColorPacking,
  cmRGB48Space                  = cmRGBSpace + cm48_16ColorPacking,
  cmRGB48LSpace                 = cmRGBSpace + cm48_16ColorPacking + cmLittleEndianPacking,
  cmARGB32Space                 = cmRGBASpace + cm32_8ColorPacking + cmAlphaFirstPacking,
  cmARGB64Space                 = cmRGBASpace + cm64_16ColorPacking + cmAlphaFirstPacking,
  cmARGB64LSpace                = cmRGBASpace + cm64_16ColorPacking + cmAlphaFirstPacking + cmLittleEndianPacking,
  cmRGBA32Space                 = cmRGBASpace + cm32_8ColorPacking + cmAlphaLastPacking,
  cmRGBA64Space                 = cmRGBASpace + cm64_16ColorPacking + cmAlphaLastPacking,
  cmRGBA64LSpace                = cmRGBASpace + cm64_16ColorPacking + cmAlphaLastPacking + cmLittleEndianPacking,
  cmARGB32PmulSpace             = cmRGBAPmulSpace + cm32_8ColorPacking + cmAlphaFirstPacking,
  cmARGB64PmulSpace             = cmRGBAPmulSpace + cm64_16ColorPacking + cmAlphaFirstPacking,
  cmARGB64LPmulSpace            = cmRGBAPmulSpace + cm64_16ColorPacking + cmAlphaFirstPacking + cmLittleEndianPacking,
  cmRGBA32PmulSpace             = cmRGBAPmulSpace + cm32_8ColorPacking + cmAlphaLastPacking,
  cmRGBA64PmulSpace             = cmRGBAPmulSpace + cm64_16ColorPacking + cmAlphaLastPacking,
  cmRGBA64LPmulSpace            = cmRGBAPmulSpace + cm64_16ColorPacking + cmAlphaLastPacking + cmLittleEndianPacking,
  cmCMYK32Space                 = cmCMYKSpace + cm32_8ColorPacking,
  cmCMYK64Space                 = cmCMYKSpace + cm64_16ColorPacking,
  cmCMYK64LSpace                = cmCMYKSpace + cm64_16ColorPacking + cmLittleEndianPacking,
  cmHSV32Space                  = cmHSVSpace + cmLong10ColorPacking,
  cmHLS32Space                  = cmHLSSpace + cmLong10ColorPacking,
  cmYXY32Space                  = cmYXYSpace + cmLong10ColorPacking,
  cmXYZ24Space                  = cmXYZSpace + cm24_8ColorPacking,
  cmXYZ32Space                  = cmXYZSpace + cmLong10ColorPacking,
  cmXYZ48Space                  = cmXYZSpace + cm48_16ColorPacking,
  cmXYZ48LSpace                 = cmXYZSpace + cm48_16ColorPacking + cmLittleEndianPacking,
  cmLUV32Space                  = cmLUVSpace + cmLong10ColorPacking,
  cmLAB24Space                  = cmLABSpace + cm24_8ColorPacking,
  cmLAB32Space                  = cmLABSpace + cmLong10ColorPacking,
  cmLAB48Space                  = cmLABSpace + cm48_16ColorPacking,
  cmLAB48LSpace                 = cmLABSpace + cm48_16ColorPacking + cmLittleEndianPacking,
  cmGamutResult1Space           = cmOneBitDirectPacking + cmGamutResultSpace,
  cmNamedIndexed32Space         = cm32_32ColorPacking + cmNamedIndexedSpace,
  cmNamedIndexed32LSpace        = cm32_32ColorPacking + cmNamedIndexedSpace + cmLittleEndianPacking,
  cmMCFive8Space                = cm40_8ColorPacking + cmMCFiveSpace,
  cmMCSix8Space                 = cm48_8ColorPacking + cmMCSixSpace,
  cmMCSeven8Space               = cm56_8ColorPacking + cmMCSevenSpace,
  cmMCEight8Space               = cm64_8ColorPacking + cmMCEightSpace
};


typedef UInt32                          CMBitmapColorSpace;
struct CMBitmap {
  char *              image;
  long                width;
  long                height;
  long                rowBytes;
  long                pixelSize;
  CMBitmapColorSpace  space;
  long                user1;
  long                user2;
};
typedef struct CMBitmap                 CMBitmap;
/* CMConvertXYZToXYZ() definitions */

typedef UInt32                          CMChromaticAdaptation;
enum {
  cmUseDefaultChromaticAdaptation = 0,
  cmLinearChromaticAdaptation   = 1,
  cmVonKriesChromaticAdaptation = 2,
  cmBradfordChromaticAdaptation = 3
};


/* Profile Locations */
enum {
  CS_MAX_PATH                   = 256
};

enum {
  cmNoProfileBase               = 0,
  cmFileBasedProfile            = 1,
  cmHandleBasedProfile          = 2,
  cmPtrBasedProfile             = 3,
  cmProcedureBasedProfile       = 4,
  cmPathBasedProfile            = 5,
  cmBufferBasedProfile          = 6
};

struct CMFileLocation {
  FSSpec              spec;
};
typedef struct CMFileLocation           CMFileLocation;
struct CMHandleLocation {
  Handle              h;
};
typedef struct CMHandleLocation         CMHandleLocation;
struct CMPtrLocation {
  Ptr                 p;
};
typedef struct CMPtrLocation            CMPtrLocation;
struct CMProcedureLocation {
  CMProfileAccessUPP  proc;
  void *              refCon;
};
typedef struct CMProcedureLocation      CMProcedureLocation;
struct CMPathLocation {
  char                path[256];
};
typedef struct CMPathLocation           CMPathLocation;
struct CMBufferLocation {
  void *              buffer;
  UInt32              size;
};
typedef struct CMBufferLocation         CMBufferLocation;
union CMProfLoc {
  CMFileLocation      fileLoc;
  CMHandleLocation    handleLoc;
  CMPtrLocation       ptrLoc;
  CMProcedureLocation  procLoc;
  CMPathLocation      pathLoc;
  CMBufferLocation    bufferLoc;
};
typedef union CMProfLoc                 CMProfLoc;
struct CMProfileLocation {
  short               locType;
  CMProfLoc           u;
};
typedef struct CMProfileLocation        CMProfileLocation;
enum {
  cmOriginalProfileLocationSize = 72,
  cmCurrentProfileLocationSize  = 2 + CS_MAX_PATH
};

/* Struct and enums used for Profile iteration */
enum {
  cmProfileIterateDataVersion1  = 0x00010000,
  cmProfileIterateDataVersion2  = 0x00020000, /* Added makeAndModel*/
  cmProfileIterateDataVersion3  = 0x00030000 /* Added MD5 digest*/
};

struct CMProfileIterateData {
  UInt32              dataVersion;            /* cmProfileIterateDataVersion2 */
  CM2Header           header;
  ScriptCode          code;
  Str255              name;
  CMProfileLocation   location;
  UniCharCount        uniCodeNameCount;
  UniChar *           uniCodeName;
  unsigned char *     asciiName;
  CMMakeAndModel *    makeAndModel;
  CMProfileMD5 *      digest;
};
typedef struct CMProfileIterateData     CMProfileIterateData;
/* Caller-supplied callback function for Profile & CMM iteration */
typedef CALLBACK_API( OSErr , CMProfileIterateProcPtr )(CMProfileIterateData *iterateData, void *refCon);
typedef CALLBACK_API( OSErr , CMMIterateProcPtr )(CMMInfo *iterateData, void *refCon);
typedef STACK_UPP_TYPE(CMProfileIterateProcPtr)                 CMProfileIterateUPP;
typedef STACK_UPP_TYPE(CMMIterateProcPtr)                       CMMIterateUPP;
/*
 *  NewCMProfileIterateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMProfileIterateUPP
NewCMProfileIterateUPP(CMProfileIterateProcPtr userRoutine);

/*
 *  NewCMMIterateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMMIterateUPP
NewCMMIterateUPP(CMMIterateProcPtr userRoutine);

/*
 *  DisposeCMProfileIterateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMProfileIterateUPP(CMProfileIterateUPP userUPP);

/*
 *  DisposeCMMIterateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMMIterateUPP(CMMIterateUPP userUPP);

/*
 *  InvokeCMProfileIterateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeCMProfileIterateUPP(
  CMProfileIterateData *  iterateData,
  void *                  refCon,
  CMProfileIterateUPP     userUPP);

/*
 *  InvokeCMMIterateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeCMMIterateUPP(
  CMMInfo *      iterateData,
  void *         refCon,
  CMMIterateUPP  userUPP);

/* Profile file and element access */
/*
 *  CMNewProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMNewProfile(
  CMProfileRef *             prof,
  const CMProfileLocation *  theProfile);


/*
 *  CMOpenProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMOpenProfile(
  CMProfileRef *             prof,
  const CMProfileLocation *  theProfile);


/*
 *  CMCloseProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMCloseProfile(CMProfileRef prof);


/*
 *  CMUpdateProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMUpdateProfile(CMProfileRef prof);


/*
 *  CMCopyProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMCopyProfile(
  CMProfileRef *             targetProf,
  const CMProfileLocation *  targetLocation,
  CMProfileRef               srcProf);


/*
 *  CMValidateProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMValidateProfile(
  CMProfileRef   prof,
  Boolean *      valid,
  Boolean *      preferredCMMnotfound);


/*
 *  CMGetProfileLocation()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetProfileLocation(
  CMProfileRef         prof,
  CMProfileLocation *  theProfile);


/*
 *  NCMGetProfileLocation()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
NCMGetProfileLocation(
  CMProfileRef         prof,
  CMProfileLocation *  theProfile,
  UInt32 *             locationSize);


/*
 *  CMFlattenProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMFlattenProfile(
  CMProfileRef   prof,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon,
  Boolean *      preferredCMMnotfound);


/*
 *  CMUnflattenProfile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */


/*
 *  CMGetProfileHeader()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetProfileHeader(
  CMProfileRef            prof,
  CMAppleProfileHeader *  header);


/*
 *  CMSetProfileHeader()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSetProfileHeader(
  CMProfileRef                  prof,
  const CMAppleProfileHeader *  header);


/*
 *  CMProfileElementExists()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMProfileElementExists(
  CMProfileRef   prof,
  OSType         tag,
  Boolean *      found);


/*
 *  CMCountProfileElements()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMCountProfileElements(
  CMProfileRef   prof,
  UInt32 *       elementCount);


/*
 *  CMGetProfileElement()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetProfileElement(
  CMProfileRef   prof,
  OSType         tag,
  UInt32 *       elementSize,
  void *         elementData);


/*
 *  CMSetProfileElement()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSetProfileElement(
  CMProfileRef   prof,
  OSType         tag,
  UInt32         elementSize,
  const void *   elementData);


/*
 *  CMSetProfileElementSize()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSetProfileElementSize(
  CMProfileRef   prof,
  OSType         tag,
  UInt32         elementSize);


/*
 *  CMSetProfileElementReference()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSetProfileElementReference(
  CMProfileRef   prof,
  OSType         elementTag,
  OSType         referenceTag);


/*
 *  CMGetPartialProfileElement()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetPartialProfileElement(
  CMProfileRef   prof,
  OSType         tag,
  UInt32         offset,
  UInt32 *       byteCount,
  void *         elementData);


/*
 *  CMSetPartialProfileElement()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSetPartialProfileElement(
  CMProfileRef   prof,
  OSType         tag,
  UInt32         offset,
  UInt32         byteCount,
  const void *   elementData);


/*
 *  CMGetIndProfileElementInfo()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetIndProfileElementInfo(
  CMProfileRef   prof,
  UInt32         index,
  OSType *       tag,
  UInt32 *       elementSize,
  Boolean *      refs);


/*
 *  CMGetIndProfileElement()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetIndProfileElement(
  CMProfileRef   prof,
  UInt32         index,
  UInt32 *       elementSize,
  void *         elementData);


/*
 *  CMRemoveProfileElement()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMRemoveProfileElement(
  CMProfileRef   prof,
  OSType         tag);


/*
 *  CMGetScriptProfileDescription()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetScriptProfileDescription(
  CMProfileRef   prof,
  Str255         name,
  ScriptCode *   code);


/*
 *  CMGetProfileDescriptions()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
CMGetProfileDescriptions(
  CMProfileRef    prof,
  char *          aName,
  UInt32 *        aCount,
  Str255          mName,
  ScriptCode *    mCode,
  UniChar *       uName,
  UniCharCount *  uCount);


/*
 *  CMSetProfileDescriptions()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
CMSetProfileDescriptions(
  CMProfileRef       prof,
  const char *       aName,
  UInt32             aCount,
  ConstStr255Param   mName,
  ScriptCode         mCode,
  const UniChar *    uName,
  UniCharCount       uCount);


/*
 *  CMCopyProfileLocalizedStringDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in 3.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 3.1 and later
 */
extern CMError 
CMCopyProfileLocalizedStringDictionary(
  CMProfileRef       prof,
  OSType             tag,
  CFDictionaryRef *  theDict);


/*
 *  CMSetProfileLocalizedStringDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in 3.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 3.1 and later
 */
extern CMError 
CMSetProfileLocalizedStringDictionary(
  CMProfileRef      prof,
  OSType            tag,
  CFDictionaryRef   theDict);


/*
 *  CMCopyProfileLocalizedString()
 *  
 *  Availability:
 *    Mac OS X:         in 3.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 3.1 and later
 */
extern CMError 
CMCopyProfileLocalizedString(
  CMProfileRef   prof,
  OSType         tag,
  CFStringRef    reqLocale,
  CFStringRef *  locale,
  CFStringRef *  str);


/*
 *  CMCloneProfileRef()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMCloneProfileRef(CMProfileRef prof);


/*
 *  CMGetProfileRefCount()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMGetProfileRefCount(
  CMProfileRef   prof,
  long *         count);


/*
 *  CMProfileModified()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMProfileModified(
  CMProfileRef   prof,
  Boolean *      modified);


/*
 *  CMGetProfileMD5()
 *  
 *  Availability:
 *    Mac OS X:         in 3.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMGetProfileMD5(
  CMProfileRef   prof,
  CMProfileMD5   digest);



/* named Color access functions */
/*
 *  CMGetNamedColorInfo()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMGetNamedColorInfo(
  CMProfileRef   prof,
  UInt32 *       deviceChannels,
  OSType *       deviceColorSpace,
  OSType *       PCSColorSpace,
  UInt32 *       count,
  StringPtr      prefix,
  StringPtr      suffix);


/*
 *  CMGetNamedColorValue()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMGetNamedColorValue(
  CMProfileRef   prof,
  StringPtr      name,
  CMColor *      deviceColor,
  CMColor *      PCSColor);


/*
 *  CMGetIndNamedColorValue()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMGetIndNamedColorValue(
  CMProfileRef   prof,
  UInt32         index,
  CMColor *      deviceColor,
  CMColor *      PCSColor);


/*
 *  CMGetNamedColorIndex()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMGetNamedColorIndex(
  CMProfileRef   prof,
  StringPtr      name,
  UInt32 *       index);


/*
 *  CMGetNamedColorName()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMGetNamedColorName(
  CMProfileRef   prof,
  UInt32         index,
  StringPtr      name);



/* General-purpose matching functions */
/*
 *  NCWNewColorWorld()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
NCWNewColorWorld(
  CMWorldRef *   cw,
  CMProfileRef   src,
  CMProfileRef   dst);


/*
 *  CWConcatColorWorld()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CWConcatColorWorld(
  CMWorldRef *          cw,
  CMConcatProfileSet *  profileSet);


/*
 *  CWNewLinkProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CWNewLinkProfile(
  CMProfileRef *             prof,
  const CMProfileLocation *  targetLocation,
  CMConcatProfileSet *       profileSet);


/*
 *  NCWConcatColorWorld()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
NCWConcatColorWorld(
  CMWorldRef *           cw,
  NCMConcatProfileSet *  profileSet,
  CMConcatCallBackUPP    proc,
  void *                 refCon);


/*
 *  NCWNewLinkProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
NCWNewLinkProfile(
  CMProfileRef *             prof,
  const CMProfileLocation *  targetLocation,
  NCMConcatProfileSet *      profileSet,
  CMConcatCallBackUPP        proc,
  void *                     refCon);


/*
 *  CWDisposeColorWorld()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */
extern void 
CWDisposeColorWorld(CMWorldRef cw);


/*
 *  CWMatchColors()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */
extern CMError 
CWMatchColors(
  CMWorldRef   cw,
  CMColor *    myColors,
  UInt32       count);


/*
 *  CWCheckColors()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */
extern CMError 
CWCheckColors(
  CMWorldRef   cw,
  CMColor *    myColors,
  UInt32       count,
  UInt32 *     result);


/*
 *  CWMatchBitmap()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CWMatchBitmap(
  CMWorldRef            cw,
  CMBitmap *            bitmap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  CMBitmap *            matchedBitmap);


/*
 *  CWCheckBitmap()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CWCheckBitmap(
  CMWorldRef            cw,
  const CMBitmap *      bitmap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  CMBitmap *            resultBitmap);


/* Quickdraw-specific matching */
#if _DECLARE_CS_QD_API_
/*
 *  CWMatchPixMap()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */
extern CMError 
CWMatchPixMap(
  CMWorldRef            cw,
  PixMap *              myPixMap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon);


/*
 *  CWCheckPixMap()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */
extern CMError 
CWCheckPixMap(
  CMWorldRef            cw,
  PixMap *              myPixMap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  BitMap *              resultBitMap);


/*
 *  NCMBeginMatching()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
NCMBeginMatching(
  CMProfileRef   src,
  CMProfileRef   dst,
  CMMatchRef *   myRef);


/*
 *  CMEndMatching()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern void 
CMEndMatching(CMMatchRef myRef);


/*
 *  NCMDrawMatchedPicture()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern void 
NCMDrawMatchedPicture(
  PicHandle      myPicture,
  CMProfileRef   dst,
  Rect *         myRect);


/*
 *  CMEnableMatchingComment()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern void 
CMEnableMatchingComment(Boolean enableIt);


/*
 *  NCMUseProfileComment()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
NCMUseProfileComment(
  CMProfileRef   prof,
  UInt32         flags);


#endif  /* _DECLARE_CS_QD_API_ */

#if TARGET_OS_WIN32
/*
 *  CWMatchHBITMAP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


#endif  /* TARGET_OS_WIN32 */

/*
 *  CMCreateProfileIdentifier()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMCreateProfileIdentifier(
  CMProfileRef             prof,
  CMProfileIdentifierPtr   ident,
  UInt32 *                 size);



/* System Profile access */
/*
 *  CMGetSystemProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetSystemProfile(CMProfileRef * prof);


/*
 *  CMSetSystemProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSetSystemProfile(const FSSpec * profileFileSpec);


/*
 *  NCMSetSystemProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
NCMSetSystemProfile(const CMProfileLocation * profLoc);


/*
 *  CMGetDefaultProfileBySpace()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
CMGetDefaultProfileBySpace(
  OSType          dataColorSpace,
  CMProfileRef *  prof);


/*
 *  CMSetDefaultProfileBySpace()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
CMSetDefaultProfileBySpace(
  OSType         dataColorSpace,
  CMProfileRef   prof);


/*
 *  CMGetProfileByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
CMGetProfileByAVID(
  CMDisplayIDType   theID,
  CMProfileRef *    prof);


/*
 *  CMSetProfileByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
CMSetProfileByAVID(
  CMDisplayIDType   theID,
  CMProfileRef      prof);


/*
 *  CMGetGammaByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 3.0 and later
 */
extern CMError 
CMGetGammaByAVID(
  CMDisplayIDType     theID,
  CMVideoCardGamma *  gamma,
  UInt32 *            size);


/*
 *  CMSetGammaByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 3.0 and later
 */
extern CMError 
CMSetGammaByAVID(
  CMDisplayIDType     theID,
  CMVideoCardGamma *  gamma);


/* Profile access by Use */
/*
 *  CMGetDefaultProfileByUse()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 3.0 and later
 */
extern CMError 
CMGetDefaultProfileByUse(
  OSType          use,
  CMProfileRef *  prof);


/*
 *  CMSetDefaultProfileByUse()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 3.0 and later
 */
extern CMError 
CMSetDefaultProfileByUse(
  OSType         use,
  CMProfileRef   prof);


/* Profile Management */
/*
 *  CMNewProfileSearch()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMNewProfileSearch(
  CMSearchRecord *      searchSpec,
  void *                refCon,
  UInt32 *              count,
  CMProfileSearchRef *  searchResult);


/*
 *  CMUpdateProfileSearch()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMUpdateProfileSearch(
  CMProfileSearchRef   search,
  void *               refCon,
  UInt32 *             count);


/*
 *  CMDisposeProfileSearch()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern void 
CMDisposeProfileSearch(CMProfileSearchRef search);


/*
 *  CMSearchGetIndProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSearchGetIndProfile(
  CMProfileSearchRef   search,
  UInt32               index,
  CMProfileRef *       prof);


/*
 *  CMSearchGetIndProfileFileSpec()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSearchGetIndProfileFileSpec(
  CMProfileSearchRef   search,
  UInt32               index,
  FSSpec *             profileFile);


/*
 *  CMProfileIdentifierFolderSearch()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMProfileIdentifierFolderSearch(
  CMProfileIdentifierPtr   ident,
  UInt32 *                 matchedCount,
  CMProfileSearchRef *     searchResult);


/*
 *  CMProfileIdentifierListSearch()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMProfileIdentifierListSearch(
  CMProfileIdentifierPtr   ident,
  CMProfileRef *           profileList,
  UInt32                   listSize,
  UInt32 *                 matchedCount,
  CMProfileRef *           matchedList);


/*
 *  CMIterateColorSyncFolder()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
CMIterateColorSyncFolder(
  CMProfileIterateUPP   proc,
  UInt32 *              seed,
  UInt32 *              count,
  void *                refCon);


/*
 *  NCMUnflattenProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
NCMUnflattenProfile(
  CMProfileLocation *  targetLocation,
  CMFlattenUPP         proc,
  void *               refCon,
  Boolean *            preferredCMMnotfound);


/* Utilities */
/*
 *  CMGetColorSyncFolderSpec()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetColorSyncFolderSpec(
  short     vRefNum,
  Boolean   createFolder,
  short *   foundVRefNum,
  long *    foundDirID);


#if TARGET_OS_WIN32 || TARGET_OS_UNIX
/*
 *  CMGetColorSyncFolderPath()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


#endif  /* TARGET_OS_WIN32 || TARGET_OS_UNIX */

/*
 *  CMGetCWInfo()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */
extern CMError 
CMGetCWInfo(
  CMWorldRef        cw,
  CMCWInfoRecord *  info);


#if TARGET_API_MAC_OS8
/*
 *  CMConvertProfile2to1()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */


#endif  /* TARGET_API_MAC_OS8 */

/*
 *  CMGetPreferredCMM()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
CMGetPreferredCMM(
  OSType *   cmmType,
  Boolean *  preferredCMMnotfound);


/*
 *  CMIterateCMMInfo()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
CMIterateCMMInfo(
  CMMIterateUPP   proc,
  UInt32 *        count,
  void *          refCon);


/*
 *  CMGetColorSyncVersion()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
CMGetColorSyncVersion(UInt32 * version);


/*
 *  CMLaunchControlPanel()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 3.0 and later
 */
extern CMError 
CMLaunchControlPanel(UInt32 flags);


/* ColorSpace conversion functions */
/*
 *  CMConvertXYZToLab()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertXYZToLab(
  const CMColor *     src,
  const CMXYZColor *  white,
  CMColor *           dst,
  UInt32              count);


/*
 *  CMConvertLabToXYZ()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertLabToXYZ(
  const CMColor *     src,
  const CMXYZColor *  white,
  CMColor *           dst,
  UInt32              count);


/*
 *  CMConvertXYZToLuv()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertXYZToLuv(
  const CMColor *     src,
  const CMXYZColor *  white,
  CMColor *           dst,
  UInt32              count);


/*
 *  CMConvertLuvToXYZ()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertLuvToXYZ(
  const CMColor *     src,
  const CMXYZColor *  white,
  CMColor *           dst,
  UInt32              count);


/*
 *  CMConvertXYZToYxy()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertXYZToYxy(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count);


/*
 *  CMConvertYxyToXYZ()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertYxyToXYZ(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count);


/*
 *  CMConvertRGBToHLS()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertRGBToHLS(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count);


/*
 *  CMConvertHLSToRGB()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertHLSToRGB(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count);


/*
 *  CMConvertRGBToHSV()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertRGBToHSV(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count);


/*
 *  CMConvertHSVToRGB()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertHSVToRGB(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count);


/*
 *  CMConvertRGBToGray()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertRGBToGray(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count);


/*
 *  CMConvertXYZToFixedXYZ()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertXYZToFixedXYZ(
  const CMXYZColor *  src,
  CMFixedXYZColor *   dst,
  UInt32              count);


/*
 *  CMConvertFixedXYZToXYZ()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertFixedXYZToXYZ(
  const CMFixedXYZColor *  src,
  CMXYZColor *             dst,
  UInt32                   count);


/*
 *  CMConvertXYZToXYZ()
 *  
 *  Availability:
 *    Mac OS X:         in 3.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMConvertXYZToXYZ(
  const CMColor *         src,
  const CMXYZColor *      srcIlluminant,
  CMColor *               dst,
  const CMXYZColor *      dstIlluminant,
  CMChromaticAdaptation   method,
  UInt32                  count);



/* PS-related */
/*
 *  CMGetPS2ColorSpace()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetPS2ColorSpace(
  CMProfileRef   srcProf,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon,
  Boolean *      preferredCMMnotfound);


/*
 *  CMGetPS2ColorRenderingIntent()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetPS2ColorRenderingIntent(
  CMProfileRef   srcProf,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon,
  Boolean *      preferredCMMnotfound);


/*
 *  CMGetPS2ColorRendering()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetPS2ColorRendering(
  CMProfileRef   srcProf,
  CMProfileRef   dstProf,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon,
  Boolean *      preferredCMMnotfound);


/*
 *  CMGetPS2ColorRenderingVMSize()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetPS2ColorRenderingVMSize(
  CMProfileRef   srcProf,
  CMProfileRef   dstProf,
  UInt32 *       vmSize,
  Boolean *      preferredCMMnotfound);



/* ColorSync 1.0 functions which have parallel 2.0 counterparts */
#if TARGET_API_MAC_OS8
/*
 *  CWNewColorWorld()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */


/*
 *  ConcatenateProfiles()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */


/*
 *  CMBeginMatching()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */


/*
 *  CMDrawMatchedPicture()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */


/*
 *  CMUseProfileComment()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */


/*
 *  CMGetProfileName()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */


/*
 *  CMGetProfileAdditionalDataOffset()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */



/* ProfileResponder definitions */
enum {
  cmSystemDevice                = 'sys ',
  cmGDevice                     = 'gdev'
};

/* ProfileResponder functions */
/*
 *  GetProfile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */


/*
 *  SetProfile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */


/*
 *  SetProfileDescription()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */


/*
 *  GetIndexedProfile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */


/*
 *  DeleteDeviceProfile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */



#endif  /* TARGET_API_MAC_OS8 */


#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __CMAPPLICATION__ */

