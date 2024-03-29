#
# -*- Makefile -*-
#
# Created      : 11/22/2017 3:46:0
# Author       : n-is
# email        : 073bex422.nischal@pcampus.edu.np
#
TARGET_NAME = codebase_01
TARGET = ../tests/$(TARGET_NAME)

CXXSRC = \
	$(SRCDIR)/TokenVisitor.cpp \
	$(SRCDIR)/Lexer.cpp \
	$(SRCDIR)/Parser.cpp \
	$(SRCDIR)/AST_Printer.cpp \
	$(SRCDIR)/C_CodeGen.cpp \

TSTSRC = \
	$(TSTDIR)/main_test.cpp \
	$(TSTDIR)/test_Error.cpp \
	$(TSTDIR)/test_Token.cpp \
	$(TSTDIR)/test_Lexer.cpp \
	$(TSTDIR)/test_Parser.cpp \

UTILSRC = \
	$(UTILDIR)/Error.cpp \

HELPERSRC = \
	$(HELPERDIR)/tokensToStrings.cpp \

INCDIR = ../includes
SRCDIR = ../src
TSTDIR = ../tests
UTILDIR = ../utils
HELPERDIR = ../helpers

PREFIX = /usr/local

###############################################################################################

VPATH=%.cpp $(SRCDIR) ../ $(TSTDIR) $(UTILDIR) $(HELPERDIR)

CC = gcc

CXX = g++
CXXFLAGS =  -Wall -Wextra -g -std=c++14 -O0 -DTEST

OBJ = $(patsubst $(SRCDIR)/%.cpp, %.o, $(CXXSRC)) $(patsubst $(TSTDIR)/%.cpp, %.o, $(TSTSRC)) \
	$(patsubst $(UTILDIR)/%.cpp, %.o, $(UTILSRC)) $(patsubst $(HELPERDIR)/%.cpp, %.o, $(HELPERSRC))
DEP = $(OBJ:.o=.d)

all : $(TARGET)

run :$(TARGET)
	./$(TARGET)

$(TARGET) : $(OBJ)
	@ echo Building the whole project
	$(CXX) $(CXXFLAGS) $^ -o $@
	@ echo "$(TARGET)" is build

install :$(TARGET)
	@ echo "Installing $(TARGET_NAME)"
	@ mkdir -p $(DESTDIR)$(PREFIX)/bin
	@ cp $< $(DESTDIR)$(PREFIX)/bin/
	@ echo "$(TARGET_NAME) Successfully Installed"

.PHONY : clean cleaner uninstall

%.d : $(SRCDIR)/%.cpp
	@ echo Creating dependency file for $<
	$(CPP) $< -MM -MT $(@:.d=.o) >$@
	
%.d : ../%.cpp
	@ echo "Creating dependency file for "$<
	$(CPP) $< -MM -MT $(@:.d=.o) >$@
	
%.d : $(TSTDIR)/%.cpp
	@ echo "Creating dependency file for "$<
	$(CPP) $< -MM -MT $(@:.d=.o) >$@

%.d : $(UTILDIR)/%.cpp
	@ echo "Creating dependency file for "$<
	$(CPP) $< -MM -MT $(@:.d=.o) >$@

%.d : $(HELPERDIR)/%.cpp
	@ echo "Creating dependency file for "$<
	$(CPP) $< -MM -MT $(@:.d=.o) >$@

-include $(DEP)

clean :
	@ rm -f $(OBJ)
	@ rm -f $(TARGET)
	@ echo "\t\t"Everything Cleaned Up

cleaner : clean
	@ rm -f $(DEP)
	@ echo "\t\t"Dependencies Cleaned Up

uninstall :
	@ echo "Uninstalling $(TARGET_NAME)"
	@ rm -f $(DESTDIR)$(PREFIX)/bin/$(TARGET_NAME)
	@ echo "$(TARGET_NAME) Successfully Uninstalled"

makeDebug :
	@ echo $(OBJ)
