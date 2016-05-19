/******************************************************************************
*
* ADOBE CONFIDENTIAL
* ___________________
*
* Copyright 2014 Adobe Systems Incorporated
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

#ifndef AdobeCommonLearnedSettingsHeader
#define AdobeCommonLearnedSettingsHeader

#import <Foundation/Foundation.h>

#import <AdobeCreativeSDKCoreOSX-Internal/AdobeCommonTypes.h>

@interface AdobeCommonLearnedSettings : NSObject

#pragma mark - Asset Browser Settings

/**
* Set the last user-selected visual layout.
*
* @param visualLayout Visual layout to use.
*/
+ (void)setLastVisualLayout:(AdobeBrowserVisualLayout)visualLayout;

/**
* Retrieves the last visual layout selected by the user. If the user never selected a visual
* layout, the default visual layout (@c AdobeStorageVisualLayoutListView) is returned.
*
* @return The last user-selected visual layout or @c AdobeStorageVisualLayoutListView if the user
* has never set the visual layout.
*/
+ (AdobeBrowserVisualLayout)lastVisualLayout;

/**
* Determines whether the user has changed the visual layout from the default value.
*
* @return @c YES if the user has previously changed the visual layout; @c NO otherwise.
*/
+ (BOOL)lastVisualLayoutSetByUser;

/**
* Set the last user-selected files sorting type.
*
* @param sortType The sort type selected by the user.
*/
+ (void)setLastFilesSortType:(AdobeBrowserSortType)sortType;

/**
* Retrieves the last sort type selected by the user. If the user has never selected a sort type,
* the default sort type @c sortType_Time is returned.
*
* @return The last user-selected files sorting type or @c sortType_Time if the user has never set sort
* type.
*/
+ (AdobeBrowserSortType)lastFilesSortType;

/**
* Determines whether the user has changed the sort type from the default value.
*
* @return @c YES if the user has previously changed the sort type; @c NO otherewise.
*/
+ (BOOL)lastFilesSortTypeSetByUser;

/**
* Set the last user-selected photos sorting type.
*
* @param sortType The sort type selected by the user.
*/
+ (void)setLastPhotosSortType:(AdobePhotoSortType)sortType;

/**
* Retrieves the last sort type selected by the user. If the user has never selected a sort type,
* the default sort type @c sortType_Time is returned.
*
* @return The last user-selected files sorting type or @c sortType_Time if the user has never set sort
* type.
*/
+ (AdobePhotoSortType)lastPhotosSortType;

/**
* Determines whether the user has changed the sort type from the default value.
*
* @return @c YES if the user has previously changed the sort type; @c NO otherewise.
*/
+ (BOOL)lastPhotosSortTypeSetByUser;

/**
* Set the last user-selected photo browser view.
*
* @param browserView The browser view selected by the user.
*/
+ (void)setLastPhotoBrowserView:(AdobePhotoBrowserView)browserView;

/**
* Retrieves the last photo browser view selected by the user.
*
* @return The last user-selected photo browser view or @c AdobePhotoBrowserShowAllPhotos if never set.
*/
+ (AdobePhotoBrowserView)lastPhotoBrowserView;

/**
* Sets the last Asset Browser data source selected by the user.
*
* @param sourceType Asset Browser data source as defined in @c AdobeAssetDataSourceFilter.
*/
+ (void)setLastAssetBrowserDataSourceType:(NSString *)sourceType;

/**
* Last user selected Asset Browser data source, if any. If the user has never changed the data
* source, the Files data source (@c AdobeAssetDataSourceFiles) is assumed.
*
* @return An NSString that represents the last user-selected Asset Browser data source. The
*         default data source is @c AdobeAssetDataSourceFiles.
*/
+ (NSString *)lastAssetBrowserDataSourceType;

/**
* Determines whether the asset browser's navigation bar buttons should be hidden.
*
* This setting is set as part of an Internal API for bringing up the asset browser in an iOS 8+
* Document Provider view controller. Since the Asset Browser is contained in a Document Provider
* popover, there is no need for these buttons.
*
* Note that the title view will remain visible.
*
* @return Whether all the navigation bar buttons should be hidden.
*/
+ (BOOL)shouldHideAllNavigationBarButtonsInAssetBrowser;

/**
* Set whether the asset browser's navigation bar buttons should be hidden.
*
* @param shouldHide Hide the buttons or not.
*/
+ (void)setShouldHideAllNavigationBarButtonsInAssetBrowser:(BOOL)shouldHide;

/**
* Determines whether the "Info" button in the OneUp view should be hidden.
*
* This setting is set as part of an Internal API for presenting the asset browser in an iOS 8+
* Document Provider extension. The Info button's functionality is not need currenty in that
* scenario.
*
* @return @c YES if the Info button should be hidden; @c NO otherwise.
*/
+ (BOOL)shouldHideNavigationBarInfoButtonInAssetBrowserOneUpView;

