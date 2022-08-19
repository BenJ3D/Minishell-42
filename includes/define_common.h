/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_common.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:30:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/08/19 17:34:08 by bducrocq         ###   ########.fr       */
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

# define BLUE		"\033[0;34m"
# define NONE_COLOR	"\033[0;37m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define PURPLE		"\033[0;35m"
# define CYAN		"\033[0;36m"

#endif