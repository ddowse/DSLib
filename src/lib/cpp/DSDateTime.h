// TODO: Mit Now() machen

#ifndef DS_DATETIME_H_
#define DS_DATETIME_H_

#include <wx/wx.h>
#include <wx/datetime.h>
#include "DSLib.h"
#include "DSClassInfo.h"

#define DS_DATETIME_VERSION				_N("0.6.9")
#define DS_DATETIME_NAME				_N("DSDateTime")
#define DS_DATETIME_AUTHOR				_N("Thorsten Geppert (thorsten@ext2fs.de)")

#define DS_DATETIME_DATE_FORMAT			_N("%Y-%m-%d")
#define DS_DATETIME_TIME_FORMAT			_N("%H:%M:%S")
#define DS_DATETIME_GERMAN_DATE			_N("%d.%m.%Y")

#define DS_DATETIME_COOKIE_FORMAT		_N("%a, %d %b %Y %X %Z")
#define DS_DATETIME_COOKIE_FORMAT_GMT	_N("%a, %d %b %Y %X GMT")

namespace DynSoft {

	class DSDateTime : public wxDateTime {
	
		public:
			DSDateTime();

			DSDateTime(time_t timet);

			DSDateTime(const struct tm& tm);

			DSDateTime(double jdn);

			DSDateTime(
				wxDateTime_t hour,
				wxDateTime_t minute = 0,
				wxDateTime_t second = 0,
				wxDateTime_t millisec = 0
			);

			DSDateTime(
				wxDateTime_t day,
				Month month = Inv_Month,
				int InvYear = Inv_Year,
				wxDateTime_t hour = 0,
				wxDateTime_t minute = 0,
				wxDateTime_t second = 0,
				wxDateTime_t millisec = 0
			);

			DSDateTime(wxString timestamp, wxChar separator = '-');

			DSDateTime(const wxString &date, const wxString &time = _N(""));

			DSDateTime FromPostgreSQLTimestamp(const wxString &timestamp);

			DSClassInfo GetClassInfo();

			wxString ToDatabaseDate() const;
			wxString ToDatabaseTime() const;
			wxString ToDatabaseDateTime() const;
			wxString ToGermanDate() const;
			static bool IsGermanDate(wxString date);
			static bool IsGermanTime(wxString time);
			void SetAmericanDate(const wxString &timestamp);
			void SetGermanDate(const wxString &date, const wxString &time = wxEmptyString);

			void SetWxDateTime(const wxDateTime &dt);
			wxDateTime GetWxDateTime() const;
			wxString ToCookieDateTime() const;

			static Month GetRealMonth(const unsigned short month);
			DSDateTime FromSQLTimestamp(wxString timestamp, wxChar separator = '-');
			bool SetBySQLTimestamp(wxString timestamp, wxChar separator = '-');
			bool SetBySQLDate(const wxString &date, wxChar separator = '-');
			bool SetBySQLTime(wxString time);

			static DSDateTime Now();
	
	};

}

#endif /* DS_DATETIME_H_ */
