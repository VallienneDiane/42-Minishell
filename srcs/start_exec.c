/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:42:11 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/28 13:18:32 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_tab(char **av)
{
	int	i;

	i = 0;
	// while (av[i])
	// {
	// 	free(av[i]);
	// 	i++;
	// }
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

void	ft_start_exec(t_list *list, t_cmd *cmd)
{	
	int		i;
	int		current_block;

	i = 0;
	current_block = 1;
	cmd->infile_error = 0;
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
		{
			ft_exec_cmd(cmd);
		}
			
		// ft_free_tab(cmd->tab_str);
		// free les tabs
		free(cmd->valid_path);
		ft_free_all_tabs(cmd);
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
	else
		ft_exec_builtin(cmd);
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
