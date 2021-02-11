/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buthor <buthor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:29:35 by buthor            #+#    #+#             */
/*   Updated: 2021/01/23 21:52:12 by buthor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define CNV "cspdiuxX%"
# define NBR "0123456789"

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int					g_len;

typedef	struct		s_data
{
	int				zero;
	int				minus;
	long			width;
	int				pnt;
	long			prc;
	char			cnv;
	long long		n;
	long int		ln;
	long int		lz;
	long int		ls;
}					t_data;

int					ft_printf(const char *string, ...);
void				dvs_cleaner(t_data *d);
const char			*dvs_parser(const char *s, va_list ap, t_data *d);
int					dvs_pars_corrector(t_data *d);
int					dvs_atoi(const char **str);
void				dvs_putchar(char c);
size_t				dvs_strlen(const char *s);
char				dvs_strchr(const char *s, int c);
void				dvs_write_c(va_list ap, t_data d);
void				dvs_write_s(va_list ap, t_data d);
int					dvs_preparation_to_write_oths(va_list ap, t_data *d);
int					dvs_nbrlen_dec(long int nbr, t_data d);
int					dvs_nbrlen_hex(unsigned long long nbr, t_data d);
void				dvs_write_others(t_data d);
void				dvs_putnbr(long int n);
void				dvs_putnbr_hex(unsigned long long nbr, t_data d);

#endif
