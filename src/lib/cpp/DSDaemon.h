#ifndef DS_DAEMON_H_
#define DS_DAEMON_H_

#include <wx/wx.h>
#include "DSLib.h"
#include "DSClassInfo.h"
#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <vector>

#define DS_DAEMON_NAME		_N("DSDaemon")
#define DS_DAEMON_VERSION	_N("0.0.5")
#define DS_DAEMON_AUTHOR	_N("Thorsten Geppert (thorsten@ext2fs.de)")

#define IMPLEMENT_DAEMON(className, objectName) \
	className objectName; \
	void EventHandler(int eventHandler) { \
		objectName.EventQueue(eventHandler); \
	} \
	\
	int main(int argc, char **argv) { \
		objectName.SetArgCount(argc); \
		objectName.SetArgValues(argv); \
		objectName.SetEventHandler(EventHandler); \
		objectName.Start(); \
		\
		return 0; \
	}


#define IMPLEMENT_DAEMON_DEBUG(className, objectName) \
	className objectName; \
	void EventHandler(int eventHandler) { \
		objectName.EventQueue(eventHandler); \
	} \
	\
	int main(int argc, char **argv) { \
		objectName.SetArgCount(argc); \
		objectName.SetArgValues(argv); \
		objectName.SetEventHandler(EventHandler); \
		objectName.ImplementEvents(); \
		const int init = objectName.Init(); \
		if(init >= 0) { \
			int result = 0; \
			while(result >= 0) \
				result = objectName.Run(); \
			\
			return result; \
		} \
		return init; \
	}

namespace DynSoft {

	class DSDaemon : public DSLib {
	
		public:
			DSDaemon();

			DSClassInfo GetClassInfo();

			int Start();
			void SetEventHandler(void (*eventHandler)(int));
			void AddEvent(int event);
			void SetDirectory(const wxString &directory);
			wxString GetDirectory() const;
			void SetUmask(const int mask);
			int GetUmask() const;
			void SetArgCount(const int argc);
			int GetArgCount() const;
			void SetArgValues(char **argv);
			char **GetArgValues() const;
			virtual int Run()                    = 0;
			virtual void EventQueue(int handler) = 0;
			virtual int Init()                   = 0;
			void ImplementEvents();

			static const int HUP          = SIGHUP;
		 	static const int INTERRUPT    = SIGINT;
			static const int QUIT         = SIGQUIT;
			static const int INSTRUCTION  = SIGILL;
			static const int TRAP         = SIGTRAP;
			static const int ABORT        = SIGABRT;
			static const int FLOAT        = SIGFPE;
			static const int KILL         = SIGKILL;
			static const int SIGNAL1      = SIGUSR1;
			static const int SEGMENTATION = SIGSEGV;
			static const int SIGNAL2      = SIGUSR2;
			static const int PIPELINE     = SIGPIPE;
			static const int ALARM        = SIGALRM;
			static const int TERMINATE    = SIGTERM;
			static const int CHILD        = SIGCHLD;
			static const int CONTINUE     = SIGCONT;
			static const int STOP         = SIGSTOP;
			static const int STOPTTY      = SIGTSTP;
			static const int TTYIN        = SIGTTIN;
			static const int TTYOUT       = SIGTTOU;
			static const int IO           = SIGIO;
			static const int CPU          = SIGXCPU;
			static const int SIZE         = SIGXFSZ;
			static const int VIRTUALALARM = SIGVTALRM;
			static const int PROFILE      = SIGPROF;
			static const int WINDOW       = SIGWINCH;

		protected:
			void (*eventHandler)(int);
			std::vector<int> events;
			wxString directory;
			int mask;
			int argc;
			char **argv;
	
	};

}

#endif /* DS_DAEMON_H_ */
