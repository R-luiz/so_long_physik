/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:37:38 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 15:37:46 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

void	ft_putchar(char c)
{
	ssize_t	bytes_written;

	bytes_written = write(1, &c, 1);
	if (bytes_written == -1)
		perror("write failed");
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return ;
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i - 1);
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr(int nb)
{
	ssize_t	bytes_written;

	bytes_written = 0;
	if (nb == -2147483648)
	{
		bytes_written = write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		bytes_written = write(1, "-", 1);
		nb = -nb;
	}
	if (bytes_written == -1)
		perror("write failed");
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
	return ;
}

void	ft_putnbr_base(unsigned int nb, char *base, unsigned int size)
{
	if (nb >= size)
		ft_putnbr_base(nb / size, base, size);
	ft_putchar(base[nb % size]);
	return ;
}

void	ft_pourcent(const char *src, va_list list, int i)
{
	if (src[i] == 's')
		ft_putstr(va_arg(list, char *));
	else if (src[i] == 'd')
		ft_putnbr(va_arg(list, int));
	return ;
}

int	ft_printf(const char *src, ...)
{
	int		i;
	va_list	list;

	i = -1;
	va_start(list, src);
	while (src[++i])
	{
		if (src[i] == '%')
			ft_pourcent(src, list, ++i);
		else
			ft_putchar(src[i]);
	}
	va_end(list);
	return (0);
}
