/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:42:11 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/22 17:09:30 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_start_exec(t_list *list, t_cmd *cmd)
{	
	int		i;
	int		current_block;

	i = 0;
	current_block = 1;
	cmd->valid_path = NULL;
	while (list)
	{
		ft_get_args(list, cmd, current_block);
		if ((ft_is_builtin(cmd->tab_str[0]) == 0) && cmd->tab_str[0])
			cmd->valid_path = ft_access_path(cmd);
		while (list && list->block == current_block)
			list = list->next;
		if (list && list->block != current_block)
		{
			ft_exec_pipex(cmd);
			current_block++;
		}
		else
			ft_exec_cmd(cmd);
		// free les tabs
	}
}

void	ft_exec_cmd(t_cmd *cmd)
{
	pid_t	pid;

	if (ft_is_builtin(cmd->tab_str[0]) == 0)
	{
		signal(SIGINT, ft_signal_exec_handler);
		pid = fork();
		if (pid < 0)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			ft_execution(cmd);
		else
			ft_exec_parent_process(cmd, pid);
	}
	else
		ft_exec_builtin(cmd);
}

void	ft_exec_parent_process(t_cmd *cmd, pid_t pid)
{
	int		status;

	if (ft_atoi(ft_getenv("SHLVL", cmd)) != 2)
	{
		ft_term_handler(1);
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		waitpid(pid, &g_status, 0);
	}
	waitpid(pid, &g_status, 0);
	status = WEXITSTATUS(g_status);
	signal(SIGINT, ft_signal_handler);
}

void	ft_execution(t_cmd *cmd)
{
	if (cmd->tab_redir_in[0] || cmd->tab_redir_out1[0] \
	|| cmd->tab_redir_out2[0])
		ft_redir_dup(cmd);
	else
		ft_execute(cmd);
}

void	ft_execute(t_cmd *cmd)
{
	char	**env_tab;

	if (ft_is_builtin(cmd->tab_str[0]))
		ft_exec_builtin(cmd);
	if (cmd->valid_path != NULL && ft_is_builtin(cmd->tab_str[0]) == 0)
	{
		if (cmd->tab_str[0])
		{
			env_tab = ft_env_to_tab(cmd);
			execve(cmd->valid_path, cmd->tab_str, env_tab);
		}
	}
	exit(1);
}
