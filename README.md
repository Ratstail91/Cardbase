A Magic: The Gathering card manager, written for personal use.

FYI, this is a COMMAND LINE ONLY tool. I might write a front end eventually, IDK.

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

## Copyright

Copyright (c) 2015-2016 Kayne Ruse

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.