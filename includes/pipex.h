/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:26:04 by ereali            #+#    #+#             */
/*   Updated: 2021/10/18 03:25:15 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	freetab(char **tab);
void	args_error(void);
void	use_perror(char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*strjoinslash(char *s1, char const *s2);
char	**ft_split(char const *s, char c);

#endif
