#include "DSDateTime.h"
#include "DSCasts.h"

DynSoft::DSDateTime::DSDateTime() : wxDateTime() {
}

DynSoft::DSDateTime::DSDateTime(time_t timet) : wxDateTime(timet) {
}

DynSoft::DSDateTime::DSDateTime(const struct tm &tm) : wxDateTime(tm) {
}

DynSoft::DSDateTime::DSDateTime(double jdn) : wxDateTime(jdn) {
}

DynSoft::DSDateTime::DSDateTime(wxString timestamp, wxChar separator) {
	SetBySQLTimestamp(timestamp, separator);
}

DynSoft::DSDateTime::DSDateTime(
	wxDateTime_t hour,
	wxDateTime_t minute,
	wxDateTime_t second,
	wxDateTime_t millisec
) : wxDateTime(
	hour,
	minute,
	second,
	millisec
) {
}

DynSoft::DSDateTime::DSDateTime(
	wxDateTime_t day,
	Month month,
	int InvYear,
	wxDateTime_t hour,
	wxDateTime_t minute,
	wxDateTime_t second,
	wxDateTime_t millisec
) : wxDateTime(
	day,
	month,
	InvYear,
	hour,
	minute,
	second,
	millisec
) {
}

DynSoft::DSDateTime::DSDateTime(const wxString &date, const wxString &time) {
	SetGermanDate(date, time);
}

void DynSoft::DSDateTime::SetGermanDate(const wxString &date, const wxString &time) {
	if(!date.IsEmpty()) {
		int pos = date.Find('.', true);

		SetDay(1);
		SetYear(DynSoft::DSCasts::ToInt(date.Mid(pos + 1)));
		SetMonth(GetRealMonth(DynSoft::DSCasts::ToUnsignedShort(date.Mid(pos -2, 2))));
		SetDay(DynSoft::DSCasts::ToUnsignedShort(date.Mid(pos - 5, 2)));
	}

	if(!time.IsEmpty()) {
		SetHour(DynSoft::DSCasts::ToUnsignedShort(time.Mid(0, 2)));
		SetMinute(DynSoft::DSCasts::ToUnsignedShort(time.Mid(3, 2)));
		if(time.Length() > 5)
			SetSecond(DynSoft::DSCasts::ToUnsignedShort(time.Mid(6, 2)));
		else
			SetSecond(0);
	}
}

DynSoft::DSClassInfo DynSoft::DSDateTime::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_DATETIME_NAME,
		DS_DATETIME_VERSION,
		DS_DATETIME_AUTHOR
	);
}

wxString DynSoft::DSDateTime::ToDatabaseDate() const {
	return Format(DS_DATETIME_DATE_FORMAT);
}

wxString DynSoft::DSDateTime::ToDatabaseTime() const {
	return Format(DS_DATETIME_TIME_FORMAT);
}

wxString DynSoft::DSDateTime::ToDatabaseDateTime() const {
	return ToDatabaseDate() + _N(" ") + ToDatabaseTime();
}

wxString DynSoft::DSDateTime::ToGermanDate() const {
	return Format(DS_DATETIME_GERMAN_DATE);
}

wxString DynSoft::DSDateTime::ToCookieDateTime() const {
	return Format(DS_DATETIME_COOKIE_FORMAT);
}

bool DynSoft::DSDateTime::IsGermanDate(wxString date) {
	wxArrayString splitted = DSLib::Split(date, '.');
	if(splitted.GetCount() != 3)
		return false;
	
	for(unsigned int i = 0; i < splitted.GetCount(); i++)
		if(DSCasts::ToUnsignedInt(splitted[i]) == 0)
			return false;

	if(splitted[0].Length() != 2 || splitted[1].Length() != 2 || splitted[2].Length() < 4)
		return false;
	
	if(DSCasts::ToUnsignedInt(splitted[0]) < 1 || DSCasts::ToUnsignedInt(splitted[0]) > 31)
		return false;
	if(DSCasts::ToUnsignedInt(splitted[1]) < 1 || DSCasts::ToUnsignedInt(splitted[1]) > 12)
		return false;
	if(DSCasts::ToUnsignedInt(splitted[2]) == 0)
		return false;
	
	return true;
}

bool DynSoft::DSDateTime::IsGermanTime(wxString time) {
	wxArrayString splitted = DSLib::Split(time, ':');
	if(splitted.GetCount() < 2 || splitted.GetCount() > 3)
		return false;
	
	unsigned long tmp;
	for(unsigned int i = 0; i < splitted.GetCount(); i++) {
		if(!splitted[i].ToULong(&tmp))
			return false;
		if((DynSoft::DSCasts::ToInt(splitted[i]) < 0 || DynSoft::DSCasts::ToInt(splitted[i]) > 24) && i == 0)
			return false;
		if((DynSoft::DSCasts::ToInt(splitted[i]) < 0 || DynSoft::DSCasts::ToInt(splitted[i]) > 59) && (i == 1 || i == 2))
			return false;
	}
	
	return true;
}

