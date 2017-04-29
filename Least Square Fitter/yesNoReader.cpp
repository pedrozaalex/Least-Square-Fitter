// Reads a character from the user and returns true for a y or Y character,
// and false for a n or N character

#include "stdafx.h"
#include <iostream>

bool yesNoReader()
{
	char char1;
	do
	{
		std::cin >> char1;
		switch (char1)
		{
		case 'y':
			return true;
			break;
		case 'Y':
			return true;
			break;
		case 'n':
			return false;
			break;
		case 'N':
			return false;
			break;
		}
	} while (char1 != 'y' && char1 != 'Y' && char1 != 'n' && char1 != 'N');
}