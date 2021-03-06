/*
     File:       CarbonCore/Components.h
 
     Contains:   Component Manager Interfaces.
 
     Version:    CarbonCore-317~6
 
     Copyright:  ? 1991-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __COMPONENTS__
#define __COMPONENTS__

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
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
  kAppleManufacturer            = 'appl', /* Apple supplied components */
  kComponentResourceType        = 'thng', /* a components resource type */
  kComponentAliasResourceType   = 'thga' /* component alias resource type */
};

enum {
  kAnyComponentType             = 0,
  kAnyComponentSubType          = 0,
  kAnyComponentManufacturer     = 0,
  kAnyComponentFlagsMask        = 0
};

enum {
  cmpIsMissing                  = 1L << 29,
  cmpWantsRegisterMessage       = 1L << 31
};

enum {
  kComponentOpenSelect          = -1,   /* ComponentInstance for this open */
  kComponentCloseSelect         = -2,   /* ComponentInstance for this close */
  kComponentCanDoSelect         = -3,   /* selector # being queried */
  kComponentVersionSelect       = -4,   /* no params */
  kComponentRegisterSelect      = -5,   /* no params */
  kComponentTargetSelect        = -6,   /* ComponentInstance for top of call chain */
  kComponentUnregisterSelect    = -7,   /* no params */
  kComponentGetMPWorkFunctionSelect = -8, /* some params */
  kComponentExecuteWiredActionSelect = -9, /* QTAtomContainer actionContainer, QTAtom actionAtom, QTCustomActionTargetPtr target, QTEventRecordPtr event */
  kComponentGetPublicResourceSelect = -10 /* OSType resourceType, short resourceId, Handle *resource */
};

/* Component Resource Extension flags */
enum {
  componentDoAutoVersion        = (1 << 0),
  componentWantsUnregister      = (1 << 1),
  componentAutoVersionIncludeFlags = (1 << 2),
  componentHasMultiplePlatforms = (1 << 3),
  componentLoadResident         = (1 << 4)
};



/* Set Default Component flags */
enum {
  defaultComponentIdentical     = 0,
  defaultComponentAnyFlags      = 1,
  defaultComponentAnyManufacturer = 2,
  defaultComponentAnySubType    = 4,
  defaultComponentAnyFlagsAnyManufacturer = (defaultComponentAnyFlags + defaultComponentAnyManufacturer),
  defaultComponentAnyFlagsAnyManufacturerAnySubType = (defaultComponentAnyFlags + defaultComponentAnyManufacturer + defaultComponentAnySubType)
};

/* RegisterComponentResource flags */
enum {
  registerComponentGlobal       = 1,
  registerComponentNoDuplicates = 2,
  registerComponentAfterExisting = 4,
  registerComponentAliasesOnly  = 8
};


struct ComponentDescription {
  OSType              componentType;          /* A unique 4-byte code indentifying the command set */
  OSType              componentSubType;       /* Particular flavor of this instance */
  OSType              componentManufacturer;  /* Vendor indentification */
  unsigned long       componentFlags;         /* 8 each for Component,Type,SubType,Manuf/revision */
  unsigned long       componentFlagsMask;     /* Mask for specifying which flags to consider in search, zero during registration */
};
typedef struct ComponentDescription     ComponentDescription;

