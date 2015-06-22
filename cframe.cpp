/*
OOP344 ASSIGNMENT 2 Frame Classes
cframe.cpp
This Program has been written by
Henry Hyungi Kim
Student ID:025 741 125
myseneca ID:hkim142
OOP344 A Winter 2014
To prof. Kamal-Al-Deen, Hasan
*/
#define _CRT_SECURE_NO_WARNINGS
#include "keys.h"
#include "cframe.h"

using namespace std;
namespace cio
{
	CFrame:: ~CFrame() {
		release(&hideArea);
	}

	int CFrame::absrow() const{
		int row;
		row = row_;
		CFrame* temp = frame();
		while (temp){
			row = row + temp->row();
			temp = temp->frame();
		}
		return row;
	}

	int CFrame::abscol() const
	{
		int col = col_;
		CFrame* temp = frame();
		while (temp)
		{
			col = col + temp->col();
			temp = temp->frame();
		}
		return col;
	}

	void CFrame::setLine(char* str, char left, char fill, char right) const
	{
		int i;
		str[0] = left;// the beginning of string str[0] will be left
		for (i = 1; i < width_ - 1; i++){ // the width(_width) location will be right
			str[i] = fill; // fill up space between left to right with char fill until it reach to _width -1
		}
		str[i] = right;
		str[i + 1] = '\0'; /// ends string by setting NULL value
	}

	void CFrame::goMiddle()
	{
		if (visible_){ // if cframe is visible 
			console.setPosition(absrow() + 1, abscol() + width_ / 2);
		}
		else{ // if not visible (false)
			console.setPosition(absrow(), abscol() + width_ / 2);
		}
	}

	void CFrame::draw(int draw){
		int i;
		char* str;
		str = new char[width() + 1];
		for (i = 0; i<width() + 1; i++)
		{
			str[i] = ' ';
		}
		capture();
		if (visible_ && draw != C_NO_FRAME)
		{
			console.setPosition(absrow(), abscol());
			setLine(str, border_[0], border_[1], border_[2]);
			console << str;

			for (i = 0; i<(height() - 2); i++)
			{
				console.setPosition((absrow() + 1 + i), abscol());
				setLine(str, border_[7], ' ', border_[3]);
				console << str;
			}

			console.setPosition((absrow() + 1 + i), abscol());
			setLine(str, border_[6], border_[5], border_[4]);
			console << str;
		}
		delete[] str;
	}

	void CFrame::capture()
	{
		if (!hideArea) hideArea = cio::capture(absrow(), abscol(), height_, width_);
	}

	void CFrame::hide(CDirection dir){
		cio::restore(absrow(), abscol(), height_, width_, dir, hideArea);
		cio::release((void**)&hideArea);
	}

	void CFrame::move(cio::CDirection move){
		if (move == C_MOVED_DOWN){
			if (parent_){
				if (bordered()){
					if (absrow() + height_ <parent_->absrow() + parent_->height() - 1){
						hide(move);
						row_ += 1;
						draw();
					}
				}
				else{
					if (absrow()>parent_->absrow() && absrow()>0){
						hide(move);
						row_ -= 1;
						draw();
					}
				}
			}
		}
		else if (move == C_MOVED_UP){
			if (parent_){
				if (bordered()){
					if (absrow()>parent_->absrow() + 1 && absrow()>0){
						hide(move);
						row_ -= 1;
						draw();
					}
				}
				else{
					if (absrow()>parent_->absrow() && absrow()>0){
						hide(move);
						row_ -= 1;
						draw();
					}
				}
			}
		}
		else if (move == C_MOVED_LEFT){
			if (parent_){
				if (bordered()){
					if (abscol()>parent_->abscol() + 1 && abscol()>0){
						hide(move);
						col_ -= 1;
						draw();
					}
				}
			}
			else{
				if (abscol()>parent_->abscol() && abscol()>0){
					hide(move);
					col_ -= 1;
					draw();
				}
			}
		}
		else if (move == C_MOVED_RIGHT){
			if (parent_){
				if (bordered()){
					if (abscol() + width_ <  parent_->abscol() + parent_->width() - 1){
						hide(move);
						col_ += 1;
						draw();
					}
				}
				else{
					if (abscol() + width_<parent_->abscol() + parent_->width()){
						hide(move);
						col_ += 1;
						draw();
					}
				}
			}
		}
		else if (move == C_STATIONARY){
			draw();
		}
	}

	void move(iFrame &mover){
		int keypress;
		console.setPosition(0, console.getCols() - 8);
		console << "Moving!";
		console >> keypress;
		while (keypress != ESCAPE){
			if (keypress == UP){
				mover.move(C_MOVED_UP);
			}
			else if (keypress == DOWN){
				mover.move(C_MOVED_DOWN);
			}
			else if (keypress == LEFT){
				mover.move(C_MOVED_LEFT);
			}
			else if (keypress == RIGHT){
				mover.move(C_MOVED_RIGHT);
			}
			console >> keypress;
		}
		mover.draw();
	}
}// name space cio ends