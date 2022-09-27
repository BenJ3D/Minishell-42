/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:13:38 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/27 19:32:47 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "includes.h"

typedef enum	e_redirection
{
	OUT_1,
	OUT_2,
	IN_1,
	IN_2
}	t_redirection;

typedef struct	s_envlst
{
	char			*key;
	char			*value;
	struct s_envlst	*next;
}			t_envlst;

typedef struct s_list //struct liste pour commande splitter mot a mot (ex: ls -> -all -> (pipe) -> cat -> -e -> (null))
{
	int				type;
	char			*str;
	struct s_list	*next;
}					t_list;

typedef struct	s_cmdtab //pour creer un tab de command, un t_list par commande (jusqu'à trouver un pipe '|'))
{									//exemple si buffer = ls -all | cat -e
	t_list	*lst;					//    cmdtab[0].lst = ls -> -all -> (pipe)
}				t_cmdtab;			//    cmdtab[1].lst = cat -> -e -> (null)



typedef struct s_data
{
	char		*pgr_name; 			//le nom de notre programe afficher dans notre prompt
	char		*line;				//\*line pour le prompt
	char		*buffer;			//buffer pour readline
	t_envlst	*env;				//contient tout l'environnement sous forme de liste
	t_cmdtab	*cmdtab; 			//toutes les commandes sont stockées dans un tableau de list
	t_list		*cmdtoparse; 		//contient toute la ligne de commande split en mot
	int			fd[2]; 				//pour pipe
}				t_data;

#endif
