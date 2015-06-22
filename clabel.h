/*
OOP344 ASSIGNMENT 2 Frame Classes
clabel.h
This Program has been written by
Henry Hyungi Kim
Student ID:025 741 125
myseneca ID:hkim142
OOP344 A Winter 2014
To prof. Kamal-Al-Deen, Hasan
*/
#ifndef clabel_h
#define clabel_h
#include "cfield.h"
namespace cio
{
	class CLabel : public CField
	{
		void allocateAndCopy(const char* str); // allocates dynamic memory for the C-style null-terminated string at the received address and copies that data into the newly allocated memory.  The maximum memory needed here is the width of the field plus 1 for the null byte.
	public:
		CLabel(const char * str, int row, int col, int len = -1);//const no.1
		CLabel(int row, int col, int len); // const no.2
		CLabel(const CLabel& L); // cc
		~CLabel(); //desct
		void draw(int label = C_NO_FRAME); //displays the label(C_NO_FRAME)
		/*
		deallocates the dynamic memory where the label's data has been stored, 
		resets the width of the field to the length of the C-style null-terminated string at the received address, 
		allocates dynamic memory for that data, and copies the data in the newly allocated memory
		*/
		void set(const void* Str);
		bool editable() const { return false; }; //returns false
		int edit(); //draws the label and returns the key code C_NOT_EDITABLE
		
	};
}
#endif