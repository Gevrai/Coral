CXXFLAGS = -g -Wall -Werror -std=c++11 `sdl2-config --cflags`
LDLIBS = `sdl2-config --libs`

SRC_PATH = Sources

PRGM  = Coral
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(PRGM)

$(PRGM): $(OBJS)
	$(CXX $(OBJS) $(LDLIBS) -o $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(PRGM)
