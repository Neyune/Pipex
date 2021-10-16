/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereali <ereali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:19:09 by ereali            #+#    #+#             */
/*   Updated: 2021/10/15 21:53:42 by ereali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	args_error(void)
{
	ft_putstr_fd("Wrong args", 2);
	exit(EXIT_FAILURE);
}

void execute(const char *argv, char **envp)
{
	char **flags;
	(void)argv;
	(void)envp;
	flags = ft_split(argv, ' ');
	if (flags == NULL) // Alors utiliser argv
	// execve();
}

void	use_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	first_cmd(int *pipefd, const char **argv, char **envp)
{
	int first_pid;

	first_pid = open(argv[1], O_RDONLY);
	if (first_pid < 0)
		args_error();
	close(pipefd[0]);
	dup2(first_pid, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	execute(argv[1], envp);
}

void	second_cmd(int *pipefd,const char **argv, char **envp)
{
	int second_pid;

	second_pid = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (second_pid < 0)
		args_error();
	close(pipefd[0]);
	dup2(second_pid, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	execute(argv[3], envp);
}

int	main(int argc,const char **argv, char **envp)
{
	int pipefd[2];
	int ret;
	int status;
	int child;
	int child2;

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
	waitpid(child, &status, 0);
	close(pipefd[1]);
	waitpid(child2, &status, 0);
	close(pipefd[0]);
	return (0);
}
