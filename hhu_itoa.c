/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim <jinkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 23:46:42 by jinkim            #+#    #+#             */
/*   Updated: 2020/05/07 15:53:46 by jinkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_hhu(unsigned char n,
		unsigned char *num, int *sign, int *len)
{
	*num = n;
	*len = 0;
	*sign = 1;
	while (*num != 0)
	{
		*num = *num / 10;
		*len = *len + 1;
	}
	if (n == 0)
		*len = 1;
}

char	*ft_itoa_hhu(unsigned char n)
{
	char			*rtn;
	unsigned char	num;
	int				i;
	int				sign;
	int				len;

	init_hhu(n, &num, &sign, &len);
	rtn = (char *)malloc(sizeof(char) * (len + 1));
	if (!rtn)
		return (0);
	if (n == 0)
		rtn[0] = '0';
	if (sign == -1)
		rtn[0] = '-';
	num = n;
	num = sign * num;
	i = len - 1;
	while (num != 0)
	{
		rtn[i] = num % 10 + '0';
		num = num / 10;
		i--;
	}
	rtn[len] = '\0';
	return (rtn);
}
