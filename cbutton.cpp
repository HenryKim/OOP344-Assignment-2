
#define _CRT_SECURE_NO_WARNINGS
#include "cbutton.h"
#include <cstring>
using namespace std;

namespace cio
{

	void CButton::allocateAndCopy(const char* data)
	{
		unsigned int i;

		char* str = new char[strlen(data) + 3];
		str[0] = ' ';

		for (i = 1; i < strlen(data) + 1; i++)
		{
			str[i] = data[i - 1];
		}

		str[i] = ' ';
		str[i + 1] = '\0';

		*CField::data() = str;
	}

	CButton::CButton(const char *Str, int Row, int Col, bool Bordered, const char* Border)
		: CField(Row, Col, (Bordered) ? (strlen(Str) + 4) : (strlen(Str) + 2), (Bordered) ? (3) : (1), NULL, Bordered, Border) 
	{
		allocateAndCopy(Str);
	}

	CButton::~CButton()
	{
		delete[](char*)pdata();
	}

	void CButton::draw(int fn)
	{
		CFrame::draw(fn);
		CField::display(0);
	}

	int CButton::edit()
	{
		int key;

		CFrame::draw();

		char* str = new char[strlen(*(char**)data())];
		strcpy(str, *(char**)data());

		str[0] = '[';
		str[strlen(str) - 1] = ']';
		*CField::data() = str;

		CField::display(0);
		CFrame::goMiddle();

		console >> key;

		if (key == ENTER || key == SPACE)
		{
			key = C_BUTTON_HIT;
		}

		str[0] = ' ';
		str[strlen(str) - 1] = ' ';
		*CField::data() = str;

		CField::display(0);
		CFrame::goMiddle();

		return key;
	}

	bool CButton::editable()const 
	{
		return true;
	}

	void CButton::set(const void* str)
	{
		delete[](char*)pdata();
		allocateAndCopy((char*)str);
		CFrame::height((CFrame::bordered()) ? (3) : (1));
		CFrame::width((CFrame::bordered()) ? (strlen((char*)str) + 4) : (strlen((char*)str) + 2));
	}
}