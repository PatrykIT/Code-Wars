#include <iostream>
#include <string>
#include <map>
#include <cmath>

std::map<int, std::string> letters {
                                    {1, "I"}, {5, "V"}, {10, "X"},
                                    {50, "L"}, {100, "C"}, {500, "D"}, {1000, "M"}
                                   };

std::map<int, std::string> compound_statements {
                                    {4, "IV"}, {9, "IX"}, {40, "XL"},
                                    {90, "XC"}, {400, "CD"}, {900, "CM"}
                                   };


int Get_First_Digit(int number)
{
    while(number >= 10)
    {
        number = number / 10;
    }

    return number;
}

int Split_Number(int number)
{
    /* For 204 we want 2 + (00). So 2 * 100. So 2 * (10 ^ 2).
     * For 3456 we want 3 + 000. So 3 * 1000. So 2 * (10 ^ 3) */
    int number_of_digits = [number] () { return number > 0 ? (int) log10 ((double) number) + 1 : 1; }();
    int first_digit = Get_First_Digit(number);
    int base = std::pow(10, number_of_digits -1);

    return first_digit * base;
}

bool Check_If_Compound_Statement_Possible(int number)
{

}

std::string solution(int number)
{
    number = 99;
    int stripped_number;
    std::string result = "";

    stripped_number = Split_Number(number);





    /* 99 -> 99 - 9 -> 9. */
    number = number - stripped_number;





}

/*
Symbol	[I]	[V]	[X]	 [L]	 [C]   [D]	  [M]
Value	[1]	[5]	[10] [50]	[100] [500]	[1,000]
*/


/* Symbols are placed from left to right in order of value, starting with the largest.
 * However, in a few specific cases to avoid four characters being repeated in succession (such as IIII or XXXX)
 * subtractive notation is used.
 * This "subtraction rule" allows the use of six compound symbols in which a smaller unit precedes the larger:
    [ Number:	4	9	40	90	400	900 ]
    [ Notation:	IV	IX	XL	XC	CD	CM ]
 *
 *
 * You can't put more then ONE smaller number in front of a larger number.
 *
 * So: I use subtractive notation if normal writing would take more than 3 identical characters OR if I can use
 * any of the six compound symbols.
 *
 *
 * You must separate ones, tens, hundreds, and thousands as separate items.
 * That means that 99 is XCIX, 90 + 9, but never should be written as IC.
 * I think that is because if there is option to use subtractive notation, then it must be used.
 *
 * For example: Split numbers - for 99 split as 90 and 9.
 * Then you will notice that both can be written from substraction rule table.
 * 90 is XC and 9 is IX.
 * That gives us XCIX :)
 *
 *
 *
 * 1. Split numbers. So for 99 split as 90 and 9.
 * For each number do:
 * a) Check if they can be written using compund statement. If yes, then write to string and skip rest.
 * b) If they can't be written using compound statement then write it normally.

*/
