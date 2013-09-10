// Analytics.h
// Copyright 2013 Segment.io
// Version 0.6.2 (Do not change this line. It is automatically modified by the build process)

#import <Foundation/Foundation.h>

@interface Analytics : NSObject

@property(nonatomic, strong) NSString *secret;
@property(nonatomic, readonly) NSDictionary *providers;


// Step 1: Initialization
// ----------------------

/*!
 @method

 @abstract
 Creates the shared Analytics instance and initializes it with your Segment.io secret key.

 @param secret        Your Segment.io secret key from the setup guide at https://segment.io

 @discussion
 While developing, we recommend you reset the settings and turn on debug logging right after you initialize the Analytics instance with your secret:

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Initialize your shared Analytics instance.
    [Analytics withSecret:@"YOUR SEGMENT.IO SECRET KEY FROM THE SETUP GUIDE AT HTTPS://SEGMENT.IO"];
    
    // During development: reset the settings cache frequently so that
    // as you change settings on your integrations page, the settings update quickly here.
    [[Analytics sharedAnalytics] reset]; // remove before app store release
    [[Analytics sharedAnalytics] debug:YES]; // if you want to see debug logs
    
    // YOUR OTHER APP LAUNCH CODE HERE....

    return YES;
}

*/
+ (void)initializeWithSecret:(NSString *)secret;





// Step 2: Accessing the Shared Instance
// -------------------------------------

/*!
 @method

 @abstract
 Gets the shared Analytics instance.

 @discussion
 Once you initialize the shared Analytics instance via [Analytics initializeWithSecret:...] you can get the instance at any time like this:

 [Analytics sharedInstance]

 This lets you call any of analytics API methods like this:

 [[Analytics sharedInstance] track:@"Bought a Shirt"];

*/
+ (instancetype)sharedAnalytics;





// Step 3: Implementing the Analytics API 
// --------------------------------------

/*!
 @method

 @abstract
 Associate a user with their unique ID and record traits about them.

 @param userId        A database ID (or email address) for this user. If you don't have a userId
                      but want to record traits, you should pass nil. We will automatically generate
                      a UUID to let you identify "anonymous" users. For more information on how we 
                      generate the UUID and Apple's policies on IDs, see https://segment.io/libraries/ios#ids

 @param traits        A dictionary of traits you know about the user. Things like: email, name, subscriptionPlan, etc.

 @discussion
 When you learn more about who your user is, you can record that information with identify.
 
*/
- (void)identify:(NSString *)userId;
- (void)identify:(NSString *)userId traits:(NSDictionary *)traits;
- (void)identify:(NSString *)userId traits:(NSDictionary *)traits context:(NSDictionary *)context;

/*!
 @method

 @abstract
 Record the actions your users perform.

 @param event         The name of the event you're tracking. We recommend using human-readable names 
                      like `Played a Song` or `Updated Status`.

 @param properties    A dictionary of properties for the event. If the event was 'Added to Shopping Cart', it might
                      have properties like price, productType, etc.

 @discussion
 When a user performs an action in your app, you'll want to track that action for later analysis. Use the event name to say what the user did, and properties to specify any interesting details of the action.
 
*/
- (void)track:(NSString *)event;
- (void)track:(NSString *)event properties:(NSDictionary *)properties;
- (void)track:(NSString *)event properties:(NSDictionary *)properties context:(NSDictionary *)context;

