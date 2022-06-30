EXENAME=brick

#compiler/linker settings
CC=g++
CFLAGS=-std=c++2a -MMD -pedantic -pedantic-errors -Wall -Werror
LINKFLAGS = -L $(PROJDIR)/src/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio

#Finding Directories
PROJDIR = ../../

SRCS=$(wildcard $(PROJDIR)/src/*.cpp) $(wildcard $(PROJDIR)/src/*/*.cpp) $(wildcard $(PROJDIR)/src/*/*/*.cpp)
SRCS_WITHOUT_PATH=$(notdir $(SRCS))
OBJS=$(SRCS_WITHOUT_PATH:.cpp=.o)

HEADERDIR = $(dir $(wildcard $(PROJDIR)/include/*.h) $(wildcard $(PROJDIR)/include/*/*.h) $(wildcard $(PROJDIR)/include/*/*/*.h)))
INCLUDEDIR = $(addprefix -I ,$(HEADERDIR)) -I $(PROJDIR)/include

VPATH = $(dir $(SRCS))

all: $(OBJS)
	@echo Linking Files...
	@$(CC) $(CFLAGS) $(OBJS) -o $(PROJDIR)/build/$(EXENAME) $(LINKFLAGS)
	@echo Build Successful :D

%.o:%.cpp
	@echo Compiling $(notdir $<)
	@$(CC) $(CFLAGS) $(INCLUDEDIR) -c $<

clean:
#for linux system change this to "rm *.o *.d ../*.exe" 
	@del *.o *.d ..\*.exe 
	@echo clean Successful