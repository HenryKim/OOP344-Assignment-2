/*
OOP344 ASSIGNMENT 2 Frame Classes
cline.cpp
This Program has been written by
Henry Hyungi Kim
Student ID:025 741 125
myseneca ID:hkim142
OOP344 A Winter 2014
To prof. Kamal-Al-Deen, Hasan
*/
#include "cline.h"
namespace cio{
	CLine::CLine(const char* str, int row, int col, int width,
		int maxDataLen, bool* insertMode,
		bool bordered,
		const char* border) : CField(row, col, width, bordered ? 3 : 1, (void*)str, bordered, border) {
	allocate = false;
	cursor = 0;
	offset = 0;
	maxDataLen_ = maxDataLen;
	insertMode_ = insertMode;
}
	CLine::CLine(int row, int col, int width,
		int maxDataLen, bool* insertMode,
		bool bordered,
		const char* border) : CField(row, col, width, bordered ? 3 : 1, NULL, bordered, border){
	cursor = 0;
	offset = 0;
	maxDataLen_ = maxDataLen;
	allocateAndCopy("");
}
CLine::~CLine(){
	if (allocate)
		delete [] data_;

}
void CLine::draw(int draw ){
	CFrame::draw(draw);
}
void CLine::allocateAndCopy(const char* Str){
	
}
int CLine:: edit(){
	return 0;
}
void CLine:: set(const void* str)
{
	if (allocate)
		delete[] data_;

	allocateAndCopy((const char*)str);
}
}//name space cio ends