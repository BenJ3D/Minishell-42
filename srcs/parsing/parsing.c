/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/20 21:45:39 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

static int	ft_count_pipe(char *buffer) //ft pour test sans parsing
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while(buffer[i])
		if (buffer[i++] == '|')
			len++;
	return (len);
}

/**
 * @brief retourne len du prochain mot
 * gère les pipes '|' (s'arrete si pipe trouvé)
 * 
 * @param str 
 * @return int 
 */
static int	ft_strlen_next_word(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '|')
		return (1);
	while (!ft_isspace(str[i]) && str[i] && str[i] != '|')
		i++;
	return (i);
}

static int	ft_define_cmd_type(t_list *lst) // FIXME: 32 lignes !!
{
	t_list	*tmp;

	if (!lst)
		return (-1);
	tmp = lst;
	tmp->type = CMD;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->str[0] == '>')
		{
			if (tmp->str[1] == '>')
				tmp->type = OUT2;
			else
				tmp->type = OUT1;
		}
		else if (tmp->str[0] == '<')
		{
			if (tmp->str[1] == '<')
				tmp->type = IN2;
			else
				tmp->type = IN1;
		}
		else if (tmp->str[0] == '|')
		{
			tmp->type = PIPE;
			tmp = tmp->next;
			tmp->type = CMD;
		}
		else
			tmp->type = ARG;
		tmp = tmp->next;
	}
	return (0);
}

/**
 * @brief split tout le buffer en plusieurs cmd dans une liste 
 * 
 * @param lst 
 * @param buffer 
 * @return int 
 */
static t_list	*ft_split_buffercmd_in_lst(char *buffer, int bufi)
{
	int		i;
	int		len;
	char	*str;
	t_list *cmd;
	
	cmd = NULL;
	while (buffer[bufi])
	{
		while(ft_isspace(buffer[bufi]) && buffer[bufi] && buffer[bufi] != '|')
			bufi = bufi + 1;
		if (buffer[bufi] == '\0')
			return (cmd);
		len = ft_strlen_next_word(buffer + bufi);
		str = ft_calloc(len + 1, sizeof(str));
		if (!str)
			return (NULL);
		i = 0;
		while(len-- > 0)
			str[i++] = buffer[bufi++];
		ft_lstadd_back(&cmd, ft_lstnew(str));
		free(str);
	}
	return (cmd);
}

/**
 * @brief 
 * 
 * @param lst 
 * @param nbrpipe 
 * @return t_cmdtab* 
 */
static t_cmdtab *ft_create_tab_per_cmd(t_list *lst, int nbrpipe)
{
	t_list		*tmp;
	t_cmdtab	*cmdtab;
	int			i;
	
	tmp = lst;
	cmdtab = ft_calloc(nbrpipe + 1, sizeof(cmdtab));
	i = 0;
	cmdtab[i++].lst = lst;
	while(tmp)
	{
		if (tmp->str[0] == '|')
		{
			cmdtab[i].lst = tmp->next;
			tmp->next = NULL;
			tmp = cmdtab[i++].lst;
		}
		else
			tmp = tmp->next;
	}
	return (cmdtab);
}

/**
 * @brief parsing de base pour decouper les cmd et args
 * 
 * @param data 
 * @param buffer 
 * @return int 
 */
int	ft_parsing_prompt(t_data *data, char *buffer)
{
	int		pipe;
	int		bufi;
	int		i;
	
	pipe = ft_count_pipe(buffer);
	if (pipe == 0)
		pipe++;
	i = 0;
	data->cmdtoparse = NULL;
	bufi = 0;
	data->cmdtoparse = ft_split_buffercmd_in_lst(buffer, 0);
	ft_define_cmd_type(data->cmdtoparse);
	data->cmdtab = ft_create_tab_per_cmd(data->cmdtoparse, pipe);
	return (pipe);
}


/**
 * @brief  return **argv pour execve (ex: "echo bonjour >> out.txt"  
 * 													==> return tab :
 * 													 tab[0]=echo /
 * 													 tab[1]=bonjour)
 * @param cmd 
 * @return char** 
 */
char	**ft_lstcmd_to_cmdarg_for_execve(t_list	*cmd)
{
	char	**argv;
	int		nbword;
	t_list	*lst;
	int		y;
	

	nbword = ft_lstsize(cmd); //FIXME: ft pour calculer le nombre de mot cmd+arg sans les redirections et pipe
	argv = ft_calloc(nbword + 1, sizeof(argv));
	lst = cmd;
	y = 0;
	while (lst)
	{
		if (lst->type == CMD || lst->type == ARG)
			argv[y] = ft_strdup(lst->str);
		y++;
		lst = lst->next;
	}
	return (argv);
}

// 							ls -all | grep @ | ls