#include "DSTesting.h"
#include "DSFile.h"

DynSoft::DSTesting::DSTesting(
) : DynSoft::DSTemplateContainer<DSTest *>(
) {
}

DynSoft::DSTesting::~DSTesting() {
	//Clear(true);
}

DynSoft::DSClassInfo DynSoft::DSTesting::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_TESTING_NAME,
		DS_TESTING_VERSION,
		DS_TESTING_AUTHOR
	);
}

unsigned int DynSoft::DSTesting::Save(
	const unsigned int format,
	const wxString &filename,
	bool *saved
) {
	message.Clear();

	unsigned int successCount = 0;
	unsigned int errorCount   = 0;
	PrintLine(_N("Starting Testing"));
	PrintLine(wxEmptyString);

	wxString underline;
	unsigned int underlineLength = 0;
	DSTest *test = NULL;
	const unsigned int countTests = GetCount();
	for(unsigned int i = 0; i < countTests; i++) {
		PrintLine(wxString::Format(_N("- Executing Part %i of %i"), i + 1, countTests));

		test = Get(i);
		if(test != NULL) {
			PrintLine(_N("\t- Test is not NULL. Execute __Test()"));
			test->__Test();
			PrintLine(_N("\t- Test was executed"));

			PrintLine(_N("\t- Working through asserts"));
			underline.Clear();
			if(format == TEXT) {
				underline = _N("\n");
				underlineLength = test->__GetModule().Length();
				for(unsigned int l = 0; l < underlineLength; l++)
					underline += _N("-");
			}
			Switcher(test->__GetModule() + underline, format);
			DSTest::DSTestEntity *entity;
			const unsigned int countEntities = test->__GetEntities()->GetCount();
			for(unsigned int j = 0; j < countEntities; j++) {
				entity = test->__GetEntities()->Get(j);
				if(entity->GetSuccess()) {
					successCount++;
					PrintLine(wxString::Format(_N("Success: %i of %i"), j + 1, countEntities));
				} else {
					errorCount++;
					PrintLine(wxString::Format(_N("Error: %i of %i"), j + 1, countEntities));
				}
				PrintLine(wxString::Format(_N("Creating line: %i of %i"), j + 1, countEntities));
				Switcher(entity, format);
			}
			PrintLine(_N("\t- Working through asserts done"));
		} else {
			PrintLine(_N("\t- Test is NULL. Aborting this test"));
		}
	}

	SetHeaderFooter(format);

	if(format != NONE) {
		bool tmpSaved = true;
		DSFile file(filename, _N("w"));
		if(!file.IsOpened()) {
			PrintLine(_N("Could not open or save to file: ") + filename + _N(". Proccess aborted."));
			tmpSaved = false;
		} else {
			if(!file.Write(message)) {
				PrintLine(_N("Could not write to file: ") + filename + _N(". Proccess aborted."));
				tmpSaved = false;
			} else {
				if(!file.Close()) {
					PrintLine(_N("Could not clsoe file: ") + filename + _N(". Proccess aborted."));
					tmpSaved = false;
				}
			}
		}

		if(saved)
			*saved = tmpSaved;
	}

	return errorCount;
}

void DynSoft::DSTesting::SetHeaderFooter(const unsigned int format) {
	wxString header;
	wxString footer;

	switch(format) {
		case HTML:
			header = _N("<html><head><meta http-equiv=\"Content-Type\" content=\"application/xhtml+xml; charset=UTF-8\" /><meta http-equiv=\"Content-Script-Type\" content=\"text/javascript; charset=utf-8\" /><title>DSTest</title></head><body><h1>DSTest</h1>");
			footer = _N("</body></html>");
			break;
		case CSV:
			break;
		case TEXT:
		default:
			header = _N("DSTest\n======\n\n");
			break;
	}

	message.Prepend(header);
	message.Append(footer);
}

void DynSoft::DSTesting::Switcher(const wxString &text, const unsigned int format) {
	switch(format) {
		case HTML:
			SaveAsHTML(text);
			break;
		case CSV:
			SaveAsCSV(text);
			break;
		case TEXT:
		default:
			SaveAsText(text);
			break;
	}
}

void DynSoft::DSTesting::Switcher(DSTest::DSTestEntity *entity, const unsigned int format) {
	switch(format) {
		case HTML:
			SaveAsHTML(entity);
			break;
		case CSV:
			SaveAsCSV(entity);
			break;
		case TEXT:
		default:
			SaveAsText(entity);
			break;
	}
}

void DynSoft::DSTesting::SaveAsText(const wxString &text) {
	message.Append(text);
	message.Append(_N("\n\n"));
}

void DynSoft::DSTesting::SaveAsCSV(const wxString &text) {
	message.Append(text);
	message.Append(_N("\"\";\"\";\"\";\"\"\n\n"));
}

void DynSoft::DSTesting::SaveAsHTML(const wxString &text) {
	message.Append(_N("<table><tr><td colspan=\"2\"><b>"));
	message.Append(text);
	message.Append(_N("</b></td></tr></table>"));
}

void DynSoft::DSTesting::SaveAsText(DSTest::DSTestEntity *entity) {
	message.Append(entity->GetTimeStamp().ToDatabaseDateTime());
	message.Append(_N("\t"));
	message.Append(entity->GetDescription());
	message.Append(_N("\n\t"));
	message.Append(entity->GetSuccess() ? _N("Success: ") : _N("Error: "));
	message.Append(entity->GetSuccess() ? entity->GetSuccessMessage() : entity->GetErrorMessage());
	message.Append(_N("\n\n"));
}

void DynSoft::DSTesting::SaveAsCSV(DSTest::DSTestEntity *entity) {
	message.Append(_N("\""));
	message.Append(entity->GetTimeStamp().ToDatabaseDateTime());
	message.Append(_N("\";\""));
	message.Append(entity->GetDescription());
	message.Append(_N("\";\""));
	message.Append(entity->GetSuccess() ? _N("Success") : _N("Error"));
	message.Append(_N("\";\""));
	message.Append(entity->GetSuccess() ? entity->GetSuccessMessage() : entity->GetErrorMessage());
	message.Append(_N("\"\n"));
}

void DynSoft::DSTesting::SaveAsHTML(DSTest::DSTestEntity *entity) {
	wxString bg(entity->GetSuccess() ? _N("#00ff00") : _N("#ff0000"));
	message.Append(_N("<p><table>"));
	message.Append(_N("<tr bgcolor=\"") + bg + _N("\">"));
	message.Append(_N("	<td><b>") + entity->GetTimeStamp().ToDatabaseDateTime() + _N("</b></td>"));
	message.Append(_N("	<td><b>") + entity->GetDescription() + _N("</b></td>"));
	message.Append(_N("</tr>"));

	message.Append(_N("<tr bgcolor=\"") + bg + _N("\">"));
	message.Append(_N("	<td><b>") + (entity->GetSuccess() ? wxString(_N("Success:")) : wxString(_N("Error:"))) + _N("</b></td>"));
	message.Append(_N("	<td><b>") + (entity->GetSuccess() ? entity->GetSuccessMessage() : entity->GetErrorMessage()) + _N("</b></td>"));
	message.Append(_N("</tr>"));
	message.Append(_N("</table></p>"));
}
