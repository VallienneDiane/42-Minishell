/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:23:25 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/31 11:31:08 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_builtin(t_list *list, t_cmd *cmd, char **envp)
{
	(void)list;
	(void)envp;
	int	i;

	i = 0;
	while (cmd->tab_str[i])
	{
		printf("je suis un builtin\n");
		i++;
	}
	// renvoyer vers les builtins codés en fonction de la commande et du nbr d'args en parcourant le tableau
}