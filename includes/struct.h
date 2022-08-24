/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:13:38 by aartiges &        #+#    #+#             */
/*   Updated: 2022/08/24 01:29:13 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "includes.h"

typedef struct s_shell
{
	char *pwd;
	char *logname;
	char *name;
}		t_shell;

typedef struct s_env
{
	char **env;
	char *key;
}		t_env;

#endif
