/*
OOP344 ASSIGNMENT 2 Frame Classes
cfg.h
This Program has been written by
Henry Hyungi Kim
Student ID:025 741 125
myseneca ID:hkim142
OOP344 A Winter 2014
To prof. Kamal-Al-Deen, Hasan
*/
#ifndef __CFG_H__
#define __CFG_H__
#include <cstdlib>

#define C_MAX_NO_FIELDS                 100
#define C_BORDER_CHARS         "/-\\|/-\\|"
#define C_FULL_FRAME					 -1
#define C_NO_FRAME						  0
#define C_NOT_EDITABLE                    0
#define C_BUTTON_HIT                      1

#ifndef NULL
#define NULL                         (void*)0
#endif

namespace cio {
    enum CDirection {C_STATIONARY, C_MOVED_LEFT, C_MOVED_RIGHT, C_MOVED_UP, C_MOVED_DOWN};
}

#endif