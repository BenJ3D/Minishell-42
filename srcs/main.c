/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:12:46 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/11 20:40:46 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

static void	ft_init_minishell(t_data *data)
{
	data->pgr_name = ft_strdup("MiniHell");
	data->s_quotes_switch = 0;
	data->d_quotes_switch = 0;
	data->savefd[0] = dup(STDIN_FILENO);
	data->savefd[1] = dup(STDOUT_FILENO);
}

static int	ft_get_current_shlvl(t_envlst *env)
{
	char	*shlvl;
	int		ret;

	shlvl = ft_env_getstr_env_value(env, "SHLVL");
	if (shlvl != NULL)
		ret = ft_atoi(shlvl);
	else
	{
		ft_builtin_export_api(env, "SHLVL", "0");
		ret = 0;
	}
	free (shlvl);
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	ac = 0;
	ft_bzero(data, t_data);
	ft_issaty_control();
	ft_stty_control(0);
	ft_init_minishell(&data);
	ft_env_init_lst(envp, &data);
	data.currentshlvl = ft_get_current_shlvl(data.env);
	prompt_minishell(&data);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_exit_normal(&data, av);
	return (0);
}
x