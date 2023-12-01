CXX = g++-11 -std=c++20
CXXFLAGS = -Wall -g -MMD -Werror=vla -lX11 # use -MMD to generate dependencies
LIBFLAGS = -L/usr/X11R6/lib -lX11 #give path to library
SOURCES = $(wildcard *.cc)   # list of all .cc files in the current directory
OBJECTS = ${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=raiinet

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)  $(LIBFLAGS)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBFLAGS)

-include ${DEPENDS}

.PHONY: clean tests
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
