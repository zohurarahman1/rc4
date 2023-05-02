CC=g++
CFLAGS=-c -Wall
LDFLAGS=

SOURCES=src/main.cpp src/rc4.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rc4

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
