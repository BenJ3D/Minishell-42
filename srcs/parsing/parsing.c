/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/19 17:37:00 by bducrocq         ###   ########.fr       */
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
/**
 * @brief split tout le buffer en plusieurs cmd dans une liste 
 * 
 * @param lst 
 * @param buffer 
 * @return int 
 */
static t_list	*ft_split_buffercmd_in_lst(char *buffer, int *bufi)//TODO: une ligne en trop
{
	int		i;
	int		len;
	char	*str;
	t_list *cmd;
	
	cmd = NULL;
	while (buffer[*bufi])
	{
		while(ft_isspace(buffer[*bufi]) && buffer[*bufi] && buffer[*bufi] != '|')
			*bufi = *bufi + 1;
		if (buffer[*bufi] == '\0')
			return (cmd);
		len = ft_strlen_next_word(buffer + *bufi);
		str = ft_calloc(len + 1, sizeof(str));
		if (!str)
			return (NULL);
		i = 0;
		while(len-- > 0)
		{
			str[i++] = buffer[*bufi];
			*bufi = *bufi + 1;
		}
		ft_lstadd_back(&cmd, ft_lstnew(str));
		free(str);
	}
	return (cmd);
}

static t_cmdtab *ft_create_tab_per_cmd(t_list *lst, int nbrpipe) //TODO: 
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

// 							ls -all | grep @ | ls
//TODO: separer data->cmdtoparse en list dans un tableau (ft_create_tab_per_cmd)
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
	printf("pipe = %i\n", pipe);
	if (pipe == 0)
		pipe++;
	// data->cmdtab = ft_calloc(pipe + 1, sizeof(data->cmdtab));
	i = 0;
	data->cmdtoparse = NULL;
	
	bufi = 0;
	printf("BUFFER %s\n", buffer);
	data->cmdtoparse = ft_split_buffercmd_in_lst(buffer, &bufi);
	ft_lstdisplay_color(data->cmdtoparse);
	data->cmdtab = ft_create_tab_per_cmd(data->cmdtoparse, pipe);
	// data->cmdtab = ft_calloc(pipe + 1, sizeof(data->cmdtab));

	// ft_lstadd_back(&data->cmdtoparse[0], tmp);
	// printf("%s\n", buffer);
	while (i <= pipe)
	{
		ft_putstr("data->cmdtab[");
		ft_putnbr(i);
		ft_putstr("] = ");
		ft_lstdisplay_color(data->cmdtab[i].lst);
		i++;
	}
	// printf("\n");
	i = 0;
	ft_lstclear(&data->cmdtab[0].lst); 
	free(data->cmdtab);
	// while (i < pipe + 1)
	// 	ft_lstclear(&data->cmdtoparse[i++]);
	// ft_split_cmd_and_arg(data->cmdtab, buffer, data);


	
	// cmd[0]->cmd = ft_split(buffer, ' ');
	// for(int i = 0;  cmd[i]; i++)
	// {
	// 	ft_putstr(cmd[i]);
	// 	ft_putstr(" --\n");
	// }
	
	return (0);
}

// /**
//  * @brief split tout le buffer en plusieurs cmd dans des lists 
//  * (lst[0]->str = "ls -all |"
//  * 	lst[1]->str = "cat -e")
//  * 
//  * @param lst 
//  * @param buffer 
//  * @return int 
//  */
// static int	ft_split_buffercmd_in_lst(t_list *cmd, char *buffer)
// {
// 	int		i;
// 	int		b;
// 	int		len;
// 	char	*tmp;
// 	i = 0;
// 	while (ft_isspace(buffer[i]) && buffer[i]) // passe les premier espace
// 		i++;
// 	len = 0;
// 	b = i;
// 	while (buffer[i] && (!ft_isspace(buffer[i++])))
// 		len++;
// 	tmp = ft_calloc(len + 1, sizeof(tmp));
// 	if (!tmp)
// 		return (1);
// 	i = b;
// 	b = 0;
// 	while(buffer[i] && (!ft_isspace(buffer[i])))
// 		tmp[b++] = buffer[i++];
// 	ft_lstadd_back(&cmd, ft_lstnew(tmp));
// 	printf("lst1 = %s\n", cmd->str);
// 	free(tmp);
// 	return (0);
// }
