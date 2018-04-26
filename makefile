#-----[Makefile]------
#$@ Contains the target file name
#$< Contains the first dependency name
#=====================

#----[Directories]----
oPath = obj
sPath = src
iPath = include
#====================

#---[Compiler and Settings]-----
compiler = g++
compilerFlags = -std=c++11 -O3
paths = -I./$(iPath)
#======================

#----[Variable Names]-------
headers = $(wildcard $(iPath)/*.hpp)
sources = $(wildcard $(sPath)/*.cpp)
objects = $(subst $(sPath)/,$(oPath)/,$(sources:.cpp=.o))
#==========================

#----[Compilation]---------
main:$(objects) $(headers) main.cpp
	$(compiler) $(compilerFlags) -o main $(objects) main.cpp $(paths)

$(oPath)/%.o:$(sPath)/%.cpp $(subst $(sPath)/, $(iPath)/,$(<:.cpp=.hpp))
	@mkdir -p $(@D)
	$(compiler) $(compilerFlags) -o $@ -c $(paths) $<

#-----[Clean up]-------
clean:
	rm main
	rm -rf $(oPath)/
