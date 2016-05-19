# AdobeCreativeSDKFoundation Release Notes

### Build 0.3.2149 (2016-04-22)
##### What's New
###### Foundation
- Added iPhone landscape orientation support for Asset Browser, PSD Extraction, and Market component.
- Device tokens will be extended beyond their original 180 day limit if used in the second half of their original expiration period.  This will reduce unexpected logouts due to expired authentication tokens.
- Fixed bug 4138560: On user sign-up, selecting country, month, day, or year in split mode no longer crashes the app on iOS 9.3 or 9.3.1.  The app will display a warning or disable the "Get an Adobe ID" link if on split view.
- Fixed bug 4135980: Manually constructed AdobeAssetFolders are missing metadata. We've added a 'refresh' method on the AdobeAssetFolder object (to mirror what is already done on AdobeAssetFile) that will pull the latest metadata for the folder object. The SDK is not notified by the server when an item's metadata has changed, so if it is important to know the current state of the folder you must refresh the object. If you are using an AdobeAssetFolder object for folder listing, a refresh is not needed. Note: if an AdobeAssetFolder is returned as part of a folder listing, it will have the current metadata at the time of the listing.
- Fixed bug 4134794: isAuthenticated is enabled consistently before calling the sign-in/sign-up success blocks
- Major update to Library Asset Browser to support bookmarks (Live Library Links)
    - It now uses Adobe Library Manager to fetch design libraries and elements.
    - AdobeSelectionLibraryAsset now returns library & selected element id's. These can be used to get the corresponding library composite & selected library elements from the AdobeLibraryManager.
    - AdobeAssetLibraryItem and all its derived classes are deprecated.
    - Library Assets Browser now supports Bookmarks. The elements can be selected like any other library elements.
    - (internal only) If you use AdobeSelectionLibraryAsset and allocate the it, the API is deprecated and no longer works. This could not be made to work with the new scheme. The property accessors for each type continue to work.
- Market and Stock browsers library selection view shows bookmarks and are disabled, grayed out.

###### Color
- Color component now has a base indicator on the theme swatch and the wheel marker in Picker view.  No change in Single color mode
- Color component library selection now show bookmarks. Saving to bookmarks is disabled.

###### Typekit
- (internal only) Added iPhone landscape orientation support for Typekit

##### Known Issues
###### Foundation
- Creative Cloud Market assets are not downloaded from Market Browser on iOS 8.1 and 8.2. Copy an asset to Creative Cloud Libraries or Creative Cloud Files in Market Browser, then download the asset from Asset Browser.
- (internal only) The CreativeSDKFoundation repo now builds dynamic frameworks.  Clients that include this repo in their build environment need to disable "Finding Implicit Dependencies" on their app scheme.  Otherwise, any link or target dependency on a `AdobeCreativeSDK*.framework` will attempt to build the dynamic framework.
- Bug 4114575: The SDK crashes if Core Data concurrency checking is enabled. I.e., if "-com.apple.CoreData.ConcurrencyDebug 1” is added to the app run argument

### Build 0.3.2147 (2016-4-11)
##### What's New
- Fixed bug 4137218: psd extractions failed to extract correct layers when executed multiple times

### Build 0.3.2146 (2016-4-05)
##### What's New
- Fixed bug 4135428: Lightroom browser is empty on launch after launching Library Assets browser

### Build 0.3.2145 (2016-4-01)
##### What's New
- Ensure a non-zero/nil GUID when checking cache in downloadMediaWithSize:priority:progressBlock:successBlock:cancellationBlock:errorBlock: of AdobeStockAsset.

### Build 0.3.2143 (2016-3-31)
##### What's New
- (internal only) Bug Fix 4126208: [Capture] Incorrect manager isStarted state for Market/Stock with delayed login.
  * Both CSDK & Apps start ALM on login notification. 
     - Case 1: If CSDK gets notification before the app, we delegate call back to get ALM config info from App & use it to start ALM. Later when app receives login notification, they need to register as ALM delegate. 
     - Case 2: App receives notification before CSDK, so app starts ALM, register's as ALM delegate. Later when CSDK receives notification it just uses the ALM.
  * Added delegate in market & stock that will let apps send ALM startup info like the rootFolderPath to CSDK.
     - `marketBrowserWillStartLibraryManagerWithConfiguration:`
     - `stockBrowserWillStartLibraryManagerWithConfiguration:` 
  * Use the AdobeBrowserLibraryManagerConfiguration to add the rootFolderPath & CSDK will use it to start the ALM.
- (internal only) The following dynamic frameworks are available, in both public and internal versions:
  - AdobeCreativeSDKCore
  - AdobeCreativeSDKCommonUX
  - AdobeCreativeSDKAssetModel
  - AdobeCreativeSDKAssetUX
  - AdobeCreativeSDKMarketUX
  - AdobeCreativeSDKColor
  - AdobeCreativeSDKTypekit
  - AdobeCreativeSDKUtility (Internal only.  Equivalent to the AdobeCretiveSDKPrivateInternalAppLib static framework)
- (internal only) Added a new configuration property to AdobeUXStockBrowserConfiguration, initialKeywordString. Setting this property will configure the Stock Browser to automatically execute a search with the provided string. Note: Setting this will cause the browser to skip the initial search landing view and go directly to the main collection view.
- Added landscape orientation support for App Library
- Fixed bug 4131814: AdobeDCXController: requestsPushOfCompositeWithID is called with a composite status of AdobeDCXAssetStateCommittedDelete
- Added iPhone landscape mode support for AdobeCreativeSDKColor and AdobeCreativeSDKAppLibraryUX frameworks.
- (internal only) Added iPhone landscape mode support for AdobeCreativeSDKStockUX framework.
- (internal only) AdobeCreativeSDKTypekit supports Traditional Chinese (Taiwan) locale.
- Added UI support for read-only folder to AssetUX

### Build 0.3.2141 (2016-3-22)
##### What's New
- Fixed bug 4130300: Poll for rendition generation of a photo asset.

### Build 0.3.2140 (2016-3-10)
##### What's New
- The Adobe360WorkflowStatusBarViewController now supports an intermediate state that allows only cancel & return to primary app. 
    - Use `- (void)enableSave: withAnimation:` API to enable/disable the save option.
    - `- (void)setRoundtripEnabled:(BOOL)enabled` that showed lock icon & disabled status bar is deprecated.
