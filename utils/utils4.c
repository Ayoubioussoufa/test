/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:11:59 by sben-ela          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count(const char *str, char c)
{
	int		i;
	int		count;
	char	n;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			count++;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			n = str[i++];
			while (str[i] && str[i] != n)
				i++;
		}
		if (str[i])
			i++;
	}
	return (count);
}

t_shell	*ft_lstnew(char *content, int index, char **env, int pipe)
{
	t_shell	*new;
	char	**split;

	new = malloc(sizeof(t_shell));
	if (!new)
		exit(1);
	new->cmd = 0;
	new->redir = 0;
	split = ft_split_space(content, ' ');
	if (!split)
		return (0);
	ft_getnew(split, env, 0, &new);
	if (!new->cmd)
		new->type = 0;
	else
		new->type = 3;
	new->pipe = pipe;
	new->index = index;
	new->next = 0;
	new->cmds = full_cmds(new->cmd);
	free(split);
	return (new);
}
