# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 11:52:20 by bducrocq          #+#    #+#              #
#    Updated: 2022/11/07 18:38:53 by bducrocq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Compiler and Linker
DEBUG=1

ifeq ($(DEBUG), 0) # for final compilation
CC = gcc $(CFLAGS)
MAKELIB = @make DEBUG=0 -C./libs/libft/
endif
ifeq ($(DEBUG), 1)  # for sanitize test
CC = gcc $(SANITIZE) $(LLDBFLAG)
MAKELIB = @make DEBUG=1 -C./libs/libft/
endif
ifeq ($(DEBUG), 2) # for LEAKS test
CC = gcc $(LLDBFLAG)
MAKELIB = @make DEBUG=2 -C./libs/libft/
endif

#The Target Binary Program
NAME        := minishell

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := srcs
INCDIR      := includes
BUILDDIR    := obj
NAMEDIR     := ./
RESDIR      := lib
SRCEXT      := c
DEPEXT      := d
OBJEXT      := o


UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux) #sur linux (ou WSL) instal readline : 'apt-get install readline'
		INC_LIB = -L/usr/local/lib
		INC_INC = -I/usr/local/include
	endif
	ifeq ($(UNAME_S),Darwin)
		INC_LIB = -L ~/.brew/opt/readline/lib
		INC_INC = -I ~/.brew/opt/readline/include
	endif

#	-L .brew/opt/readline/lib -I .brew/opt/readline/include

#Flags, Libraries and Includes
CFLAGS      := -Wall -Wextra -Werror
SANITIZE    := -fsanitize=address
LLDBFLAG    := -g3
LIBFT_PATH  := ./libs/libft/libft.a
LIB         := $(INC_LIB) $(INC_INC) -lreadline $(LIBFT_PATH)
# LIB         := $(INC_LIB) $(INC_INC) -lreadline $(LIBFT_PATH)
INC         := -I$(INCDIR)
INCDEP      := -I$(INCDIR)
#------------------------------------------------------------------------------#
#                                  RULES.......................................#
#------------------------------------------------------------------------------#
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT))) 

#Defauilt Make
all: lib $(NAME) cleand

#Remake
re: fclean all

fix: cleand

#Copy Resources from Resources Directory to NAME Directory
resources: directories
	@cp $(RESDIR)/* $(NAMEDIR)/

lib: directories
	$(MAKELIB)
	
#Make the Directories
directories:
	@mkdir -p $(NAMEDIR)
	@mkdir -p $(BUILDDIR)

dbg:


#Clean only Objecst
clean:
	@echo "\033[33mRemoval of .o files of $(NAME) ...\033[0m"
	@$(RM) -rf $(BUILDDIR)
	@make clean -C ./libs/libft/
	@echo "\033[31mFiles .o deleted\n\033[0m"

#Full Clean, Objects and Binaries
fclean: clean
	@echo "\033[33mRemoval of $(NAME)...\033[0m"
	@$(RM) -rf $(NAME)
	@make fclean -C ./libs/libft/
	@echo "\033[31mBinary $(NAME) deleted\n\033[0m"

#Clean file *.d
cleand:
	@find . -name "*.d" -type f -delete

#Compile and keep the executable only
b:	lib $(NAME) clean

#compile and keep only the binary
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

git:
	@git add .
	@printf "Message of the commit: " && read msg && git commit -m "$$msg"
	@git push

#Link
$(NAME): $(OBJECTS)
	$(CC) -o $(NAMEDIR)/$(NAME) $^ $(LIB)
	@echo "\033[32m$(NAME) created\n\033[0m"

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT) $(LIBFT_PATH) ./Makefile ./includes/*.h 
	@mkdir -p $(dir $@)
	$(CC) $(INC) $(INC_INC) -c -o $@ $<
	@$(CC) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Non-File NAMEs
.PHONY: multi all re clean fclean
