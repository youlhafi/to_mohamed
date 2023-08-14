/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:43:33 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/09 19:17:47 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*minishell(char *str)
{
	char	*dst;
	int		len;

	dst = NULL;
	len = (ft_strlen(str) - 2);
	if (!dst)
		return (NULL);
	dst = ft_substr(str, 2, len);
	return (dst);
}

int	ft_token(char *str, t_pip *p)
{
	t_cmd	*cmd_list;
	t_list	*new;
	char	**dst;
	int		i;

	i = 0;
	new = NULL;
	cmd_list = NULL;
	dst = split_string(str, SPACE);
	if (!dst)
		return (1);
	new = get_lexed_list(dst, p);
	if (!new)
		return (0);
	cmd_list = cmd(ft_lstsize(new));
	if (cmd_list)
	{
		if (parse_input(cmd_list, &new, 0, 0))
			check_pipe(p, cmd_list);
	}
	ft_free_token(new);
	ft_free_list(cmd_list);
	return (0);
}

char	**get_short_env(void)
{
	t_env	env;
	char	**ret;

	env.envp = NULL;
	env.pwd = ft_strdup("PWD=");
	env.pwd1 = getcwd(NULL, 0);
	env.pwd = ft_strjoin_get(env.pwd, env.pwd1);
	env.shlvl = ft_strdup("SHLVL=1");
	env._ = ft_strdup("_=/usr/bin/env");
	env.envp = ft_strjoinspace(env.envp, env.pwd);
	env.envp = ft_strjoinspace(env.envp, env.shlvl);
	env.envp = ft_strjoinspace(env.envp, env._);
	ret = ft_split(env.envp, ' ');
	free(env._);
	free_strings(env.pwd1, env.pwd, env.shlvl, env.envp);
	return (ret);
}

void	main_shell(t_pip p)
{
	char	*str;

	str = NULL;
	while (1)
	{
		signal(SIGINT, handle_ctrl_c);
		signal(SIGQUIT, handle_ctrl_b);
		str = readline("minishell>");
		if (str != NULL)
		{
			if (str[0])
			{
				g_global.herdoc = 0;
				if (!ft_token(str, &p))
					add_history(str);
			}
		}
		if (!str)
			ctrl_d();
		free(str);
		if (p.if_exit == 1)
			break ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_pip	p;

	(void)ac;
	(void)av;
	// rl_catch_signals = 0;
	if (!getenv("PWD"))
		p.envp = get_short_env();
	else
		p.envp = get_env1(env);
	p.pwd = malloc(sizeof(char));
	get_pwd(&p);
	p.export = NULL;
	p.if_exit = 0;
	main_shell(p);
	return (g_global.status);
}
