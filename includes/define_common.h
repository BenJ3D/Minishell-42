/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_common.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:30:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/22 21:04:22 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_COMMON_H

# define DEFINE_COMMON_H
# if defined(__linux__) || defined(linux) || defined(__linux)
#  define MY_SIZE_T_MAX	SIZE_MAX
#  define PATH_MAX 4096
# else
#  define MY_SIZE_T_MAX SIZE_T_MAX
# endif
# define TRUE 1
# define FALSE 0

# define SPACES " \t\n\r\v\f"

# define USER_MAX_LEN 16

# define DOUBLE_QUOTE 34
# define SIMPLE_QUOTE 39

# define READ 0
# define WRITE 1

# define PATH_HEREDOC "/tmp/.hdctmp1"
# define BUFFER_SIZE 10



# define CMD 0
# define ARG 1
# define PIPE 2 //	|
# define IN1 3 //	<
# define IN2 4	//	<<
# define OUT1 5	//	>
# define OUT2 6 //	>>
# define INFILE 7 // le nom du fichier
# define INQUOTE 8 // les characteres de fin de quote
# define OUTFILE 9 // le nom du fichier de sortie

# define NO_BUILTIN 0
# define BUILT_CD 1
# define BUILT_ECHO 2
# define BUILT_ENV 3
# define BUILT_EXPORT 4
# define BUILT_UNSET 5
# define BUILT_PWD 6
# define BUILT_EXIT 7


# define COLOR_BLACK	"\001\033[0;30m\002"
# define COLOR_RED		"\001\033[0;31m\002"
# define COLOR_GREEN	"\001\033[0;32m\002"
# define COLOR_YELLOW	"\001\033[0;33m\002"
# define COLOR_BLUE		"\001\033[0;34m\002"
# define COLOR_PURPLE	"\001\033[0;35m\002"
# define COLOR_CYAN		"\001\033[0;36m\002"
# define COLOR_NONE		"\001\033[0;37m\002"

#endif