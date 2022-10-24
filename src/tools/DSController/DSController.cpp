#include <wx/wx.h>
#include <wx/file.h>
#include <iostream>

#define VERSION "0.0.2"
#define CHANGED "17.04.2011"

void print_usage(const char *program);

int main(int argc, char *argv[]) {
	if(argc != 3) {
		print_usage(argv[0]);
		return 1;
	}

	wxString sql;
	if(strcmp(argv[1], "m") == 0) {
		sql = wxT("MySQL");
	} else if(strcmp(argv[1], "p") == 0) {
		sql = wxT("PostgreSQL");
	} else if(strcmp(argv[1], "s") == 0) {
		sql = wxT("SQLite");
	} else {
		print_usage(argv[0]);
		return 1;
	}

	const wxString name(argv[2], wxConvUTF8);

	wxFile controllerHeader(name + wxT("Controller.h"), wxFile::write);
	if(!controllerHeader.IsOpened()) {
		std::cerr << "Could not open " << argv[2] << "Controller.h" << std::endl;
		return 2;
	}

	controllerHeader.Write(wxT("#ifndef ") + name.Upper() + wxT("_CONTROLLER_H_\n"));
	controllerHeader.Write(wxT("#define ") + name.Upper()+ wxT("_CONTROLLER_H_\n\n"));
	controllerHeader.Write(wxT("#include <DS") + sql + wxT("Database.h>\n"));
	controllerHeader.Write(wxT("#include <DS") + sql + wxT("EntityData.h>\n\n"));
	controllerHeader.Write(wxT("using namespace DynSoft;\n\n"));
	controllerHeader.Write(wxT("class ") + name + wxT("Controller : public DS") + sql + wxT("EntityData {\n\n"));
	controllerHeader.Write(wxT("	public:\n"));
	controllerHeader.Write(wxT("		") + name + wxT("Controller(\n"));
	controllerHeader.Write(wxT("			DS") + sql + wxT("Database *db\n"));
	controllerHeader.Write(wxT("		);\n\n"));
	controllerHeader.Write(wxT("};\n\n"));
	controllerHeader.Write(wxT("#endif /* ") + name.Upper() + wxT("_CONTROLLER_H_ */\n"));

	controllerHeader.Close();

	wxFile controllerCpp(name + wxT("Controller.cpp"), wxFile::write);
	if(!controllerCpp.IsOpened()) {
		std::cerr << "Could not open " << argv[2] << "Controller.cpp" << std::endl;
		return 2;
	}

	controllerCpp.Write(wxT("#include \"") + name + wxT("Controller.h\"\n\n"));
	controllerCpp.Write(name + wxT("Controller::") + name + wxT("Controller(\n"));
	controllerCpp.Write(wxT("	DS") + sql + wxT("Database *db\n"));
	controllerCpp.Write(wxT(") : DS") + sql + wxT("EntityData(\n"));
	controllerCpp.Write(wxT("	db,\n"));
	controllerCpp.Write(wxT("	_N(\"\"), // Table\n"));
	controllerCpp.Write(wxT("	_N(\"\")  // Primary key\n"));
	controllerCpp.Write(wxT(") {\n"));
	controllerCpp.Write(wxT("}\n"));

	controllerCpp.Close();

	wxFile entityHeader(name + wxT("Entity.h"), wxFile::write);
	if(!entityHeader.IsOpened()) {
		std::cerr << "Could not open " << argv[2] << "Entity.h" << std::endl;
		return 2;
	}

	entityHeader.Write(wxT("#ifndef ") + name.Upper() + wxT("_ENTITY_H_\n"));
	entityHeader.Write(wxT("#define ") + name.Upper() + wxT("_ENTITY_H_\n\n"));
	entityHeader.Write(wxT("#include <DS") + sql + wxT("Database.h>\n"));
	entityHeader.Write(wxT("#include <DS") + sql + wxT("DatabaseEntity.h>\n\n"));
	entityHeader.Write(wxT("using namespace DynSoft;\n\n"));
	entityHeader.Write(wxT("class ") + name + wxT("Entity : public DS") + sql + wxT("DatabaseEntity {\n\n"));
	entityHeader.Write(wxT("	public:\n"));
	entityHeader.Write(wxT("		") + name + wxT("Entity(DS") + sql + wxT("Database *db);\n\n"));
	entityHeader.Write(wxT("};\n\n"));
	entityHeader.Write(wxT("#endif /* ") + name.Upper() + wxT("_ENTITY_H_ */\n"));

	entityHeader.Close();

	wxFile entityCpp(name + wxT("Entity.cpp"), wxFile::write);
	if(!entityCpp.IsOpened()) {
		std::cerr << "Could not open " << argv[2] << "Entity.cpp" << std::endl;
		return 2;
	}

	entityCpp.Write(wxT("#include \"") + name + wxT("Entity.h\"\n\n"));
	entityCpp.Write(name + wxT("Entity::") + name + wxT("Entity(\n"));
	entityCpp.Write(wxT("	DS") + sql + wxT("Database *db\n"));
	entityCpp.Write(wxT(") : DS") + sql + wxT("DatabaseEntity(\n"));
	entityCpp.Write(wxT("	db,\n"));
	entityCpp.Write(wxT("	_N(\"\"), // Table\n"));
	entityCpp.Write(wxT("	_N(\"\")  // Primary\n"));
	entityCpp.Write(wxT(") {\n"));
	entityCpp.Write(wxT("}\n"));

	entityCpp.Close();

	return 0;
}

void print_usage(const char *program) {
	std::cout << std::endl;
	std::cout << "DynSoft.com - DSController and DSEntity Creator (very simple version)";
	std::cout << std::endl;
	std::cout << "=====================================================================";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Usage:" << std::endl;
	std::cout << "\t" << program << " [m]ysql|[p]sql|[s]qlite [name]";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Version: " << VERSION << std::endl;
	std::cout << " Author: Thorsten Geppert (thorsten@ext2fs.de)" << std::endl;
	std::cout << "Address: Kirchgaesschen 8" << std::endl;
	std::cout << "         56626 Andernach" << std::endl;
	std::cout << "Created: 25.10.2010" << std::endl;
	std::cout << "Changed: " << CHANGED << std::endl;
	std::cout << std::endl;
}
