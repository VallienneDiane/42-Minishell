/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tabs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:20:19 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/27 16:49:22 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_fill_tab_str(t_cmd *cmd, t_list *list, int *i)
{
	cmd->tab_str[*i] = malloc(sizeof(char) * ft_strlen(list->content));
	if (!cmd->tab_str[*i])
	{
		free(cmd->tab_str);
		exit(EXIT_FAILURE);
	}
	cmd->tab_str[*i] = list->content;
	*i += 1;
}

void	ft_fill_heredoc(t_cmd *cmd, t_list *list, int *m)
{
	char	*str;
	pid_t	pid;

	cmd->last_in = 0;
	cmd->tab_heredoc[*m] = malloc(sizeof(char) * ft_strlen(list->content));
	if (!cmd->tab_heredoc[*m])
	{
		free(cmd->tab_heredoc);
		exit(EXIT_FAILURE);
	}
	cmd->tab_heredoc[*m] = list->content;

	signal(SIGINT, SIG_DFL);
	signal(SIGINT, ft_signal_exec_handler);
	signal(SIGQUIT, ft_signal_exec_handler);
	ft_term_handler(0);
	pipe(cmd->pipe_heredoc_fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(cmd->stdin_copy, STDIN_FILENO);
		str = ft_heredoc_loop(list->content);
		write(cmd->pipe_heredoc_fd[1], str, ft_strlen(str));
		close(cmd->pipe_heredoc_fd[1]);
		dup2(cmd->pipe_heredoc_fd[0], STDIN_FILENO);
		close(cmd->pipe_heredoc_fd[0]);
		signal(SIGINT, ft_signal_exec_handler);
		ft_term_handler(1);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		if (WIFSIGNALED(g_status) == 1 && WTERMSIG(g_status) == SIGINT)
		{
			printf(">\n");
			ft_term_handler(1);
		}			
		close(cmd->pipe_heredoc_fd[1]);
		dup2(cmd->pipe_heredoc_fd[0], STDIN_FILENO);
		close(cmd->pipe_heredoc_fd[0]);
	}
}

void	ft_fill_redir_in(t_cmd *cmd, t_list *list, int *j)
{
	cmd->tab_redir_in[*j] = malloc(sizeof(char) * ft_strlen(list->content));
	if (!cmd->tab_redir_in[*j])
	{
		free(cmd->tab_redir_in);
		exit(EXIT_FAILURE);
	}
	cmd->tab_redir_in[*j] = list->content;
	if (list->type == REDIR_IN)
		ft_create_file_in(cmd);
	cmd->last_in = 1;
}

void	ft_fill_redir_out1(t_cmd *cmd, t_list *list, int *k)
{
	cmd->tab_redir_out1[*k] = malloc(sizeof(char) * ft_strlen(list->content));
	if (!cmd->tab_redir_out1[*k])
	{
		free(cmd->tab_redir_out1);
		exit(EXIT_FAILURE);
	}
	cmd->tab_redir_out1[*k] = list->content;
	ft_create_file_out1(cmd);
	cmd->last_out = 1;
}

void	ft_fill_redir_out2(t_cmd *cmd, t_list *list, int *l)
{
	cmd->tab_redir_out2[*l] = malloc(sizeof(char) * ft_strlen(list->content));
	if (!cmd->tab_redir_out2[*l])
	{
		free(cmd->tab_redir_out2);
		exit(EXIT_FAILURE);
	}
	cmd->tab_redir_out2[*l] = list->content;
	ft_create_file_out2(cmd);
	cmd->last_out = 2;
}
