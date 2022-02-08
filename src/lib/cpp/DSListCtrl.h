#include "DSSetup.h"

#ifdef  DS_WITH_GUI
#ifndef DS_LISTCTRL_H_
#define DS_LISTCTRL_H_

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "DSLib.h"
#include "DSType.h"
#include "DSClassInfo.h"
#include "DSChangeInterface.h"

#define DS_LISTCTRL_NAME		_N("DSListCtrl")
#define DS_LISTCTRL_VERSION		_N("0.0.8")
#define DS_LISTCTRL_AUTHOR		_N("Thorsten Geppert (thorsten@ext2fs.de)")

#define DS_LISTCTRLROW_NAME		_N("DSListCtrlRow")
#define DS_LISTCTRLROW_VERSION	_N("0.0.1")
#define DS_LISTCTRLROW_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSListCtrl : public wxListCtrl, public DSLib {

		DECLARE_DYNAMIC_CLASS(DSListCtrl)
	
		public:
			class DSListCtrlRow : public wxArrayString, public DSType {

				public:
					DSListCtrlRow();
					DSListCtrlRow(void *pointer);

					DSClassInfo GetClassInfo();
					
					void SetPointer(void *pointer);
					void *GetPointer() const;

					void SetBackgroundColour(const wxColour &backgroundColour);
					wxColour GetBackgroundColour() const;

				protected:
					void *pointer;
					wxColour backgroundColour;

			};

			DSListCtrl();
			DSListCtrl(
				wxWindow *parent,
				wxWindowID id,
				const wxPoint &pos = wxDefaultPosition,
				const wxSize &size = wxDefaultSize,
				long style = wxLC_REPORT,
				const wxValidator &validator = wxDefaultValidator,
				const wxString &name = wxListCtrlNameStr
			);

			DSClassInfo GetClassInfo();

			bool Append(DSListCtrl::DSListCtrlRow *row, const bool removePointer = true);
			bool Prepend(DSListCtrl::DSListCtrlRow *row, const bool removePointer = true);
			bool Insert(int position, DSListCtrl::DSListCtrlRow *row, const bool removePointer = true);
			bool Set(DSListCtrl::DSListCtrlRow *row, const bool removePointer = true);
			long GetSingleSelectionPosition();
			DSListCtrlRow *GetSingleSelection();
			void *GetSingleSelectionPointer();
			long GetPosition(void *pointer);
			void CleanUp();

			bool SetText(const int row, const int col, const wxString &text);
			wxString GetText(const int row, const int col, bool *found = NULL);
			bool SetPointer(const int row, const int col, void *pointer);
			void *GetPointer(const int row, const int col);
			bool ExistField(const int row, const int col);

			bool IsRowSelected(const int row);

			void SelectAll(const bool all);

			void SetChange(bool *changed);
			bool *GetChange() const;
			bool SetChanged(const bool changed);

			bool SelectedItemUp();
			bool SelectedItemDown();

			bool SetSelection(const int row);

		protected:
			DECLARE_EVENT_TABLE()

			void ChangeEvent(wxListEvent &event);

			bool *changed;
	
	};

}

#endif /* DS_LISTCTRL_H_ */
#endif /* DS_WITH_GUI */
