/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:32:05 by aybiouss          #+#    #+#             */
/*   Updated: 2023/11/06 15:41:04 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freeredir(t_redire *tmp)
{
	t_redire	*t;

	while (tmp)
	{
		if (tmp->type == INFILE)
			free(tmp->infile);
		else if (tmp->type == OUTFILE)
			free(tmp->outfile);
		else if (tmp->type == DELIMITER)
			free(tmp->delimiter);
		else if (tmp->type == APPEND)
			free(tmp->outfile);
		t = tmp;
		tmp = tmp->next;
		free(t);
	}
}

void	free_array(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

void	freedata(t_shell *shell, char **line, char **read)
{
	t_cmd	*cmd;
	t_shell	*tmp;
	t_cmd	*save;

	free(*line);
	free(*read);
	while (shell != NULL)
	{
		cmd = shell->cmd;
		while (cmd != NULL)
		{
			save = cmd;
			cmd = cmd->next;
			free(save);
		}
		freeredir(shell->redir);
		free_array(shell->cmds);
		tmp = shell;
		shell = shell->next;
		free(tmp);
	}
}

char *custom_readline(const char *prompt) {
    char *line = NULL;
    size_t bufsize = 0;
    printf("%s", prompt);
    
    ssize_t n = getline(&line, &bufsize, stdin);

    if (n == -1) {
        free(line);
        return NULL; // End of input or error occurred.
    }

    if (line[n - 1] == '\n') {
        line[n - 1] = '\0'; // Remove the newline character.
    }

    return line;
}

void	mini_shell(t_env *ev, t_shell *shell, char *read, char *line)
{
	while (1)
	{
		read = custom_readline("\033[1;34m➜  Minishell ✗ \033[0m");
		if (!read)
			(printf("exit\n"), exit(g_status));
		// add_history(read);
		if (read[0] && !parse_syntax(read))
		{
			line = malloc(ft_strlen(read) + 1 + (count_redirect(read) * 2));
			if (!line)
				exit(1);
			line = parse_read(read, line, 0, 0);
			shell = parse_line(line, ev->env, -1);
			execute(shell, ev);
			freedata(shell, &line, &read);
		}
		else if (read[0])
			(free(read), printf("syntax error\n"));
		else
			free(read);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*ev;

	(void) av;
	g_status = 0;
	ev = create_env(env);
	ev->env = convert_array(ev);
	if (ac != 1)
	{
		printf("Invalid number of argument\n");
		return (0);
	}
	// signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, SIG_IGN);
	mini_shell(ev, 0, 0, 0);
	return (g_status);
}
