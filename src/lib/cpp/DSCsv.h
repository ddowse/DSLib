#ifndef CSV_H_
#define CSV_H_

#include "DSLib.h"

#define DS_CSV_VERSION _N("0.0.3")
#define DS_CSV_NAME    _N("DSCsv")
#define DS_CSV_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSCsv : public DSLib {

		public:
			DSCsv(
				const wxChar fieldSeparator = ';',
				const wxChar textSeparator  = '"'
			);
			~DSCsv();

			DSClassInfo GetClassInfo();

			bool SetFile(const wxString &filename);
			bool SetContent(wxString &content);

			bool GetFields(wxArrayString &fields);
			unsigned int GetRows() const;
			unsigned int GetRow() const;
			wxString GetLine(const unsigned row);

		protected:
			wxChar fieldSeparator;
			wxChar textSeparator;
			wxArrayString lines;
			unsigned int row;
			unsigned int rows;


	};

}

#endif /* CSV_H_ */
