#ifndef cframe_h
#define cframe_h
/*
OOP344 ASSIGNMENT 2 Frame Classes
cframe.h
This Program has been written by
Henry Hyungi Kim
Student ID:025 741 125
myseneca ID:hkim142
OOP344 A Winter 2014
To prof. Kamal-Al-Deen, Hasan
*/
#include <cstring>
#include "iframe.h"
#include "console.h"
#include "consoleplus.h"
#include "consolebackup.h"
namespace cio
{
	class CFrame : public iFrame
	{
	protected:
		int col_; // the frame's top row position relative to its parent frame
		int row_; //the frame's left-most column position relative to its parent frame
		int width_; // the frame's width
		int height_; //the frame's height
		bool visible_; // the frame's visibility 
		bool fullscreen;
		char border_[9]; //the C-style null-terminated string that describes the frame's border 
		void* hideArea;
		CFrame* parent_; // the initial address of the parent frame
		void setLine(char* str, char left, char fill, char right) const;
		void capture();
		int absrow() const;
		int abscol() const;
	public:
		CFrame(int col = -1, int row = -1, int width = -1, int height = -1, bool visible = false, const char* border = C_BORDER_CHARS, CFrame* parent = (CFrame*)NULL)
		{
			row_ = row;
			col_ = col;
			parent_ = parent;
			if (height < 0)
			{
				width_ = console.getCols();
				height_ = console.getRows();
				visible_ = false;
				border_[0] = '\0';
				fullscreen = true;
			}
			else
			{
				width_ = width;
				height_ = height;
				visible_ = visible;
				memcpy(border_, border, sizeof(border));
				fullscreen = false;
			}

		};// cframe const
		~CFrame();
		CFrame* frame() const{ return (CFrame*)parent_; }
		void frame(CFrame* parent){ parent_ = parent; }
		void goMiddle();
		void bordered(bool border){ visible_ = border; };
		bool bordered() const{ return visible_; };
		void row(int row) { row_ = row; };
		int row() const { return row_; };
		void col(int col){ col_ = col; };
		int col() const{ return col_; };
		void height(int height){ height_ = height; };
		int height() const{ return height_; };
		void width(int width){ width_ = width; };
		int width() const { return width_; };
		void draw(int = C_FULL_FRAME);
		void hide(CDirection dir = C_STATIONARY);
		void move(cio::CDirection dir);

	};//CFrame ends
	void move(iFrame& move);
}// cido name space ends
#endif