- Apps calling `AdobeUXAuthManager setAuthenticationParametersWithClientID:withClientSecret:` (typically 3rd party apps) have their login period extended from two weeks to six months.
- Removed the requirement to use the USE_CSDK_COMPONENTS pre-processor directive when building with the new Split Frameworks.
- (internal only) Added CoreLogging Module that adds CoreLogFatal, CoreLogError, CoreLogWarn, CoreLogDebug and CorelogTrace. This allows verboseLogging by turning on the verboseLog flag on the `[AdobeCoreLogging sharedObject]`. Only output information that is *not* sensitive to this log as it is possible to enable this in release mode via a plist change similar to enabling AuthLogging. LogDebug and friends are still disabled when in release mode. 
- (internal only) AuthLogging used to be enabled with `[AdobeAuthLogging sharedObject].verboseAuthLogging = YES;` now it is `[AdobeAuthLogging sharedObject].verboseLogging = YES;`. 
- (internal only) Test App settings now allows turning on logging levels on a per module basis. All Logging is moved to one section of the settings. 
- (internal only) Detailed Cache Logging is available through LogTrace when in Debug. Imporant Cache errors will appear in CoreLog logging module. This can be enabled by 1st parties. There is no longer a separate Cache logging switch. 
- (internal only) Cache hit location is no longer returned in the callback for the new APIs. Nobody was using it, it complicated the callbacks, the APIs did not match the functionality of the synchronous versions, it was untested, and exposes information that clients should not use. To detect a cache miss the item comes back nil.
- (internal only) Call back on cache hit has now been changed to return on only one completion queue. 
- (internal only) the old AdobeCommonCache APIs are deprecated so you will get bunch of warnings if using them. If you could move quickly to the new APIs we can delete them and reduce the support burden. The following improvements were made:
    * Added some synchronous versions of the methods, we had some but now all types supported. Object, Directory, Array, Data and Image. 
    * Next the heavy use of prepositions were changed so that they read more consistently. For example, we use “forGUID” and “andKey” but drop the rest of the prepositions  this shows that GUID and Key are tied together. No more “withOptions”, “fromCache” etc. Instead of fromGUID it is forGUID, since we are getting it for a particular GUID and Key pair. 
    * The cache name and options are swapped which is more consistent. 
    * Enable cache is renamed to setEnable:cache:error: 
    * configureCache api changed to get rid of prepositions. 
    * For the asynchronous methods, the “get" word was removed from the beginning of the method, The hit and miss handers were moved into one callback. The new callback is at the end of methods. This is so that Swift can use the trailing syntax. Since there is one completion callback you must check to see either if the item returned is null or whether the cache location is AdobeCommonCacheHitLocationNone when the callback completes. If the item is nil, then that means it was a miss. The other advantage  of the single callback is the call site flow is easier to follow because you don’t have many interspersed blocks which tends to float out in the middle of the line. The hit and miss queues are moved earlier in method name, and it will call back for a hit or miss appropriate queue. Other than the position, you should pass the same values as the old API.  
    * For Swift support nullability annotations were added. With the new APIs we do check for nil, so if you have some parameters that used to rely on nil, you will get an exception. 
    * Internal changes were made to unify the code and more unit tests were added to help find issues earlier. 
- (internal only) Deprecated `AdobeUXAuthManager logoutWithAlert`.  Renamed as`logoutMayAlert`.
- Subscription to Adobe newsletter is no longer optional in Adobe ID sign up screen.
- (internal only) Typekit SDK source code has been merged into the CreativeSDKFoundation git repository.
- (internal only) Typekit creates locale dependent font folders for bundled fonts. The localized font files are moved to the app font files when the language is changed to the matching language.
- (internal only) Stock now shows alerts upon failing to save/license an asset. It will continue calling its error delegate, however clients do not need to show their own alert from the error delegate callback.
- Added UI support for read-only design libraries to AssetUX, StockUX, MarketUX and Color frameworks.

### Build 0.3.2139 (2016-2-18)
##### What's New
- Market UX can be browsed without sign in into creative cloud account.
    - Users will be prompted to login when they try to download assets/add-to-library.
- Adobe360Message and Adobe360MessageBuilder now support array-valued inputs and outputs.
    - Array valued input will represent two new action types: captureN & embedN.
    - New methods have been added specifically for creating named input and output arrays in the Adobe360MessageBuilder class.
    - New methods for retrieving individual items in input and output arrays have also been added to the Adobe360Message class. 
    - The inputDescriptors and outputDescriptors properties on both classes may now contain values that are arrays of descriptors, as well as individual descriptors.
- Deprecated AdobeUXAssetBrowser in favor of new, UIViewController-based API: AdobeUXAssetBrowserViewController. Please see AdobeUXAssetBrowserViewController.h in AdobeCreativeSDKAssetUX.framework for more details.
- Deprecated AdobeUXMarketAssetBrowser in favor of the new UIViewController-based class: AdobeUXMarketBrowserViewController. Now the Market Browser can be presented like a normal UIViewController subclass as is the norm with almost all Apple-provided view controllers in iOS. Please see the documentations for AdobeUXMarketBrowserViewController for more information.
- Deprecated AdobeUXAppLibrary in favor of the new UIViewController-based API: AdobeUXAppLibraryBrowserViewController. Please see AdobeUXAppLibraryBrowserViewController.h in AdobeCreativeSDKAppLibrary.framework for more details.
- Moved Adobe360Workflow View Controller constructors from the now deprecated AdobeUXAppLibrary to their respective classes.
- (internal only) Deprecated AdobeStockAssetsViewController - renamed to AdobeUXStockBrowserViewController.
- (internal only) Deprecated AdobeStockConfiguration - renamed to AdobeUXStockBrowserConfiguration.
- (internal only) Deprecated block-based API in Stock UX in favor of a delegate pattern. This provides consistency between Stock and Asset UX. See AdobeUXStockBrowserViewController.h for more details.
- Photo Browser: the default photo view is now "All Photos." It can be toggled to "View Collections" by touching the more (...) button.
- The following frameworks now contain Asset Catalogs: AdobeCreativeSDKAppLibraryUX, AdobeCreativeSDKAssetUX, AdobeCreativeSDKColorComponent, AdobeCreativeSDKCommonUX, AdobeCreativeSDKCore, AdobeCreativeSDKMarketUX, AdobeCreativeSDKStockUX
- Added support for 3D Elements in libraries. All existing APIs that handle library assets are now aware of 3D Elements can work with such assets.
- Deprecated and modified `AdobeUXAuthManager setAuthenticationParametersWithClientID:clientSecret:enableSignUp:`.  Both this and `setAuthenticationParametersWithClientID:withClientSecret:` always allow user sign-up.  The `enableSignUp` argument is ignored.
- (internal only) AdobeAssetFile.resourceItem and AdobeAssetCollection.resourceCollection can no longer be accessed. It was leading to synchronization issues between the lower level AdobeStorageResource and the wrapper classes. If you need access to this low level class, please notify the dev team.
- Added support for Looks and Patterns in Creative Cloud Libraries. Looks/Patterns can now be viewed and opened like other already supported assets in libraries. Support includes full API access to the rendition in addition to the file itself.
- (internal only) Added ETS events to aid identify unexpected logouts and for new 360 workflow embedN and captureN events.
- Added revertCurrentBranch and revertCurrentBranchToBase methods on AdobeDCXComposite
- Several DCX bug fixes involving recently added AdobeDCXElement

### Build 0.3.2138 (2016-2-3)
##### What's New
- (Internal Only) Added back the deprecated copyFile: methods to AdobeStorageSession+File.h until new APIs and server-side support are available.

### Build 0.3.2135 (2016-1-28)
##### What's New
- armv7s frameworks are not included anymore. Apple recommended dropping armv7s from the target architectures since Xcode 6. Upgrading to Xcode 6 or later suggests making this project file change.  Most clients have done so already. Building for armv7s devices (iPhone 5/5c and iPad (4th generation)) now requires targeting armv7 and using the armv7 frameworks. The armv7 instruction set is a subset of armv7s'. armv7s provided performance benefits to some floating-point intensive apps.
- Adobe360WorkflowSenderDelegate contains a new API contentDidChangeToSize. This is called when the Adobe360WorkflowActionsViewController content size is changed.
- Adobe360WorkflowDispatch contains a new API preloadActionRegistriesAndAppIcons. This should be called as soon as the app is launched, that way when 360 is launched there is no delay in displaying the app icons
- Adobe3PopoverView is now deprecated and will be removed in a future release. Use UIPopoverPresentationController instead.
- Color SDK: AdobeColorPickerControllerDelegate has a new optional API colorPickerControllerDidCancel, this is called from AdobeColorViewController when the Cancel button is hit
- Added support for video assets in libraries. This includes all the related APIs for downloading a rendition or the linked video file from the Stock servers. Note that currently the only supported video asset in a library on the server is videos added through the Stock web interface.
- Adobe360Message and Adobe360MessageBuilder now support adding AdobeDCXElement as input and/or output asset for use in non-destructive workflows.
    - Additionally, methods that worked for both inputs and outputs (e.g. `writeAssetWithName:`, `dataForAssetWithName:`, etc.) have been deprecated and replaced with new versions that are specific to inputs or outputs.
