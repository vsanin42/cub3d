/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:36:09 by olomova           #+#    #+#             */
/*   Updated: 2024/02/09 14:47:48 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
	{
		write(fd, "\n", 1);
		return ;
	}
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
/*
#include <unistd.h>
#include <fcntl.h> 
#include <string.h> 
#include <stdio.h>  
 int main() {
    // Example string
    char *message = "This is a test message.";

    // File descriptor for standard output (usually represents the screen)
    int stdout_fd = STDOUT_FILENO;

    // File descriptor for a file (replace "output.txt" 
    // with your desired file path)
    int file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (file_fd == -1) {
        perror("open");
        return 1; // Return error if file opening fails
    }

    // Call ft_putendl_fd to print the message to standard output
    ft_putendl_fd(message, stdout_fd);

    // Call ft_putendl_fd to print the message to the file
    ft_putendl_fd(message, file_fd);

    // Close the file descriptor
    if (close(file_fd) == -1) {
        perror("close");
        return 1; // Return error if closing file fails
    }

    return 0;
}
int ft_strlen(char *s)
{
        int i;
        i = 0;
        while(s[i] != '\0')
                i++;
        return i;
}
*/
