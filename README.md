
# Visual assets management

###### Prerequisites

1. XCode (it was tested for Version 7.2.1)
2. Adobe Experience Design (it was tested for Version 0.5.4.28Beta)
3. ImageMagick (the application makes use of the `convert` command within ImageMagick; used for exporting paths and lines)

###### Build steps


1. Run ``
	mkdir [path-to-VisualAssetsManagement]
	git clone git@git.corp.adobe.com:crogoz/VisualAssetsManagementXD.git
	cd [path-to-VisualAssetsManagement]
	``
2. Open *XDXCodeTranslator.xcodeproj* with XCode
3. Build the project
4. Run 
	`cd [path-to-VisualAssetsmanagement]/Build/Products/Debug/XDXCodeTranslator.app/Contents/MacOS`
5. The executable file is named `XDXCodeTranslator`
	* Available arguments: 
		./XDXCodeTranslator [-h|-i|-e] [file Paths]
	where 
		-h  = help
		-i <path>; imports given xcode project; teh result needs to be Ctrl+V into an XD project;
		-e [-nosync] <path>; exports an XD project into the given xcode path
 
	•	Import:
		o	<calea catre executabil> -i <calea catre proiectul xcode de la care se importa> <calea catre un fisier Xd>
			♣	<cale proiect> de forma <cale_root>/<nume_proiect>/<director in care se gaseste Base.lproj>
			♣	[EXEMPLU SAMPLE] ./XDXCodeTranslator  -i <caleVisualManagemenetXD>/SampleXcodeImport/Try/Try ~/Desktop/NewXd.xd
		o	in urma rularii se va obtine rezultatul [Import DONE], 
			iar in Clipboard se va afla fisierul agc echivalent; In XD se va da paste la continut
	•	Export
		o	 Se selecteaza elementele vizuale din XD pe care dorim sa le exportam si le copiem in Clipboard
		o	 <calea catre executabil>    -e  <calea catre proiectul xcode la care se se va exporta>
			♣	<cale proiect> de forma <cale_root>/<nume_proiect>/<director in care se gaseste Base.lproj>
		o	Se deschide automat reprezentarea echivalenta in Xcode