struct ResourceSpec {
  OSType              resType;                /* 4-byte code    */
  short               resID;                  /*         */
};
typedef struct ResourceSpec             ResourceSpec;
struct ComponentResource {
  ComponentDescription  cd;                   /* Registration parameters */
  ResourceSpec        component;              /* resource where Component code is found */
  ResourceSpec        componentName;          /* name string resource */
  ResourceSpec        componentInfo;          /* info string resource */
  ResourceSpec        componentIcon;          /* icon resource */
};
typedef struct ComponentResource        ComponentResource;
typedef ComponentResource *             ComponentResourcePtr;
typedef ComponentResourcePtr *          ComponentResourceHandle;
struct ComponentPlatformInfo {
  long                componentFlags;         /* flags of Component */
  ResourceSpec        component;              /* resource where Component code is found */
  short               platformType;           /* gestaltSysArchitecture result */
};
typedef struct ComponentPlatformInfo    ComponentPlatformInfo;
struct ComponentResourceExtension {
  long                componentVersion;       /* version of Component */
  long                componentRegisterFlags; /* flags for registration */
  short               componentIconFamily;    /* resource id of Icon Family */
};
typedef struct ComponentResourceExtension ComponentResourceExtension;
struct ComponentPlatformInfoArray {
  long                count;
  ComponentPlatformInfo  platformArray[1];
};
typedef struct ComponentPlatformInfoArray ComponentPlatformInfoArray;
struct ExtComponentResource {
  ComponentDescription  cd;                   /* registration parameters */
  ResourceSpec        component;              /* resource where Component code is found */
  ResourceSpec        componentName;          /* name string resource */
  ResourceSpec        componentInfo;          /* info string resource */
  ResourceSpec        componentIcon;          /* icon resource */
  long                componentVersion;       /* version of Component */
  long                componentRegisterFlags; /* flags for registration */
  short               componentIconFamily;    /* resource id of Icon Family */
  long                count;                  /* elements in platformArray */
  ComponentPlatformInfo  platformArray[1];
};
typedef struct ExtComponentResource     ExtComponentResource;
typedef ExtComponentResource *          ExtComponentResourcePtr;
typedef ExtComponentResourcePtr *       ExtComponentResourceHandle;
struct ComponentAliasResource {
  ComponentResource   cr;                     /* Registration parameters */
  ComponentDescription  aliasCD;              /* component alias description */
};
typedef struct ComponentAliasResource   ComponentAliasResource;
/*  Structure received by Component:        */
struct ComponentParameters {
  UInt8               flags;                  /* call modifiers: sync/async, deferred, immed, etc */
  UInt8               paramSize;              /* size in bytes of actual parameters passed to this call */
  short               what;                   /* routine selector, negative for Component management calls */
  long                params[1];              /* actual parameters for the indicated routine */
};
typedef struct ComponentParameters      ComponentParameters;
struct ComponentRecord {
  long                data[1];
};
typedef struct ComponentRecord          ComponentRecord;
typedef ComponentRecord *               Component;
struct ComponentInstanceRecord {
  long                data[1];
};
typedef struct ComponentInstanceRecord  ComponentInstanceRecord;
typedef ComponentInstanceRecord *       ComponentInstance;
struct RegisteredComponentRecord {
  long                data[1];
};
typedef struct RegisteredComponentRecord RegisteredComponentRecord;
typedef RegisteredComponentRecord *     RegisteredComponentRecordPtr;
struct RegisteredComponentInstanceRecord {
  long                data[1];
};
typedef struct RegisteredComponentInstanceRecord RegisteredComponentInstanceRecord;
typedef RegisteredComponentInstanceRecord * RegisteredComponentInstanceRecordPtr;
typedef long                            ComponentResult;
enum {
  platform68k                   = 1,    /* platform type (response from gestaltComponentPlatform) */
  platformPowerPC               = 2,    /* (when gestaltComponentPlatform is not implemented, use */
  platformInterpreted           = 3,    /* gestaltSysArchitecture) */
  platformWin32                 = 4,
  platformPowerPCNativeEntryPoint = 5
};

enum {
  platformIRIXmips              = 1000,
  platformSunOSsparc            = 1100,
  platformSunOSintel            = 1101,
  platformLinuxppc              = 1200,
  platformLinuxintel            = 1201,
  platformAIXppc                = 1300,
  platformNeXTIntel             = 1400,
  platformNeXTppc               = 1401,
  platformNeXTsparc             = 1402,
  platformNeXT68k               = 1403,
  platformMacOSx86              = 1500
};

