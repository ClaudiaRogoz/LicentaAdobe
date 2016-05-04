UPDATE (14 apr 2016)
	Changed first argument to ...../<Proj_Name>/<Proj_name>

--------------
Build & Run App:
	Xcode IDE
 
	args: ./XMLParser [-h|-i|-e|-s] <path>
	where 
		-h  = help
		-i <path>; imports given xcode project; teh result needs to be Ctrl+V into an XD project;
		-e <path>; exports an XD project into the given xcode path
		-s ; syncs an xd project with an xcode project
 
----------------
Importing objects from Xcode: 

	-> textField, Labels
	-> rectangles
	-> switch ( I’ve saved the agc corresponding to a switch in the Button.agc file ; the switch code
		will simply be attached to the current level in the artboard’s agc)

----------------
Exporting objects XD to Xcode
	->text, group, images (the images are copied in the xcode project; they have to be manually inserted into
SupportingFiles)
	->paths can be exported as svg files (Problem: Xcode doesn;t support svg files=> TODO: convert to png)

----------------

---------------
WORKFLOW: 

-> Basic object Import
DONE: basic import based on several NSDictionaries
DONE: create schemas for translations

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

->TODO Import/export transitions 

