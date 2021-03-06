/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:19:09 by ereali            #+#    #+#             */
/*   Updated: 2021/10/18 03:17:54 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **argv, char **envp)
{
	char	*pathname;
	int		i;

	i = 0;
	while (envp[i] && (!(ft_strnstr(envp[i], "PATH", 4))))
		i++;
	envp = ft_split(envp[i] + 5, ':');
	i = 0;
	while (envp[i])
	{
		pathname = strjoinslash(envp[i], argv[0]);
		if (access(pathname, X_OK) == 0)
		{
			freetab(envp);
			return (pathname);
		}
		i++;
		free(pathname);
	}
	freetab(envp);
	return (NULL);
}

void	execute(const char *cmd, char **envp)
{
	char	**argv;
	char	*pathname;
	int		ret;
	int		ret2;

	ret2 = 0;
	argv = ft_split(cmd, ' ');
	if (argv == NULL)
		return ;
	if (access(cmd, X_OK) == -1)
		pathname = find_path(argv, envp);
	else
	{
		pathname = (char *)cmd;
		ret2 = 1;
	}
	ret = execve(pathname, argv, envp);
	freetab(argv);
	if (ret2 == 1)
		free(pathname);
	if (ret < 0)
		use_perror("execve");
}

void	first_cmd(int *pipefd, const char **argv, char **envp)
{
	int	first_pid;

	first_pid = open(argv[1], O_RDONLY);
	if (first_pid < 0)
		args_error();
	close(pipefd[0]);
	dup2(first_pid, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(first_pid);
	execute(argv[2], envp);
}

void	second_cmd(int *pipefd, const char **argv, char **envp)
{
	int	second_pid;

	second_pid = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (second_pid < 0)
		args_error();
	close(pipefd[1]);
	dup2(second_pid, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(second_pid);
	execute(argv[3], envp);
}

int	main(int argc, const char **argv, char **envp)
{
	int		pipefd[2];
	int		ret;
	pid_t	child;
	pid_t	child2;

	if (argc != 5)
		args_error();
	ret = pipe(pipefd);
	if (ret == -1)
		use_perror("pipe");
	child = fork();
	if (child < 0)
		use_perror("fork");
	if (child == 0)
		first_cmd(pipefd, argv, envp);
	child2 = fork();
	if (child2 < 0)
		use_perror("fork");
	if (child2 == 0)
		second_cmd(pipefd, argv, envp);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
