/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:42:11 by dvallien          #+#    #+#             */
/*   Updated: 2022/05/03 15:24:55 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_start_exec(t_list *list, t_cmd *cmd)
{	
	int		i;
	int		current_block;

	i = 0;
	current_block = 1;
	ft_init_exec(cmd, list);
	while (list)
	{
		ft_get_args(list, cmd, current_block);
		cmd->path_ok = 0;
		if ((ft_is_builtin(cmd->tab_str[0]) == 0) && cmd->tab_str[0])
			cmd->valid_path = ft_access_path(cmd);
		while (list && list->block == current_block)
			list = list->next;
		ft_pipex_or_exec(cmd, list, &current_block);
	}
	ft_free_exec(cmd, i);
}

void	ft_pipex_or_exec(t_cmd *cmd, t_list *list, int *current_block)
{
	if (list && list->block != *current_block)
	{
		ft_exec_pipex(cmd);
		if (cmd->path_ok)
			free(cmd->valid_path);
		ft_free_all_tabs(cmd);
		*current_block += 1;
		cmd->infile_error = 0;
	}
	else
	{
		ft_exec_cmd(cmd);
		if (cmd->path_ok)
			free(cmd->valid_path);
	}
}

void	ft_exec_cmd(t_cmd *cmd)
{
	pid_t	pid;

	if (ft_is_builtin(cmd->tab_str[0]) == 0)
	{
		signal(SIGINT, ft_signal_exec_handler);
		signal(SIGQUIT, ft_signal_exec_handler);
		pid = fork();
		if (pid < 0)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			ft_execution(cmd);
		else
			ft_exec_parent_process(pid);
	}
	else if (cmd->infile_error == 0)
	{
		ft_exec_builtin(cmd);
		signal(SIGINT, ft_signal_handler);
	}
}

void	ft_exec_parent_process(pid_t pid)
{
	waitpid(pid, &g_status, 0);
	if (WIFSIGNALED(g_status) == 1 && WTERMSIG(g_status) == SIGINT)
	{
		printf("\n");
		g_status = 130;
	}
	else if (WIFSIGNALED(g_status) == 1 && WTERMSIG(g_status) == SIGQUIT)
	{
		printf("Quit: 3\n");
		g_status = 131;
	}
	else
		g_status = WEXITSTATUS(g_status);
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_exec_handler);
}

void	ft_execute(t_cmd *cmd)
{
	char	**env_tab;

	signal(SIGINT, SIG_DFL);
	if (ft_is_builtin(cmd->tab_str[0]) && cmd->infile_error == 0)
	{
		ft_exec_builtin(cmd);
	}
	if (cmd->valid_path != NULL && ft_is_builtin(cmd->tab_str[0]) == 0)
	{
		if (cmd->tab_str[0] && cmd->infile_error == 0)
		{
			env_tab = ft_env_to_tab(cmd);
			execve(cmd->valid_path, cmd->tab_str, env_tab);
		}
	}
	if (cmd->valid_path)
		exit (126);
	else
		exit (127);
}
