#include "DSDaemon.h"
#include "DSCasts.h"

DynSoft::DSDaemon::DSDaemon(
) : DSLib(
) {
}

DynSoft::DSClassInfo DynSoft::DSDaemon::GetClassInfo() {
	return DynSoft::DSClassInfo(
		DS_DAEMON_NAME,
		DS_DAEMON_VERSION,
		DS_DAEMON_AUTHOR
	);
}

int DynSoft::DSDaemon::Start() {
	pid_t pid;

	if((pid = fork()) != 0)
		return -1;
	
	if(setsid() < 0)
		return -2;
	
	signal(SIGHUP, SIG_IGN);

	if((pid = fork()) != 0)
		return -3;
	
	const char *changeDirectory = DSCasts::ToChar(GetDirectory());
	chdir(changeDirectory);
	delete [] changeDirectory;

	umask(GetUmask());

	for(unsigned int i = sysconf(_SC_OPEN_MAX); i > 0; i--)
		close(i);
	
	ImplementEvents();

	const int init = Init();
	if(init >= 0) {
		int result = 0;
		while(result >= 0)
			result = Run();

		return result;
	}

	return init;
}

void DynSoft::DSDaemon::SetEventHandler(void (*eventHandler)(int)) {
	this->eventHandler = eventHandler;
}

void DynSoft::DSDaemon::SetDirectory(const wxString &directory) {
	this->directory = directory;
}

wxString DynSoft::DSDaemon::GetDirectory() const {
	return directory;
}

void DynSoft::DSDaemon::SetUmask(const int mask) {
	this->mask = mask;
}

int DynSoft::DSDaemon::GetUmask() const {
	return mask;
}

void DynSoft::DSDaemon::AddEvent(int event) {
	events.push_back(event);
}

void DynSoft::DSDaemon::SetArgCount(const int argc) {
	this->argc = argc;
}

int DynSoft::DSDaemon::GetArgCount() const {
	return argc;
}

void DynSoft::DSDaemon::SetArgValues(char **argv) {
	this->argv = argv;
}

char **DynSoft::DSDaemon::GetArgValues() const {
	return argv;
}

void DynSoft::DSDaemon::ImplementEvents() {
	std::vector<int>::iterator it;
	for(it = events.begin(); it != events.end(); it++)
		signal(*it, eventHandler);
}
