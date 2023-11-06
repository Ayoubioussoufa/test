/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:10:51 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_two(t_shell *shell)
{
	if (shell->cmd->fd.in != STDIN_FILENO)
		close(shell->cmd->fd.in);
	if (shell->cmd->fd.out != STDOUT_FILENO)
		close(shell->cmd->fd.out);
}

void	exec_redir_outp(t_shell *shell, t_redire *redir)
{
	close(shell->cmd->fd.out);
	if (redir->type == OUTFILE)
		shell->cmd->fd.out = open(redir->outfile, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		shell->cmd->fd.out = open(redir->outfile, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	if (shell->cmd->fd.out == -1)
		error("open", errno);
}

void	exec_redir_inp(char *infile, int *in)
{
	if (access(infile, R_OK) == 0)
	{
		if (*in != STDIN_FILENO && *in > 0)
		{
			if (close(*in) == -1)
				error("close", errno);
		}
		*in = open(infile, O_RDONLY, 0666);
		if (*in == -1)
			error("open", errno);
	}
	else if (access(infile, F_OK) == 0)
	{
		*in = -1;
		write(2, "Minishell:", 11);
		ft_perror(infile, " : Permission denied");
		exit(1);
	}
	else
	{
		*in = -1;
		write(2, "Minishell:", 11);
		ft_perror(infile, " : No such file or directory");
		exit(1);
	}
}

void	exec_redirp(t_shell *shell)
{
	t_redire	*redir;

	redir = shell->redir;
	if (!redir)
		return ;
	while (redir)
	{
		if (redir->type == INFILE)
			exec_redir_inp(redir->infile, &shell->cmd->fd.in);
		else if (redir->type == OUTFILE || redir->type == APPEND)
			exec_redir_outp(shell, redir);
		else if (redir->type == DELIMITER)
		{
			close(shell->cmd->fd.in);
			shell->cmd->fd.in = open("/tmp/minishell", O_RDWR, 0644);
		}
		redir = redir->next;
	}
}
