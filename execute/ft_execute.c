/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:28:01 by aybiouss          #+#    #+#             */
/*   Updated: 2023/11/06 15:41:18 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
			if (WIFEXITED(g_status))
				g_status = WEXITSTATUS(g_status);
			else if (WIFSIGNALED(g_status))
				g_status = WTERMSIG(g_status);
*/

void	ft_execute(t_shell *shell, t_env *env)
{
	pid_t	pid;

	// signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, sigint_handler);
	if (if_directory(shell->cmds[0]))
		return ;
	if (check_builtins(shell->cmds[0]) == 1)
		ft_which_cmd(shell->cmds, env, 1, shell);
	else
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			exec_redirp(shell);
			check_fd(shell->cmd);
			execute_cmd(shell, env->env);
		}
		else
			(parent_two(shell), signal(SIGINT,
					SIG_IGN), waitpid(pid, &g_status, 0));
	}
}

void	child(t_shell *shell, t_env *env, int fd[2])
{
	// signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, sigint_handler);
	close(fd[0]);
	exec_redirp(shell);
	dup_close(&shell->cmd->fd);
	if (shell->next != NULL)
		close(shell->cmd->fd.out);
	if (check_builtins(shell->cmds[0]))
		ft_which_cmd(shell->cmds, env, 0, NULL);
	else
		execute_cmd(shell, env->env);
	exit(EXIT_SUCCESS);
}

void	waitchilds(int orig_stdin, int orig_stdout)
{
	// signal(SIGINT, sigint_handler);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	else if (WIFSIGNALED(g_status))
		g_status = WTERMSIG(g_status) + 128;
	dup2(orig_stdin, STDIN_FILENO);
	close(orig_stdin);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdout);
}

void	protection_null(t_shell *shell, int fd[2])
{
	if (shell->next->cmd != NULL)
	{
		shell->cmd->fd.out = fd[1];
		shell->next->cmd->fd.in = fd[0];
	}
}

void	executings(t_shell *shell, t_env *env, int in, int out)
{
	int		fd[2];
	pid_t	pid;

	if (shell && shell->type == 3)
	{
		while (shell && shell->next)
		{
			if (pipe(fd) == -1)
				error("pipe", errno);
			protection_null(shell, fd);
			pid = fork();
			if (pid == -1)
				error("fork", errno);
			if (pid == 0)
				child(shell, env, fd);
			else
				parent(shell, fd);
				shell = shell->next;
				g_status = 999;
		}
		if (shell && shell->cmd != NULL)
			ft_execute(shell, env);
		waitchilds(in, out);
	}
}

//cat /dev/random | head -n1

// void	executings(t_shell *shell, t_env *env, int in, int out)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	if (shell && shell->type == 3)
// 	{
// 		while (shell && shell->next)
// 		{
// 			if (pipe(fd) == -1)
// 				error("pipe", errno);
// 			shell->cmd->fd.out = fd[1];
// 			shell->next->cmd->fd.in = fd[0];
// 			pid = fork();
// 			if (pid == -1)
// 				error("fork", errno);
// 			if (pid == 0)
// 			{
// 				close(fd[0]);
// 				child(shell, env, fd);
// 			}
// 			else
// 			{
// 				close(fd[1]);
// 				parent(shell, fd);
// 				shell = shell->next;
// 				g_status = 999;
// 			}
// 		}
// 		if (shell)
// 			ft_execute(shell, env);
// 		waitchilds(in, out);
// 	}
// }