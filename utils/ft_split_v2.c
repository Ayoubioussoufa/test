/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:05:16 by sben-ela          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_lenword(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		i++;
	}
	return (i);
}

static char	*ft_fullstr(char const *str, char c)
{
	char	*word;
	int		i;
	int		len;

	i = 0;
	len = ft_lenword(str, c);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	**ft_second(char **strs, char const *str, char c, int count)
{
	int	i;
	int	len;

	i = 0;
	while (*str)
	{
		len = 0;
		while (*str && *str == c)
			str++;
		if (*str)
		{
			strs[i] = ft_fullstr(str, c);
			if (!strs[i])
				return (ft_free(strs, i), NULL);
			i++;
		}
		len = ft_lenword(str, c);
		while (*str && len)
		{
			str++;
			len--;
		}
	}
	return (strs[count] = 0, strs);
}

char	**ft_split_v2(char const *str, char c)
{
	char	**strs;
	int		count;

	if (!str)
		return (NULL);
	if (!str[0])
		return (NULL);
	count = ft_count(str, c);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	strs = ft_second(strs, str, c, count);
	return (strs);
}
