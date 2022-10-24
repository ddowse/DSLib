#ifndef DS_LIB_H_
#define DS_LIB_H_

#include <wx/wx.h>
#include "DSClassInfo.h"
#include "DSStringHashMap.h"

#define DS_LIB_VERSION			_N("0.21.8")
#define DS_LIB_NAME				_N("DSLib")
#define DS_LIB_AUTHOR			_N("Thorsten Geppert (thorsten@ext2fs.de)")
#define DS_LIB_DESCRIBER_OR		' '
#define DS_LIB_DESCRIBER_AND	'+'
#define DS_LIB_DESCRIBER_NOT	'-'

#define DS_PL(value) ( DynSoft::DSLib::PrintLine(value) )
#define DS_PLE(value) ( DynSoft::DSLib::PrintLineError(value) )

#ifndef _N
	#define _N(value) ( wxString(value, wxConvUTF8) )
#endif

namespace DynSoft {

	class DSDatabase;

	class DSLib {
	
		public:
			static const int OK         =  0;
			static const int ERROR_FILE = -1;

			static const int EQUAL      =  0;
			static const int GREATER    =  1;
			static const int LESSER     =  2;

			DSLib(DSDatabase *db = NULL);
			virtual ~DSLib();

			static DSClassInfo GetInfo();
			virtual DSClassInfo GetClassInfo() = 0;

			void SetDatabase(DSDatabase *db);
			DSDatabase *GetDatabase() const;

			static wxArrayString Split(const wxString &string, wxChar delimeter);
			static unsigned int ParseSearchWords(
				const wxString &search,
				wxArrayString *relations,
				wxArrayString *words
			);
			static bool PrintArrayString(wxArrayString *messages);
			static void Print(wxString message);
			static void Print(const char *message);
			static void PrintLine(wxString message);
			static void PrintLineError(wxString message);
			static void PrintLine(const char *message);
			static void PrintLineError(const char *message);
			static wxString ReadLine(const wxString &input = wxEmptyString);

			int LoadResourceFile(const wxString &filename, DSStringHashMap *resource);
			int LoadResource(const wxString &filename);
			int AppendResource(const wxString &filename);
			unsigned int ClearResource();
			DSStringHashMap *GetResource();
			wxString GetResourceByName(const wxString &name);
			wxString res(const wxString &name);

			static bool IsGreaterVersion(const wxString &first, const wxString &second);
			static bool IsEqualVersion(const wxString &first, const wxString &second);
			static bool IsLesserVersion(const wxString &first, const wxString &second);
			static bool IsValidVersion(const wxString &version);
			static bool SplitVersion(const wxString &version, unsigned int &major, unsigned int &minor, unsigned int &patch);
			static wxString VersionToString(const unsigned int major, const unsigned int minor, const unsigned int patch);
			static wxString HtmlSpecialChars(wxString html);
			static wxString nl2br(wxString str);

		protected:
			DSDatabase *db;
			DSStringHashMap resource;

			static bool CompareVersion(const wxString &first, const wxString &second, const int flag);
	
	};

}

#endif /* DS_LIB_H_ */
