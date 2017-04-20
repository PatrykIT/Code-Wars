#include <iostream>
#include <string>

std::string solution(int number)
{
    std::cout << "HI.\n";
  // convert the number to a roman numeral
}

/*
Symbol	[I]	[V]	[X]	 [L]	 [C]   [D]	  [M]
Value	[1]	[5]	[10] [50]	[100] [500]	[1,000]
*/


/* Symbols are placed from left to right in order of value, starting with the largest.
 * However, in a few specific cases to avoid four characters being repeated in succession (such as IIII or XXXX)
 *  subtractive notation is used: as in this table:
    [ Number:	4	9	40	90	400	900 ]
    [ Notation:	IV	IX	XL	XC	CD	CM ]
 *
 *
 * You can't put more then ONE smaller number in front of a larger number.
 *
 * So: I use subtractive notation if normal writing would take more than 3 identical characters.
 *
 *
 * You must separate ones, tens, hundreds, and thousands as separate items.
 * That means that 99 is XCIX, 90 + 9, but never should be written as IC. WHY ?! ?!
*/
