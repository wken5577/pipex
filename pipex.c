/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:09:40 by hyunkyle          #+#    #+#             */
/*   Updated: 2022/08/04 13:02:22 by hyunkyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void	execute1(char **comm)
{
	if (execve(comm[0], comm, 0) == -1)
	{
		release(comm);
		print_error();
	}
}

void	child_logic(t_data *arg_data, int n, int finish_flag, int fd_pipe[2])
{
	char	**comm;

	if (!finish_flag)
		close(fd_pipe[READ]);
	comm = ft_split(arg_data->argv[n], ' ');
	if (ft_strchr(comm[0], '/') > 0)
	{
		if (access(comm[0], F_OK | X_OK) == -1)
		{
			print_error2(comm, 0, arg_data);
		}
		free(arg_data);
		execute1(comm);
	}
	else
		make_fullpath_execute(comm, arg_data);
}

void	recursive_pipe(int fd_read, t_data *arg_data, int n, int bonus_flag)
{
	pid_t	pid;
	int		fd_pipe[2];
	int		finish_flag;

	finish_flag = 0;
	if (n + 2 == arg_data->argc)
		finish_flag = 1;
	dup2_read(fd_read, arg_data);
	if (finish_flag)
		conn_out_file(arg_data, n, bonus_flag);
	else
		dup2_write(fd_pipe, arg_data);
	pid = exe_fork(arg_data);
	if (pid > 0)
	{
		if (!finish_flag)
			recursive_pipe(fd_pipe[READ], arg_data, n + 1, bonus_flag);
		if (wait(NULL) < 0)
		{
			free(arg_data);
			print_error();
		}
	}
	else if (fd_read != -1 && pid == 0)
		child_logic(arg_data, n, finish_flag, fd_pipe);
}

void	here_doc_start(char *finish_flag, t_data *arg_data)
{
	char	*buffer;
	int		fd;
	int		flag_size;
	int		buffer_size;

	flag_size = ft_strlen(finish_flag);
	fd = open ("tmp.txt", O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		free(arg_data);
		print_error();
	}
	while (1)
	{
		buffer = get_next_line(STD_IN);
		buffer_size = ft_strlen(buffer);
		if (ft_strncmp(finish_flag, buffer, flag_size) == 0
			&& buffer_size - 1 == flag_size)
			break ;
		write(fd, buffer, buffer_size);
	}
	close(fd);
	open_infile("tmp.txt", arg_data, 1);
	free(arg_data);
}

int	main(int argc, char **argv, char **envp)
{
	int		read_fd;
	t_data	*arg_data;

	if (argc < 5)
	{
		ft_putstr_fd("invalid arguments", 2);
		exit(1);
	}
	arg_data = init_data(argc, argv, envp);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		here_doc_start(argv[2], arg_data);
		if (unlink("tmp.txt") == -1)
			print_error();
	}
	else
	{
		open_infile(argv[1], arg_data, 0);
		free(arg_data);
	}
	return (0);
}
