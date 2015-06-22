/*
OOP344 ASSIGNMENT 2 Frame Classes
clabel.cpp
This Program has been written by
Henry Hyungi Kim
Student ID:025 741 125
myseneca ID:hkim142
OOP344 A Winter 2014
To prof. Kamal-Al-Deen, Hasan
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "consoleplus.h"
#include "clabel.h"

using namespace std;

namespace cio
{
	void CLabel::allocateAndCopy(const char *Str){
		//allocates dynamic memory for the C-Style null-terminated string at the received address
		*data() = new char[width() + 1];
		//copies the data into the newly allocated memory
		strncpy(*(char**)data(), Str, width());
		(*(char**)data())[width()] = '\0';
	}
	/* copy constructor copies the source object's data into the dynamic memory
	that stores the label's data.*/
	CLabel::CLabel(const CLabel& L) :CField(L)
	{
		allocateAndCopy((char*)L.pdata());
	}
	CLabel::CLabel(const char *str, int row, int col, int len) : CField(row, col, len == -1 ? strlen(str) : len)
	{
		allocateAndCopy(str);
	}
	CLabel::CLabel(int row, int col, int len) : CField(row, col, len)
	{
		allocateAndCopy("");
	}
	CLabel::~CLabel(){
		delete[](char*)pdata();
	}
	void CLabel::draw(int draw){
		CField::display(0);
	}
	int CLabel::edit(){
		draw();
		return C_NOT_EDITABLE;
	}
	void CLabel::set(const void* str){
		width((int)strlen((const char*)str));
		//deallocates the dynamic memory where the label's data has been stored
		delete[](char*)pdata();
		//allocates dynamic memory for that data and copies the data in the newly allocated memory
		allocateAndCopy((const char*)str);
	}
}// name space cio ends