/**
* Set whether the Info button in the asset browser's OneUp view should be hidden.
*
* @param shouldHide @c YES to hide the Info button; @c NO for the button to remain visible.
*/
+ (void)setShouldHideNavigationBarInfoButtonInAssetBrowserOneUpView:(BOOL)shouldHide;

/**
* Whether all the UI/code hacks are enabled. This setting should be enable when the Storage
* Browser is running in an iOS 8+ Document Provider extension.
*
* @return Whether the hacks should be enabled.
*
* @see setEnableAllExtensionHacks:
*/
+ (BOOL)shouldEnableAllExtensionHacks;

/**
* Whether to enable all the UI/code hacks for running the Storage Browser in an iOS 8+ Document
* Provider extension.
*
* @param shouldEnable Whether to enable the hacks.
*
* @see shouldEnableAllExtensionHacks
*/
+ (void)setEnableAllExtensionHacks:(BOOL)shouldEnable;

#pragma mark - Stock Browser Configuration

/**
*  Whether the account button should be hidden in the Stock Browser.
*
*  @return YES if the button should be hidden, otherwise NO.
*/
+ (BOOL)shouldHideAccountButtonInStockBrowser;

/**
*  Sets whether the account button should be hidden in the Stock Browser.
*
*  @param shouldHide Whether or not to hide the account button.
*/
+ (void)setShouldHideAccountButtonInStockBrowser:(BOOL)shouldHide;

/**
*  Indicates whether the stock browser has disabled auto dismissal behavior.
*
*  @return YES if it won't auto dismiss upon success or error, otherwise NO.
*/
+ (BOOL)shouldDisableAutoDismissOnSuccessOrError;

/**
*  Sets whether to disable the auto-dismissal behavior of the stock browser.
*
*  @param shouldDismiss If YES, the stock browser will not be automatically be dismissed upon success or error.
*/
+ (void)setShouldDisableAutoDismissOnSuccessOrError:(BOOL)shouldDismiss;

/**
*  Whether client manages navigation bar and presentation.
*
*  @return Whether client manages navigation bar and presentation.
*/
+ (BOOL)clientManagesNavigationAndPresentation;

/**
*  Set whether client manages navigation bar and presentation.
*
*  @param clientManages Whether client manages navigation bar and presentation.
*/
+ (void)setClientManagesNavigationAndPresentation:(BOOL)clientManages;

/**
*  Sets whether to disable the save preview buttons in the stock browser.
*
*  @param shouldDisable Whether or not to disable.
*/
+ (void)setShouldDisableSavePreviewButtonsInStockBrowser:(BOOL)shouldDisable;

/**
*  Whether to disable the save preview buttons in the stock browser.
*
*  @return YES if the buttons should be disabled, otherwise NO.
*/
+ (BOOL)shouldDisableSavePreviewButtonsInStockBrowser;

/**
*  Sets whether to disable the license asset buttons in the stock browser.
*
*  @param shouldDisable Whether or not the button should be disabled.
*/
+ (void)setShouldDisableLicenseAssetButtonsInStockBrowser:(BOOL)shouldDisable;

/**
*  Whether or not the license asset butotn should be disabled in the stock browser.
*
*  @return Whether or not the button should be disabled.
*/
+ (BOOL)shouldDisableLicenseAssetButtonsInStockBrowser;

#pragma mark - Storage Container More Toolbar Button

/**
* Retrieve the last calculated content size for the More (...) toolbar button's popover view
* controller.
*
* Since the length of the options presented in the popover can change due to localization, we need
* to calculate the final size of the popover view controller by traversing all the items and
* calculated the final size for the string objects. To avoid having to recaulated the final size
* every time the popover is displayed, we calculate the value once and store it using this method.
*
* @return A @c CGSize value that represents the last calculated content size for the More (...)
* toolbar button's popover view controller.
*/
+ (CGSize)lastCalculatedPopoverSize;

/**
* Store the last calculated content size for the More (...) toolbar button's -- in the storage  * container view controller -- popover view controller.
*
* @param lastSize Last calculated content size.
*/
+ (void)setLastCalculatedPopoverSize:(CGSize)lastSize;

#pragma mark -
#pragma mark Last Select Item

/**
* Stores the GUID for the last selected asset/file/directory.
*
* @param guid GUID for the last selected asset/file/directory. If @c guid is @c nil, the existing
* setting is removed.
*/
+ (void)setLastSelectedItemGUID:(NSString *)guid;

/**
* Retrieves the GUID for the last user-selected asset/file/directory.
*
* @return An @c NSString containing the GUID for the asset/file/directory, or @c nil if the user
* has never selected anything.
*/
+ (NSString *)lastSelectedItemGUID;

