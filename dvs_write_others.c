/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvs_write_others.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:29:15 by buthor            #+#    #+#             */
/*   Updated: 2021/01/23 21:14:40 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	dvs_putnbr(long int n)
{
	if (n == -2147483648)
	{
		dvs_putchar('-');
		dvs_putchar('2');
		n = 147483648;
	}
	if (n < 0)
	{
		n = n * -1;
		dvs_putchar('-');
	}
	if (n >= 10)
	{
		dvs_putnbr(n / 10);
		dvs_putnbr(n % 10);
	}
	else
		dvs_putchar((char)(n + '0'));
}

void	dvs_putnbr_hex(unsigned long long nbr, t_data data)
{
	if (nbr < 16)
	{
		if (data.cnv == 'x' || data.cnv == 'p')
		{
			nbr = (unsigned char)"0123456789abcdef"[nbr];
			dvs_putchar((char)nbr);
			return ;
		}
		else
		{
			nbr = (unsigned char)"0123456789ABCDEF"[nbr];
			dvs_putchar((char)nbr);
			return ;
		}
	}
	dvs_putnbr_hex(nbr / 16, data);
	dvs_putnbr_hex(nbr % 16, data);
}

void	dvs_write_others(t_data d)
{
	if (d.minus == 0)
		while (d.ls-- > 0)
			dvs_putchar(' ');
	if (d.n < 0 && d.cnv != 'p')
	{
		d.n = d.n * -1;
		dvs_putchar('-');
	}
	if (d.cnv == 'p')
	{
		dvs_putchar('0');
		dvs_putchar('x');
	}
	while (d.lz-- > 0)
		dvs_putchar('0');
	if (d.prc != 0 || d.pnt != 1 || d.n > 0)
	{
		if (d.cnv == 'd' || d.cnv == 'i' || d.cnv == 'u')
			dvs_putnbr(d.n);
		else
			dvs_putnbr_hex(d.n, d);
	}
	if (d.minus == 1)
		while (d.ls-- > 0)
			dvs_putchar(' ');
}
