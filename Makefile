# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 11:52:20 by bducrocq          #+#    #+#              #
#    Updated: 2022/11/11 21:43:21 by hmarconn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Compiler and Linker
DEBUG=0

ifeq ($(DEBUG), 0) # for final compilation
CC = cc $(CFLAGS)
MAKELIB = @make DEBUG=0 -C./libs/libft/
endif
ifeq ($(DEBUG), 1)  # for sanitize test
CC = cc $(SANITIZE) $(LLDBFLAG)
MAKELIB = @make DEBUG=1 -C./libs/libft/
endif
ifeq ($(DEBUG), 2) # for LEAKS test
CC = cc $(LLDBFLAG)
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
INC         := -I$(INCDIR)
INCDEP      := -I$(INCDIR)
HEADERS      := 	./includes/define_common.h \
				./includes/includes.h \
				./includes/minishell.h \
				./includes/struct.h

#------------------------------------------------------------------------------#
#                                  RULES.......................................#
#------------------------------------------------------------------------------#

SOURCES     := 		./srcs/main.c \
					./srcs/builtins/cd.c \
					./srcs/builtins/echo.c \
					./srcs/builtins/env.c \
					./srcs/builtins/exit.c \
					./srcs/builtins/export.c \
					./srcs/builtins/export_api.c \
					./srcs/builtins/pwd.c \
					./srcs/builtins/unset.c \
					./srcs/dbg/debug_lst.c \
					./srcs/dbg/debug_pars.c \
					./srcs/env/env_init.c \
					./srcs/env/env_init2.c \
					./srcs/env/env_lst.c \
					./srcs/env/env_lst2.c \
					./srcs/env/env_utils.c \
					./srcs/env/env_utils2.c \
					./srcs/err/error_management.c \
					./srcs/exec/execve1.c \
					./srcs/exec/execve2.c \
					./srcs/exec/execve_findprog.c \
					./srcs/exec/execve_pipe.c \
					./srcs/exec/execve_utils.c \
					./srcs/exec/execve_utils2.c \
					./srcs/exec/heredoc/redirection_heredoc.c \
					./srcs/exec/redirection/redirection.c \
					./srcs/exec/redirection/redirection_dup.c \
					./srcs/exec/stat.c \
					./srcs/free/free.c \
					./srcs/list/list.c \
					./srcs/list/list2.c \
					./srcs/parsing/define_cmd_types.c \
					./srcs/parsing/define_cmdtypes_cmp.c \
					./srcs/parsing/pa_cmp_ft.c \
					./srcs/parsing/pa_double_quotes_env.c \
					./srcs/parsing/pa_double_quotes_env_cmp.c \
					./srcs/parsing/pa_env.c \
					./srcs/parsing/pa_env_variables.c \
					./srcs/parsing/pa_others.c \
					./srcs/parsing/pa_others_complementary.c \
					./srcs/parsing/pa_others_fcts.c \
					./srcs/parsing/pa_special_character.c \
					./srcs/parsing/pa_test.c \
					./srcs/parsing/pa_utils.c \
					./srcs/parsing/pa_utils_complementary.c \
					./srcs/parsing/pa_utils_len.c \
					./srcs/parsing/parsing.c \
					./srcs/parsing/prompt/prompt.c \
					./srcs/parsing/quotes_parsing.c \
					./srcs/parsing/quotes_parsing_complementary.c \
					./srcs/parsing/quotes_related.c \
					./srcs/signal/signal.c \
					./srcs/signal/stty.c
					
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


dbg:


#Clean only Objecst
clean:
	@echo "\033[33mRemoval of .o files of $(NAME) ...\033[0m"
	@$(RM) -rf $(OBJECTS)
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
	@$(CC) -o $(NAMEDIR)/$(NAME) $^ $(LIB)
	@echo "\n\033[32m🔥$\MiniHell created🔥\n\033[0m"

%.o : %.c $(HEADERS) Makefile $(LIBFT_PATH)
	@/bin/echo -n 🔥
	@$(CC) -c $< -o $@ -I $(INCDIR)

#Non-File NAMEs
.PHONY: all re clean fclean git