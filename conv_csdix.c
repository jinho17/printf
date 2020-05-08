/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_csdix_upn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 03:31:00 by jinkim            #+#    #+#             */
/*   Updated: 2020/05/08 19:51:12 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conv_x_hh(void)
{
	int temp;

	temp = va_arg(g_tag->ap, signed int);
	while (1)
	{
		if (temp <= 255 && temp >= 0)
			break ;
		if (temp > 0)
			temp = temp - 256;
		if (temp < 0)
			temp = temp + 256;
	}
	if (temp < 0)
		temp = temp * (-1);
	g_tag->s = ft_dectohex(temp, g_tag->specifier);
}

void	conv_x(void)
{
	long long	tmp;
	char		*t;

	if (g_tag->specifier == 'x' || g_tag->specifier == 'X')
	{
		if (!ft_strncmp(g_tag->length, "hh", 3))
			conv_x_hh();
		else
		{
			tmp = (long long)va_arg(g_tag->ap, unsigned int);
			g_tag->s = ft_dectohex(tmp, g_tag->specifier);
		}
		if ((!ft_strncmp(g_tag->length, "hh", 3)
			|| !ft_strncmp(g_tag->length, "h", 3))
			&& ft_strlen(g_tag->s) > 4)
		{
			t = ft_substr(g_tag->s, ft_strlen(g_tag->s) - 4, 4);
			free(g_tag->s);
			g_tag->s = ft_strdup(t);
			free(t);
		}
	}
}

void	conv_di(void)
{
	if (g_tag->specifier == 'd' || g_tag->specifier == 'i')
	{
		if (ft_strncmp(g_tag->length, "l", 3) == 0)
			g_tag->s = ft_itoa_unsigned(va_arg(g_tag->ap, long int));
		else if (!ft_strncmp(g_tag->length, "ll", 3))
			g_tag->s = ft_itoa_unsigned(va_arg(g_tag->ap, long long int));
		else if (!ft_strncmp(g_tag->length, "h", 3)
				|| !ft_strncmp(g_tag->length, "hh", 3))
			g_tag->s = ft_itoa_unsigned(va_arg(g_tag->ap, int));
		else
			g_tag->s = ft_itoa(va_arg(g_tag->ap, int));
	}
}

void	conv_s(void)
{
	char *t;

	if (g_tag->specifier == 's')
	{
		t = va_arg(g_tag->ap, char *);
		if (!t)
		{
			if (g_tag->prec == 1)
				g_tag->s = ft_substr("(null)", 0, g_tag->precision);
			else
				g_tag->s = ft_strdup("(null)");
		}
		else if (g_tag->prec == 1)
			g_tag->s = ft_substr(t, 0, g_tag->precision);
		else
			g_tag->s = ft_substr(t, 0, ft_strlen(t));
	}
}

void	conv_csdix(void)
{
	if (g_tag->specifier == 'c')
	{
		g_tag->s = (char *)malloc(sizeof(char) * 2);
		g_tag->s[0] = va_arg(g_tag->ap, int);
		g_tag->s[1] = '\0';
		if (g_tag->s[0] == '\0')
		{
			free(g_tag->s);
			g_tag->s = ft_strdup("^@");
			if (g_tag->width != 0)
				g_tag->width = g_tag->width + 1;
			if (g_tag->precision != 0)
				g_tag->precision = g_tag->precision + 1;
			g_tag->rtn_len = g_tag->rtn_len - 1;
		}
	}
	else if (g_tag->specifier == '%')
		g_tag->s = ft_strdup("%");
	conv_s();
	conv_di();
	conv_x();
}
