#ifndef _CLINE_H_
#define _CLINE_H_
#include "cfield.h"

namespace cio{

	class CLine : public CField{

		bool allocate;
		bool bordered_;
		int maxDataLen_;
		bool insertMode_;
		int refreshed;
		int cursor;
		int offset;
		void allocateAndCopy(const char*);

	public:
		CLine(const char* str, int row, int col, int width,
			int maxDataLen, bool* insertMode,
			bool bordered = false,
			const char* border = C_BORDER_CHARS);
		CLine(int row, int col, int width,
			int maxDataLen, bool* insertMode,
			bool bordered = false,
			const char* border = C_BORDER_CHARS);
		~CLine();
		void draw(int = C_NO_FRAME);
		int edit();
		bool editable()const{ return true; };
		void  set(const void* Str);
	};
}
#endif