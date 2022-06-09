cc = g++
flags = -w
src := $(wildcard ./*.cpp)
obj := $(patsubst ./%.cpp,./%.o,$(src))

all: $(obj)

%.o: %.cpp %.h
	$(cc) $(flags) -c $< -o $@