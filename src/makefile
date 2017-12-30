CPP = g++
CFLAGS = -Wall -std=c++11 $(shell sdl2-config --cflags)
LDLIBS = $(shell sdl2-config --libs) -lSDL2_image

SRC_PATH = Sources

PRGM  = Coral
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(PRGM) run

$(PRGM): $(OBJS)
	$(CPP) $(OBJS) $(LDLIBS) -o $@

%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

run:
	./Coral

clean:
	rm -rf $(OBJS) $(PRGM)
