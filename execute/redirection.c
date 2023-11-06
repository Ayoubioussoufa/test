/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:26:00 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_close(t_fd *fd)
{
	if (fd->in != STDIN_FILENO && fd->in > 0)
	{
		if (dup2(fd->in, STDIN_FILENO) == -1)
			error("dup2", errno);
		if (close(fd->in) == -1)
			error("close", errno);
	}
	if (fd->out != STDOUT_FILENO && fd->out > 1)
	{
		if (dup2(fd->out, STDOUT_FILENO) == -1)
			error("dup2", errno);
		if (close(fd->out) == -1)
			error("close", errno);
	}
}

int	exec_redir_in(char *infile, int *in)
{
	if (access(infile, R_OK) == 0)
	{
		if (*in != STDIN_FILENO && *in > 0)
			if (close(*in) == -1)
				error("close", errno);
		*in = open(infile, O_RDONLY, 0666);
		if (*in == -1)
			error("open", errno);
	}
	else if (access(infile, F_OK) == 0)
	{
		*in = -1;
		write(2, "Minishell: ", 11);
		ft_perror(infile, ": Permission denied");
		return (1);
	}
	else
	{
		*in = -1;
		write(2, "Minishell: ", 11);
		ft_perror(infile, ": No such file or directory");
		return (1);
	}
	return (0);
}

void	check_fd(t_cmd *cmd)
{
	if (cmd && cmd->fd.in != STDIN_FILENO && cmd->fd.in > 0)
	{
		if (dup2(cmd->fd.in, STDIN_FILENO) == -1)
			error("dup2", errno);
		if (close(cmd->fd.in) == -1)
			error("close", errno);
	}
	if (cmd && cmd->fd.out != STDOUT_FILENO && cmd->fd.out > 1)
	{
		if (dup2(cmd->fd.out, STDOUT_FILENO) == -1)
			error("dup2", errno);
		if (close(cmd->fd.out) == -1)
			error("close", errno);
	}
}

int	exec_redir_out(t_shell *shell, t_redire *redir)
{
	if (shell->cmd && shell->cmd->fd.out)
		close(shell->cmd->fd.out);
	if (redir->type == OUTFILE)
		shell->cmd->fd.out = open(redir->outfile, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		shell->cmd->fd.out = open(redir->outfile, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	if (shell->cmd->fd.out == -1)
		error("open", errno);
	return (0);
}

int	exec_redir(t_shell *shell)
{
	t_redire	*redir;
	int			i;
	int			j;

	i = 0;
	j = 0;
	redir = shell->redir;
	if (!redir)
		return (0);
	while (redir)
	{
		if (redir->type == INFILE)
			i = exec_redir_in(redir->infile, &shell->cmd->fd.in);
		else if (redir->type == OUTFILE || redir->type == APPEND)
			j = exec_redir_out(shell, redir);
		else if (redir->type == DELIMITER)
		{
			close(shell->cmd->fd.in);
			shell->cmd->fd.in = open("/tmp/minishell", O_RDWR, 0644);
		}
		redir = redir->next;
	}
	if (!i && !j)
		return (0);
	return (1);
}
