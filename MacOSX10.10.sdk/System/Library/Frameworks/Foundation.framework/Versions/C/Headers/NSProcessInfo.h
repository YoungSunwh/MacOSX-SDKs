/*	NSProcessInfo.h
	Copyright (c) 1994-2014, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

enum {	/* Constants returned by -operatingSystem */
    NSWindowsNTOperatingSystem = 1,
    NSWindows95OperatingSystem,
    NSSolarisOperatingSystem,
    NSHPUXOperatingSystem,
    NSMACHOperatingSystem,
    NSSunOSOperatingSystem,
    NSOSF1OperatingSystem
} NS_ENUM_DEPRECATED(10_0, 10_10, 2_0, 8_0);

typedef struct {
    NSInteger majorVersion;
    NSInteger minorVersion;
    NSInteger patchVersion;
} NSOperatingSystemVersion;

@class NSArray, NSString, NSDictionary;

@interface NSProcessInfo : NSObject {
@private
    NSDictionary	*environment;
    NSArray		*arguments;
    NSString		*hostName;
    NSString		*name;
    NSInteger		automaticTerminationOptOutCounter;
}

+ (NSProcessInfo *)processInfo;

@property (readonly, copy) NSDictionary *environment;
@property (readonly, copy) NSArray *arguments;
@property (readonly, copy) NSString *hostName;
@property (copy) NSString *processName;
@property (readonly) int processIdentifier;

@property (readonly, copy) NSString *globallyUniqueString;

- (NSUInteger)operatingSystem NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "-operatingSystem always returns NSMACHOperatingSystem, use -operatingSystemVersion or -isOperatingSystemAtLeastVersion: instead");
- (NSString *)operatingSystemName NS_DEPRECATED(10_0, 10_10, 2_0, 8_0, "-operatingSystemName always returns NSMACHOperatingSystem, use -operatingSystemVersionString instead");

	/* Human readable, localized; appropriate for displaying to user or using in bug emails and such; NOT appropriate for parsing */
@property (readonly, copy) NSString *operatingSystemVersionString;

@property (readonly) NSOperatingSystemVersion operatingSystemVersion NS_AVAILABLE(10_10, 8_0);

@property (readonly) NSUInteger processorCount NS_AVAILABLE(10_5, 2_0);
@property (readonly) NSUInteger activeProcessorCount NS_AVAILABLE(10_5, 2_0);
@property (readonly) unsigned long long physicalMemory NS_AVAILABLE(10_5, 2_0);

- (BOOL) isOperatingSystemAtLeastVersion:(NSOperatingSystemVersion)version NS_AVAILABLE(10_10, 8_0);
@property (readonly) NSTimeInterval systemUptime NS_AVAILABLE(10_6, 4_0);

/* Disable or reenable the ability to be quickly killed. The default implementations of these methods increment or decrement, respectively, a counter whose value is 1 when the process is first created. When the counter's value is 0 the application is considered to be safely killable and may be killed by the operating system without any notification or event being sent to the process first. If an application's Info.plist has an NSSupportsSuddenTermination entry whose value is true then NSApplication invokes -enableSuddenTermination automatically during application launch, which typically renders the process killable right away. You can also manually invoke -enableSuddenTermination right away in, for example, agents or daemons that don't depend on AppKit. After that, you can invoke these methods whenever the process has work it must do before it terminates. For example:
 - NSUserDefaults uses these to prevent process killing between the time at which a default has been set and the time at which the preferences file including that default has been written to disk.
 - NSDocument uses these to prevent process killing between the time at which the user has made a change to a document and the time at which the user's change has been written to disk.
 - You can use these whenever your application defers work that must be done before the application terminates. If for example your application ever defers writing something to disk, and it has an NSSupportsSuddenTermination entry in its Info.plist so as not to contribute to user-visible delays at logout or shutdown time, it must invoke -disableSuddenTermination when the writing is first deferred and -enableSuddenTermination after the writing is actually done.
 */
- (void)disableSuddenTermination NS_AVAILABLE(10_6, NA);
- (void)enableSuddenTermination NS_AVAILABLE(10_6, NA);

