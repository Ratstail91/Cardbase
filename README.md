A Magic: The Gathering card manager, written for personal use.

## Formats Supported

* Cardbase CSV
* Deckbox CSV
* Pucatrade Importer
* Tappedout.dek

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
* Elements are delimited by semicolons (;)
* Records are delimited by newlines
* Fields are:
	* Name
	* Set Code
	* Language
	* Foil
	* Count
	* Condition
* Commented lines are supported using hash symbols (#)
* Blank lines are ignored