all: breakout

CXXFLAGS = -std=c++17 -ggdb3 -O0
CPPFLAGS = $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS  = $(shell pkg-config --libs gtk+-3.0)

SOURCE = main.cpp gui.cpp breakout.cpp
HEADER = gui.h breakout.h
OBJECT = $(SOURCE:%.cpp=%.o)

%.o: %.cpp $(HEADER)
	g++ $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

breakout: $(OBJECT)
	g++ $(CXXFLAGS) $^ $(LDFLAGS) -o $@

dist:
	-mkdir breakout1
	cp main.cpp gui.cpp gui.h breakout.cpp breakout.h Makefile breakout1/
	unifdef -x2 -m -U REF breakout1/breakout.cpp
	tar cfz breakout1.tar.gz breakout1/
	
clean:
	rm -rf breakout1
