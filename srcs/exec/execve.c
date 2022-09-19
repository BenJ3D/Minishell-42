/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/20 01:35:02 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

// ft_lstcmd_to_cmdarg_for_execve

char	*get_next_path(t_data *data, int *ipath)
{
	char	*path;
	char	*envpaths;
	int		i;
	
	envpaths = ft_env_getstr_env_value(data->env, "PATH");
	printf("env paths = %s\n",envpaths);//FIXME:
	i = *ipath;
	while(envpaths[i])
	{
		if (envpaths[i] == ':')
			break ;
		i++;
	}
	path = ft_calloc(i + 1, sizeof(path));
	ft_strlcpy(path, (envpaths + *ipath), i);
	return (path);
}

char	*ft_find_prog_path(char *progname, char *envpath) //TODO:
{
	int		ipath;

	ipath = 0;
	return (NULL);
}

int	ft_run_execve(t_cmdtab *cmdtab, t_data *data)
{
	char	**argv;
	char	**envp;
	char	*progpath;
	int		ipath;

	ipath = 0;
	argv = ft_lstcmd_to_cmdarg_for_execve(cmdtab[0].lst);
	envp = ft_env_convert_envlst_to_tab(data->env);
	dbg_display_argv(argv);
	get_next_path(data, &ipath); // FIXME: pas ici

	execve(progpath, argv, envp);
	ft_free_argv(argv);
	return (0);
}