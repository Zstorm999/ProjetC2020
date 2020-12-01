#===================================================================================================================
# - Copyright 01/11/2020
#
# This source code is released the GNU GPLv3's policy,
# thus, is hereby granted the legal permission, to any individual obtaining a copy of this file, to copy,
# distribute and/or modify any of part of the project
# 
# the autors, CLEMENT Aimeric and ARCHAMBEAU Thomas
# discaim all copyright interest in the program ProjectC2020
#===================================================================================================================

# Compiler settings - Can be customized.
CC = gcc
CXXFLAGS = -std=c11 -O3 -w
LDFLAGS = -lm

# Makefile settings - Can be customized.
APPNAME = subwaysimulator
EXT = .c
SRCDIR = src
OBJDIR = obj

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)


########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME) 

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $< 

################### Cleaning rules ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)


