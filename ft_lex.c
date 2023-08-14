/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:14:27 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/03 09:07:55 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_case(char *s, char **res, int *i)
{
	int	rest;

	rest = 0;
	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
	{
		res[*i] = ft_substr(s, 0, 2);
		(*i)++;
		rest += 2;
	}
	else if (s[0] == '|' || s[0] == '<' || s[0] == '>')
	{
		res[*i] = ft_substr(s, 0, 1);
		(*i)++;
		rest += 1;
	}
	else
	{
		res[*i] = ft_substr(s, 0, 1);
		(*i)++;
		rest += 1;
	}
	return (rest);
}

int	skip_quote(char *s, int len)
{
	char	quote;

	quote = s[len++];
	while (s[len] && s[len] != quote)
		len++;
	return (len);
}

static char	**split_args(char *s, int i)
{
	int		len;
	char	**res;

	res = ft_calloc(ft_strlen(s) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	while (*s)
	{
		len = 0;
		while (s[len] && s[len] != '<' && s[len] != '>' && s[len] != '|')
		{
			if (is_quote(s[len]))
				len = skip_quote(s, len);
			len++;
		}
		if (len > 0)
		{
			res[i++] = ft_substr(s, 0, len);
			s += len;
		}
		else
			s += special_case(s, res, &i);
	}
	return (res);
}

int	add_lex(char *str, t_list **lst)
{
	char	**arg;
	int		i;

	arg = NULL;
	arg = split_args(str, 0);
	if (!arg)
		return (1);
	i = 0;
	while (arg[i])
		ft_add_back_token(lst, ft_new_token(arg[i++]));
	ft_free_str(arg);
	return (0);
}

t_list	*ft_lex(char **dst)
{
	t_list	*lst;
	int		i;

	lst = NULL;
	i = 0;
	while (dst[i])
	{
		if (ft_strchr(dst[i], '|') || ft_strchr(dst[i], '>')
			|| ft_strchr(dst[i], '<'))
		{
			if (add_lex(dst[i], &lst))
				return (NULL);
		}
		else
			ft_add_back_token(&lst, ft_new_token(dst[i]));
		i++;
	}
	ft_free_str(dst);
	return (lst);
}
