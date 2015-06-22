/*
OOP344 ASSIGNMENT 1 Line Editing Facility
This Program has been written by
Henry Hyungi Kim
Student ID:025 741 125
myseneca ID:hkim142
OOP344 A Winter 2014
To prof. Kamal-Al-Deen, Hasan
*/
//declairing defines and libs
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdlib>
#include "console.h"
#include "consoleplus.h"
#include "keys.h"

namespace cio
{
	void display(const char *str, int row, int col, int fieldLen)
	{
		int numCharsToPrint, max_row, max_col, cur_y, strLen;
	  	const int col_fixed = col;
		const int row_fixed = row;
		console.setPosition(row, col);
		/* gets maximum values(boundries) of rows amd col from buffer */
		max_row = console.getRows();
		max_col = console.getCols();
		/*
		C-style, null-terminated string pointed to by str.
		*/
		if (!str)// if str is false ( null)
		{
			numCharsToPrint = 0;
		}
		/*
		if given string is not null( true)
		*/
		else
		{
			/*
			get lenght of given string
			*/
			strLen = strlen(str);
			/*
			 If fieldLen is 0 or less, function displays the portion of the entire string
			 that fits on the screenwith no trailing spaces.
			 */
			if (!fieldLen)//if fieldlenght is flase(null)
			{
				numCharsToPrint = strLen;
			}
			/*
			if current col postion + fieldLen passes max col limit
			*/
			else if (col + fieldLen > max_col)
			{
				/* if field lenght pass limit of col than calculate
				remain col left*/
				int remain_col = (max_col -col);
				numCharsToPrint = remain_col;
				/*
				if string length is lesser than remain col(total field len)
				*/
				if (strLen < remain_col) numCharsToPrint = strLen;
			}
			/*
			no special cases, fieldLen >0 & col+fieldLen !> max_col
			*/
			else
			{
				/*
					If the string is longer than fieldLen, function displays
					the first fieldLen characters
					*/
				numCharsToPrint = fieldLen;
				/*
					 If the string is shorter than fieldLen, function displays the portion of the entire string
					 that fits on the screen, followed by enough trailing spaces to fill out the field completely
					 */
				if (strLen < fieldLen) numCharsToPrint = strLen;

			}

			for (int i = 0; i < numCharsToPrint; i++)
			{
				console.setPosition(row, col + i); // updates row and col location
				console.setCharacter(str[i]); // gets character from string(character array)
				console.setPosition(row, col + i); // updates row and col location
				console.drawCharacter(); // draws character on user screen
				if (numCharsToPrint < fieldLen && i == numCharsToPrint - 1 && row == row_fixed && col < max_col)
				{
					for (int y = i + 1; y < fieldLen && (y+col) !=80; y++)//over write missing space in fieldlenght with space (' ')
					{
						console.setPosition(row, col + y);//update row and col location
						console.setCharacter(' '); // set character to draw as blank (' ')
						console.setPosition(row, col + y);// updates row and col location
						console.drawCharacter(); //drows the blank on user screen
						}
					i = numCharsToPrint + 1;//breaks loop
				}
			}
			if (numCharsToPrint == 0)// if there is any character to pring just print 1 space(' ')
			{
				console.setPosition(row, col_fixed);//updats cursor position to where field starts
				console.setCharacter(' ');// set character to draw as blank (' ')
				console.setPosition(row, col_fixed);// updates row and col location
				console.drawCharacter();// draws the blank on user screen
			}
		}
	}// end void display(...){...}

