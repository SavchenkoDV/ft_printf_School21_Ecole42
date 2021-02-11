/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:03:51 by buthor            #+#    #+#             */
/*   Updated: 2021/01/23 21:56:00 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			dvs_cleaner(t_data *d)
{
	d->zero = 0;
	d->minus = 0;
	d->width = 0;
	d->pnt = 0;
	d->prc = 0;
	d->cnv = ' ';
	d->ls = 0;
}

const char		*dvs_parser(const char *s, va_list ap, t_data *d)
{
	dvs_cleaner(d);
	s++;
	while (d->cnv == ' ' && *s != '\0')
	{
		if ((*s == '0' && !d->width && d->pnt == 0) ||
			(*s == '0' && !d->prc && d->pnt == 0))
			d->zero = 1;
		else if (*s == '-')
			d->minus = 1;
		else if (*s == dvs_strchr(NBR, *s) && !d->width && !d->pnt)
			d->width = dvs_atoi(&s);
		else if (*s == '.')
			d->pnt = 1;
		else if (*s == dvs_strchr(NBR, *s) && d->prc == 0 && d->pnt == 1)
			d->prc = dvs_atoi(&s);
		else if (*s == '*' && d->prc == 0 && d->pnt == 1)
			d->prc = va_arg(ap, int);
		else if (*s == '*' && d->width == 0 && d->pnt == 0)
			d->width = va_arg(ap, int);
		else if (*s == dvs_strchr(CNV, *s))
			d->cnv = *s;
		s++;
	}
	return (s);
}

int				dvs_pars_corrector(t_data *d)
{
	if (d->width < 0)
	{
		d->width = d->width * -1;
		d->minus = 1;
	}
	if (d->prc < 0)
	{
		d->pnt = 0;
		d->prc = 0;
	}
	return (0);
}

int				dvs_atoi(const char **str)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	if ((*str)[i] == '-')
	{
		sign = sign * -1;
		i++;
	}
	nb = (*str)[i] - '0';
	while ((*str)[i] >= '0' && (*str)[i] <= '9')
	{
		if ((*str)[i + 1] >= '0' && (*str)[i + 1] <= '9')
			nb = nb * 10 + ((*str)[i + 1] - '0');
		else
		{
			*str = *str + i;
			return (nb * sign);
		}
		i++;
	}
	return (0);
}

int				ft_printf(const char *s, ...)
{
	va_list ap;
	t_data	d;

	g_len = 0;
	va_start(ap, s);
	while (s && *s != '\0')
	{
		if (*s == '%')
		{
			(s = dvs_parser(s, ap, &d)) && dvs_pars_corrector(&d);
			if (d.cnv == 'c' || d.cnv == '%')
				dvs_write_c(ap, d);
			else if (d.cnv == 's')
				dvs_write_s(ap, d);
			else if (dvs_preparation_to_write_oths(ap, &d))
				dvs_write_others(d);
		}
		else
			dvs_putchar(*s++);
	}
	va_end(ap);
	return (g_len);
}