enum {
  mpWorkFlagDoWork              = (1 << 0),
  mpWorkFlagDoCompletion        = (1 << 1),
  mpWorkFlagCopyWorkBlock       = (1 << 2),
  mpWorkFlagDontBlock           = (1 << 3),
  mpWorkFlagGetProcessorCount   = (1 << 4),
  mpWorkFlagGetIsRunning        = (1 << 6)
};

enum {
  cmpAliasNoFlags               = 0,
  cmpAliasOnlyThisFile          = 1
};

struct ComponentMPWorkFunctionHeaderRecord {
  UInt32              headerSize;
  UInt32              recordSize;
  UInt32              workFlags;
  UInt16              processorCount;
  UInt8               unused;
  UInt8               isRunning;
};
typedef struct ComponentMPWorkFunctionHeaderRecord ComponentMPWorkFunctionHeaderRecord;
typedef ComponentMPWorkFunctionHeaderRecord * ComponentMPWorkFunctionHeaderRecordPtr;
typedef CALLBACK_API( ComponentResult , ComponentMPWorkFunctionProcPtr )(void *globalRefCon, ComponentMPWorkFunctionHeaderRecordPtr header);
typedef CALLBACK_API( ComponentResult , ComponentRoutineProcPtr )(ComponentParameters *cp, Handle componentStorage);
typedef CALLBACK_API( OSErr , GetMissingComponentResourceProcPtr )(Component c, OSType resType, short resID, void *refCon, Handle *resource);
typedef STACK_UPP_TYPE(ComponentMPWorkFunctionProcPtr)          ComponentMPWorkFunctionUPP;
typedef STACK_UPP_TYPE(ComponentRoutineProcPtr)                 ComponentRoutineUPP;
typedef STACK_UPP_TYPE(GetMissingComponentResourceProcPtr)      GetMissingComponentResourceUPP;
/*
    The parameter list for each ComponentFunction is unique. It is
    therefore up to users to create the appropriate procInfo for their
    own ComponentFunctions where necessary.
*/
typedef UniversalProcPtr                ComponentFunctionUPP;
/*
 *  NewComponentFunctionUPP()
 *  
 *  Discussion:
 *    For use in writing a Carbon compliant Component.  It is used to
 *    create a ComponentFunctionUPP needed to call
 *    CallComponentFunction in the Components dispatch routine.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ComponentFunctionUPP 
NewComponentFunctionUPP(
  ProcPtr        userRoutine,
  ProcInfoType   procInfo);


/*
 *  DisposeComponentFunctionUPP()
 *  
 *  Discussion:
 *    For use in writing a Carbon compliant Component.  It is used to
 *    dispose of a ComponentFunctionUPP created by
 *    NewComponentFunctionUPP.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void 
DisposeComponentFunctionUPP(ComponentFunctionUPP userUPP);



#if TARGET_RT_MAC_CFM
/* 
    CallComponentUPP is a global variable exported from InterfaceLib.
    It is the ProcPtr passed to CallUniversalProc to manually call a component function.
*/
/*
 *  CallComponentUPP
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UniversalProcPtr CallComponentUPP;
#endif

#define ComponentCallNow( callNumber, paramSize ) \
    FIVEWORDINLINE( 0x2F3C,paramSize,callNumber,0x7000,0xA82A )

/********************************************************
*                                                       *
*               APPLICATION LEVEL CALLS                 *
*                                                       *
********************************************************/
/********************************************************
* Component Database Add, Delete, and Query Routines
********************************************************/
/*
 *  RegisterComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Component 
RegisterComponent(
  ComponentDescription *  cd,
  ComponentRoutineUPP     componentEntryPoint,
  short                   global,
  Handle                  componentName,
  Handle                  componentInfo,
  Handle                  componentIcon);


/*
 *  RegisterComponentResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Component 
RegisterComponentResource(
  ComponentResourceHandle   cr,
  short                     global);


/*
 *  UnregisterComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
UnregisterComponent(Component aComponent);


/*
 *  FindNextComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Component 
FindNextComponent(
  Component               aComponent,
  ComponentDescription *  looking);


/*
 *  CountComponents()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
CountComponents(ComponentDescription * looking);


/*
 *  GetComponentInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetComponentInfo(
  Component               aComponent,
  ComponentDescription *  cd,
  Handle                  componentName,
  Handle                  componentInfo,
  Handle                  componentIcon);


/*
 *  GetComponentListModSeed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetComponentListModSeed(void);


/*
 *  GetComponentTypeModSeed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetComponentTypeModSeed(OSType componentType);


/********************************************************
* Component Instance Allocation and dispatch routines
********************************************************/
/*
 *  OpenAComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
OpenAComponent(
  Component            aComponent,
  ComponentInstance *  ci);


/*
 *  OpenComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentInstance 
OpenComponent(Component aComponent);


/*
 *  CloseComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CloseComponent(ComponentInstance aComponentInstance);


/*
 *  GetComponentInstanceError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetComponentInstanceError(ComponentInstance aComponentInstance);


/********************************************************
* Component aliases
********************************************************/
/*
 *  ResolveComponentAlias()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Component 
ResolveComponentAlias(Component aComponent);


/********************************************************
* Component public resources and public string lists
********************************************************/
/* Note: GetComponentPublicResource returns a Handle, not a resource.  The caller must dispose it with DisposeHandle. */
/*
 *  GetComponentPublicResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 4.0 and later
 */
