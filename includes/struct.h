/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:13:38 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/11 02:54:44 by bducrocq         ###   ########.fr       */
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
	char	*cmd;
	char	**arg;
}				t_cmdtable;


typedef struct s_data
{
	char		*pgr_name;
	t_envlst	*env;
	t_list		*cmd;
}				t_data;

#endif
