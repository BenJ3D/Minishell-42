/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:13:38 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/12 18:22:03 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "includes.h"

typedef struct s_envlst
{
	char *key;
	char *value;
	struct s_envlst *next;
}		t_envlst;

typedef struct s_cmdtable
{
	char	*progname;
	char	**arg;
}				t_cmdtable;


typedef struct s_data
{
	char		*pgr_name;
	t_envlst	*env;
	t_cmdtable	*cmdtab;
	t_list		*cmdlst;
}				t_data;

#endif
