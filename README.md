
# Visual assets management

###### Prerequisites

1. XCode (it was tested for Version 7.2.1)
2. Adobe Experience Design (it was tested for Version 0.5.4.28Beta)
3. ImageMagick (the application makes use of the `convert` command within ImageMagick; used for exporting paths and lines)


(Please see section *Further Work*)
###### Build steps


* Run
```
mkdir [path-to-VisualAssetsManagement]
git clone git@git.corp.adobe.com:crogoz/VisualAssetsManagementXD.git
cd [path-to-VisualAssetsManagement]
```
* Open *XDXCodeTranslator.xcodeproj* with XCode
* Build the project
* Run 

```
cd [path-to-VisualAssetsmanagement]/Build/Products/Debug/XDXCodeTranslator.app/Contents/MacOS
```
* The executable file is named `XDXCodeTranslator`
	* Available arguments: 
		```
		./XDXCodeTranslator [-h|-i [-nosync]|-e] <path1> <path2>
		```
	where 
		- \-h  = help;
		- \-i [-nosync] <xcodeProjectDirectory> <xdFullPath> : translates an XCode Project into an XD one; If no *-nosync* parameter, then the Xcode project will be updated based on the latest changes within the xd file (the updates will be done when the xd file is saved); If *-nosync*, the app will only translate the XCode project into the XD;

			Example:
				``` ./XDXCodeTranslator -i [path-to-VisualAssetsManagement]/SampleProjects/Test/Test ~/anXDFile.xd ``` : creates an xd file named *anXDFile.xd* in the home directory; Because *-nosync* is not specified, the Xcode project will be updated based on the modification from the xd file
		- \-e xdFullPath xcodeProjectDirectory : translates an XD project into an XCode Project;
			
			Example:
				```
				./XDXcodetranslator -e ~/anXDFile.xd [path-to-VisualAssetsManagement]/SampleProjects/Test/Test
				``` : translates the xd file named *anXDFile.xd* into the XCode project



**Important** : the Xcode path will be the full path to the Xcode project that contains the directory named *Base.lproj*
**Important** : all paths should be absolute
###### Sample Projects

The *SampleProjects* directory contains 2 projects: 
	1. an XCode project: SampleProjects/Test/Test
	2. an XD project: SampleProjects/xd_tutorial.xd

###### Assets that can pe properly recognized & translated

1. simple view controllers
3. scenes with only 1 view
4. transitions
5. groups (from XD)
6. labels, text, text area...
7. imageView(XCode)/image (XD)
8. buttons(XCode)
9. different paths (including lines) are translated from XD to XCode as png using ImageMagick
10. only **single line text** can be translated as button into XCode (the schema must be extended for multiline text)
11. paths CANNOT be translated as buttons (the schema must be extended)
 
###### Further Work

Used version 0.9 for the manifest.json file (within the xd) : "uxdesign#version" : "0.9".
The version number can be updated in the "manifest.json" file within the current project; (in the Xcode project, the *manifest.json* file is in the *AgcResources* Group)