- Added relationship property to AdobeDCXNode.
- Added customKeys property to AdobeDCXNode to allow enumeration of custom properties that have been added to a node via `setValue:forKey:`.
  - Additionally, keys with corresponding first-class property getters/setters (e.g. type, name, relationship, etc.) will now generate an exception when used with `setValue:forKey:` or `value:forKey:`.
- The AdobeAsset APIs (AdobeAsset, AdobeAssetFile, AdobeAssetFolder, AdobeAssetPackage) have been moved (with deprecations) to use the newer API signatures.
- The data transfer APIs for AdobeAssetFile now returns an AdobeAssetAsyncRequest object which can be used to re-prioritized or cancelled. This will allow for multiple streams of transfer without losing the ability to make changes.
- (internal only) The AdobeStorageSession+Files APIs have been moved (with deprecations) to use the newer API signatures.
- Stock Browser: Licensed Stock Photos are un-watermarked in 1-up. This does not apply to Vectors or illustrations.
- Added the ability select multiple LR Photos, in addition Files. Now multiple Files and LR Photos can be selected simultaneously.

### Build 0.3.2134 (2016-1-22)
##### What's New
- Fixed crash when switching back and forth between users. Fixed several retain cycles that were recently discovered in DCX code that could interfere with the correct behavior of the composite instance cache used by the new versions of the composite factory methods.  Fixes Watson #4109531.

### Build 0.3.2133 (2016-1-14)
##### What's New
- Fixed bug in new copyNode method on AdobeDCXCompositeMutableBranch and AdobeDCXElement where ‘index’ parameter was being ignored.
- Fixed bug in new getChildrenOfNode method on AdobeDCXCompositeMutableBranch and AdobeDCXElement, in which the returned nodes might not be completely initialized.
- Fixed crash that could occur when calling resolvePullWithBranch on a DCX composite that was created on another client and has been pulled for the first time.

### Build 0.3.2132 (2015-12-18)
##### What's New
- (Internal Only) Client apps need to import `<AdobeCreativeSDKCore/AdobeCreativeSDKCore.h>` before use of any Core internal header file.  A recent change to `AdobeUXAuthManager+Protected.h`  and `AdobeUXAuthManager_Restricted.h`  may make this apparent.  A practical way to do this is to import `<AdobeCreativeSDKCore/AdobeCreativeSDKCore.h>` from a client app Prefix.pch file.
- App Library GET/OPEN button renamed to "LAUNCH" on iOS 9. We launch the app if it's already installed else we show the Store Kit UI.
- AdobeDCXManifestNode and AdobeDCXMutableManifestNode classes have been deprecated and are replaced by a single class called AdobeDCXNode: The highlights:
  -  AdobeDCXNode objects act as live references to the child node on its branch.
  -  If an AdobeDCXNode refers to a child node on a mutable branch then updates to its properties are reflected on that branch immediately, so there is no need to repeatedly call mutableCopy on the return value from updateChild (which is itself no longer needed) if you are making incremental updates to a child node on a branch.
  -  All of the methods that accepted or returned AdobeDCXManifestNode objects have been deprecated and are replaced with equivalent methods that deal with AdobeDCXNodes.

- AdobeDCXElement class has been added.  A DCX Element is fundamentally a composite that has been embedded as a child node in another composite.  In more practical terms, any child node in a DCX manifest can be  considered to be an element if it has both a 'name' and a 'type' property. The AdobeDCXElement class exposes an interface to an element node that has been detached from its host branch.  This allows a client to edit it directly, using methods that are identical to those found on AdobeDCXCompositeMutableBranch.  Unlike AdobeDCXNode, changes made to an AdobeDCXElement object are reflected on a composite branch only when the replaceElement or copyElement methods on the branch are called.

- A new set of construction methods for AdobeDCXComposite ensures that clients don't create multiple in-memory instances of the same on-disk composite. The AdobeDCXComposite class now
    manages a weakly-referenced instance cache. compositeStoredAt:usingController:withError: is the new method to use for instantiating composites given a local storage path. It
    returns an already existing instance or (if none exists) constructs a new one. There are four new methods for creating new composites newCompositeXXX:... which will now fail if provided
    with a local storage path that is already in use by a live instance. Lastly AdobeDCXComposite has a new localStoragePath property along with a setLocalStoragePath:withError: method which will also
    fail in case of a conflict. The old construction/init methods and the old path property have been deprecated.

- The AdobePhoto APIs (AdobePhotoAsset, AdobePhotoAssetRendition, AdobePhotoCatalog, and AdobePhotoCollection) have been moved (with deprecations) to use the newer API signatures.
- The data transfer APIs for AdobePhotoAsset now returns an AdobePhotoAsyncRequest object which can be used to re-prioritized or cancelled. This will allow for multiple streams of transfer without losing the ability to make changes.
- (internal only) The AdobePhotoSession APIs have been moved (with deprecations) to use the newer API signatures.
- (internal only) AdobePhotoSession:accountLimitsForID no longer returns the limits for catalogs and catalog_users (per the request of the server team).

- Adobe360Message now supports embedding AdobeDCXElement objects as inputs and outputs.  

- (Internal Only) The Public framework AdobeCreativeSDKAssetUX.framework is no longer dependent on the internal framework AdobeCreativeSDKStockModel.framework.

- All extension frameworks have been removed.  Only the Core extension functionality is still available, but not as a separate framework.  Applications that need the Core extension must link to `AdobeCreativeSDKCore.framework`; the extension functionality is selected at runtime.  The Core extension provides authentication capability.

- The PSD Extraction workflow has been updated to use Size Classes, to support iOS9 split view, and consequently is now supported on the iPhone platform. 

- Photoshop Mix projects created in PS Mix v2 are now showing in Asset Browser. To trigger this you must open Mix v2 projects in the Mix 2.2 app at least once.

### Build 0.3.2131 (2015-11-18)
##### What's New
- Update framework version number in plist to 0.3

### Build 0.1.2130 (2015-11-12)
##### What's New
- Bug Fix 4086960: Color SDK/Foundation: "Color" is using inconsistent translation
- Bug Fix 4086646: Shared library: stock assets licensed from within comp FROM ANOTHER USER can not be placed on canvas and give no error on iphone (licensed images from web can be placed on canvas)
- Bug Fix 4086595: Assets that can not be placed due to turning network off will not load once back online
- Fix bug where we were returning a path with the error token for a failed external link rendition download
- Return AdobeNetworkErrorRequestForbidden as the underlying error when user requests an Adobe Stock image that they dont have a license for. Fallback to the watermarked image if client calls getRenditionPath for an external link that they dont have the license to.
- Fix updateAdobeStockElement so it can handle old style stock elements.
- Cache the error when failed to download an external link and return it along with library error.
- Check for error key in prefix when checking for cached error value since we now also cache the error domain and code.

### Build 0.1.2129 (2015-11-11)
##### What's New
- Bug Fix 4086575: Download fail with error 400 when licensing a vector stock asset