extern OSErr 
GetComponentPublicResource(
  Component   aComponent,
  OSType      resourceType,
  short       resourceID,
  Handle *    theResource);


/*
 *  GetComponentPublicResourceList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 4.0 and later
 */
extern OSErr 
GetComponentPublicResourceList(
  OSType                           resourceType,
  short                            resourceID,
  long                             flags,
  ComponentDescription *           cd,
  GetMissingComponentResourceUPP   missingProc,
  void *                           refCon,
  void *                           atomContainerPtr);


/*
 *  GetComponentPublicIndString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 4.0 and later
 */
extern OSErr 
GetComponentPublicIndString(
  Component   aComponent,
  Str255      theString,
  short       strListID,
  short       index);


/********************************************************
*                                                       *
*                   CALLS MADE BY COMPONENTS            *
*                                                       *
********************************************************/
/********************************************************
* Component Management routines
********************************************************/
/*
 *  SetComponentInstanceError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetComponentInstanceError(
  ComponentInstance   aComponentInstance,
  OSErr               theError);


/*
 *  GetComponentRefcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetComponentRefcon(Component aComponent);


/*
 *  SetComponentRefcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetComponentRefcon(
  Component   aComponent,
  long        theRefcon);


/*
 *  OpenComponentResFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
OpenComponentResFile(Component aComponent);


/*
 *  OpenAComponentResFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
OpenAComponentResFile(
  Component   aComponent,
  short *     resRef);


/*
 *  CloseComponentResFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CloseComponentResFile(short refnum);


/* Note: GetComponentResource returns a Handle, not a resource.  The caller must dispose it with DisposeHandle. */
/*
 *  GetComponentResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetComponentResource(
  Component   aComponent,
  OSType      resType,
  short       resID,
  Handle *    theResource);


/*
 *  GetComponentIndString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetComponentIndString(
  Component   aComponent,
  Str255      theString,
  short       strListID,
  short       index);


/********************************************************
* Component Instance Management routines
********************************************************/
/*
 *  GetComponentInstanceStorage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Handle 
GetComponentInstanceStorage(ComponentInstance aComponentInstance);


/*
 *  SetComponentInstanceStorage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetComponentInstanceStorage(
  ComponentInstance   aComponentInstance,
  Handle              theStorage);


/*
 *  GetComponentInstanceA5()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  SetComponentInstanceA5()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */


