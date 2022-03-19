/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:48:52 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/19 16:49:50 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redir(t_list *list, t_cmd *cmd, char **envp)
{
	(void)list;
	(void)cmd;
	(void)envp;

	printf("je suis une redirection\n");
}