Move along, nothing to see here.

## External Dependencies

* N/a

## Credits

Using and including nlohmann's json tool ([source](https://github.com/nlohmann/json))  
Using and including MtG json database available at [mtgjson.com](http://mtgjson.com/)  
Using and including the extended mana symbols made by "Goblin Hero" ([source](http://www.slightlymagic.net/forum/viewtopic.php?t=4430))  

## Notes

The mana symbols apparently have dimensions of 100px, separated by margins of 5px.  

## Card CSV Format

* All cardbase deck lists are stored in this custom format
* Semiolon (;) delimiters
* Fields are:
	* Name (quote-enclosed string)
	* Count (integer)
	* Foil [true|false]
	* Set Code (three-letter code)
	* Condition [M|NM|SP|MP|HP|ER], (Mint, Near mint, slightly played, moderatly played, heavily played, misprint/production error)
	* Language (quote-enclosed string)

