/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:43:32 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/06 15:08:40 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_proc(int sig)
{
	if (sig == SIGINFO)
		return ;
}

static void	wait_child(t_pip *p)
{
	close_fd(p);
	waitpid(-1, &g_global.status, 0);
	if (WIFEXITED(g_global.status))
		g_global.status = WEXITSTATUS(g_global.status);
	free(p->cmd);
}

static void	exec_no_builtins(t_pip *p, t_cmd *cmds)
{
	pid_t	child;

	g_global.status = check_cmd(p, cmds->cmd, p->envp, cmds);
	if (g_global.status != 0)
	{
		close_fd(p);
		return ;
	}
	if (ft_strcmp(p->cmd, "./minishell") == 0)
		signal(SIGINT, child_proc);
	child = fork();
	if (child == -1)
	{
		ft_error("fork failed", 1, NULL, NULL);
		return ;
	}
	if (child == 0)
	{
		if (g_global.status != 0)
			exit(g_global.status);
		ft_exec(p, p->envp, cmds);
	}
	wait_child(p);
}

void	dup_fd(t_pip *p, t_cmd *cmds)
{
	if (cmds->files[0])
	{
		if (p->sign_in == -1)
		{
			p->std_in = dup(0);
			dup2(p->fd_in, 0);
			close(p->fd_in);
		}
		if (p->sign_out == -1)
		{
			p->std_out = dup(1);
			dup2(p->fd_out, 1);
			close(p->fd_out);
		}
	}
}

void	single_cmd(t_pip *p, t_cmd *cmds)
{
	p->sign_in = 0;
	p->sign_out = 0;
	p->if_here_doc = 0;
	open_files(p, cmds);
	if (p->sign_in == 1 || p->sign_out == 1)
		return ;
	dup_fd(p, cmds);
	if (!cmds->cmd)
	{
		if (p->if_here_doc)
			unlink(".tmp_file");
		close_fd(p);
		return ;
	}
	if (if_builtins(cmds->cmd))
	{
		exec_builtins(p, cmds->cmd, cmds);
		close_fd(p);
	}
	else
		exec_no_builtins(p, cmds);
	if (p->if_here_doc)
		unlink(".tmp_file");
}
