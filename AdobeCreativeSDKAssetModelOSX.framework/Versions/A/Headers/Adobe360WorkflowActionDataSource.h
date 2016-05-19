/*************************************************************************
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 *  Copyright 2015 Adobe Systems Incorporated
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by all applicable intellectual property
 * laws, including trade secret and copyright laws.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/

/**************************************************************************
 * [PRIVATE BETA] CreativeSync enables seamless multi-app workflows via
 * the included APIs. If you have any questions, please contact us at
 * https://creativesdk.zendesk.com/hc/en-us/requests/new
 *************************************************************************/

#ifndef Adobe360WorkflowActionDataSourceHeader
#define Adobe360WorkflowActionDataSourceHeader

#import <Foundation/Foundation.h>

@class Adobe360Asset;
@class Adobe360Context;
@class Adobe360Message;
@class Adobe360WorkflowAction;
@class AdobeDCXComposite;

/*
 * This block is called for every action in the action registry & the dynamically
 * added actions as well. A positve value prioritizes the action. Return 0 or negative value if
 * the action need not be prioritized.
 *
 * For example, if the values are 25, 3, 100, -1. The actions corresponding to positive values are
 * ordered in the descending order 100 will be first action, next 25 & then 3. The action with -1
 * will be placed in the regular section below the priotrized section.
 */
typedef NSInteger (^adobe360ActionPriorityBlock) (Adobe360WorkflowAction *action);

@protocol Adobe360WorkflowActionDataSourceDelegate <NSObject>

@optional

/*
 * Delegate is called to inform that the action registry is either starting to load or
 * is going to refresh.
 */
- (void)willLoadActionRegistry;

/*
 * Delegate is called to inform that the action registry completed loading or
 * completed refreshing.
 */
- (void)didLoadActionRegistry;

/*
 * Delegate is called when the data source fails to load the action registry.
 */
- (void)didFailToLoadActionRegistryWithError:(NSError *)error;

@end


/**
 * A data source wrapper around the action registry data. Provides data fetching
 * and configurable sorting and filtering of the data.
 */
@interface Adobe360WorkflowActionDataSource : NSObject

/**
 * The delegate for data source loading events.
 */
@property (weak, nonatomic) id <Adobe360WorkflowActionDataSourceDelegate> dataSourceDelegate;

/**
 * A list of action types & corresponding media types explicitly supported.
 * Use Adobe360SupportedAction instances to specify supported actions.
 */
@property (copy, nonatomic) NSArray *supportedActionTypes;

/**
 * A list of NSStrings matching the subtypes to show explicitly. By default, this is empty, and
 * the registry will only return a list of values that do not have a specified subtype.
 */
@property (copy, nonatomic) NSArray *whitelistedSubTypes;

/**
 * A list of NSStrings matching the action ids to show explicitly. By default, this is empty, and
 * the registry will only return a list of general values that do not have a specified subtype.
 *
 * If this is specified, the whitelistedSubTypes property will be ignored.
 */
@property (copy, nonatomic) NSArray *whitelistedActionIds;

/*
 * This block is called for every action in the action registry & the dynamically
 * added actions as well. A positve value prioritizes the action. Return 0 or negative value if
 * the action need not be prioritized.
 *
 * For example, if the values are 25, 3, 100, -1. The actions corresponding to positive values are
 * ordered in the descending order 100 will be first action, next 25 & then 3. The action with -1
 * will be placed in the regular section below the priotrized section.
 */
@property (copy, nonatomic) adobe360ActionPriorityBlock prioritizeBlock;

/**
 * Set to YES to hide general actions as well the types explicitly listed by the whitelist arrays.
 * If NO, general actions, or actions without a subtype and other default actions, will always be 
 * shown below the list of specific actions.
 *
 * NO by default.
 */
@property (assign, nonatomic) BOOL showOnlyWhitelistedActions;

/**
 * The unfiltered list of actions from the service and explicitly specified. Sorted by
 * frequency of action selection.
 *
 * This will peform a sort under the hood, so it shouldn't be called too often.
 *
 * @return An NSArray of Adobe360WorkflowAction objects.
 */
- (NSArray *)rawActionList;

/**
 * The method returns an array of actions to be displayed.
 * These actions initiate the primary app workflow.
 *
 * These actions are filtered and sorted based on the following 
 * algorithm:
 * - the actions will be split into generic actions, or actions without
 * specified subtypes, and the actions with subtypes specified by
 * [Adobe360WorkflowActionDataSource setWhitelistedSubTypes:].
 * - these groups are sorted by priority using the block specified at 
 * [Adobe360WorkflowActionDataSource setPrioritizeBlock:]
 * - the two groups are joined with the specific actions prioritized 
 * above the generic list
 * - all actions are sorted by usage. This usage is increased using 
 * [Adobe360WorkflowActionDataSource increaseFrequencyForAction:]
 * 
 * @return An array of Adobe360WorkflowAction instances.
 */
- (NSArray *)actionsToDisplay;

/**
 * The method allows to add actions dynamically to ActionsViewController.
 * Clients can use this method to add necessary actions not present in action registry.
 *
 * @param action An Adobe360WorkflowAction instance that needs to be added.
 */
- (void)addActionToRegistry:(Adobe360WorkflowAction *)action;


/**
 * Adds the action selection to the frequency list maintained by
 * the data source. The frequency list is used by the data source to 
 * sort the returned actions.
 */
- (void)increaseFrequencyForAction:(Adobe360WorkflowAction *)action;

#pragma mark - Data Methods

/**
 * The method loads the action registry from the server. The registry is locally cached as well as
 * a version of it is included in the bundle. Any network error returns the cached registry if one is
 * is available.
 * Calls both willLoadActionRegistry & didLoadActionRegistry delegate methods.
 */
- (void)loadActionRegistry;

@end

#endif
