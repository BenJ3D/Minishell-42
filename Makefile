NAME = minishell

#SILENT THE RECIPE
ifndef VERBOSE
.SILENT:
endif

LIBFT_PATH = libft/libft.a

SRCS = 

OBJS = ${SRCS:.c=.o}

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

HEADER = minishell.h libft/libft.HEADER

all : libft ${NAME}

${NAME}: ${OBJS} ${HEADER} ${LIBFT_PATH}
			${CC} ${CFLAGS} ${OBJS} ${LIBFT_PATH} -o ${NAME}

%.o = %.c ${HEADER} Makefile
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

libft = 
		$(MAKE) libft/

clean = 
		${RM} ${OBJS}

fclean = clean
		${RM} ${NAME}

re = fclean re

.PHONY: all clean fclean re