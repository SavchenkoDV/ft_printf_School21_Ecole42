/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:57:04 by buthor            #+#    #+#             */
/*   Updated: 2021/01/23 21:51:29 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	dvs_putchar(char c)
{
	write(1, &c, 1);
	g_len++;
}

size_t	dvs_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	dvs_strchr(const char *s, int c)
{
	char	*src;

	src = (char *)s;
	while (*src != '\0')
	{
		if (*src == (char)c)
			return (*src);
		src++;
	}
	if (*src == (char)c && (char)c == '\0')
		return (*src);
	return (' ');
}

void	dvs_write_c(va_list ap, t_data data)
{
	char ch;

	if (data.cnv == 'c')
		ch = (char)(va_arg(ap, int));
	else
		ch = data.cnv;
	if (data.width > 0)
		data.width = data.width - 1;
	if (data.width && data.minus == 1)
	{
		dvs_putchar(ch);
		while (data.width-- > 0)
			dvs_putchar(' ');
	}
	else if (data.width && data.minus == 0)
	{
		while (data.width-- > 0)
			data.zero == 1 ? dvs_putchar('0') : dvs_putchar(' ');
		dvs_putchar(ch);
	}
	else
		dvs_putchar(ch);
}

void	dvs_write_s(va_list ap, t_data data)
{
	char	*s;
	int		len_str;
	int		len_space;

	len_space = 0;
	s = va_arg(ap, char*);
	if (s == NULL)
		s = "(null)";
	len_str = dvs_strlen(s);
	if (data.prc < len_str && data.pnt == 1)
		len_str = (int)data.prc;
	if (data.width > len_str)
		len_space = (int)data.width - len_str;
	if (data.minus == 1)
	{
		while (len_str-- > 0)
			dvs_putchar(*s++);
		while (len_space-- > 0)
			dvs_putchar(' ');
		return ;
	}
	while (len_space-- > 0)
		dvs_putchar(' ');
	while (len_str-- > 0)
		dvs_putchar(*s++);
}