### Build 0.1.2128 (2015-11-10)
##### What's New
- New, more granular error codes for network connections related to endpoint resolution. In addition to `AdobeNetworkErrorCannotReachCloudEndpoint`, which indicated an unreachable endpoint, we now have two new error codes: `AdobeNetworkErrorCannotReachCloudEndpointDueToLostConnection` and `AdobeNetworkErrorCannotReachCloudEndpointDueToTimeout`. The first one, as the name suggests, indicates a lost connection and is reported if the underlaying CoreFoundation networking error is `kCFURLErrorNetworkConnectionLost`. The second error code indicates a timeout of the connection and is reported in the case of `kCFURLErrorTimedOut`. `AdobeNetworkErrorCannotReachCloudEndpoint` is now reported when the underlaying error is `kCFURLErrorCannotFindHost`. Combined, these error codes should make it easier to determine the cause of a failed connection.
- The sign-in view now retains the email from the previously logged in user.  From clients feedback, this provides a better user experience.
- The CSDK upgraded to WKWebView.  Apps need to link to `WebKit.framework`.
- (internal only) Phase II of refactoring is complete. We now have OSX frameworks for core and assetModel (for DMA support only). Please see https://wiki.corp.adobe.com/pages/viewpage.action?pageId=1055835330.
- The Libraries panel in AdobeUXAssetBrowser now displays an un-watermarked thumbnail for Stock assets that are licensed. 
- AdobeCreativeSDKAssetUX.framework now depends on AdobeCreativeSDKStockModel.framework.
- (internal only) Enabled access to Stock browser for Enterprise (CCE/CCEP) accounts.

### Build 0.1.2127 (2015-10-22)
##### What's New
- 360 menu localization changes are now in production.
- Fixed Watson 4059114: App icons on the 360 popover are flickering.
- Stock search for Color UI has been updated

### Build 0.1.2126 (2015-10-14)
##### What's New
- Several AdobeDCXController-related improvements:
  1. Eliminate the need for clients to check to see if syncing has been paused in their controller delegate's request methods.
  2. Prevent inadvertently requesting overlapping push operations in the event that a transfer operation is rapidly cancelled and restarted due to pausing and resuming sync (fixes Watson 4042427)
  3. Add appropriate error handling for AdobeDCXErrorMissingManifest and several new networking and authorization errors.
  4. Fixed bug in which requestsBytesConsumedByCompositeWithID could get called by a thread other than the main thread when the delegateQueue parameter to the factory method was nil.
  5. Fixed bug in which requestsResolveOfCompositeWithID would not get called unless a completionHandler was also passed to a call to pullMinimalComposite.
  6. Prevent delegate methods from being called multiple times if resumeSyncForComposite is called more than once.
  7. Changed AdobeDCXComposite's commitChangesWithError to only cause a requestsPush delegate call from the controller if the state of the composite is Modified or PendingDelete.
  8. Updated AdobeDCXController to protect against a run-time exception that has been reported in rare cases.

- (potentially internal-only) A new domain added to the list of ATS (App Transport Security) exception list. Brightcove.com was added to the list of ATS exceptions to allow some older CCV videos to be play back.
- (internal only) Auth tokens are no longer returned as nil if expired.  The recommendation is for client apps not to use Auth tokens directly, but calling out the change.  A client app can use `AdobeUXAuthManager hasValidAccessToken` to determine if the access token exists and hasn't expired.
- (internal only) StockModel and StockUX are now correctly packaged with internal frameworks.  These frameworks are not yet available to third-party developers.
- (internal only) `licenseWithPriority` was moved from `AdobeStockAsset.h` to `AdobeStockAsset+Protected.h`.  This method is not expected to be usable by third-party developers. 
- Changed minimum iOS version from 7.0 to 8.1.
- Enabled support for bitcode.
- Add support for stock_id on stock search queries and when adding stock comps or licensed assets to libraries.
- (internal only) Phase I of refactoring is complete. A temporary list of moved and renamed header files can be found in this wiki -- https://wiki.corp.adobe.com/display/EcoSDK/CSDK+Header+Refactoring. In phase II, coming in the next master build, we'll have umbrella headers for each framework to insulate clients from future changes.

### Build 0.1.2124 (2015-09-25)
##### What's New
- Fixed an issue that prevented Loki from being able to use disable license/save button options

### Build 0.1.2122 (2015-09-23)
##### What's New
- Fixed Watson 4060859: Draw can sometimes crash on launch and not recover
- Fixed Watson 4061799: ETS app.launch events are generated too many times
- Fixed Watson 4062564: Force quitting app leads to crash on startup when using VERBOSE LOGGING
- Fixed Watson 4062611: Open a licensed image will invoke "You must have an Adobe Stock Subscription..." message

### Build 0.1.2121 (2015-09-21)
##### What's New
-  Fixed Watson 4060002: 360 menu does not filter based on accepted types

### Build 0.1.2120 (2015-09-18)
- Fixed Watson 4051913: Action view controller hangs after log out
- Fixed Watson 4049196: Localized strings of Action item are not displayed for some regions
- Fixed Watson 4046400: Upsell is visible for workflows even for paying CC members.
- Added new version of copyChild method on AdobeDCXCompositeMutableBranch with a newId parameter
- Fixed Watson 4052698: DCX synchronization slows down considerably once composite has lots of composites
  - Eliminated superfluous file writes for each component
  - Eliminated extraneous "saved" events in the xmp metadata component
- Added a new "Adobe Stock" browser component.
  - The Stock functionality is being delivered in separate model and ux frameworks: AdobeSDKStockModel.framework and AdobeSDKStockUX.framework.
  - The Stock component browser is being provided as a view controller, AdobeStockAssetsViewController, which is a new direction for the SDK w.r.t. how we present our browser components.
  - There is now an integration of the Stock component with Libraries. Stock elements are added using "external link representations". You may need to update your client code to use the latest Adobe Library Manager.
  - To support Stock assets in the "Library Assets" panel of our asset browser, the class AdobeAssetLibraryItem has a new property called "hasExternalLinks". If a selected library asset has this set, then you should use the Adobe Library Manager to fetch the comp or licensed external links. For stock assets, the image and rendition properties on AdobeAssetLibraryItemImage will all point to the rendition image.
- (internal only) Added `decodeToken` method to `AdobeAuthLogging`.   This can be helpful to display clientID features like its scope.  Available only on DEBUG builds.
- (internal only) Added `verboseAuthLogging` property to `AdobeAuthLogging`.  The property enables verbose auth output to the Xcode device console. The verbosity level is controlled by `changeLogLevel` in `AdobeCommonLogging`.
- (internal only) Added partial ETS data collection.
- copyChild and copyComponent methods on AdobeDCXCompositeMutableBranch now allow for copying DCX manifest nodes and components when the component file isn't present on local storage but exists on the server.
- Fixed retain cycle in DCX pullComposite operation that could lead to leaked instances of AdobeDCXController.
- The relative order of execution of `AppDelegate` and `MainViewController` methods at startup may change with each iOS version.  When upgrading to iOS 9 check that `setAuthenticationParametersWithClientID:` is called before any other authentication functionality .

