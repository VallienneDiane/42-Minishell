/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:26:31 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/22 15:04:40 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_valid(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (0);
	return (1);
}

void	ft_check_bracket_s(char *line, t_pars_info *p_info)
{
	if (line[p_info->j] == '{')
	{
		p_info->j += 1;
		p_info->bracket = 1;
	}
	else
		p_info->bracket = 0;
}

int	ft_errno_size(void)
{
	char	*errno_str;
	int		errno_size;

	errno_str = ft_itoa(WEXITSTATUS(g_status));
	errno_size = ft_strlen(errno_str);
	free(errno_str);
	return (errno_size);
}

int	ft_env_size(char *line, t_pars_info *p_info)
{
	char	*env_name;
	int		l;

	p_info->j += 1;
	l = 0;
	ft_check_bracket_s(line, p_info);
	if (line[p_info->j] == '?')
		return (ft_errno_size());
	while (line[p_info->j + l] && ft_is_valid(line[p_info->j + l]))
		l++;
	env_name = ft_calloc(sizeof(char), l + 1);
	l = 0;
	while (line[p_info->j] && ft_is_valid(line[p_info->j]))
		env_name[l++] = line[p_info->j++];
	if (p_info->bracket)
		p_info->j += 1;
	if (ft_getenv(env_name, p_info->cmd))
	{
		l = ft_strlen(ft_getenv(env_name, p_info->cmd));
		free(env_name);
		return (l);
	}
	free(env_name);
	return (0);
}
