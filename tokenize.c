/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:06:41 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/05 10:23:39 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(void)
{
	printf("exit\n");
	exit(g_global.status);
}

char	*copy_word(char *str, int *n)
{
	char	quote;
	int		i;
	int		len;
	int		y;

	y = *n;
	i = *n;
	len = 0;
	while (str[i] && str[i] != SPACE && str[i] != TAB)
	{
		if (is_quote(str[i]))
		{
			len++;
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				len++;
				i++;
			}
		}
		i++;
		len++;
	}
	*n += len;
	return (ft_substr(str, y, len));
}

char	**split_string(char *s, char c)
{
	char	**word;
	int		i;
	int		j;

	word = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != SPACE && s[i] != TAB)
		{
			word[j] = copy_word(s, &i);
			if (!word[j])
				return (ft_free_str(word), NULL);
			j++;
		}
		else
			i++;
	}
	if (!j)
		return (ft_free_str(word), NULL);
	word[j] = NULL;
	return (word);
}
