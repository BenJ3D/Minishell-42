/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_common.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:30:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/19 18:54:02 by bducrocq         ###   ########.fr       */
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

# define DOUBLE_QUOTE 34
# define SIMPLE_QUOTE 39

# define READ 0
# define WRITE 1

# define CMD 0
# define ARG 1
# define REDI 2
# define PIPE 3



# define BLUE		"\001\033[0;34m\002"
# define NONE_COLOR	"\001\033[0;37m\002"
# define RED		"\001\033[0;31m\002"
# define GREEN		"\001\033[0;32m\002"
# define PURPLE		"\001\033[0;35m\002"
# define CYAN		"\001\033[0;36m\002"

#endif