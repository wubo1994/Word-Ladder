CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCES=word_ladder.cpp headers.h
BOOST_HOME=/home/b/bowu/boost_1_66_0
CFLAGS += -I$(BOOST_HOME)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hello

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


