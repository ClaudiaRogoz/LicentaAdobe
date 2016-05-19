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

#ifndef AdobeCommonTypesHeader
#define AdobeCommonTypesHeader

/**
* Visual Layout for the storage component.
*/
typedef NS_ENUM (NSInteger, AdobeBrowserVisualLayout)
{
/**
* No visual layout.
*/
AdobeBrowserVisualLayoutNone = 0,

/**
* List view where assets are displayed in a list.
*/
AdobeBrowserVisualLayoutListView = 1,

/**
* Grid view where assets are displayed in a grid view with large thumbnails.
*/
AdobeBrowserVisualLayoutWaterFall = 2
};

/**
* Selection mode for the storage component.
*/
typedef NS_ENUM (NSInteger, AdobeBrowserSelectionMode)
{
/**
* Single select mode. Only a single file at a time can be viewed or opened.
*/
AdobeBrowserSelectionModeSingle = 0,

/**
* Multi-select mode. Multiple assets can be selected and opened.
*/
AdobeBrowserSelectionModeMulti = 1
};

/**
* Options for sorting items.
*/
typedef NS_ENUM (NSInteger, AdobeBrowserSortState)
{
/**
* Sorting items in ascending order.
*/
AdobeBrowserSortStateAscending,

/**
* Sorting items in descending order.
*/
AdobeBrowserSortStateDescending
};

/**
* Describes all the different sort types offered by the UI.
*/
typedef NS_ENUM (NSInteger, AdobeBrowserSortType)
{
/**
* Sorting items by date and time.
*/
AdobeBrowserSortTypeTime = 0,

/**
* Sorting items alphabetically.
*/
AdobeBrowserSortTypeAlpha = 1
};

typedef NS_ENUM (NSInteger, AdobePhotoSortType)
{
/**
* Sorting items by date and time.
*/
AdobePhotoSortTypeTime = 0,

/**
* Sorting items by cusom order.
*/
AdobePhotoSortTypeCustom = 1
};

typedef NS_ENUM (NSInteger, AdobePhotoBrowserView)
{
/**
* Show all photos.
*/
AdobePhotoBrowserShowAllPhotos = 0,

/**
* Show collections.
*/
AdobePhotoBrowserShowCollections = 1
};

#endif /* ifndef AdobeCommonTypesHeader */