### Build 0.1.2119 (2015-08-21)
##### What's New
- Added support for 360 Workflows. For a comprehensive guide for using workflows, please consult https://wiki.corp.adobe.com/pages/viewpage.action?pageId=1011604180. 
- Applications using the Core framework now require linking to libz.dylib.
- ** INTERNAL ONLY ** AdobeCommonAccountViewController.h is included in CreativeSDKCommonUX-internal.framework.  This allows internal clients to be able to access to this view controller to display user's account information. Also enable the user the ability to switch account.
- Deprecate support for iOS versions prior to iOS8.
- Discontinue building the following extension binaries: AdobeCreativeSDKAppLibraryUXExtension, AdobeCreativeSDKMarketUXExtension, AdobeCreativeSDKFoundationExtension. Until we complete our extension transition plan with the Loki team later in the year, we will continue building the following extension binaries:  AdobeCreativeSDKAssetModelExtension, AdobeCreativeSDKAssetUXExtension, AdobeCreativeSDKCommonUXExtension, AdobeCreativeSDKCoreExtension. 
- Cease building the monolithic Foundation framework which have been replaced by the new split frameworks.
- Added the `developmentMode` property to `AdobeAuthUserProfile`.  The property indicates the application's clientID allows a restricted number of AdobeIDs.  SDK components can use the property to visually alert the developer about the restriction.  Intended mostly for 3rd-party developers.
- Fixed bug in DCX removeLocalFilesForComponentsWithIds method that prevented components from being found in local storage after a subsequent call to downloadComponentsForCompositeBranch.
- Fixed bug in DCX pullComposite method that could cause the pulled branch to refer to a locally-modified component in certain circumstances.
- Updated DCX pushComposite method to recover from a previously interrupted push operation in which a server-to-server component copy request ultimately succeeded without resorting to unnecessarily uploading the file from the client.
- Fixed bug in ETS event logging to prevent recently-injected crash that could occur when canceling DCX operations.
- Refactored the Market model. APIs in the model now have the "proper" method signatures applied to them. That is, no more prepositions to match Apple's latest coding guidelines. Most APIs with the old signatures have been deprecated with a message pointing to the new API, with one exception: [MarketAsset downloadRenditionWithDimension]. Part of the Market refactor introduces a new set of superclasses AdobeCommunity*, in which Market is just one of them.
- New Creative Cloud icon in all UX browsers.
- New API for presenting App Library & deprecated old API.
- New data sources (Mix and Comp) in the Asset Browser

### Build 0.1.2118 (2015-07-17)
##### What's New
- The monolithic Foundation SDK has been broken up into six smaller SDKs.
  - The component SDKs are described in: https://wiki.corp.adobe.com/display/EcoSDK/Foundation+SDK+Breakup
  - User guide: https://wiki.corp.adobe.com/display/EcoSDK/Using+the+Split+Foundation+CSDKs
- More helpful empty/no file screen for Illustrator Draw, Illustrator Line and Photoshop Sketch datasources. These empty screens now have a helpful description about what each app does and what benefits there are in using them. Each app can also be downloaded by tapping the available download button from the App Store.
- The App Library is redesigned with new sort options and catgegory/subcategory filters.
  - The categories expand to show subcategories when there are a significant number of apps under the category.
  - Existing category filter & sort option APIs are deprecated.
- Updates to handling of library item selections in the Asset Browser:
  - We no longer automatically filter out brushes, character styles, or layout styles.
  - Added the library ID to the returned library selection info.
  - Fixed rounding issues with displaying colors or color hex values as names in certain situations.
  - Removed deprecated color properties/methods.
- (internal only) AGC: Two new apis have been added to create a PSD and AI file using the AGC workflow. They are found in their respective AdobeAsset*File classes with the method name "create".

### Build 0.1.2113 (2015-07-13)
##### What's New
- Bug Fix for Watson 4018929: Library is not accessible after app is used with a device, force-quit, logged out and logged in again
- ** INTERNAL ONLY ** AdobeCloudManagerDefaultCloudUpdatedNotification is now being sent on all updates to defaultCloud.

### Build 0.1.2112 (2015-07-09)
##### What's New
- (internal only) Bug Fix for Watson # 4018200 — [Hot Fix] [CCE] New Uploads Displayed As 1:1 in 1UP & Grid View
- (internal only) Bug Fix for Watson # 4009528 — Dilato: iOS: [LOC]: All Languages (except RUS): String "Enterprise ID" is over-localized on "You are currently signed in with an Enterprise ID" dialog.

##### Known Issues
- To cancel downloading master data or proxy data of Lightroom Photo assets, use `cancelDownloadRequest` method instead of `cancelDownloadMasterDataToFileRequest` method
- The `downloadToPath:` method of AdobeAssetFile, AdobeMarketAsset and AdobePhotoAsset classes increments memory usage per download on iOS 8. We will work with Apple to resolve this issue.
- (internal only) Calls to `-getRenditionWithType:` with type `AdobeAssetFileRenditionTypeJPEG` will not work while on private clouds.

### Build 0.1.2111 (2015-07-06)
##### What's New
- (internal only) Bug Fix for Watson # 4013603 - Sketch does not sync as synthetic default cloud is not reset to real cloud after going back online.

### Build 0.1.2110 (2015-06-24)
##### What's New
- (internal only) Restored the previous behavior of the async refreshClouds method to invoke completion blocks on the main thread.
- Bug Fix for Watson # 4011588 - Blank cloud list appears after log out and log in.
- Fixed an issue where the hashedAdobeID was not cleared on logout.

### Build 0.1.2108 (2015-06-22)
##### What's New
- (internal only) Added a synchronous version of the refreshClouds method to the AdobeCloudManager: (BOOL)refreshCloudsWithError:(NSError **)errorPtr;
- (internal only) The asynchronous refreshClouds: method used to always call the completion blocks on the main thread. This is no longer the case, and clients should ensure that they dispatch back to the main thread if needed.
- (internal only) Use the eTag when encoding the eTag rather the GUID. This was a small issue, most likely a typo, that could end up having more serious repercussions.
- Bug Fix for Watson # 4010643: [Hot Fix] Color CC: App crashes on closing live view
- Bug Fix for Watson # 4010252: [Hot Fix] ECR: need a sync version of the refreshClouds API
- Bug Fix for Watson # 4002345: [Hot Fix] [PrivCloud] After changing private cloud, CC My Files display generic file icon with no thumbnail of file asset (Sketch/Draw/Line)
- Bug Fix for Watson # 4010993: [PrivCloud] Private Cloud still showing in cloud picker after user was removed access to this private cloud ( Sketch/Draw/Line)


### Build 0.1.2106 (2015-06-21)
##### What's New
- Bug Fix for Watson # 4010190: [CCE] First party apps only: user interaction is blocked if there are no cloud objects to use after upgrading app version
- Bug Fix for Watson # 4009480: [CCE] Draw: Current cloud not remembered after relaunch in some cases

### Build 0.1.2103 (2015-06-10)
##### What's New
- Bug Fix for Watson # 4000522: Pulling components during PSD extraction fails when pointing to AEM instance.
- Bug Fix for Watson # 4001386: Comp: [Ship Stopper] Sync false state:  Projects in gallery are not showing.
- Bug Fix for Watson # 4004789: [CCE] App crashes when switching clouds repeatedly.
- Bug Fix for Watson # 4004805: PS Mix: CC library content is not shown first time after sign in.
- Bug Fix for Watson # 4007131: [CCE] Asset browsers call refreshClouds when the user doesn't specify a cloud even if a defaultCloud is set.
- Bug Fix for Watson # 4000461: [CCE] Public - Market allows shows incorrect list of Libraries on the account for public disabled key accounts.
- Bug Fix for Watson # 4002316: [CCE] [PrivCloud] - Cloud Details are duplicated in cloud picker.
- Bug Fix for Watson # 4005526: Animation to bring up CC My Files and From Market browsers is not smooth, a third of the screen blank before filling pane (Sketch/Draw/Line).
- Bug Fix for Watson # 4005719: AdobeAssetFolder getNextPage does not return a result via the success or error blocks when invoked while the device is offline/in airplane mode.
- Bug Fix for Watson # 4002282: Comp: Library sync activity after clean install gives Assert in AdobeLibraryManager.

