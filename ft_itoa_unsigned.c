#include <stdlib.h>

char	*ft_itoa_unsigned(long long n)
{
	char		*rtn;
	long long	num;
	int			i;
	int			sign;
	int			len;

	num = n;
	len = 0;
	sign = 1;
	if (num < 0)
	{
		len++;
		sign = -1;
		num = sign * num;
	}
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	if (n == 0)
		len = 1;
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
