/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tabs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:20:19 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/28 13:24:55 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_fill_tab_str(t_cmd *cmd, t_list *list, int *i)
{
	cmd->tab_str[*i] = list->content;
	*i += 1;
}

void	ft_fill_heredoc(t_cmd *cmd, t_list *list, int *m)
{
	pid_t	pid;

	cmd->last_in = 0;
	cmd->tab_heredoc[*m] = list->content;
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, ft_signal_exec_handler);
	signal(SIGQUIT, ft_signal_exec_handler);
	ft_term_handler(0);
	pipe(cmd->pipe_heredoc_fd);
	pid = fork();
	if (pid == 0)
		ft_heredoc_child(cmd, list);
	else
		ft_heredoc_parent(cmd, pid);
}

void	ft_fill_redir_in(t_cmd *cmd, t_list *list, int *j)
{
	cmd->tab_redir_in[*j] = list->content;
	if (list->type == REDIR_IN)
		ft_create_file_in(cmd);
	cmd->last_in = 1;
}

void	ft_fill_redir_out1(t_cmd *cmd, t_list *list, int *k)
{
	cmd->tab_redir_out1[*k] = list->content;
	ft_create_file_out1(cmd);
	cmd->last_out = 1;
}

void	ft_fill_redir_out2(t_cmd *cmd, t_list *list, int *l)
{
	cmd->tab_redir_out2[*l] = list->content;
	ft_create_file_out2(cmd);
	cmd->last_out = 2;
}
