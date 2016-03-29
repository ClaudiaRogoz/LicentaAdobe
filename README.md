Build & Run App:
	Xcode IDE
 
	input: 
		<xmlFile> which corresponds to Xcode Storyboard
		<resources Directory> where are the resources <images> located

	output: 
		multiple <file>.agc that correspond to an artboard ( path: ~/Documents)
-------------------
!!!!!IMPORTANT! I use "Untitled.xd" file to monitor! (this file is the xd file where the agc where dropped)
		I use absolute path for "myXMLfileScenes.xml" = my project's Main.storyboard
		When trying to import an xml file -> only viewController works, it could be extended to any type of scene
		 (tableview, tabbar controller etc. ) -> only add to the xml2agcDictionary the mapping <tabbar controller> to 
		<artboard>.  		 
		When the file changes, the data is being rewritten to the intial files; just press "A" when prompeted with the question: "override ... ? " 
————————————————————
Importing objects from Xcode: 

	-> textField, Labels
	-> rectangles
	-> switch ( I’ve saved the agc corresponding to a switch in the Button.agc file ; the switch code
		will simply be attached to the current level in the artboard’s agc)

	The mapping between the  xml ( initial format ) and agc ( final format)  is made with the use of several
	NSDictionaries ( it is very easy to translate from xml to nsdictionary; 
					translation from agc to nsdictionary is made with the use of jsonserialization class)

	TODO: read the xml2json from a file; maybe translation between 2 schemas ( one for agc and one for xml)

	defaultValues -> in case one child tag misses; ex. color ( the default colour in Xcode is 0. 0 .0 )
	xml2agcDictionary -> map between xml tag and agc object
					-> it is also contains the inverted map; used when we  have to replace an attribute;
	attributes -> “template” for an agc object 

	dictionaryStack -> used for the inheritance relationship between dictionaries
	

——————————————————————
Importing artboards 

				 
Tried inserting several artboards in a single agc file, ;but XD won’t recognize it
-> Solution: split into several files (path: Documents directory ) 
-> TODO: DCX compression; move files to corresponding directories


——————————————————————
WORKFLOW: 

-> Basic object Import
DONE: basic import based on several NSDictionaries
TODO: create schemas for translations

-> Updates automatically ( from XD to XCode = from agc back to xml )
DONE: Given the path of the XD file, my app receives notifications every time the XD file changes ( it has been written )
DONE/TODO: iterate through each artboard, 
check if diff (initial_artboard, xd_artboard) == 0  then no need to update the corresponding xml tags
else , we update only with the difference noticed ( with the use of a mapping see < TODO  Basic object Import> )
TODO: Because the initial conversion doesn’t include all the info that is put when XD generates an agc file ( I’ve included only the minimum info in order to work, metadata or so ar discarded ), there is big difference when first CTRL+S appears. 
Solution: for the first CTRL+S -> (1) check for each artboard the  nsdictionary ; goto (2);
For rest of CTRL+S -> diff = <sha(prev_agc)  ==  sha(current_agc)>
If (diff == 0) continue;
Else // this is the artboard that was changed -> goto (1); goto(2)
(2) : update the xml only with the diff (TODO: See how ? maybe use “id” attributes; see which “id” is the “parent” of the change )
Prev_agc = current_agc

-> Export basic objects
See < TODO  Basic object Import>

->Import/export transitions 

----------------------

LOG

-> TODO multiple scenes
->TODO update diffOffset + copy scene if scene not modified :)
