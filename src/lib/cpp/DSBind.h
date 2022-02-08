#include "DSSetup.h"

#ifdef  DS_WITH_GUI
#ifndef DS_BIND_H_
#define DS_BIND_H_

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/datectrl.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include "DSTemplateContainer.h"
#include "DSEntity.h"

#define DS_BIND_VERSION                     _N("0.0.5")
#define DS_BIND_NAME                        _N("DSBind")
#define DS_BIND_AUTHOR                      _N("Thorsten Geppert (thorsten@ext2fs.de)")
#define DS_BIND_TYPE_VERSION                _N("0.0.1")
#define DS_BIND_TYPE_NAME                   _N("DSBindType")
#define DS_BIND_TYPE_AUTHOR                 _N("Thorsten Geppert (thorsten@ext2fs.de)")
#define DS_BIND_TEXTCTRL_TYPE_VERSION       _N("0.0.1")
#define DS_BIND_TEXTCTRL_TYPE_NAME          _N("DSBindTextCtrlType")
#define DS_BIND_TEXTCTRL_TYPE_AUTHOR        _N("Thorsten Geppert (thorsten@ext2fs.de)")
#define DS_BIND_COMBOBOX_TYPE_VERSION       _N("0.0.1")
#define DS_BIND_COMBOBOX_TYPE_NAME          _N("DSBindComboBoxType")
#define DS_BIND_COMBOBOX_TYPE_AUTHOR        _N("Thorsten Geppert (thorsten@ext2fs.de)")


#define DS_BIND_LISTBOX_TYPE_VERSION        _N("0.0.1")
#define DS_BIND_LISTBOX_TYPE_NAME           _N("DSBindListBoxType")
#define DS_BIND_LISTBOX_TYPE_AUTHOR         _N("Thorsten Geppert (thorsten@ext2fs.de)")
#define DS_BIND_SPINCTRL_TYPE_VERSION       _N("0.0.1")
#define DS_BIND_SPINCTRL_TYPE_NAME          _N("DSBindSpinCtrlType")
#define DS_BIND_SPINCTRL_TYPE_AUTHOR        _N("Thorsten Geppert (thorsten@ext2fs.de)")
#define DS_BIND_CHECKBOX_TYPE_VERSION       _N("0.0.1")
#define DS_BIND_CHECKBOX_TYPE_NAME          _N("DSBindCheckBoxType")
#define DS_BIND_CHECKBOX_TYPE_AUTHOR        _N("Thorsten Geppert (thorsten@ext2fs.de)")
#define DS_BIND_DATEPICKERCTRL_TYPE_VERSION _N("0.0.1")
#define DS_BIND_DATEPICKERCTRL_TYPE_NAME    _N("DSBindDatePickerCtrlType")
#define DS_BIND_DATEPICKERCTRL_TYPE_AUTHOR  _N("Thorsten Geppert (thorsten@ext2fs.de)")

namespace DynSoft {

	class DSBind : public DSLib {

		public:
			static const unsigned int VALUE     = 0;
			static const unsigned int SELECTION = 1;
			static const unsigned int STRING    = 2;

		public:
			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////
			////
			//// DSBindType
			////
			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			class DSBindType : public DSType {
			
				public:
					DSBindType(const wxString &key, const unsigned int kind = VALUE);

					DSClassInfo GetClassInfo();

					wxString GetKey() const;
					unsigned int GetKind() const;

				protected:
					wxString key;
					unsigned int kind;

			};

			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////
			////
			//// DSBindTextCtrlType
			////
			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			class DSBindTextCtrlType : public DSBindType {
			
				public:
					DSBindTextCtrlType(const wxString &key, wxTextCtrl *value);
					wxTextCtrl *GetValue();

					DSClassInfo GetClassInfo();

				protected:
					wxTextCtrl *value;

			};

			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////
			////
			//// DSBindComboBoxType
			////
			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			class DSBindComboBoxType : public DSBindType {
			
				public:
					DSBindComboBoxType(const wxString &key, wxComboBox *value, const unsigned int kind = VALUE);
					wxComboBox *GetValue();

					DSClassInfo GetClassInfo();

				protected:
					wxComboBox *value;

			};

			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////
			////
			//// DSBindSpinCtrlType
			////
			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			class DSBindSpinCtrlType : public DSBindType {
			
				public:
					DSBindSpinCtrlType(const wxString &key, wxSpinCtrl *value);
					wxSpinCtrl *GetValue();

					DSClassInfo GetClassInfo();

				protected:
					wxSpinCtrl *value;

			};

			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////
			////
			//// DSBindDatePickerCtrlType
			////
			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			class DSBindDatePickerCtrlType : public DSBindType {
			
				public:
					DSBindDatePickerCtrlType(const wxString &key, wxDatePickerCtrl *value);
					wxDatePickerCtrl *GetValue();

					DSClassInfo GetClassInfo();

				protected:
					wxDatePickerCtrl *value;

			};

			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////
			////
			//// DSBindListBoxType
			////
			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			class DSBindListBoxType : public DSBindType {
			
				public:
					DSBindListBoxType(const wxString &key, wxListBox *value, const unsigned int kind = VALUE);
					wxListBox *GetValue();

					DSClassInfo GetClassInfo();

				protected:
					wxListBox *value;

			};

			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////
			////
			//// DSBindCheckBoxType
			////
			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			class DSBindCheckBoxType : public DSBindType {
			
				public:
					DSBindCheckBoxType(const wxString &key, wxCheckBox *value);
					wxCheckBox *GetValue();

					DSClassInfo GetClassInfo();

				protected:
					wxCheckBox *value;

			};

	
		public:
			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////
			////
			//// DSBind
			////
			/////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			DSBind(DSEntity *entity);
			~DSBind();

			DSClassInfo GetClassInfo();

			void Bind(const wxString &key, wxTextCtrl *value);
			void Bind(const wxString &key, wxComboBox *value, const unsigned int kind = VALUE);
			
			void Bind(const wxString &key, wxListBox *value, const unsigned int kind = SELECTION);
			void Bind(const wxString &key, wxSpinCtrl *value);
			void Bind(const wxString &key, wxCheckBox *value);
			void Bind(const wxString &key, wxDatePickerCtrl *value);

			wxControl *Get(const wxString &key, const bool removeIfFound = false);
			void Push();
			void Pull();
			DSEntity *GetEntity() const;
			void EnableAll(const bool enable);

		protected:
			DSEntity *entity;

			DSTemplateContainer<DSBindTextCtrlType *>       textCtrlContainer;
			DSTemplateContainer<DSBindComboBoxType *>       comboBoxContainer;

			DSTemplateContainer<DSBindListBoxType *>        listBoxContainer;
			DSTemplateContainer<DSBindSpinCtrlType *>       spinCtrlContainer;
			DSTemplateContainer<DSBindCheckBoxType *>       checkBoxContainer;
			DSTemplateContainer<DSBindDatePickerCtrlType *> datePickerCtrlContainer;
	
	};

};

#endif /* DS_BIND_H_ */
#endif
