/******************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2015 Adobe Systems Incorporated
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Adobe Systems Incorporated and its suppliers, if any. The intellectual and
 * technical concepts contained herein are proprietary to Adobe Systems
 * Incorporated and its suppliers and are protected by trade secret or
 * copyright law. Dissemination of this information or reproduction of this
 * material is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 ******************************************************************************/

/**************************************************************************
 * [PRIVATE BETA] CreativeSync enables seamless multi-app workflows via
 * the included APIs. If you have any questions, please contact us at
 * https://creativesdk.zendesk.com/hc/en-us/requests/new
 *************************************************************************/

#ifndef Adobe360WorkflowActionHeader
#define Adobe360WorkflowActionHeader

#ifndef DMALIB

#import <Foundation/Foundation.h>

/**
 * The action types.
 */
typedef NS_ENUM(NSUInteger, Adobe360WorkflowActionType)
{
    /**
     * Edit action. E.g. applying a filter.
     */
    Adobe360WorkflowActionTypeEdit = 1,
    
    /**
     * Embed action. E.g. sharing a picture.
     */
    Adobe360WorkflowActionTypeEmbed,
    
    /**
     * Capture actions. E.g. taking an image or screenshot.
     */
    Adobe360WorkflowActionTypeCapture,
    
    /**
     * Embed multiple assets action. E.g. share multiple images.
     */
    Adobe360WorkflowActionTypeEmbedN,
    
    /**
     * Capture multiple assets action. E.g. get a set of images.
     */
    Adobe360WorkflowActionTypeCaptureN
};

/**
 * Supported device types
 */
typedef NS_ENUM(NSUInteger, Adobe360WorkflowDeviceType)
{
    /**
     * Unknown. The device type is not know.
     */
    Adobe360WorkflowDeviceTypeUnknown = 0,
    
    /**
     * iPhone and iPod touch.
     */
    Adobe360WorkflowDeviceTypeiPhone,
    
    /**
     * iPad.
     */
    Adobe360WorkflowDeviceTypeiPad,
    
    /**
     * Universal. All devices: iPhone, iPod touch and iPad.
     */
    Adobe360WorkflowDeviceTypeUniversal
};


/**
 * Supported workflow action type & Internet Media Types.
 * Use this class instances & add to supportedActions property to filter out
 * unsupported actions.
 */
@interface Adobe360SupportedAction : NSObject

/**
 * Action type.
 */
@property (assign, nonatomic, readonly) Adobe360WorkflowActionType actionType;

/**
 * Collection of accepted Internet Media Types.
 */
@property (strong, nonatomic, readonly) NSArray *mediaTypes;

/**
 * Method initializes the instance with given Adobe360WorkflowActionType & the Internet Media Types.
 * Examples of Internet Media Type include "image/png", "image/jpeg" etc.
 *
 * @return Initialized instance of Adobe360SupportedAction class.
 */
- (instancetype)initWithActionType:(Adobe360WorkflowActionType)actionType
                        mediaTypes:(NSArray *)mediaTypes;

@end

/**
 * Workflow action input.
 */
@interface Adobe360WorkflowActionInput : NSObject

/**
 * Name of the input.
 */
@property (strong, nonatomic, readonly) NSString *name;

/**
 * Collection of accepted Internet Media Types.
 */
@property (strong, nonatomic, readonly) NSArray *mediaTypes;

/**
 * Creates a new input.
 *
 * @param name  Name of the input. Currently the only supported value is "input". Specifying anyting else has no effect and will be ignored.
 * @param types Internet Media Types supported by this input.
 *
 * @return An input that can be used to create a new 360 Workflow Action.
 */
- (instancetype)initWithName:(NSString *)name mediaTypes:(NSArray *)types;

@end



/**
 * Workflow action output.
 */
@interface Adobe360WorkflowActionOutput : NSObject

/**
 * Name of the output.
 */
@property (strong, nonatomic, readonly) NSString *name;

/**
 * Collection of supported Internet Media Types.
 */
@property (strong, nonatomic, readonly) NSArray *mediaTypes;

/**
 * Creates a new output.
 *
 * @param name  Name of the output. Currently the only supported value is "output". Specifying anything else has no effect and will be ignored.
 * @param types Internet Media Types supported by this input.
 *
 * @return An output that can be used to create a new 360 Workflow Action.
 */
- (instancetype)initWithName:(NSString *)name mediaTypes:(NSArray *)types;

@end

/**
 * Represent an action object defined in the Action Registery.
 *
 * @see https://wiki.corp.adobe.com/display/dma/Action+Registry
 */
@interface Adobe360WorkflowAction : NSObject

/**
 * Unique identifier for the action.
 */
@property (strong, nonatomic, readonly) NSString *actionId;

