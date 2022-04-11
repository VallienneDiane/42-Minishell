/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:36:20 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/29 15:10:02 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strjoin_content(char *s1, char *s2)
{
	// char	*str;
	int		i;
	int		j;
	// int		k;

	// printf("je joins : %s\navec : %s\n", s1, s2);

	// if (s1 == NULL || s2 == NULL)
	// 	return (NULL);
	i = 0;
	j = 0;
	// k = 0;
	// str = malloc(sizeof(char) * (ft_strlen((char *)s1)
	// 			+ ft_strlen((char *)s2) + 1));
	// if (!str)
	// 	return (NULL);
	while (s1[i])
	{
		i++;
	// printf("\033[91mICI\n\033[0m");
	// printf("\033[91ms1[%d] : %c\n\033[0m", j, s1[j]);
	// 	str[i++] = s1[j++];
	}
	while (s2[j])
		s1[i++] = s2[j++];
	// str[i] = '\0';
	// free(s1);
	// return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	str = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1));
	if (!str)
		return (NULL);
	while (s1[j])
	{
		str[i++] = s1[j++];
	}
	while (s2[k])
		str[i++] = s2[k++];
	str[i] = '\0';
	free(s1);
	return (str);
}
