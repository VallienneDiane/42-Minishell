/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:10:43 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/22 17:43:36 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_option(char *arg)
{
	int	i;

	i = 1;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_redir_putstr(t_cmd *cmd, char *str)
{
	if (cmd->last_out == 2)
		ft_putstr_fd(str, cmd->fd_out_append);
	else if (cmd->last_out == 1)
		ft_putstr_fd(str, cmd->fd_out_trunc);
	else
	{
		ft_putstr_fd(str, STDOUT_FILENO);
	}
}

void	ft_print_echo(t_cmd *cmd, int *option, int *is_arg, int i)
{
	if (cmd->tab_str[i][0] == '-' && *is_arg == 0)
	{
		if (ft_option(cmd->tab_str[i]))
			*option = 1;
		else
			*is_arg = 1;
	}
	if (*is_arg || cmd->tab_str[i][0] != '-')
	{
		ft_redir_putstr(cmd, cmd->tab_str[i]);
		*is_arg = 1;
	}
}

void	ft_print_space(t_cmd *cmd)
{
	if (cmd->last_out == 2)
		ft_putstr_fd(" ", cmd->fd_out_append);
	else if (cmd->last_out == 1)
		ft_putstr_fd(" ", cmd->fd_out_trunc);
	else
		ft_putstr_fd(" ", STDOUT_FILENO);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	is_arg;
	int	option;

	i = 1;
	is_arg = 0;
	option = 0;
	while (cmd->tab_str[i])
	{
		ft_print_echo(cmd, &option, &is_arg, i);
		i++;
		if (is_arg == 1 && cmd->tab_str[i])
			ft_print_space(cmd);
	}
	if (!option)
		ft_redir_putstr(cmd, "\n");
	g_status = 0;
	return (0);
}
