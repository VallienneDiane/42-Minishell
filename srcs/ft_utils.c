/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:04:06 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/24 15:06:24 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(src);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (0);
	else
	{
		while (src[i])
		{
			copy[i] = src[i];
			i++;
		}
		copy[i] = '\0';
		return (copy);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i]
			|| ((unsigned char *)s1)[i] == '\0'
			|| ((unsigned char *)s2)[i] == '\0')
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

static char	*ft_filltab(char *s1, char *s2, char *ptr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		((char *)ptr)[i] = ((char *)s1)[i];
		i++;
	}
	while (s2[j])
	{
		((char *)ptr)[i] = ((char *)s2)[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ptr)
		return (0);
	ptr = ft_filltab(s1, s2, ptr);
	return (ptr);
}
