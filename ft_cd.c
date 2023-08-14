/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:48:19 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/09 17:31:35 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home(t_pip *p)
{
	char	*pwd;

	if (!get_env("HOME", p))
		return (ft_error("HOME not set", 1, NULL, "cd"));
	pwd = getcwd(NULL, 0);
	set_env("OLDPWD=", pwd, p);
	free(pwd);
	pwd = ft_strdup(get_env("HOME", p));
	if (pwd == NULL)
		return (ft_error("HOME not set", 1, NULL, "cd"));
	chdir(pwd);
	set_env("PWD=", pwd, p);
	free(pwd);
	return (0);
}

int	cd_oldpwd(t_pip *p)
{
	char	*pwd;
	char	*pwd1;

	pwd = ft_strdup(get_env("OLDPWD", p));
	if (pwd == NULL)
		return (ft_error("OLDPWD not set", 1, NULL, "cd"));
	if (access(pwd, F_OK) != 0)
		return (ft_error("no such file or directory", 1,
				pwd, "cd"));
	pwd1 = getcwd(NULL, 0);
	set_env("OLDPWD=", pwd1, p);
	free(pwd1);
	chdir(pwd);
	if (if_exist(p, "PWD"))
		set_env("PWD=", pwd, p);
	get_pwd(p);
	ft_pwd(p);
	free(pwd);
	return (0);
}

int	change_env(t_pip *p, t_cmd *cmds)
{
	char	*pwd;
	char	*pwd1;

	if (access(cmds->args[1], F_OK))
		return (ft_error("no such file or directory", 1,
				cmds->args[1], "cd"));
	if (access(cmds->args[1], X_OK) != 0)
		return (ft_error("Permission denied", 1, cmds->args[1], "cd"));
	pwd1 = ft_strdup(get_env("PWD", p));
	set_env("OLDPWD=", pwd1, p);
	chdir(cmds->args[1]);
	pwd = getcwd(NULL, 0);
	if (pwd)
		g_global.cd_f = 0;
	if (if_exist(p, "PWD"))
		set_env("PWD=", pwd, p);
	free(pwd1);
	free(pwd);
	return (0);
}

int	cd_error(t_pip *p, t_cmd *cmds)
{
	char	*pwd;
	char	*pwd1;

	chdir(cmds->args[1]);
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		pwd1 = ft_strdup(get_env("PWD", p));
		set_env("OLDPWD=", pwd1, p);
		if (if_exist(p, "PWD"))
			set_env("PWD=", pwd, p);
		free(pwd1);
		free(pwd);
		return (0);
	}
	write (2, "cd: error retrieving current directory: getcwd: cannot", 55);
	write(2, " access parent directories: No such file or directory\n", 55);
	p->pwd = ft_strjoin_get(p->pwd, "/..");
	if (if_exist(p, "PWD"))
		set_env("PWD=", p->pwd, p);
	free(pwd);
	return (1);
}

int	ft_cd(t_pip *p, t_cmd *cmds)
{
	char	*pwd;

	if (!cmds->args[1])
		return (cd_home(p));
	else if (ft_strcmp(cmds->args[1], "-") == 0)
		return (cd_oldpwd(p));
	else if (ft_strcmp(cmds->args[1], "~") == 0)
		return (cd_home(p));
	else
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL && access(cmds->args[1], X_OK) == 0)
		{
			if ((ft_strcmp(cmds->args[1], "..") == 0))
				g_global.cd_f++;
			if (g_global.cd_f >= 2)
				cd_error(p, cmds);
			else
				return (ft_error("no such file or directory", 1,
						cmds->args[1], "cd"));
		}
		else
			return (free(pwd), change_env(p, cmds));
	}
	return (0);
}
