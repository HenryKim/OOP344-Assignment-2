/*
OOP344 ASSIGNMENT 1 Line Editing Facility
This Program has been written by
Henry Hyungi Kim
Student ID:025 741 125
myseneca ID:hkim142
OOP344 A Winter 2014
To prof. Kamal-Al-Deen, Hasan
*/
#ifndef CONSOLEPLUS_H
#define CONSOLEPLUS_H
namespace cio{
// function definition delcariation
void display(const char *str, int row, int col, int fieldLen);
int edit(char *str, int row, int col, int fieldLength, int maxStrLength, bool* insertMode, int* strOffset, int* curPosition);
}
#endif