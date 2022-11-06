/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:21:26 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/06 20:37:10 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_env_extract_key_name_norm(char *str, int len, int i)
{
	char	*tmp;

	len = 0;
	while (str[len] != '=' && str[len])
		len++;
	len++;
	tmp = ft_calloc(len, sizeof(char *));
	i = 0;
	while (str[i] != '=' && str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

/**
 * @brief return name key without '='
 * 
 * @param str 
 * @return char* 
 */
char	*ft_env_extract_key_name(char *str, int *isenv)
{
	int		i;
	int		len;
	char	*tmp;

	i = 1;
	len = 0;
	tmp = NULL;
	while (str[i])
		if (str[i++] == '=')
			len++;
	if (len == 0)
	{
		*isenv = FALSE;
		tmp = ft_strdup(str);
		return (tmp);
	}
	else
		tmp = ft_env_extract_key_name_norm(str, len, i);
	return (tmp);
}

/**
 * @brief pour triage export (ne set pas isenv comme ft_env_extract_key_name)
 * 
 * @param str 
 * @return char* 
 */
char	*ft_env_extract_key(char *str)
{
	int		i;
	int		len;
	char	*tmp;

	i = 1;
	len = 0;
	while (str[i])
		if (str[i++] == '=')
			len++;
	if (len == 0)
	{
		tmp = ft_strdup(str);
		return (tmp);
	}
	tmp = ft_env_extract_key_name_norm(str, len, i);
	return (tmp);
}

/**
 * @brief return content value after '=' key env
 * 
 * @param str 
 * @return char* 
 */
char	*ft_env_extract_value_content(char *str)
{
	int		i;
	int		y;
	char	*tmp;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] == '\0')
		return (ft_strdup(""));
	i++;
	tmp = ft_calloc((ft_strlen(str) - i) + 1, sizeof(char));
	y = 0;
	while (str[i])
	{
		tmp[y] = str[i];
		i++;
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
}