/*
 *  CountComponentInstances()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
CountComponentInstances(Component aComponent);


/* useful helper routines for convenient method dispatching */
/*
 *  CallComponentFunction()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
CallComponentFunction(
  ComponentParameters *  params,
  ComponentFunctionUPP   func);


/*
 *  CallComponentFunctionWithStorage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
CallComponentFunctionWithStorage(
  Handle                 storage,
  ComponentParameters *  params,
  ComponentFunctionUPP   func);


#if TARGET_CPU_PPC
/*
 *  CallComponentFunctionWithStorageProcInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 */
extern long 
CallComponentFunctionWithStorageProcInfo(
  Handle                 storage,
  ComponentParameters *  params,
  ProcPtr                func,
  ProcInfoType           funcProcInfo);


#else
#define CallComponentFunctionWithStorageProcInfo(storage, params, func, funcProcInfo ) CallComponentFunctionWithStorage(storage, params, func)

#endif  /* TARGET_CPU_PPC */

/*
 *  DelegateComponentCall()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
DelegateComponentCall(
  ComponentParameters *  originalParams,
  ComponentInstance      ci);


/*
 *  SetDefaultComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetDefaultComponent(
  Component   aComponent,
  short       flags);


/*
 *  OpenDefaultComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentInstance 
OpenDefaultComponent(
  OSType   componentType,
  OSType   componentSubType);


/*
 *  OpenADefaultComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
OpenADefaultComponent(
  OSType               componentType,
  OSType               componentSubType,
  ComponentInstance *  ci);


/*
 *  CaptureComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Component 
CaptureComponent(
  Component   capturedComponent,
  Component   capturingComponent);


/*
 *  UncaptureComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
UncaptureComponent(Component aComponent);


/*
 *  RegisterComponentResourceFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
RegisterComponentResourceFile(
  short   resRefNum,
  short   global);


/*
 *  GetComponentIconSuite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetComponentIconSuite(
  Component   aComponent,
  Handle *    iconSuite);


/*
 * These calls allow you to register a file system entity.  The
 * Component Manager will "do the right thing" with the entity,
 * whether it is a standard resource fork based CFM component, CFM
 * bundle, mach-o bundle, or packaged bundle.  
 *
 * The *Entries calls allow you to specify a component description
 * which will be used to register selective components.  (Passing
 * NULL, 0 means to register all components.  
 */
/*
 *  RegisterComponentFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
RegisterComponentFile(
  const FSSpec *  spec,
  short           global);


/*
 *  RegisterComponentFileEntries()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
RegisterComponentFileEntries(
  const FSSpec *                spec,
  short                         global,
  const ComponentDescription *  toRegister,          /* can be NULL */
  UInt32                        registerCount);


/*
 *  RegisterComponentFileRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
RegisterComponentFileRef(
  const FSRef *  ref,
  short          global);


/*
 *  RegisterComponentFileRefEntries()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
RegisterComponentFileRefEntries(
  const FSRef *                 ref,
  short                         global,
  const ComponentDescription *  toRegister,          /* can be NULL */
  UInt32                        registerCount);


/********************************************************
*                                                       *
*           Direct calls to the Components              *
*                                                       *
********************************************************/
/* Old style names*/

/*
 *  ComponentFunctionImplemented()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
ComponentFunctionImplemented(
  ComponentInstance   ci,
  short               ftnNumber);


/*
 *  GetComponentVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetComponentVersion(ComponentInstance ci);


/*
 *  ComponentSetTarget()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
ComponentSetTarget(
  ComponentInstance   ci,
  ComponentInstance   target);


/* New style names*/

