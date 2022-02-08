CC		= cc
CXX		= c++
LINK	= c++

OBJECTS = DSExtractor.o

INCPATH = -I/usr/include -I/usr/local/include -Iinclude
			
LIBPATH = -L/usr/local/lib

WX_CXX  = `wx-config --cppflags`
WX_LIBS = `wx-config --libs`

TARGET  = DSExtractor

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

DSExtractor.o: DSExtractor.cpp
	$(CXX) $(INCPATH) -fPIC -Wall -g -c DSExtractor.cpp -o DSExtractor.o $(WX_CXX)
