/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_nocmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:21:58 by aybiouss          #+#    #+#             */
/*   Updated: 2023/03/17 19:12:17 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_inp(char *infile, int *in)
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
	}
	else
	{
		*in = -1;
		write(2, "Minishell:", 11);
		ft_perror(infile, " : No such file or directory");
	}
}

void	redir_outp(t_redire *redir)
{
	int	fd;

	fd = 0;
	if (redir->type == OUTFILE)
		fd = open(redir->outfile, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->outfile, O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		error("open", errno);
	free(redir->outfile);
}

void	redir(t_shell *shell, int in)
{
	t_redire	*tmp;

	if (!shell->redir)
		return ;
	while (shell->redir)
	{
		if (shell->redir->type == INFILE)
		{
			redir_inp(shell->redir->infile, &in);
			free(shell->redir->infile);
		}
		else if (shell->redir->type == OUTFILE || shell->redir->type == APPEND)
			redir_outp(shell->redir);
		else if (shell->redir->type == DELIMITER)
		{
			close(in);
			in = open("/tmp/minishell", O_RDWR, 0644);
			free(shell->redir->delimiter);
		}
		tmp = shell->redir;
		shell->redir = shell->redir->next;
		free(tmp);
	}
}