### Build 0.1.2100 (2015-06-10)
##### What's New
- Bug Fix for Watson # 4004274: CMYK/Lab/RGB color themes are shown incorrectly in ColorComponent 
4003034: [Must Fix] Comp: AdobeCloudManager does not return a result via the success or error blocks when invoked while the device is offline/in airplane mode.
- Bug Fix for Watson # 3998072: Image service related features doesn't work
- Bug Fix for Watson # 4002543: CCEP: PSMix crash on import from CC Lib
- Bug Fix for Watson # 4002404: [CQ-43995] CCEP: Save to library didn't save any files after popped up "Stored in Library"
- Bug Fix for Watson # 4003208: Sketch: Backup in Progress continues until all the projects synced down.
- Bug Fix for Watson # 4002419: Dilato: iOS: iPad only: [Core]:  Arrow hasn't point to the Layer icon for "Images" list when there are many Draw Layers in current drawing.

### Build 0.1.2099 (2015-06-05)
##### What's New
- Bug Fix for Watson # 3997904: Crash when repeatedly switching CCE Private clouds.
- Bug Fix for Watson # 4000624: [Must Fix] Comp: Datasource filter does not filter out CC Libraries

### Build 0.1.2098 (2015-06-03)
##### What's New
- None Documented

### Build 0.1.2097 (2015-06-02)
##### What's New
- Bug Fixes for Background Transfers in the Extension and DCX updates.

### Build 0.1.2096 (2015-05-29)
##### What's New
- Added a new class, AdobeNetworkBackgroundTransferManager, that handles most of the background transfer functionality.
- AdobeNetworkBackgroundTransferManagerDelegate can be adopted to receive callbacks when background transfers complete (upload or download).
- Enabled background transfer mode in test app capabilities.
- Added the `clearAllUserDataCaches` method to `AdobeCommonCache`.  The method clear only the caches with Creative Cloud user data.  It does not clear caches used internally by the Foundation SDK, in particular, the entitlements cache which keeps the clouds information.  Clients are required to use this method instead of `clearAllCaches`.
- Bug fixes.

### Build 0.1.2093 (2015-05-22)
##### What's New
- Removed the public cloud from user's list of clouds if the user has 0gb quota.
- Added support for path prefixes for private cloud endpoints.
- Deprecated `Base64Encoding` and `ModifiedBase64FilenameEncoding`. These classes and the corresponding header file will be removed in the next SDK release. Use the relevant NSData methods for plain Base64 encoding and decoding. There is no alternative for the `ModifiedBase64FilenameEncoding`. If you require that functionality, please provide your own implementation.

### Build 0.1.2092 (2015-05-15)
##### What's New
- Improved error reporting and miscellaneous bug fixes, in particular fixing URL redirections.
- Displaying a full overlay when invoking the Market Browser on a private cloud indicating the feature is not yet available.

### Build 0.1.2091 (2015-05-13)
##### What's New
- The SDK now includes `sao.cce_private` as a default scope for 1st-party apps' private cloud access.  1st-party apps need to have the `sao.cce_private` scope whitelisted by IMS.  We have requested whitelisting of the known set of clientIDs that require private cloud access.  Please check your clientID is whitelisted properly.

### Build 0.1.2090 (2015-05-11)
##### What's New
- None Documented

### Build 0.1.2089 (2015-05-07)
##### What's New
- Added support for private clouds to our send-to-desktop functionality.
- Improvements were made to AdobeEntitlementServices.

### Build 0.1.2088 (2015-04-29)
##### What's New
- Added new copyFile methods to AdobeStorageSession+Files.
- File extension to mime type mapping changes:
  - `IDML` to `application/vnd.adobe.indesign-idml-package`
  - `SHAPE` to `image/vnd.adobe.shape+svg`
- Added ability to control logging level to the CSDK test app.
- Fixed paging of Lightroom Photo collections.
- Added rootNode property to AdobeDCXCompositeBranch.
- Important: Fixed bugs in component garbage collection for AdobeDCXComposite that could lead to missing components.
- Fixed bug in AdobeDCXController where it would still request a subsequent 'push' even when a push conflict had been resolved with the unmodified pulled branch.
- Fixed bug in AdobeDCXController which could lead to it dispatching a requestsResolveForCompositeWithID for an incomplete composite (i.e. a composite with missing components) if the application had previously been terminated in the middle of a pullComposite operation.
- Removed some deprecated DCX APIs, and deprecated and replaced DCX APIs that have parameters that refer to the local storage scheme used by a composite (mostly initalizers and factory methods). These newly deprecated initializers now return an error if the old AdobeDCXLocalStorageSchemeDirectories is specified.
- Changed internal method -- [AdobeStorageSession service] can no longer be called by 1st-party apps due to the CCE workflows. Instead [AdobeStorageSession serviceForSchemaId:schemaId] where schemaId is either: AdobeStorageSessionFileServiceTag, AdobeStorageSessionAssetServiceTag, or AdobeStorageSessionLibraryServiceTag.
- Deprecated `setAuthenticationParametersWithClientID:withClientSecret:` in favor of `setAuthenticationParametersWithClientID:clientSecret:enableSignUp:` to allow new user sign up in 3rd-party apps.
- Added internal method `loginWithDeviceToken:success:error` to `AdobeUXAuthManager`.  Internal client apps can use this method in cases where user login is required, but the SUSI dialog must not be presented (e.g., Touch ID).
- Now displaying the user's profile picture in the account information view.

### Build 0.1.2082 (2015-03-17)
##### What's New
- Augmented `AdobeAuthLoginDelegate` to give apps more control when to dismiss the login view controller. Fixed typo in `promptUserWithLoginUI` method name.
- Added support for Auth verbose logging in Release builds.  Apps wanting to control Auth verbose logging can do so by accessing the `keyAdobeCreativeSDKVerboseAuthLogging` key in `NSUserDefaults`.
- Removed the `utcOffset` property (e.g., the user time zone) from `AdobeAuthUserProfile`.  It's not supported on IMS; it always returns `nil`.
- DCX: fixed bug in which acceptPushWithError was not properly setting the state of the merged composite to be “modified” under some circumstances if the current composite had no modified components.
- DCX: Added new version of addComponent method that includes an optional sourceHref parameter and added support for making server-to-server copies of components which already exist on the endpoint to which a composite is being pushed.
- DCX: Fixed bug where a subsequent call to getChildWithAbsolutePath would return the incorrect manifest node after calling updateChild with a node that did *not* have an updated path.
- DCX: Fixed bugs in which component files that were copied or moved into a composite’s local storage as a result of calling addComponent or updatedComponent would remain in the event that an error occurred while updating the composite’s DOM.  Fixed similar issues if an error occurs when calls to copyChild and copyComponent are copying components across different composites.
- DCX: Fixed a crash that could occur when calling acceptPush on a composite marked as ‘PendingDelete’ when the composite has an assigned AdobeDCXController.
- CC Library API changes: Support for multiple delegates that can register with AdobeLibraryManager.
  1. AdobeLibraryDelegate: each delegate now has its own set of startup options for filtering element type and auto sync downloading options. See AdobeLibraryDelegateStartupOptions.
  2. AdobeLibraryManager: startupWithOptions is now startupWithFolder and only takes the root folder, storage session and an error ptr. Each delegate should now use registerDelegate to specify their options and register with the library manager. deregisterDelegate should be used to remove a delegate.
  3. AdobeLibraryComposite: elements, elementsWithFilter, countElements, and insertElement now take the delegate as a parameter.
