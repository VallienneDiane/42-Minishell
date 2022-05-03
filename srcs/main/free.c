/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:11:56 by dvallien          #+#    #+#             */
/*   Updated: 2022/05/03 15:49:10 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tab(char **av)
{
	free(av);
}

void	ft_free_all_tabs(t_cmd *cmd)
{
	if (cmd->tab_heredoc)
		ft_free_tab(cmd->tab_heredoc);
	if (cmd->tab_str)
		ft_free_tab(cmd->tab_str);
	if (cmd->tab_redir_in)
		ft_free_tab(cmd->tab_redir_in);
	if (cmd->tab_redir_out1)
		ft_free_tab(cmd->tab_redir_out1);
	if (cmd->tab_redir_out2)
		ft_free_tab(cmd->tab_redir_out2);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	temp = *lst;
	while (*lst)
	{
		*lst = temp->next;
		free(temp->content);
		free(temp);
		temp = *lst;
	}
}

void	ft_free_split(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

void	ft_wait_pids(t_cmd *cmd)
{
	int	i;

	i = 0;
	close(STDIN_FILENO);
	while (i <= cmd->pipe_id && cmd->pipe_id > 0)
		waitpid(cmd->pipe_pids[i++], &g_status, 0);
	free(cmd->pipe_pids);
	ft_free_all_tabs(cmd);
}
