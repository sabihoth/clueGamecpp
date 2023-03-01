appname := clueGame

CXX := g++
CXXFLAGS := -Wall -Werror -g -std=c++17

srcfiles := $(shell find . -maxdepth 1 -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))


#This command compiles alll files into seperate object files
all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

#Clears all object files, please do this before submitting
clean:
	rm -f $(objects) clueGame
	
#This can be used to run the project a bit eaise
run:
	./$(appname)
	