/**
* Set the index path for the last selected item.
*
* @param indexPath Index path for the selected item. If @c indexPath is nil, the existing setting
* is removed.
*/
+ (void)setLastSelectedIndexPath:(NSIndexPath *)indexPath;

/**
* Retrieves the last selected index path.
*
* @return Index path for the last selected item or @c nil if no item has ever been selected.
*/
+ (NSIndexPath *)lastSelectedIndexPath;

#pragma mark -
#pragma mark Asset Layer Extraction

/**
* Set whether asset layer extraction is enabled.
*
* @param canExtractLayers Whether to enable layer extraction for assets that suppor it.
*/
+ (void)setCanExtractAssetLayers:(BOOL)canExtractLayers;

/**
* Whether asset layer extraction is enabled.
*
* @return Whether layer extraction for asset types that support it is enabled.
*/
+ (BOOL)canExtractAssetLayers;

/**
* Whether to suppres the instructions that show up when layer extraction is invoked.
*
* @return @c YES if the instructions overlay should be suppressed.
*/
+ (BOOL)suppressAssetLayerExtractionInstructions;

/**
* Set whether the asset extraction instructions should be suppressed.
*
* @param suppress Whether to suppress the instructions overlay.
*/
+ (void)setSuppressAssetLayerExtractionInstructions:(BOOL)suppress;

/**
* Whether to allow multiple PSD layers to be selected when exploring/extract a PSD's layers.
*
* @return @c YES if multiple layers should be selected (default); @c NO otherwise.
*/
+ (BOOL)enableMultiplePSDLayerSelection;

/**
* Enable multiple PSD layers to be selectable when exploring a PSD's layers.
*
* @param enable Whether to enable multiple selection.
*/
+ (void)setEnableMultiplePSDLayerSelection:(BOOL)enable;

#pragma mark - Market Assets

/**
* Retrieves the last time interval that the Market Assets' Premium Notice was displayed.
*
* @return The last @c NSTimeInterval that the Premium Notice was displayed.
*/
+ (NSTimeInterval)marketAssetsPremiumNoticeLastDisplayedTimeInterval;

/**
* Record the last time interval that the Market Assets' Premium Notice was displayed.
*
* @param lastTimeInterval Date and time, as an @c NSTimeInterval, that the Premium notice was
* displayed.
*/
+ (void)setMarketAssetsPremiumNoticeLastDisplayedTimeInterval:(NSTimeInterval)lastTimeInterval;

/**
* The number of days to wait between showing the Premium Notice.
*
* If this value is never set, 7 is returned.
*
* @return Number of days to wait.
*/
+ (NSInteger)marketAssetsPremiumNoticeRepeatDays;

/**
* Whether to suppress the instructions that show up when a market asset is selected.
*
* @return @c YES if the instructions overlay should be suppressed.
*/
+ (BOOL)suppressAddMarketAssetToDesignLibraryInstructions;

/**
* Set whether the instructions for adding market assets to design libraries should be suppressed.
*
* @param suppress Whether to suppress the instructions overlay.
*/
+ (void)setSuppressAddMarketAssetToDesignLibraryInstructions:(BOOL)suppress;

/**
* Whether to always provoke the instructions that show up when a market asset is selected
*
* @return @c YES if the instructions overlay should be always provoked.
*/
+ (BOOL)provokeAddMarketAssetToDesignLibraryInstructions;

/**
* Whether to provoke Monthly Download Limit dialog in Market Browser
*
* @return @c YES if Monthly Downalod Limit dialog should be provoked
*/
+ (BOOL)provokeMonthlyDownloadLimitDialog;

/**
* Provide mock error object to provoke Monthly Download Limit dialog in Market Browser
*
* @return a dictionary containing mock data to provoke Monthly Download Limit dialog
*/
+ (NSDictionary *)getMockErrorProvokeMonthlyDownloadLimitDialog;

#pragma mark - 360 Degress Workflows

/**
* Determines whether the 360 Degree Workflow's Premium overlay has been displayed.
*
* @return @c YES if the overlay has been displayed; @c NO otherwise.
*/
+ (BOOL)didDisplay360WorkflowPremiumOverlay;

/**
* Sets whether the 360 Degree Workflow's Premium overlay has been displayed.
*
* @param didDisplay Whether the Premium overlay has been displayed.
*/
+ (void)setDidDisplay360WorkflowPremiumOverlay:(BOOL)didDisplay;

#pragma mark - Reset All Settings

/**
* Resets all user settings, like sort preference, visual layout, etc.
*
* This method is useful in situations where all user-set settings need to be reset, like when
* logging out.
*/
+ (void)resetAllSDKUserSettings;

@end

#endif /* ifndef AdobeCommonLearnedSettingsHeader */
