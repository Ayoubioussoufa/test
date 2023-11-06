/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:19:14 by sben-ela          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_normalword(char *word, t_content *content, int type, char **env)
{
	content->quotes = WITHOUT_QUOTE;
	content->content = expand(word, env, type, ft_strdup(""));
	content->content = handle_param(content->content, '\'');
	content->content = handle_param(content->content, '\"');
}

t_content	*parseword(char *word, char **env, int type)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	if (!content)
		exit(1);
	if (check_edges(word) == 1)
	{
		content->quotes = SINGLE_QUOTE;
		content->content = expand(word, env, type, ft_strdup(""));
		content->content = handle_param(content->content, '\"');
	}
	else if (check_edges(word) == 2)
	{
		content->quotes = DOUBLE_QUOTE;
		content->content = expand(word, env, type, ft_strdup(""));
		content->content = handle_param(content->content, '\'');
	}
	else
		parse_normalword(word, content, type, env);
	content->type = type;
	if (type != DELIMITER)
		free(word);
	return (content);
}

void	ft_getnew(char **split, char **env, int i, t_shell **new)
{
	t_content	*content;

	while (split[i])
	{
		content = parseword(split[i], env, 0);
		split[i] = content->content;
		if (!ft_strcmp(split[i], ">"))
			(free(split[i]), redi_add_back(&(*new)->redir,
					new_redir(parseword(split[++i], env, OUTFILE))));
		else if (!ft_strcmp(split[i], "<"))
			(free(split[i]), redi_add_back(&(*new)->redir,
					new_redir(parseword(split[++i], env, INFILE))));
		else if (!ft_strcmp(split[i], "<<"))
			(free(split[i]), redi_add_back(&(*new)->redir,
					new_redir(parseword(split[++i], env, DELIMITER))));
		else if (!ft_strcmp(split[i], ">>"))
			(free(split[i]), redi_add_back(&(*new)->redir,
					new_redir(parseword(split[++i], env, APPEND))));
		else
			cmd_add_back(&(*new)->cmd, new_cmd(content->content));
		free(content);
		i++;
	}
}

t_shell	*parse_line(char *line, char **env, int i)
{
	char	**args;
	t_shell	*shell;
	t_shell	*new;
	int		pipe;

	shell = 0;
	args = ft_split_v2(line, '|');
	if (!args)
		exit (1);
	while (args[++i])
		args[i] = ft_strtrimfree(args[i], " ");
	i = -1;
	while (args[++i])
	{
		pipe = 0;
		if (args[i + 1])
			pipe = PIPE;
		new = ft_lstnew(args[i], i, env, pipe);
		ft_lstadd_back(&shell, new);
	}
	freedouble(args);
	return (shell);
}