/*
 * Increment or decrement the counter tracking the number of automatic quit opt-out requests. When this counter is greater than zero, the app will be considered 'active' and ineligible for automatic termination.
 * An example of using this would be disabling autoquitting when the user of an instant messaging application signs on, due to it requiring a background connection to be maintained even if the app is otherwise inactive.
 * Each pair of calls should have a matching "reason" argument, which can be used to easily track why an application is or is not automatically terminable.
 * A given reason can be used more than once at the same time (for example: two files are transferring over the network, each one disables automatic termination with the reason @"file transfer in progress")
 */
- (void)disableAutomaticTermination:(NSString *)reason NS_AVAILABLE(10_7, NA);
- (void)enableAutomaticTermination:(NSString *)reason NS_AVAILABLE(10_7, NA);

/*
 * Marks the calling app as supporting automatic termination. Without calling this or setting the equivalent Info.plist key (NSSupportsAutomaticTermination), the above methods (disableAutomaticTermination:/enableAutomaticTermination:) have no effect,
 * although the counter tracking automatic termination opt-outs is still kept up to date to ensure correctness if this is called later. Currently, passing NO has no effect.
 * This should be called during -applicationDidFinishLaunching or earlier.
 */
@property BOOL automaticTerminationSupportEnabled NS_AVAILABLE(10_7, NA);

@end

/*
 The system has heuristics to improve battery life, performance, and responsiveness of applications for the benefit of the user. This API can be used to give hints to the system that your application has special requirements. In response to creating one of these activities, the system will disable some or all of the heuristics so your application can finish quickly while still providing responsive behavior if the user needs it.
 
 These activities can be used when your application is performing a long-running operation. If the activity can take different amounts of time (for example, calculating the next move in a chess game), it should use this API. This will ensure correct behavior when the amount of data or the capabilities of the user's computer varies. You should put your activity into one of two major categories:
 
 User initiated: These are finite length activities that the user has explicitly started. Examples include exporting or downloading a user specified file.
 
 Background: These are finite length activities that are part of the normal operation of your application but are not explicitly started by the user. Examples include autosaving, indexing, and automatic downloading of files.
 
 In addition, if your application requires high priority IO, you can include the 'NSActivityLatencyCritical' flag (using a bitwise or). This should be reserved for activities like audio or video recording.
 
 If your activity takes place synchronously inside an event callback on the main thread, you do not need to use this API.
 
 Be aware that failing to end these activities for an extended period of time can have significant negative impacts to the performance of your user's computer, so be sure to use only the minimum amount of time required. User preferences may override your application???s request.
 
 This API can also be used to control auto termination or sudden termination. 
 
    id activity = [[NSProcessInfo processInfo] beginActivityWithOptions:NSActivityAutomaticTerminationDisabled reason:@"Good Reason"];
    // work
    [[NSProcessInfo processInfo] endActivity:activity];
 
 is equivalent to:
 
    [[NSProcessInfo processInfo] disableAutomaticTermination:@"Good Reason"];
    // work
    [[NSProcessInfo processInfo] enableAutomaticTermination:@"Good Reason"]
 
 Since this API returns an object, it may be easier to pair begins and ends. If the object is deallocated before the -endActivity: call, the activity will be automatically ended.
 
 This API also provides a mechanism to disable system-wide idle sleep and display idle sleep. These can have a large impact on the user experience, so be sure not to forget to end activities that disable sleep (including NSActivityUserInitiated).
 
 */

