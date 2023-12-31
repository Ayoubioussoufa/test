/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:19:31 by sben-ela          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_redirect(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if ((line[i] == '>' && line[i + 1] == '>')
			|| (line[i] == '<' && line[i + 1] == '<'))
		{
			count++;
			i++;
		}
		else if (line[i] == '>' || line[i] == '<')
			count++;
		i++;
	}
	return (count);
}

int	handledel(char *line, int i, char c)
{
	line[i++] = ' ';
	line[i++] = c;
	line[i++] = c;
	line[i++] = ' ';
	return (i);
}

int	handleredir(char *line, int i, char c)
{
	line[i++] = ' ';
	line[i++] = c;
	line[i++] = ' ';
	return (i);
}

char	*parse_read(char *read, char *line, int i, int j)
{
	while (read[j])
	{
		if (read[j] == '<' && read[j + 1] == '<')
		{
			i = handledel(line, i, '<');
			j += 2;
		}
		else if (read[j] == '>' && read[j + 1] == '>')
		{
			i = handledel(line, i, '>');
			j += 2;
		}
		else if (read[j] == '<' || read[j] == '>')
		{
			i = handleredir(line, i, read[j]);
			j++;
		}
		line[i] = read[j];
		i++;
		j++;
	}
	line[i] = '\0';
	return (line);
}
