
	Xcode IDE
 
	args: ./XDXCodeTranslator [-h|-i|-e|-s] [file Paths]
	where 
		-h  = help
		-i <path>; imports given xcode project; teh result needs to be Ctrl+V into an XD project;
		-e <path>; exports an XD project into the given xcode path
		-s ; syncs an xd project with an xcode project
 
1.Compilare si rulare

Pasii pentru compilarea aplicatiei si obtinerea executabilului:

	•	Proiectul este descarcat de la adresa [1]
	•	Proiectul se deschide cu XCode si se compileaza
	•	In urma compilarii, se genereaza un executabil: 
	“VisualAssetsManagement/Build/Products/Debug/XDXCodeTranslator.app/Contents/MacOS/XDXCodeTranslator”

Pasii pentru rularea aplicatiei:

	•	Import:
		o	<calea catre executabil> -I <calea catre proiectul xcode de la care se importa>
			♣	<cale proiect> de forma <cale_root>/<nume_proiect>/<director in care se gaseste Base.lproj>
			♣	[EXEMPLU SAMPLE] ./XDXCodeTranslator  -i <caleVisualManagemenetXD>/SampleXcodeImport/Samples
		o	in urma rularii se va obtine rezultatul [Import DONE], 
			iar in Clipboard se va afla fisierul agc echivalent; In XD se va da paste la continut
	•	Export
		o	 Se selecteaza elementele vizuale din XD pe care dorim sa le exportam si le copiem in Clipboard
		o	 <calea catre executabil>    -e  <calea catre proiectul xcode la care se se va exporta>
			♣	<cale proiect> de forma <cale_root>/<nume_proiect>/<director in care se gaseste Base.lproj>
		o	Se deschide automat reprezentarea echivalenta in Xcode
