#ifndef DS_TABLE_H_
#define DS_TABLE_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSType.h"
#include "DSClassInfo.h"
#include "DSTemplateContainer.h"
#include "DSContainerType.h"

#define DS_TABLE_VERSION			_N("0.0.2")
#define DS_TABLE_NAME				_N("DSTable")
#define DS_TABLE_AUTHOR				_N("Thorsten Geppert (thorsten@ext2fs.de)")

#define DS_TABLE_CELL_VERSION		DS_TABLE_VERSION
#define DS_TABLE_CELL_NAME			_N("DSTableCell")
#define DS_TABLE_CELL_AUTHOR		DS_TABLE_AUTHOR

#define DS_TABLE_COLUMN_VERSION		DS_TABLE_VERSION
#define DS_TABLE_COLUMN_NAME		_N("DSTableColumn")
#define DS_TABLE_COLUMN_AUTHOR		DS_TABLE_AUTHOR

#define DS_TABLE_ROW_VERSION		DS_TABLE_VERSION
#define DS_TABLE_ROW_NAME			_N("DSTableRow")
#define DS_TABLE_ROW_AUTHOR			DS_TABLE_AUTHOR


namespace DynSoft {

	class DSTable : public DSLib {

		protected:
			class DSTableCell : public DSType {

				public:
					void SetContent(const wxString &content) {
						this->content = content;
					}

					wxString GetContent() const {
						return content;
					}

					void SetData(DSContainerType *data) {
						this->data = data;
					}

					DSContainerType *GetData() const {
						return data;
					}

					void SetRemovePointer(const bool removePointer) {
						this->removePointer = removePointer;
					}

					bool GetRemovePointer() const {
						return removePointer;
					}
				
				protected:
					wxString content;
					DSContainerType *data;
					bool removePointer;

				public:
					DSTableCell(
						const wxString &content = wxEmptyString,
						DSContainerType *data = NULL,
						const bool removePointer = true
					) {
						this->content       = content;
						this->data          = data;
						this->removePointer = removePointer;
					}

					virtual ~DSTableCell() {
						if(removePointer && data != NULL)
							delete (const DSContainerType *) data;
					}

					DSClassInfo GetClassInfo() {
						return DSClassInfo(
							DS_TABLE_CELL_NAME,
							DS_TABLE_CELL_VERSION,
							DS_TABLE_CELL_AUTHOR
						);
					}

			};
	
		public:
			class DSTableColumn : public DSTableCell {
				public:
					DSTableColumn(
						const wxString &content = wxEmptyString,
						DSContainerType *data = NULL,
						const bool removePointer = true
					) : DSTableCell(
						content,
						data,
						removePointer
					) {
					}

					DSClassInfo GetClassInfo() {
						return DSClassInfo(
							DS_TABLE_COLUMN_NAME,
							DS_TABLE_COLUMN_VERSION,
							DS_TABLE_COLUMN_AUTHOR
						);
					}

			};

			class DSTableRow : public DSTemplateContainer<DSTableColumn *>, public DSTableCell {
				public:
					DSTableRow(
						const unsigned int init = 0,
						const wxString &content = wxEmptyString,
						DSContainerType *data = NULL,
						const bool removePointer = true
					) : DSTemplateContainer<DSTableColumn *>(
					), DSTableCell(
						content,
						data,
						removePointer
					) {
						for(unsigned int i = 0; i < init; i++)
							Add(new DSTableColumn);
					}

					virtual ~DSTableRow() {
						Clear(true);
					}

					DSClassInfo GetClassInfo() {
						return DSClassInfo(
							DS_TABLE_ROW_NAME,
							DS_TABLE_ROW_VERSION,
							DS_TABLE_ROW_AUTHOR
						);
					}

			};

			DSTable();
			virtual ~DSTable();
			void Reset();

			DSClassInfo GetClassInfo();

			unsigned int AppendRow();
			unsigned int InsertRow(unsigned int position);
			bool RemoveRow(unsigned int position);
			unsigned int GetRowCount() const;
			DSTableRow *GetRow(unsigned int position) const;

			unsigned int AppendColumn();
			void InsertColumn(unsigned int position);
			bool RemoveColumn(unsigned int position);
			unsigned int GetColumnCount() const;
			int GetColumnPosition(unsigned int row, const wxString &content);
			DSTableColumn *GetCell(
				const unsigned int row,
				const unsigned int column
			) const;

			wxString GetContent(
				const unsigned int row,
				const wxString &column
			);

			wxString GetContent(
				const unsigned int row,
				const unsigned column
			);

		protected:
			DSTemplateContainer<DSTableRow *> *rows;
	
	};

}

#endif /* DS_TABLE_H_ */
