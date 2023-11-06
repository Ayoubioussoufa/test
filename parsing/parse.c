/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:01:50 by sben-ela          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_pipes(char *line)
{
	char	*str;

	if (count_char(line, '\"') + count_char(line, '\'') == ft_strlen(line))
		return (1);
	str = ft_strtrim(line, " ");
	if (!str)
		return (0);
	if (str[0] && (str[0] == '|' || str[ft_strlen(str) - 1] == '|'))
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

int	parse_redir(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '<')
		{
			i++;
			if (!line[i] || (line[i - 1] == ' ' && line[i] == '<')
				|| line[i] == '>' || (line[i] == '<' && !line[i + 1])
				|| (line[i] == '<' && line[i + 1] == '<'))
				return (1);
		}
		if (line[i] == '>')
		{
			i++;
			if ((line[i - 1] == ' ' && line[i] == '>') || line[i] == '<'
				|| !line[i] || (line[i] == '>' && !line[i + 1])
				|| (line[i] == '>' && line[i + 1] == '>'))
				return (1);
		}
		i++;
	}
	return (0);
}

int	parse(char **split_line, char *line, char *string, int i)
{
	while (split_line[i])
		string = ft_strjoinfree(string, split_line[i++]);
	if (parse_redir(string, 0))
		return (free(string), freedouble(split_line), 1);
	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			i++;
			while (line[i] && line[i] == ' ')
				i++;
			if ((line[i] == '>' || line[i] == '<') && line[i - 1] == ' ')
				return (freedouble(split_line), 1);
			i++;
		}
		if (line[i])
			i++;
	}
	freedouble(split_line);
	free(string);
	return (0);
}

int	parse_pipe(char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			c = line[i];
			while (line[i] && line[i] != c)
				i++;
		}
		if (line[i] == '|')
		{
			while (line[++i] == ' ')
				;
			if (!line[i] || line[i] == '|')
			{
				free(line);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	parse_syntax(char *line)
{
	char	*string;
	char	*trimmed_line;

	string = ft_strdup("");
	if (handle_pipes(line) || count_single_quotes(line)
		|| count_double_quotes(line))
		return (free(string), 1);
	trimmed_line = ft_strdup(line);
	trimmed_line = ft_strtrimfree(trimmed_line, "\"");
	trimmed_line = ft_strtrimfree(trimmed_line, "\'");
	if (parse(ft_split(trimmed_line, ' '), trimmed_line, string, 0))
		return (free(trimmed_line), 1);
	if (parse_pipe(trimmed_line))
		return (1);
	free(trimmed_line);
	return (0);
}