typedef NS_OPTIONS(uint64_t, NSActivityOptions) {
    // To include one of these individual flags in one of the sets, use bitwise or:
    //   NSActivityUserInitiated | NSActivityIdleDisplaySleepDisabled
    // (this may be used during a presentation, for example)
    
    // To exclude from one of the sets, use bitwise and with not:
    //   NSActivityUserInitiated & ~NSActivitySuddenTerminationDisabled
    // (this may be used during a user intiated action that may be safely terminated with no application interaction in case of logout)
    
    // Used for activities that require the screen to stay powered on.
    NSActivityIdleDisplaySleepDisabled = (1ULL << 40),
    
    // Used for activities that require the computer to not idle sleep. This is included in NSActivityUserInitiated.
    NSActivityIdleSystemSleepDisabled = (1ULL << 20),
    
    // Prevents sudden termination. This is included in NSActivityUserInitiated.
    NSActivitySuddenTerminationDisabled = (1ULL << 14),
    
    // Prevents automatic termination. This is included in NSActivityUserInitiated.
    NSActivityAutomaticTerminationDisabled = (1ULL << 15),
    
    // ----
    // Sets of options.
    
    // App is performing a user-requested action.
    NSActivityUserInitiated = (0x00FFFFFFULL | NSActivityIdleSystemSleepDisabled),
    NSActivityUserInitiatedAllowingIdleSystemSleep = (NSActivityUserInitiated & ~NSActivityIdleSystemSleepDisabled),
    
    // App has initiated some kind of work, but not as the direct result of user request.
    NSActivityBackground = 0x000000FFULL,
    
    // Used for activities that require the highest amount of timer and I/O precision available. Very few applications should need to use this constant.
    NSActivityLatencyCritical = 0xFF00000000ULL,
} NS_ENUM_AVAILABLE(10_9, 7_0);

@interface NSProcessInfo ()
/*
 * Pass in an activity to this API, and a non-NULL, non-empty reason string. Indicate completion of the activity by calling the corresponding endActivity: method with the result of the beginActivityWithOptions:reason: method. The reason string is used for debugging.
 */
- (id <NSObject>)beginActivityWithOptions:(NSActivityOptions)options reason:(NSString *)reason NS_AVAILABLE(10_9, 7_0);

/*
 * The argument to this method is the result of beginActivityWithOptions:reason:.
 */
- (void)endActivity:(id <NSObject>)activity NS_AVAILABLE(10_9, 7_0);

/*
 * Synchronously perform an activity. The activity will be automatically ended after your block argument returns. The reason string is used for debugging.
 */
- (void)performActivityWithOptions:(NSActivityOptions)options reason:(NSString *)reason usingBlock:(void (^)(void))block NS_AVAILABLE(10_9, 7_0);

@end

// Describes the current thermal state of the system.
typedef NS_ENUM(NSInteger, NSProcessInfoThermalState) {
    // No corrective action is needed.
    NSProcessInfoThermalStateNominal,
    
    // The system has reached a state where fans may become audible.
    NSProcessInfoThermalStateFair,

    // Fans are running at maximum speed, system performance maybe impacted. Recommendation: reduce application's usage of CPU, GPU and I/O, if possible. Switch to lower quality visual effects, reduce frame rates.
    NSProcessInfoThermalStateSerious,
    
    // System performance is significantly impacted and the Mac needs to cool down. Recommendation: reduce application's usage of CPU, GPU, and I/O to the minimum level needed to respond to user actions. Consider stopping use of camera and other peripherals if your application is using them.
    NSProcessInfoThermalStateCritical
} NS_ENUM_AVAILABLE(10_10_3, NA);

@interface NSProcessInfo ()

// Retrieve the current thermal state of the system. On systems where thermal state is unknown or unsupported, the value returned from the thermalState property is always NSProcessInfoThermalStateNominal.
@property (readonly) NSProcessInfoThermalState thermalState NS_AVAILABLE(10_10_3, NA);

@end

/*
 This notification is posted once the thermal state of the system has changed. Once the notification is posted, use the thermalState property to retrieve the current thermal state of the system.
 
 You can use this opportunity to take corrective action in your application to help cool the system down. Work that could be done in the background or at opportunistic times should be using the Quality of Service levels in NSOperation or the NSBackgroundActivityScheduler API.
 
 This notification is posted on the global dispatch queue. Register for it using the default notification center. The object associated with the notification is +[NSProcessInfo processInfo].
*/
FOUNDATION_EXTERN NSString * const NSProcessInfoThermalStateDidChangeNotification NS_AVAILABLE(10_10_3, NA);

