#include <wx/wx.h>
#include <wx/xml/xml.h>
#include <iostream>

#define VERSION "0.0.1"
#define CHANGED "10.04.2009"

void print_usage(const char *program);
void parse(wxXmlNode *node, wxArrayString *classes, wxArrayString *names);
unsigned int longest(wxArrayString *entries);

int main(int argc, char *argv[]) {
	if(argc != 3) {
		print_usage(argv[0]);
		return 1;
	}

	const char *file = argv[2];
	wxXmlDocument doc;
	if(!doc.Load(wxString(file, wxConvUTF8))) {
		std::cerr << "Could not load file: " << file << std::endl;
		return 2;
	}

	if(doc.GetRoot()->GetName() != wxT("resource")) {
		std::cerr << "No entry point: <resource...>" << std::endl;
		return 3;
	}

	wxArrayString classes, names;
	wxXmlNode *child = doc.GetRoot()->GetChildren();
	parse(child, &classes, &names);

	const wxString parent(argv[1], wxConvUTF8);
	wxString n, c;
	const unsigned int c_longest = longest(&classes);
	const unsigned int n_longest = longest(&names);
	unsigned int n_length        = 0;
	unsigned int c_length        = 0;
	const unsigned int count     = classes.GetCount();
	for(unsigned int i = 0; i < count; i++) {
		c        = classes[i];
		c_length = c.Length();
		n        = names[i];
		n_length = n.Length();

		std::cerr << static_cast<const char *>(c.mb_str(wxConvUTF8));
		for(unsigned int j = 0; j < c_longest - c_length; j++)
			std::cerr << " ";
		std::cerr << " *" << static_cast<const char *>(n.mb_str(wxConvUTF8)) << ";" << std::endl;

		std::cout << static_cast<const char *>(n.mb_str(wxConvUTF8));
		for(unsigned int j = 0; j < n_longest - n_length; j++)
			std::cout << " ";
		std::cout << " = XRCCTRL(" << static_cast<const char *>(parent.mb_str(wxConvUTF8)) << ", \"" << static_cast<const char *>(n.mb_str(wxConvUTF8)) << "\", " << static_cast<const char *>(c.mb_str(wxConvUTF8)) << ");" << std::endl;
	}

	return 0;
}

unsigned int longest(wxArrayString *entries) {
	if(!entries)
		return 0;

	unsigned int length = 0;
	const unsigned int count  = entries->GetCount();
	for(unsigned int i = 0; i < count; i++)
		length = length < entries->Item(i).Length() ? entries->Item(i).Length() : length;
	
	return length;
}

void parse(wxXmlNode *node, wxArrayString *classes, wxArrayString *names) {
	wxString c, n, name;
	wxXmlNode *children = NULL;
	while(node) {
		children = node->GetChildren();
		if(children)
			parse(children, classes, names);
		name = node->GetName();
		if(name == wxT("object") || name == wxT("ToolbarButton")) {
			c = name == wxT("ToolbarButton") ? name : c = node->GetPropVal(wxT("class"), wxEmptyString);
			n = node->GetPropVal(wxT("name"), wxEmptyString);
			if(!c.IsEmpty() && !n.IsEmpty()) {
				classes->Add(c);
				names->Add(n);
			}
		}
		node = node->GetNext();
	}
}

void print_usage(const char *program) {
	std::cout << std::endl;
	std::cout << "DynSoft.com - wxWidgets XML class extractor";
	std::cout << std::endl;
	std::cout << "===========================================";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Usage:" << std::endl;
	std::cout << "\t" << program << " parent input_file 2> output_file.h > output_file.cpp";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Version: " << VERSION << std::endl;
	std::cout << " Author: Thorsten Geppert (thorsten@ext2fs.de)" << std::endl;
	std::cout << "Address: Kirchgaesschen 8" << std::endl;
	std::cout << "         56626 Andernach" << std::endl;
	std::cout << "Created: 04.10.2009" << std::endl;
	std::cout << "Changed: " << CHANGED << std::endl;
	std::cout << std::endl;
}