void DynSoft::DSDateTime::SetWxDateTime(const wxDateTime &dt) {
	Set(
		dt.GetDay(),
		dt.GetMonth(),
		dt.GetYear(),
		dt.GetHour(),
		dt.GetMinute(),
		dt.GetSecond(),
		dt.GetMillisecond()
	);
}

wxDateTime DynSoft::DSDateTime::GetWxDateTime() const {
	return wxDateTime(
		GetDay(),
		GetMonth(),
		GetYear(),
		GetHour(),
		GetMinute(),
		GetSecond(),
		GetMillisecond()
	);
}

void DynSoft::DSDateTime::SetAmericanDate(const wxString &timestamp) {
	SetBySQLTimestamp(timestamp);
}

DynSoft::DSDateTime::Month DynSoft::DSDateTime::GetRealMonth(const unsigned short month) {
	DSDateTime::Month realMonth;

	switch(month) {
		case  1: realMonth = DSDateTime::Jan;       break;
		case  2: realMonth = DSDateTime::Feb;       break;
		case  3: realMonth = DSDateTime::Mar;       break;
		case  4: realMonth = DSDateTime::Apr;       break;
		case  5: realMonth = DSDateTime::May;       break;
		case  6: realMonth = DSDateTime::Jun;       break;
		case  7: realMonth = DSDateTime::Jul;       break;
		case  8: realMonth = DSDateTime::Aug;       break;
		case  9: realMonth = DSDateTime::Sep;       break;
		case 10: realMonth = DSDateTime::Oct;       break;
		case 11: realMonth = DSDateTime::Nov;       break;
		case 12: realMonth = DSDateTime::Dec;       break;
		default: realMonth = DSDateTime::Inv_Month; break;
	}

	return realMonth;
}

DynSoft::DSDateTime DynSoft::DSDateTime::FromSQLTimestamp(wxString timestamp, wxChar separator) {
	DynSoft::DSDateTime dt(timestamp, separator);
	return dt;
}

bool DynSoft::DSDateTime::SetBySQLTimestamp(wxString timestamp, wxChar separator) {
	// 2015-01-02 23:34:12.123456
	
	bool result = false;

	if(!timestamp.IsEmpty()) {
		*this = Now();

		const int position = timestamp.Find(_N("."));
		if(position != wxNOT_FOUND)
			timestamp = timestamp.Mid(0, position);

		wxArrayString dateTime(DSLib::Split(timestamp, ' '));
		if(dateTime.GetCount() == 2) {
			wxArrayString date(DSLib::Split(dateTime[0], separator));
			wxArrayString time(DSLib::Split(dateTime[1], ':'));

			bool dateOk = false;
			bool timeOk = false;

			if(date.GetCount() == 3) {
				SetDay(1);
				SetYear(DSCasts::ToUnsignedInt(date[0]));
				SetMonth(GetRealMonth(DSCasts::ToUnsignedInt(date[1])));
				SetDay(DSCasts::ToUnsignedShort(date[2]));

				dateOk = true;
			}

			if(time.GetCount() == 3) {
				SetHour(DSCasts::ToUnsignedShort(time[0]));
				SetMinute(DSCasts::ToUnsignedShort(time[1]));
				SetSecond(DSCasts::ToUnsignedShort(time[2]));

				timeOk = true;
			}

			result = dateOk && timeOk;
		} else {
			wxArrayString date(DSLib::Split(timestamp, separator));

			if(date.GetCount() == 3) {
				SetDay(1);
				SetYear(DSCasts::ToUnsignedInt(date[0]));
				SetMonth(GetRealMonth(DSCasts::ToUnsignedInt(date[1])));
				SetDay(DSCasts::ToUnsignedShort(date[2]));

				result = true;
			}
			
		}
	}

	return result;
}

bool DynSoft::DSDateTime::SetBySQLDate(const wxString &date, wxChar separator) {
	// 2015-01-02
	
	bool result = false;

	if(!date.IsEmpty()) {
		wxArrayString tmp(DSLib::Split(date, separator));

		if(tmp.GetCount() == 3) {
			SetDay(1);
			SetYear(DSCasts::ToUnsignedInt(tmp[0]));
			SetMonth(GetRealMonth(DSCasts::ToUnsignedInt(tmp[1])));
			SetDay(DSCasts::ToUnsignedShort(tmp[2]));

			result = true;
		}
	}

	return result;
}

bool DynSoft::DSDateTime::SetBySQLTime(wxString time) {
	// 23:34:12.123456
	
	bool result = false;

	if(!time.IsEmpty()) {
		const int position = time.Find(_N("."));
		if(position != wxNOT_FOUND)
			time = time.Mid(0, position);

		wxArrayString tmp(DynSoft::DSLib::Split(time, ':'));
		if(tmp.GetCount() == 3) {
			SetHour(DSCasts::ToUnsignedShort(tmp[0]));
			SetMinute(DSCasts::ToUnsignedShort(tmp[1]));
			SetSecond(DSCasts::ToUnsignedShort(tmp[2]));

			result = true;
		}
	}

	return result;
}

DynSoft::DSDateTime DynSoft::DSDateTime::Now() {
	DynSoft::DSDateTime dt;
	dt.SetWxDateTime(wxDateTime::Now());
	return dt;
}
