/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:37:08 by ereali            #+#    #+#             */
/*   Updated: 2021/10/15 21:49:55 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!(s))
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

static size_t	ft_count_word(char const *s, char c)
{
	size_t	i;
	size_t	word;

	i = 0;
	word = 0;
	if (ft_strlen(s) == 0)
		return (0);
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			word++;
			while (s[i] == c)
				i++;
			if (!(s[i]))
				i--;
		}
		i++;
	}
	if (s[i - 1] == c)
		return (word);
	return (word + 1);
}

static char	*ft_get_next_word(char const *s, char c, size_t *j)
{
	char	*word;
	size_t	jcopy;
	size_t	i;

	i = 0;
	while (s[*j] == c)
		(*j)++;
	jcopy = *j;
	while (s[jcopy] && s[jcopy] != c)
		jcopy++;
	word = (char *)malloc(sizeof(char) * (jcopy - *j + 1));
	if (!(word))
		return (NULL);
	while (*j < jcopy)
	{
		word[i] = s[*j];
		i++;
		(*j)++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_freetablib(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;
	size_t	word;

	i = 0;
	j = 0;
	if (!(s))
		return (NULL);
	word = ft_count_word(s, c);
	if (word <= 1)
		return(NULL);
	tab = (char **)malloc(sizeof(char *) * (word + 1));
	if (!(tab))
		return (NULL);
	while (i < word)
	{
		tab[i] = ft_get_next_word(s, c, &j);
		if (!(tab[i]))
		{
			ft_freetablib(tab, i);
			return (NULL);
		}
		i++;
	}
	tab[word] = NULL;
	return (tab);
}
