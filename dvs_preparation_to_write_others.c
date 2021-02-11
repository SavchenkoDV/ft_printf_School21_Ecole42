/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvs_preparation_to_write_others.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 21:08:34 by buthor            #+#    #+#             */
/*   Updated: 2021/01/23 21:10:13 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		dvs_nbrlen_dec(long int nbr, t_data data)
{
	int i;

	i = 0;
	if (data.cnv == 'd' || data.cnv == 'i' || data.cnv == 'u')
	{
		if (nbr < 0)
			i++;
		while ((nbr = nbr / 10))
			i++;
		i++;
	}
	return (i);
}

int		dvs_nbrlen_hex(unsigned long long nbr, t_data data)
{
	int i;

	i = 0;
	if (data.cnv == 'p' || data.cnv == 'x' || data.cnv == 'X')
	{
		while ((nbr = nbr / 16))
			i++;
		i++;
	}
	return (i);
}

int		dvs_preparation_to_write_oths(va_list ap, t_data *d)
{
	if (d->cnv == 'p')
		d->n = (long long)(va_arg(ap, void*));
	else if (d->cnv == 'd' || d->cnv == 'i')
		d->n = (long int)va_arg(ap, int);
	else
		d->n = va_arg(ap, unsigned int);
	d->ln = (d->cnv == 'd' || d->cnv == 'i' || d->cnv == 'u') ?
			dvs_nbrlen_dec(d->n, *d) : dvs_nbrlen_hex(d->n, *d);
	if (!d->n && d->pnt && d->prc == 0 && d->width == 0 && d->cnv != 'p')
		return (0);
	d->ln = (d->n == 0 && d->prc == 0 && d->pnt) ? 0 : d->ln;
	d->lz = (d->prc > d->ln) ? d->prc - d->ln : 0;
	if (d->width > d->prc && d->pnt == 1)
		d->ls = (d->prc > d->ln) ? d->width - d->prc : d->width - d->ln;
	else if (d->width > d->ln + d->lz)
		d->ls = d->width - d->ln;
	d->ls -= (d->cnv == 'p') ? 2 : 0;
	if (d->n < 0 && d->pnt == 1 && d->prc >= d->ln)
		++d->lz && d->ls--;
	if (d->zero == 1 && d->minus == 0 && !d->pnt && d->cnv != 'p')
	{
		d->lz = d->ls;
		d->ls = 0;
	}
	return (1);
}
