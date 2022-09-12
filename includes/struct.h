/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:13:38 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/12 23:46:48 by bducrocq         ###   ########.fr       */
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

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}					t_list;
typedef enum e_redirection
{
	OUT_1,
	OUT_2,
	IN_1,
	IN_2
}	t_redirection;
typedef struct s_cmdlst
{
	char			*cmd;
	char			**arg;
	char			*file;
	t_redirection	type_redirection;
	struct s_cmdlst	*next;
}				t_cmdlst;

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
