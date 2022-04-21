/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tabs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:20:19 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/21 11:43:22 by dvallien         ###   ########.fr       */
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

	cmd->last_in = 0;
	cmd->tab_heredoc[*m] = malloc(sizeof(char) * ft_strlen(list->content));
	if (!cmd->tab_heredoc[*m])
	{
		free(cmd->tab_heredoc);
		exit(EXIT_FAILURE);
	}
	cmd->tab_heredoc[*m] = list->content;
	dup2(cmd->stdin_copy, STDIN_FILENO);
	str = ft_heredoc_loop(list->content);
	pipe(cmd->pipe_heredoc_fd);
	write(cmd->pipe_heredoc_fd[1], str, ft_strlen(str));
	close(cmd->pipe_heredoc_fd[1]);
	dup2(cmd->pipe_heredoc_fd[0], STDIN_FILENO);
	close(cmd->pipe_heredoc_fd[0]);
}

void	ft_fill_redir_in(t_cmd *cmd, t_list *list, int *j)
{
	cmd->last_in = 1;
	cmd->tab_redir_in[*j] = malloc(sizeof(char) * ft_strlen(list->content));
	if (!cmd->tab_redir_in[*j])
	{
		free(cmd->tab_redir_in);
		exit(EXIT_FAILURE);
	}
	cmd->tab_redir_in[*j] = list->content;
	if (list->type == REDIR_IN)
	{
		if (ft_create_file(cmd, 0) == -1)
			ft_error_create_file();
	}
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
	if (ft_create_file(cmd, 1) == -1)
		ft_error_create_file();
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
	if (ft_create_file(cmd, 2) == -1)
		ft_error_create_file();
	cmd->last_out = 2;
}
