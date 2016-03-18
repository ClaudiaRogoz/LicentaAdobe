# VisualAssetsManagementXD
Run Project:

        -> Xcode

        -> input: Set 2 arguments:
		argv[1]: .xml file (Storyboard representation -> ${XcodeApp}/Base.lproj/Main.storyboard)
        	argv[2]: path to image resources

	-> output: $HOME/Documents/${input_file_name}_out.agc (agc file for Comet , just drag & drop)

-------------------------------------------------------

Supported objects: Text, Labels, Images, Background

--------------------------Implementation---------------

-> it uses a nested Dictionary for the agc template;
-> also, it uses a NSDictionary for inverted data
-> uses a NSDictionary for defaultValues 
( when values needed for agc implemenattion can't be found 
in the xml's tags)
 
-------------------------- Issues ---------------------

Background -> only when xcode color type = calibratedRGB 
		-> TODO: calibratedWhite etc.
Text -> only textAlignment = center
        -> no shadows or any special effects

Labels -> same as above

Images -> TODO change size info

TODO: switches + several other assets that can be found in ios material in Comet
TODO: transitions + multiple artboards