- DCX: Updated AdobeDCXUtils convertLocalStorageScheme method to convert base branch manifests, in addition to current.
- DCX: Added new ‘committedCompositeState’ property on AdobeDCXComposite to provide access to the saved composite state without having to rely on the deprecated and soon-to-be-removed ‘localCommitted’ branch.
- Deleted the deprecated `sendItem` method from the public `AdobeSendToDesktopApplication` API.  Its functionality is covered by the other public methods.
- Added cancellation and progress report to `AdobeSendToDesktopApplication`.  Added new methods, `cancelSendToDesktopRequest` and `changeSendToDesktopRequestPriority` to cancel or change the priority of a request.
- The `AdobeSendToDesktopApplication` send methods now return a request token that can be used to cancel or change the priority of the request.
- Ability to Download Large Photo Assets and handle Proxy Data in AdobePhotoAsset class
  - Added a new method which allows large Lightroom Photo assets to be downloaded easily without consuming a significant amount of memory. This new method compliments the existing `downloadMasterData:onProgress:onCompletion:onCancellation:onError:` method.
  - Added new methods for downloading proxy data for Lightroom Photo assets.

### Build 0.1.2080 (2015-03-05)
##### What's New
- Fixed a memory leak in `AdobeUXAuthManager login`.
- Fixed an unexpected logout bug when upgrading from old versions of the SDK.  Encountered when upgrading from the MAX 2014-timeframe SDK.

### Build 0.1.2078 (2015-02-18)
##### What's New
- Changed the AdobeAuthKeychain implementation to use the iOS keychain instead of encrypted values in the NSUserDefaults.  Change needed to comply with ASSET requirements.
- Ability to Download Very Large Assets
  - Added new methods to `AdobeAssetFile` and `AdobeMarketAsset` which allow very large files to be downloaded easily without consuming a significant amount of memory. These new methods compliment the existing `getData:onProgress:onCompletion:onCancellation:onError:` (`AdobeAssetFile`) and `download:withMimeType:onProgress:onCompletion:onCancellation:onError:` (`AdobeMarketAsset`) methods.
- Support for a new protected version of [AdobeAsset PSDFilegetRenditionForLayers] that support batch mode rendering of multiple layers. An array of layer nodes is passed in to this API.  The image service render API now supports multiple layer ids being passed in and returns a multipart/mixed payload with the image data for the layers. This should improve the render performance of the layer image cells in the collection views.
- Support the ability to pull a minimal Composite object that only includes a manifest. Layer components are only pulled down from service when the user wants to open a selection of layers and return them. This works in conjunction with a new image service introspect API which returns a psd preview object contains all requisite meta data to render the PSD extract workflow. Pulling just the psd preview object should download quicker than pulling an entire PSD composite object so the UI is much more responsive. The UI is not blocked by the pullMinimalPSDComposite call since that happens in the background.
- Added a zoomable, fullscreen view for the Market Asset browser on iPad. Tapping on an asset from the details view now hides the navigation and status bars and allows for zooming (similar in behavior to the Asset browser.)
- Moved Market Asset metadata info (on iPad) into an 'info' popover, accessible from the navigation bar in the Details view. This behavior is now consistent with the iPhone version of the Market Asset browser.

### Build 0.1.2076 (2015-02-17)
- Optimized Market images to reduce bundle size

### Build 0.1.2074 (2015-01-29)
- Change deblur function in AdobeImageSession.h (Add a new param "optimized")
- Fixed LR Photos to properly handle spaces in collection and asset names (no more percent escaping).
- Some of the AdobeLibrary header files are now public.
  - Clients will need to update any import statements for the relocated files from <nowiki>&lt;</nowiki>AdobeCreativeSDKFoundation-Internal/...<nowiki>&gt;</nowiki> to <nowiki>&lt;</nowiki>AdobeCreativeSDKFoundation/...<nowiki>&gt;</nowiki>
  - If a client was including all of the libraries related headers via AdobeLibrary.h, that file is now in public also but is the limited read-only public version of the API. To get full access as before, clients should now import <nowiki>&lt;</nowiki>AdobeCreativeSDKFoundation-Internal/AdobeLibraryInternal.h<nowiki>&gt;</nowiki>
- Updated AdobeSendToDesktopApplication:
  - Added sendAsset and sendLocalFile methods for sending CC files and local files to a desktop application.
  - Added support for CC /asset objects.  Sketch drawings can be sent to a desktop application.
  - All methods in the class changed their signature for consistency.  All methods now include onProgress and onCancellation block arguments.  Support is in progress.
  - Deprecated sendItem method.  It is still available, but it will be removed from the public API in a future release.
- Fixed some issues around handling etags and HTTP 304 responses when fetching a file's data from cc-storage.
- Added analytic events when creating Photoshop and Illustrator files.
- Added Market Assets feature for iPhone:
 - feature parity with iPad version
 - includes ability to zoom in on Asset view

### Build 0.1.2073 (2014-12-18)
##### What's New
- Removed the phoneNumber property from AdobeAuthUserProfile to reduce the amount of PII on the device.
- Added sendImage and sendData methods to AdobeSendToDesktopApplication.  Deprecated sendItem from the public API.
- Several minor bug fixes in AdobeDCXController
- Support for hiding Design Library interface in browser.
- Support for filtering out specific Design Library Asset types.
- Support checking "renderable" file flag from CCStorage directory metadata to short circuit rendition fetching for files types that don't support renditions. This should cut down on the number of 415 errors that the CCStorage service is seeing.

### Build 0.1.2068 (2014-12-10)
##### What's New
- The "Send to Desktop" feature now uses the api-gateway (adobe.io) endpoints.
- Removed all AdobeClean fonts with the exception of: AdobeClean-Regular, AdobeClean-Light,	AdobeClean-LightIt,	AdobeClean-Bold
- Consolidated common images into Common resource bundle.
- Security enhancements:
  1. Moved auth keychain from NSUserDefaults to the iOS keychain.
  2. Stopped saving auth tokens in URL cache.
- Added the following properties to AdobeAuthUserProfile:
  - isEnterpriseUser
  - fullName
  - phoneNumber
  - countryCode
  - utcOffset
  - preferredLanguages

