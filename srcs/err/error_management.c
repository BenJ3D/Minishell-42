/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief affiche dans stderr un message d'erreur sous forme : 
 * "programe name: commande: erreur type" avec code couleur
 * @param data 
 * @param cmd la commande en cours
 * @param msg le message d'erreur à afficher
 */
void	ft_err_display_line_error(t_data *data, char *cmd, char *msg)
{
	char	*errline;

	errline = ft_strjoin_max("%s%s: %s%s: %s%s%s\n",
			COLOR_CYAN, data->pgr_name, COLOR_PURPLE,
			cmd, COLOR_RED, msg, COLOR_NONE);
	ft_putstr_fd(errline, STDERR_FILENO);
	free(errline);
}

/**
 * @brief affiche dans stderr un message d'erreur sous forme : 
 * "programe name: commande: erreur type" avec code couleur
 * @param data 
 * @param cmd la commande en cours
 * @param msg le message d'erreur à afficher
 */
void	ft_err_display_line_export_error(t_data *data, char *cmd, char *msg)
{
	char	*errline;

	errline = ft_strjoin_max("%s%s: %s`%s': %s%s%s\n",
			COLOR_CYAN, data->pgr_name, COLOR_PURPLE,
			cmd, COLOR_RED, msg, COLOR_NONE);
	ft_putstr_fd(errline, STDERR_FILENO);
	free(errline);
}
