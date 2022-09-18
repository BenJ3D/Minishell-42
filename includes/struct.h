/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:13:38 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/18 16:29:56 by bducrocq         ###   ########.fr       */
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
	struct s_list	*arg;
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
	char			*arg;
	char			*file;
	t_redirection	type_redirection;
	struct s_cmdlst	*next;
}				t_cmdlst;

typedef struct s_cmdtab
{
	t_list	*lst;
}				t_cmdtab;

typedef struct s_data
{
	char		*pgr_name;
	t_envlst	*env;
	t_cmdtab	*cmdtab;
	t_list		*cmdtoparse; //contient toute la commande separer par mot
}				t_data;

#endif
