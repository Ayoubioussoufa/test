/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:29:39 by aybiouss          #+#    #+#             */
/*   Updated: 2023/11/06 15:43:10 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_hand(int sig)
{
	(void)sig;
	exit(1);
}

void	here_doc(t_redire *redir, char **env)
{
	int		fd;
	char	*str;

	// signal(SIGINT, sigint_hand);
	fd = open("/tmp/minishell", O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
	{
		perror("minishell");
		return ;
	}
	str = custom_readline("> ");
	while (str
		&& ft_strcmp(str, redir->delimiter))
	{
		if (!redir->quotes)
			str = expand(str, env, 0, ft_strdup(""));
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = custom_readline("> ");
	}
	free(str);
	close(fd);
	exit(0);
}

int	waiting(pid_t pid)
{
	// signal(SIGINT, SIG_IGN);
	waitpid(pid, &g_status, 0);
	if (g_status)
		return (EXIT_FAILURE);
	// signal(SIGINT, sigint_handler);
	return (EXIT_SUCCESS);
}

int	opening(t_shell *shell, t_env *env)
{
	t_redire	*x;
	t_shell		*here;
	pid_t		pid;

	here = shell;
	while (here)
	{
		x = here->redir;
		while (x)
		{
			if (x->type == DELIMITER)
			{
				pid = fork();
				if (pid == -1)
					error("fork", errno);
				if (!pid)
					here_doc(x, env->env);
				else
					return (waiting(pid));
			}
			x = x->next;
		}
		here = here->next;
	}
	return (EXIT_SUCCESS);
}

int	open_heredocs(t_shell *shell, t_env *env)
{
	t_redire	*tmp;
	int			i;

	i = 0;
	tmp = shell->redir;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->type == DELIMITER)
			i++;
		tmp = tmp->next;
	}
	if (i > 16)
		error("maximum here-document count exceeded", 2);
	return (opening(shell, env));
}