- DCX API changes (see the DMA team wiki for more details: https://wiki.corp.adobe.com/display/dma/Home)
  1. New AdobeDCXController class replaces AdobeDCXSyncController (now deprecated)
  2. New downloadComponents:ofCompositeBranch: method replaces pullComponents:ofComposite: (now deprecated) on AdobeDCXCompositeXfer
  3. localCommitted property of AdobeDCXComposite has been deprecated 

- Critical DCX fix for bug introduced in Build 0.1.2067 for acceptPushWithError: and mergePushedBranchWithCurrentOfComposite: methods
  that could lead to incorrect component length getting recorded during overlapping composite push and local component update operations 

### Build 0.1.2067 (2014-11-11)
##### What's New
- Add page number to cache key for AssetFile
- Fix crash in Shape when sync is disabled just before a push or pull completes
- Fix crash when libraries list changes while being iterated by client
- Fix problems that can occur with triggering multiple pulls or pushes on the same library
- Fix problems with syncOnCommit flag
- Cancel active download representation requests (in addition to active pulls and pushes) when the manager shuts down
- Fix a problem where elementWasRemoved is not always sent to the delegate
- Remove an unnecessary assert when we do a push and nothing was changed
- If you're currently running into symbol duplication in your project for in app purchase, please do the following:
  1. Remove all of the sources around InAppPurchase that were copied from Loki:
     - AdobeiTunesServiceSession_Private.h
     - AdobeiTunesServiceSession (.h/.m)
     - AdobeiTunesServiceSession+Singleton.m
     - AdobeiTunesParsers (.h/m)
     - Base64Encoding (.h/.m)
  2. Replace calls to requestProductIDsWithCompletionBlock: with -[AdobeUXInAppPurchase checkUpgradeAvailability:]​

#### Build 0.1.2066 (2014-11-10)
#####What's New
- Fixed SSO

#### Build 0.1.2065 (2014-11-07)
#####What's New
- DCX API changes and deprecated functions, for more details see https://wiki.corp.adobe.com/display/dma/Home
  1. New acceptPushWithError: method replaces acceptPushedBranch: (now deprecated) on AdobeDCXComposite
  2. New resolvePullWithBranch: method replaces acceptPulledBranch: (now deprecated) on AdobeDCXComposite
  3. New removeLocalFilesWithError: method replaces removeLocalFiles: (now deprecated) on AdobeDCXComposite
  4. New removeLocalFilesForComponentsWithIDs: method has been added to AdobeDCXComposite
  5. New localStorageBytesConsumed property has been added to AdobeDCXComposite
  6. New markCompositeForDeletion method on AdobeDCXCompositeMutableBranch will set the compositeState property to AdobeDCXAssetStatePendingDelete
  7. The compositeState property is now automatically set to AdobeDCXAssetStateModified whenever changes are made to the the current branch
     and should no longer be set by the client.  It proved impossible to mark only the setter for this property as being deprecated, but
     clients should consider it officially deprecated. It will become read-only in the future.

- Fixes for authentication and network connection issues
- Lots of bug fixes

#### Build 0.1.2063 (2014-10-15)
#####What's New
- Exposed the popupAppLibraryWithParent call in the public header file.
- Added run-time checking to return an error if a valid parent view controller does not exist for App Library, Market Browser, and the Asset Browser.

#### Build 0.1.2062 (2014-10-14)
#####What's New
- Updated Creative SDK to compile on Xcode 6 and use the iOS 8 SDK. Compiling on Xcode 5 is no longer supported.
- Design Library support for iPhone.
- Bug Fixes

#### Build 0.1.2060 (2014-10-07)
#####What's New
- Ability to browse drawings from Illustrator Draw, Illustrator Line, and Photoshop Sketch
- Design Library support (iPad only)
- Bug Fixed: Behance SDK Bug Fixed - crash when invoking edit user profile

#### Build 0.1.2054 (2014-09-25)
#####What's New
- Bug Fixed: iOS 8 Xcode6 only: Preview does not display after selecting thumbnail in the grid view (3829733)
- Bug Fixed: Files and Photos: flipping device in 1up is not smooth, asset is moved before centering (3823080)
- Bug Fixed: 1up does not maintain zoom after flipping device orientation (3823117)
- Bug Fixed: Pinch to zoom is not centered around the target area (3827023)
- Bug Fixed: double tap zoom to the wrong spot (3827024)

#### Build 0.1.2053 (2014-09-24)
#####What's New
- Bug Fixed: iOS8 - on clean install of iOS8, installing Sketch, sign in, delete the app, then restarting the OS bricks the device (3830612)
- PSD Extraction: Clear read-only bits on orphaned DCX files
- Bug Fixed: Not all LightRoom photos are visible in the Asset Browser (3830831)

#### Build 0.1.2046 (2014-09-23)
#####What's New
- Bug Fixed: Device SDK: Draw app crashes on selection of Share from Share menu from Pen tip menu (3829890)
- Bug Fixed: Not all LightRoom photos are visible in the Asset Browser when scrolling (3829173)
- Bug Fixed: [LOC] In File Browser under 'Photos', there is a mock string still left for "You don't have any collection yet" (3829032)
- Bug Fixed: Intermittent "Send Failed" error message in Sketch/Draw/Line when trying to Send to Illustrator/Photoshop (3827907)
- Bug Fixed: Behance SDK: Memory Crash when adding image via camera after open the 'get feedback' (3829105)
- Bug Fixed: Draw: App crashes on getting Design Library info after closing Market Browser (3829158)
- Bug Fixed: Device SDK: The battery icon for Adobe Ink is at low res on non-retina display (3827851)

#### Build 0.1.2046 (2014-09-21)
#####What's New
- Asset Browser v2 Full Screen and redesign of asset browser UI with LR photo support
- AI Creation APIs
- Market component with Design Libraries support
- Bug Fixed: Download Market asset fails and Market Browser is blank next time it opens (3828703)
- Bug Fixed: iOS8: Market Browser view is placed off center downward in landscape mode (3828749)
- Bug Fixed: Draw/Line/Sketch will crash when Cancel button from Share option in iOS8 (3827905)
- Bug Fixed: Need to change Enable slide icon for retina display from pen drop down menu (3826912)

#### Build 0.1.2040 (2014-09-16)
#####What's New
- Show the video view even if the video asset hasn't finished transcoding. If the user taps on the play button, show an alert saying the video is still being transcoded and use that to trigger a check for the HLS URL.

#### Build 0.1.2039 (2014-09-12)
#####What's New
- Bug fix: App crashes by navigating between 1-up and main view while video is being transcoded (3823777)
- DCX: Fixed garbage collection bug that could lead to the failure of pushComposite due to the deletion of referenced component files that had been updated and committed in the compositeâ€™s current branch while the push was in progress. 
- DCX: Address Stan's report of suspicious (possibly buggy) code in AdobeDCXCompositeXfer.m

#### Build 0.1.2036 (2014-09-11)
#####What's New
- Bug fix: Switch Accounts button renders incorrectly on iPhone 6 and 6+ (3821923)
- Bug fix: Search header does not fill screen on iPhone 6 and 6+ (3821925)
- Bug fix: Exception is returned when attempting to access lightroom catalog (3822952)
- Bug fix: Receive AdobeDCXErrorUnknownComposite errors, rather than generic AdobeAssetErrorUnexpectedReponse, when attempting to push a composite that has been, or is being, deleted from the server

#### Build 0.1.2034 (2014-09-10)
#####What's New
- Fix the search bar width for iPhone 6 and 6 Plus
- Edit Profile: configurable capture session preset, prefer front facing camera

#### Build 0.1.2033 (2014-09-05)
#####What's New
- Ability to hide Switch Accounts option from SDK on iPhone
- Update Device SDK

#### Build 0.1.2032 (2014-09-03)
#####What's New
- Send to Desktop: capability to push an asset to a desktop application via Creative Cloud. Creative Cloud for desktop application (Photoshop CC and/or Illustrator CC) needs to be installed on the target desktops and signed in with the same Adobe ID as signed in with Creative SDK apps. https://creative.adobe.com/products/creative-cloud
- Illustrator File Creation: capability to create an Adobe Illustrator file from an SVG file and save it in Creative Cloud. Available only on Image Service stage systems
- Video Streaming in Browser
- Analytics (Available for Internal Adobe first parties only). For more info contact Kim Ortiz.
