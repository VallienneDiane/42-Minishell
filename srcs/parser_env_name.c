/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:37:02 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/28 14:36:36 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_bracket_n(char *line, t_pars_info *p_info)
{
	if (line[p_info->i] == '{')
	{
		p_info->i += 1;
		p_info->bracket = 1;
	}
	else
		p_info->bracket = 0;
}

char	*ft_errno_name(t_pars_info *p_info)
{
	char	*env_name;

	env_name = ft_calloc(sizeof(char), 2);
	env_name[0] = '?';
	p_info->i++;
	if (p_info->bracket)
		p_info->i++;
	return (env_name);
}

char	*ft_env_name(char *line, t_pars_info *p_info)
{
	int		l;
	char	*env_name;

	l = 0;
	p_info->i++;
	ft_check_bracket_n(line, p_info);
	if (line[p_info->i] == '?')
		return (ft_errno_name(p_info));
	while (line[p_info->i + l] && ft_is_valid(line[p_info->i + l]))
		l++;
	env_name = ft_calloc(sizeof(char), l + 1);
	l = 0;
	while (line[p_info->i] && ft_is_valid(line[p_info->i]))
		env_name[l++] = line[p_info->i++];
	if (p_info->bracket)
		p_info->i++;
	return (env_name);
}
