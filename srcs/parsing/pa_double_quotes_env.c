/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_double_quotes_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:15:31 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/10 16:54:21 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_padq_env_code_error(t_data	*data, char	*semi_final)
{
	char	*value_env;

	if (semi_final == NULL)
		semi_final = ft_itoa(g_status & 255);
	else
	{
		value_env = ft_itoa(g_status & 255);
		semi_final = ft_strjoin_parsing(semi_final, value_env);
		printf("'%s', value_env\n", __func__);
		free(value_env);
	}
	data->scroller++;
	return (semi_final);
}

char	*ft_padq_env_digits(t_data	*data, char	*semi_final, char	*buffer)
{
	char	*value_env;

	if (semi_final == NULL)
		semi_final = ft_var_no_env(data, buffer);
	else
	{
		value_env = ft_var_no_env(data, buffer);
		semi_final = ft_strjoin_parsing(semi_final, value_env);
		printf("'%s', value_env\n", __func__);
		free(value_env);
		value_env = NULL;
	}
	return (semi_final);
}

char	*ft_pa_dq_env_bis(t_data	*data, char	*value_env)
{
	char	*tmp;

	tmp = ft_strdup(value_env);
	free(value_env);
	value_env = ft_env_getstr_env_value(data->env, tmp);
	free(tmp);
	return (value_env);
}

char	*ft_pq_dq_env_final(char	*semi_final, char	*value_env)
{
	char	*final;

	if (semi_final != NULL)
	{
		final = ft_strjoin_parsing(semi_final, value_env);
		printf("'%s', valu_env\n", __func__);
		free(value_env);
		value_env = NULL;
	}
	else
	{
		final = ft_strdup(value_env);
		printf("'%s', value_env\n", __func__);
		free(value_env);
		value_env = NULL;
	}
	return (final);
}

char	*ft_pa_fill_value(t_data	*data, char	*buffer, int len)
{
	int		pan;
	int		pin;
	char	*value_env;

	pan = 0;
	value_env = ft_calloc(sizeof(char), len + 1);
	if (!value_env)
		exit (42);
	pin = data->scroller - len;
	while (pan < len)
		value_env[pan++] = buffer[pin++];
	value_env[pan] = '\0';
	return (value_env);
}