	int edit(char *str, int row, int col, int fieldLength, int maxStrLength, bool* insertMode, int* strOffset, int* curPosition)
	{
		int numCharsToWrite, user_input, y,key=0; // delclaration of fuction that will used on this function
		const int row_fixed = row;// initial value of row, which will never change. need for displaying and calculation
		const int col_fixed = col;// initial value of col, which will never change. need for displaying and calculation
		const int max_row = console.getRows(); //maximum row value can have
		const int max_col = console.getCols(); //maxium col value can have
		char input_temp, *modify, *mirror = new char[maxStrLength]; // creates variable needed for operation
		strcpy(mirror, str); //keeps original given str for back up
		if(*insertMode)// if insert mode is true( has value)
			display("Insertmode: ON",max_row -2,65,15); // shows insert mode is on 
		else if(!*insertMode)// if insertmode is false ( has ni value or its not positive value)
			display("Insertmode: OFF",max_row -2,65,15); //shows inser mode is off
		/*If the initial offset is beyond the end of the string,
		your function resets the offset to the length of the string;
		that is, to the index of the character immediately beyond the end of the string.*/
		if (*str && (*strOffset + col) > max_col)
			*strOffset = strlen(str);
		/*If no offset variable is pointed to; that is, if the address of the variable is NULL,
		your function sets the offset to the index of the first character in the string; that is, to 0.*/
		else if (!*str || !*strOffset)
			*strOffset = 0;
		/*If the initial cursor position is beyond the end of the field,
		your function resets the position to the last character in the field.*/
		if ((*curPosition + col) > max_col && !*str)
		{
			console.getPosition(row, col);

			/*If the position is beyond the end of the string, your function resets the position
			to that immediately beyond the end of the string. */

			if (col > max_col)
			{
				col = strlen(str); //position end of string == total string lenght exclude null bite which is strlen(str)
				console.setPosition(row, col);
			}
			console.setPosition(row, col);

		} // ends if( (*curPosition+col) > max_col && !str)

		/*If no cursor position variable is pointed to; that is,
		if the address of the variable is NULL,
		your function sets the cursor position to the first position in the field;
		that is, to position 0. */

		else if (!*curPosition)//curposition is  false (null)
			console.setPosition(0, 0);

		/*The function does not allow the cursor to move before the start of the field or past the end of the field.
		If the field ends at the right edge of the screen, your function does not allow the cursor to the right of that edge.*/

		if (fieldLength + col >= max_col)
			console.setPosition(0, 0);
		/*The user terminates editing by pressing ENTER, TAB, ESCAPE, UP, DOWN, PGUP, PGDN or any of the Function keys F(1) through F(12) inclusive. */
		if (*curPosition)
			col += *curPosition;//update cursor position by given curposition value if it has value(true)
		do// do loop start. this loop will not end until returning value from this function or entering speicific keys during loop
		{
			display(str + *strOffset, row_fixed, col_fixed, fieldLength); // call display where reference value is located at
			int lenght = strlen(str);//calculate updated string lenght for operation(calculation)
			console.setPosition(row, col ); // set cursor postion
			console.getPosition(row, col); //update
			console >> key;// get user input
			switch (key)// switch starts
			{
			case LEFT: // moves the cursor left one character, if possible, changing the offset, if necessary.
				if (*strOffset && col == col_fixed)// offSet is true and cursor located at where edit field start
					*strOffset -= 1;
				else if (col != col_fixed) // when cursor is not located at where edit field start (left end of field)
				{
					console.setPosition(row, col - 1); // set cursor postion
					console.getPosition(row, col); // update row, and col
				}
				break;
			case RIGHT://moves the cursor right one character, if possible, changing the offset, if necessary.
				if (col == fieldLength + col_fixed  && str[col - col_fixed + *strOffset] != '\0')//when cursor flahses end of field and string has offset value ( str[end_of_field+1] !='\0';)
					*strOffset += 1;// if operation need to change the offset
				else if (col < col_fixed + fieldLength)// when col is not flashing right end of field
				{
					console.setPosition(row, col + 1); // set cursor postion
					console.getPosition(row, col);  //update row, and col
				}
				break;
			case HOME: // moves the cursor to the beginning of the string, changing the offset, if necessary.
				if (*strOffset)//if there is any strOffset value (true)
					*strOffset = 0; // moves to beginning of string variable = reset the offet value
				console.setPosition(row_fixed, col_fixed); // set cursor postion
				console.getPosition(row, col); // update row, and col
				break;
			case END:// moves the cursor to the position to the right of the last character in the string, changing the offset, if necessary.
				if (lenght > fieldLength) // if total lenght of string is longer than field
					*strOffset = lenght - fieldLength; // calculate and set total offset vaule of this field
				console.setPosition(row, fieldLength + col_fixed); // set cursor postion to end of field
				console.getPosition(row, col); // update row, and col
				break;
			case DEL:
				modify = new char[maxStrLength]; // allocate memory
				strcpy(modify, str); // copys str
				for (int i = 0; i < lenght; i++)// while i is smaller than total lenght of string
				{
					modify[i] = str[i]; // copys string untill where cursor locates
					if (i == (col - col_fixed + *strOffset)) // cursor location calculation
					{
						for (y = i + 1; y <= lenght; y++) // loops skils 1 bits in string 
						{
							modify[y - 1] = str[y]; // modifiyed string copys 1 skiped value 
						}
						i = lenght + 1; // breaks loop
					}
				}
				strcpy(str, modify); // copy str from finished modifyed string
				delete[] modify; // delete string
				break;
			case BACKSPACE:
				if (col == col_fixed && *strOffset){ // if there is offset value and cursor points at beginning of field
					console.setPosition(row, col+ *strOffset);//updates console location +offset value
					*strOffset = 0; // pushes offset 
					console.getPosition(row, col);//update row, and col
				}
				if (col > col_fixed)
				{
					for (int i = col - col_fixed + *strOffset; str[i - 1]; i++)// calculate location of string which is (where cursor located )-(where field starts) + offset value
					{
						str[i - 1] = str[i]; // shift by 1 but startsy from left of cursor locates
					}
					console.setPosition(row, col - 1); // set cursor postion , moves to 1 left because its an backspacing
					console.getPosition(row, col); // update row, and col
				}
				break;
			case INSERT: // toggles Insert/Overstrike mode.
				if (*insertMode)//if insertmode is on (true) than turn off (false)
				{ 
					*insertMode = false;
					display("Insertmode: OFF",max_row -2,65,15); // shows insert mode is OFF
				}
				else if (!*insertMode)//if insertmode is off(false) than turn on (true)
				{
					*insertMode = true;
					display("Insertmode: ON",max_row -2,65,15); // shows insert mode is ON
				}
				break;
			case ESCAPE:
				strcpy(str, mirror);// return to original str received
				break;
			case ENTER:
				delete[] mirror;// erase memory allocation
				break;
			case UP: break;
			case DOWN: break;
			case PGUP: break;
			case PGDN: break;
			case F(1): break;
			case F(2): break;
			case F(3): break;
			case F(4): break;
			case F(5): break;
			case F(6): break;
			case F(7): break;
			case F(8): break;
			case F(9): break;
			case F(10): break;
			case F(11): break;
			case F(12): break;
			case UNKNOWN: break;
			default:
				if (key >= 32 && key <= 126 && lenght < maxStrLength)// when key is 32>= key value=< 126 which is 32 is 'a' is ACII and 126 is 'Z" is ACII and while string lenght is smaller than maximum string legnht value
				{
					if (*insertMode) // when insert mode is on (true) than endable insert mode
					{/*notice this may not finished*/
						for (int i = lenght; i > (col - col_fixed + *strOffset);i--)//when insert mode is triggered starts from end of string and shift back all character by 1
						{
							str[i] = str[i - 1];//shifting
						}
						str[col - col_fixed + *strOffset] = key;// after finished shifting enters user_input where cursor points at
					}
					else if (!*insertMode)// when insert mode is off (false) than endable overwriting mode
					{
						if (lenght < maxStrLength){ // while string has a space to enter more character
							str[col - col_fixed + *strOffset] = key;  // calculate location cursor location and overwirte input values
							if (col >= (fieldLength + col_fixed )) // if input value creates offset
								*strOffset += 1; // offset +1
						}
					}
					if (col < fieldLength+col_fixed)// if cursor is not located at end of field
						console.setPosition(row, col + 1); // set cursor postion and +1 from col because cursor moves next 1 after insert any
					else
					console.setPosition(row, col);  // otherwise cursor stays same location
					console.getPosition(row, col); // update row, and col
				}//key >= 32 && key <= 126 && lenght < maxStrLength
				break;
		}//switch(key) ends
			} while (key != ESCAPE &&  key != UP && key != DOWN && key != PGDN && key != PGUP && key != TAB); // ends while loop if thoses specification has been entered
		delete[] mirror;// erase memory allocation
		*insertMode = false; // exit insertmode when edit mode is finished6
		return key; // key user input latest
	}// edit(...) ends
}// namespace cio ends