/**
 * Localized and user-presentable name of the action.
 */
@property (strong, nonatomic, readonly) NSString *name;

/**
 * Localized and user-presentable description of the action.
 */
@property (strong, nonatomic, readonly) NSString *actionDescription;

/**
 * The main type of the action.
 */
@property (assign, nonatomic, readonly) Adobe360WorkflowActionType type;

/**
 * The action subtype.
 */
@property (strong, nonatomic, readonly) NSString *subType;

/**
 * The App Store ID of the app that can perform this action.
 */
@property (strong, nonatomic, readonly) NSString *appId;

/**
 * App group name that is used by the related app.
 */
@property (strong, nonatomic, readonly) NSString *appGroupName;

/**
 * Bundle ID of the related app.
 */
@property (strong, nonatomic, readonly) NSString *bundleId;

/**
 * URL scheme of the app. Could be used to launch the app.
 */
@property (strong, nonatomic, readonly) NSString *URLScheme;

/**
 * Support device for the app.
 */
@property (assign, nonatomic, readonly) Adobe360WorkflowDeviceType deviceType;

/**
 * List of inputs the app provides.
 */
@property (copy, nonatomic, readonly) NSArray *inputs;

/**
 * List of support outputs.
 */
@property (copy, nonatomic, readonly) NSArray *outputs;

/**
 * Deserializes a dictionary representation of an action into a usable instance.
 *
 * @param data The data to deserialize into an action.
 *
 * @return An instance of an action or @c nil if @c data cannot be deserialized or the action is 
 *         for an unsupported platform.
 */
+ (Adobe360WorkflowAction *)actionFromData:(NSDictionary *)data;

/**
 * Converts the action type to a string value.
 *
 * @param actionType The action type to convert.
 *
 * @return A string representation of the action type.
 */
+ (NSString *)stringFromActionType:(Adobe360WorkflowActionType)actionType;

/**
 * Create a new action with the given parameters.
 *
 * @param actionId        Unique identifier for the action.
 * @param name            Name of the action.
 * @param description     Description for the action.
 * @param type            Type of the action.
 * @param subType         SubType of the action.
 * @param appId           The App Store Id of the app.
 * @param appGroupName    The App Group name in which the app participates.
 * @param bundleId        Bundle Id of the app.
 * @param URLScheme       URL scheme used to launch the app.
 * @param supportedDevice Supported device type.
 * @param inputs          Array of Adobe360WorkflowActionInput objects, representing inputs 
 *                        supported by the action.
 * @param outputs         Array of Adobe360WorkflowActionOutput objects, respsenting outputs 
 *                        supported by the action.
 *
 * @return A usable action object.
 */
- (instancetype)initWithId:(NSString *)actionId
                      name:(NSString *)name
               description:(NSString *)description
                      type:(Adobe360WorkflowActionType)type
                   subType:(NSString *)subType
                     appId:(NSString *)appId
              appGroupName:(NSString *)appGroupName
                  bundleId:(NSString *)bundleId
                 URLScheme:(NSString *)URLScheme
                deviceType:(Adobe360WorkflowDeviceType)supportedDevice
                    inputs:(NSArray *)inputs
                   outputs:(NSArray *)outputs;

/**
 * Add an input object to the list of supported inputs.
 *
 * @param input The input object to add to the supported inputs.
 */
- (void)addInput:(Adobe360WorkflowActionInput *)inputToAdd;

/**
 * Add an output object to the list of supported outputs.
 *
 * @param output The output object to add to the supported list.
 */
- (void)addOutput:(Adobe360WorkflowActionOutput *)outputToAdd;

/**
 * Remove an input object from the list of supported inputs.
 *
 * @param inputToRemove Input object to remove from the list.
 */
- (void)removeInput:(Adobe360WorkflowActionInput *)inputToRemove;

/**
 * Remove an output object from the list of supported outputs.
 *
 * @param outputToRemove Output object to remove the list.
 */
- (void)removeOutput:(Adobe360WorkflowActionOutput *)outputToRemove;

/**
 * Retrieves the icon for the app that is providing the action.
 *
 * If the icon image data is not cached locally, an asynchronous network request will be made to 
 * retrieve it. Once the icon has been retrieved it will be cached so any subsequent calls to this 
 * method will succeed without any network calls.
 *
 * @param completionBlock Block to execute when the method completes. If successful, 
 * @c thumbnailData will contain usable data that can be used by an instance of @c UIImage;
 * otherwise, @c error will indicate any potential issues.
 */
- (void)retrieveAppIconOfSize:(CGSize)size onCompletion:(void (^)(UIImage *image, NSError *error))completionBlock;

@end

#endif // !DMALIB

#endif
