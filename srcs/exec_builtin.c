/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:23:25 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/19 16:52:00 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_builtin(t_list *list, t_cmd *cmd, char **envp)
{
	(void)list;
	(void)envp;
	int	i;

	i = 0;
	printf("Tableau des arguments :\n");
	while (cmd->tab_args[i])
	{
		printf("%s\n", cmd->tab_args[i]);
		i++;
	}
	// renvoyer vers les builtins codés en fonction de la commande et du nbr d'args en parcourant le tableau
}