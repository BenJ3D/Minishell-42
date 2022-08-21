# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 11:52:20 by bducrocq          #+#    #+#              #
#    Updated: 2022/08/21 12:41:46 by bducrocq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Compiler and Linker
CC = gcc $(CFLAGS) $(SANITIZE) $(LLDBFLAG)


#The Target Binary Program
TARGET      := program

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := srcs
INCDIR      := includes
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := res
SRCEXT      := c
DEPEXT      := d
OBJEXT      := o


UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		INC_LIB = -L/usr/local/lib
		INC_INC = -I/usr/local/include
	endif
	ifeq ($(UNAME_S),Darwin)
		INC_LIB = -L ~/.brew/opt/readline/lib
		INC_INC = -I ~/.brew/opt/readline/include
	endif

#Flags, Libraries and Includes
CFLAGS      :=#-Wall -Wextra -Werror
SANITIZE    := -fsanitize=address
LLDBFLAG    := -g3
LIB         := $(INC_LIB) $(INC_INC) -lreadline
LIB         := -fopenmp -lm -larmadillo
INC         := -I$(INCDIR) -I/usr/local/include
INCDEP      := -I$(INCDIR)

#---------------------------------------------------------------------------------
#                        DO NOT EDIT BELOW THIS LINE.............................-
#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Defauilt Make
all: resources $(TARGET)

#Remake
remake: cleaner all

#Copy Resources from Resources Directory to Target Directory
resources: directories
    @cp $(RESDIR)/* $(TARGETDIR)/

#Make the Directories
directories:
    @mkdir -p $(TARGETDIR)
    @mkdir -p $(BUILDDIR)

#Clean only Objecst
clean:
    @$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries
cleaner: clean
    @$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(TARGET): $(OBJECTS)
    $(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
    @mkdir -p $(dir $@)
    $(CC) $(CFLAGS) $(INC) -c -o $@ $<
    @$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
    @cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
    @sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
    @sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
    @rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Non-File Targets
.PHONY: all remake clean cleaner resources