CC		= gcc
CXX		= g++
LINK	= g++

OBJECTS = DSController.o

INCPATH = -I/usr/include -I/usr/local/include -Iinclude
			
LIBPATH = -L/usr/local/lib

WX_CXX  = `wx-config --cppflags`
WX_LIBS = `wx-config --libs`

TARGET  = DSController

all: $(TARGET)

install: all
	sudo cp $(TARGET) /usr/local/bin
	sudo chmod +rx /usr/local/bin/$(TARGET)

deinstall:
	rm /usr/include/DS*.h
	rm /usr/lib/libds.o

clean:
	rm -rf $(OBJECTS) $(TARGET)

$(TARGET): $(OBJECTS) 
	$(LINK) $(LIBPATH) -g -o $(TARGET) $(OBJECTS) $(WX_LIBS)

DSController.o: DSController.cpp
	$(CXX) $(INCPATH) -fPIC -Wall -g -c DSController.cpp -o DSController.o $(WX_CXX)