/*!
 @method

 @abstract
 Record the screens or views your users see.

 @param screenTitle   The title of the screen being viewed. We recommend using human-readable names
                      like 'Photo Feed' or 'Completed Purchase Screen'.

 @param properties    A dictionary of properties for the screen view event. If the event was 'Added to Shopping Cart',
                      it might have properties like price, productType, etc.

 @discussion
 When a user views a screen in your app, you'll want to record that here. For some tools like Google Analytics and Flurry, screen views are treated specially, and are different from "events" kind of like "page views" on the web. For services that don't treat "screen views" specially, we map "screen" straight to "track" with the same parameters. For example, Mixpanel doesn't treat "screen views" any differently. So a call to "screen" will be tracked as a normal event in Mixpanel, but get sent to Google Analytics and Flurry as a "screen".
 
*/
- (void)screen:(NSString *)screenTitle;
- (void)screen:(NSString *)screenTitle properties:(NSDictionary *)properties;
- (void)screen:(NSString *)screenTitle properties:(NSDictionary *)properties context:(NSDictionary *)context;



/*!
 @method
 
 @abstract
 Register the given device to receive push notifications from applicable providers.
 
 @discussion
 Some providers (such as Mixpanel) are capable of sending push notification to users based on 
 their traits and actions. This will associate the device token with the current user in providers
 that have this capability. You should call this method with the <code>NSData</code> token passed to
 <code>application:didRegisterForRemoteNotificationsWithDeviceToken:</code>.
 
 @param deviceToken     device token as returned <code>application:didRegisterForRemoteNotificationsWithDeviceToken:</code>
 */
- (void)registerPushDeviceToken:(NSData *)deviceToken;


// Development Tools
// -----------------

/*!
 @method

 @abstract
 Forces an update of your analytics settings, including which services are enabled, API keys and options.

 @discussion
 By default, the SDK will retrieve updated settings (including which services are enabled, API keys and options) on first SDK initialization per device, and on a regular time interval (typically 1 hour). While you integrate the SDK and test you'll probably want to frequently update your analytics settings, espeically if you are playing with the settings on https://segment.io, hence this reset function.

 While developing, we recommend you reset the settings and turn on debug logging right after you initialize the Analytics instance with your secret:

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Initialize your shared Analytics instance.
    [Analytics initializeWithSecret:@"YOUR SEGMENT.IO SECRET KEY FROM THE SETUP GUIDE AT HTTPS://SEGMENT.IO"];
    
    // During development: reset the settings cache frequently so that
    // as you change settings on your integrations page, the settings update quickly here.
    [[Analytics sharedAnalytics] reset]; // remove before app store release
    [[Analytics sharedAnalytics] debug:YES]; // if you want to see debug logs
    
    // Override point for customization after application launch.

    // YOUR OTHER APP LAUNCH CODE HERE

    return YES;
}

*/
- (void)reset;

/*!
 @method

 @abstract
 Enables/disables additional debug logging to help you track down any analytics issues.

 @param showDebugLogs        YES to enable debug logging, NO to disable debug logging.

 @discussion
 By default, the SDK will not log anything to the Xcode output console. If you want to track down an issue affecting your analytics code, or just see that analytics requests are indeed going out, you can enable debug logging with this method.

 While developing, we recommend you reset the settings and turn on debug logging right after you initialize the Analytics instance with your secret:

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Initialize your shared Analytics instance.
    [Analytics initializeWithSecret:@"YOUR SEGMENT.IO SECRET KEY FROM THE SETUP GUIDE AT HTTPS://SEGMENT.IO"];
    
    // During development: reset the settings cache frequently so that
    // as you change settings on your integrations page, the settings update quickly here.
    [[Analytics sharedAnalytics] reset]; // remove before app store release
    [[Analytics sharedAnalytics] debug:YES]; // if you want to see debug logs
    
    // Override point for customization after application launch.

    // YOUR OTHER APP LAUNCH CODE HERE

    return YES;
}

*/
- (void)debug:(BOOL)showDebugLogs;


// Advanced
// --------

/*!
 @method

 @abstract
 Used internally to create an Analytics instance.
*/
- (id)initWithSecret:(NSString *)secret;
+ (NSString *)version;

// Must be called before initializing Analytics in order to successfully register provider
+ (NSDictionary *)registeredProviders;
+ (void)registerProvider:(Class)providerClass withIdentifier:(NSString *)identifer;


@end
