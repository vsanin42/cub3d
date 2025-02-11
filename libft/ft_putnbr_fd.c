/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:21:16 by olomova           #+#    #+#             */
/*   Updated: 2024/02/17 15:49:44 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	poww(int power)
{
	int	ten;

	ten = 1;
	while (power)
	{
		ten = ten * 10;
		power--;
	}
	return (ten);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	int		i;
	char	c;

	i = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(fd, "-2147483648", 11);
			return ;
		}
		n = -n;
		write(fd, "-", 1);
	}
	len = int_len(n);
	while (i < len)
	{
		c = n / poww(len - i - 1) + '0';
		write(fd, &c, 1);
		n = n % poww(len - i - 1);
		i++;
	}
}
/*#include <unistd.h> // for STDOUT_FILENO
#include <fcntl.h>  // for open function
#include <string.h> // for strlen function
#include <stdio.h>  // for perror function
int main() {
    // Example string

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
    ft_putnbr_fd(-42, stdout_fd);

    // Call ft_putendl_fd to print the message to the file
    ft_putnbr_fd(-42, file_fd);

    // Close the file descriptor
    if (close(file_fd) == -1) {
        perror("close");
        return 1; // Return error if closing file fails
    }

    return 0;
}*/
