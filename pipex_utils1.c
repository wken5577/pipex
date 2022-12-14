/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:09:42 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/08/04 13:01:56 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "pipex.h"
#include <stdio.h>

void	open_infile(char *infile, t_data *arg_data, int bonus_flag)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		perror("zsh");
	}
	recursive_pipe(fd, arg_data, 2 + bonus_flag, bonus_flag);
}

void	dup2_read(int fd_read, t_data *arg_data)
{
	int	status;

	if (fd_read == -1)
		return ;
	status = dup2(fd_read, STD_IN);
	if (status < 0)
	{
		free(arg_data);
		print_error();
	}
	close(fd_read);
}

void	conn_pipe(int fd_pipe[], t_data *arg_data)
{
	int	status;

	status = pipe(fd_pipe);
	if (status < 0)
	{
		free(arg_data);
		print_error();
	}
}

void	dup2_write(int fd_pipe[], t_data *arg_data)
{
	int	status;

	conn_pipe(fd_pipe, arg_data);
	status = dup2(fd_pipe[WRITE], STD_OUT);
	if (status < 0)
	{
		free(arg_data);
		print_error();
	}
	close(fd_pipe[WRITE]);
}

pid_t	exe_fork(t_data *arg_data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		free(arg_data);
		print_error();
	}
	return (pid);
}
