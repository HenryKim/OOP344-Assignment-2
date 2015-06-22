
#ifndef cbutton_H
#define cbutton_H
#include "cfg.h"
#include "cfield.h"
#include "cframe.h"
#include "console.h"
#include "keys.h"

namespace cio 
{
	class CField;

	class CButton: public CField 
	{
		int b_frame;

		void allocateAndCopy(const char* data);

		public:
		CButton(const char* Str, int Row, int Col, bool Bordered = true, const char* Border=C_BORDER_CHARS);
		~CButton();
		void draw(int fn=C_NO_FRAME);
		int edit();
		bool editable()const;
		void set(const void* str);
	};
}
#endif