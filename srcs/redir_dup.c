/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:04:02 by dvallien          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/20 10:56:57 by amarchal         ###   ########.fr       */
=======
/*   Updated: 2022/04/21 11:43:22 by dvallien         ###   ########.fr       */
>>>>>>> 9a1a48ef57e64b47809ce1c91c29fd41204e0aa7
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redir_dup(t_cmd *cmd)
{
	int	out1;
	int	out2;
	int	in;

	in = 0;
	out1 = 0;
	out2 = 0;
	if (cmd->tab_redir_in[0] != NULL && cmd->last_in == 1)
		ft_redir_dup_in(cmd, &in);
	if (cmd->tab_redir_out1[0] != NULL && cmd->last_out == 1)
	{
		out1 = dup(1);
		close(1);
		dup2(cmd->fd_out_trunc, 1);
	}
	if (cmd->tab_redir_out2[0] != NULL && cmd->last_out == 2)
	{
		out2 = dup(1);
		close(1);
		dup2(cmd->fd_out_append, 1);
	}
	ft_execute(cmd);
	ft_redir_clean(cmd, in, out1, out2);
}

void	ft_redir_dup_in(t_cmd *cmd, int *in)
{
	*in = dup(0);
	close(0);
	dup2(cmd->fd_in, 0);
}

void	ft_redir_clean(t_cmd *cmd, int in, int out1, int out2)
{
	if (cmd->tab_redir_in)
		dup2(in, 0);
	if (cmd->tab_redir_out1)
		dup2(out1, 1);
	if (cmd->tab_redir_out2)
		dup2(out2, 1);
}
