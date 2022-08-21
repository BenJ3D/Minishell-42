# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 11:52:20 by bducrocq          #+#    #+#              #
#    Updated: 2022/08/21 19:01:19 by bducrocq         ###   ########.fr        #
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
CFLAGS      :=#-Wall -Wextra -Werror
SANITIZE    := -fsanitize=address
LLDBFLAG    := -g3
LIB         := $(INC_LIB) $(INC_INC) -lreadline ./libs/libft/libft.a
INC         := -I$(INCDIR)
INCDEP      := -I$(INCDIR)

#------------------------------------------------------------------------------#
#                                  RULES.......................................#
#------------------------------------------------------------------------------#
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT))) 

#Defauilt Make
all: lib $(NAME)

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
	@$(RM) -rf $(BUILDDIR)
	@make clean -C ./libs/libft/

#Full Clean, Objects and Binaries
fclean: clean
	@$(RM) -rf $(NAME)
	@make fclean -C ./libs/libft/

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

norme:
	norminette ./srcs/
	norminette ./includes/*.h


git:
	@git add .
	@printf "Message of the commit: " && read msg && git commit -m "$$msg"
	@git push

#Link
$(NAME): $(OBJECTS)
	$(CC) -o $(NAMEDIR)/$(NAME) $^ $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT) ./Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Non-File NAMEs
.PHONY: all re clean fclean