/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:49:26 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/06 15:48:27 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_loop(char **env, char **res, char *cmd, int j)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], cmd, j) != 0)
			res[k++] = ft_strdup(env[i]);
		i++;
	}
	res[k] = NULL;
}

void	ft_unset_export(t_pip *p, char *cmd, int i, int j)
{
	char	**res;

	if (!p->export)
		return ;
	while (cmd[j] && cmd[j] != '=')
		j++;
	while (p->export[i])
		i++;
	if (i == 1)
	{
		res = NULL;
		free_double(p->export);
		p->export = res;
		g_global.status = 0;
		return ;
	}
	res = malloc(sizeof (char *) * i);
	if (!res)
		return ;
	unset_loop(p->export, res, cmd, j);
	free_double(p->export);
	p->export = res;
	g_global.status = 0;
}

void	ft_unset_help(t_pip *p, char *cmd, int i, int j)
{
	char	**res;

	if (if_valid_name_export(cmd))
	{
		if (!p->envp)
			return ;
		if (!if_exist(p, cmd))
		{
			g_global.status = 0;
			return ;
		}
		while (cmd[j] && cmd[j] != '=')
			j++;
		while (p->envp[i])
			i++;
		res = malloc(sizeof (char *) * i);
		if (!res)
			return ;
		unset_loop(p->envp, res, cmd, j);
		free_double(p->envp);
		p->envp = res;
		g_global.status = 0;
	}
	else
		ft_error("not a valid identifier", 1, cmd, "unset");
}

void	ft_unset(t_pip *p, t_cmd *cmds)
{
	int	i;

	i = 1;
	g_global.status = 0;
	if (cmds->args[1])
	{
		while (cmds->args[i])
		{
			if (if_export(p, cmds->args[i]))
				ft_unset_export(p, cmds->args[i], 0, 0);
			ft_unset_help(p, cmds->args[i], 0, 0);
			i++;
		}
	}
}