/*
 *  CallComponentOpen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentOpen(
  ComponentInstance   ci,
  ComponentInstance   self);


/*
 *  CallComponentClose()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentClose(
  ComponentInstance   ci,
  ComponentInstance   self);


/*
 *  CallComponentCanDo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentCanDo(
  ComponentInstance   ci,
  short               ftnNumber);


/*
 *  CallComponentVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentVersion(ComponentInstance ci);


/*
 *  CallComponentRegister()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentRegister(ComponentInstance ci);


/*
 *  CallComponentTarget()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentTarget(
  ComponentInstance   ci,
  ComponentInstance   target);


/*
 *  CallComponentUnregister()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentUnregister(ComponentInstance ci);


/*
 *  CallComponentGetMPWorkFunction()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
CallComponentGetMPWorkFunction(
  ComponentInstance             ci,
  ComponentMPWorkFunctionUPP *  workFunction,
  void **                       refCon);


/*
 *  CallComponentGetPublicResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib via QuickTime 4.0 and later
 */
extern ComponentResult 
CallComponentGetPublicResource(
  ComponentInstance   ci,
  OSType              resourceType,
  short               resourceID,
  Handle *            resource);



/*
    CallComponentDispatch is a CarbonLib routine that replaces CallComponent inline glue
    to call a component function.
 */
/*
 *  CallComponentDispatch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
CallComponentDispatch(ComponentParameters * cp);



/* UPP call backs */
/*
 *  NewComponentMPWorkFunctionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ComponentMPWorkFunctionUPP
NewComponentMPWorkFunctionUPP(ComponentMPWorkFunctionProcPtr userRoutine);

/*
 *  NewComponentRoutineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ComponentRoutineUPP
NewComponentRoutineUPP(ComponentRoutineProcPtr userRoutine);

/*
 *  NewGetMissingComponentResourceUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern GetMissingComponentResourceUPP
NewGetMissingComponentResourceUPP(GetMissingComponentResourceProcPtr userRoutine);

/*
 *  DisposeComponentMPWorkFunctionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeComponentMPWorkFunctionUPP(ComponentMPWorkFunctionUPP userUPP);

/*
 *  DisposeComponentRoutineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeComponentRoutineUPP(ComponentRoutineUPP userUPP);

/*
 *  DisposeGetMissingComponentResourceUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeGetMissingComponentResourceUPP(GetMissingComponentResourceUPP userUPP);

/*
 *  InvokeComponentMPWorkFunctionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ComponentResult
InvokeComponentMPWorkFunctionUPP(
  void *                                  globalRefCon,
  ComponentMPWorkFunctionHeaderRecordPtr  header,
  ComponentMPWorkFunctionUPP              userUPP);

/*
 *  InvokeComponentRoutineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ComponentResult
InvokeComponentRoutineUPP(
  ComponentParameters *  cp,
  Handle                 componentStorage,
  ComponentRoutineUPP    userUPP);

/*
 *  InvokeGetMissingComponentResourceUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeGetMissingComponentResourceUPP(
  Component                       c,
  OSType                          resType,
  short                           resID,
  void *                          refCon,
  Handle *                        resource,
  GetMissingComponentResourceUPP  userUPP);

/* ProcInfos */

/* MixedMode ProcInfo constants for component calls */
enum {
    uppComponentFunctionImplementedProcInfo    = 0x000002F0,
    uppGetComponentVersionProcInfo             = 0x000000F0,
    uppComponentSetTargetProcInfo              = 0x000003F0,
    uppCallComponentOpenProcInfo               = 0x000003F0,
    uppCallComponentCloseProcInfo              = 0x000003F0,
    uppCallComponentCanDoProcInfo              = 0x000002F0,
    uppCallComponentVersionProcInfo            = 0x000000F0,
    uppCallComponentRegisterProcInfo           = 0x000000F0,
    uppCallComponentTargetProcInfo             = 0x000003F0,
    uppCallComponentUnregisterProcInfo         = 0x000000F0,
    uppCallComponentGetMPWorkFunctionProcInfo  = 0x00000FF0,
    uppCallComponentGetPublicResourceProcInfo  = 0x00003BF0
};







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

#endif /* __COMPONENTS__ */

