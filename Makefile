# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 11:52:20 by bducrocq          #+#    #+#              #
#    Updated: 2022/09/02 19:23:48 by bducrocq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Compiler and Linker
CC = gcc $(CFLAGS) $(SANITIZE) $(LLDBFLAG)


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
	ifeq ($(UNAME_S),Linux)
		INC_LIB = -L/usr/local/lib
		INC_INC = -I/usr/local/include
	endif
	ifeq ($(UNAME_S),Darwin)
		INC_LIB = -L ~/.brew/opt/readline/lib
		INC_INC = -I ~/.brew/opt/readline/include
	endif

#Flags, Libraries and Includes
CFLAGS      :=# -Wall -Wextra -Werror
SANITIZE    :=# -fsanitize=address
LLDBFLAG    := -g3
LIBFT_PATH  := ./libs/libft/libft.a
LIB         := $(INC_LIB) $(INC_INC) -lreadline $(LIBFT_PATH)
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

#Copy Resources from Resources Directory to NAME Directory
resources: directories
	@cp $(RESDIR)/* $(NAMEDIR)/

lib: directories
	@make -C./libs/libft/
	
#Make the Directories
directories:
	@mkdir -p $(NAMEDIR)
	@mkdir -p $(BUILDDIR)

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
b:	lib $(NAME) cleand

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
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Non-File NAMEs
.PHONY: all re clean fclean
