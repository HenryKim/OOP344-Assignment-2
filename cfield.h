/*
OOP344 ASSIGNMENT 2 Frame Classes
cfield.h
This Program has been written by
Henry Hyungi Kim
Student ID:025 741 125
myseneca ID:hkim142
OOP344 A Winter 2014
To prof. Kamal-Al-Deen, Hasan
*/
#ifndef cfield_h
#define cfield_h
#include "cframe.h"
namespace cio
{
	class CField : public CFrame
	{
	protected:
		void* data_;
	public:
		CField(int row = 0, int col = 0, int width = 0, int height = 0, void* data = NULL, bool visible = false, const char* border = C_BORDER_CHARS) : CFrame(row, col, width, height, visible, border)
		{
			data_ = data;
		};
		~CField();
		void allocateAndCopy(const char*);
		void* data() const{ return data_; };
		void data(void*);
		virtual int edit();
		virtual bool editable() const;
		virtual void set(const void*);

	};
}
#endif