#include "Libft/libft.h"
#include <stdarg.h>
#include <unistd.h>

typedef struct		s_tag
{
	va_list			ap;
	char			flag;
	int				width;
	int				precision;
	char			length[2];
	char			specifier;
	char			*str;
	int				str_len;
	
	//cspdiuxX% nfge
	char			*s; //s, d, i, x, X, c, %
}					t_tag;

int ft_printf(const char *format, ...)
{
	int		i;
	int		idx;
	int		len_fm;
	t_tag	*tag;
	
	//f			
	double	f;
	char	*dec;
	char	*b_dec;
	int		len;
	double	b_d;
	char	*t;
	double	dou;
	
	//g	
	/*		
	double	f;
	char	*dec;
	char	*t;
	double	dou;
	double	b_d;
	int		len;
	*/
	
	//e
	/*			
	double	f;
	double	b_d;
	double	dou;
	char	*dec;
	char	*t;
	int		len;
	*/
	len_fm = ft_strlen(format);
	i = 0;
	tag = (t_tag *)malloc(sizeof(t_tag));
	va_start(tag->ap, format);
	while (i < len_fm)
	{
		if (format[i] != '%')
			ft_putchar_fd(format[i], 1);
		else
		{
			i++;
			//flag			ex) -, #, ' ', +
			if (format[i] == '-')
				tag->flag = format[i++];
			else if (format[i] == '#')
				tag->flag = format[i++];
			else if (format[i] == '+')
				tag->flag = format[i++];
			else if (format[i] == ' ')
				tag->flag = format[i++];


			//width			ex) 5
			if (format[i] == '*')
			{
				tag->width = va_arg(tag->ap, int);
				i++;
			}
			else if (format[i] >= '0' && format[i] <= '9')
				tag->width = format[i++] - '0';
			while (format[i] >= '0' && format[i] <= '9')
				tag->width = (format[i++] - '0') + (tag->width * 10);

			if (format[i] == '.')
			{
				i++;
				//.precision	ex) .10
				if (format[i] == '*')
				{
					tag->precision = va_arg(tag->ap, int);
				i++;
				}
				else if (format[i] >= '0' && format[i] <= '9')
					tag->precision = format[i++] - '0';
				while (format[i] >= '0' && format[i] <= '9')
					tag->precision = (format[i++] - '0') + (tag->precision * 10);

				//length		ex) l, ll, h, hh
				idx = 0;
				while (format[i] == 'l' || format[i] == 'h')
					tag->length[idx++] = format[i++];
				//specifier		ex) cspdiuxX% nfge
				tag->specifier = format[i];
			}
			else
			{
				//length		ex) l, ll, h, hh
				idx = 0;
				while (format[i] == 'l' || format[i] == 'h')
					tag->length[idx++] = format[i++];
				//specifier		ex) cspdiuxX% nfge
				tag->specifier = format[i];
			}

			//test
			/*
			printf("test\n");
			printf("flag : %c\n",tag->flag);
			printf("width : %d\n", tag->width);
			printf("precision : %d\n", tag->precision);
			printf("length : %c\n",tag->length[0]);
			printf("specifier : %c\n",tag->specifier);
			*/
			if (tag->specifier == 'c')
			{
				tag->s = (char *)malloc(sizeof(char) * 2);
				tag->s[0] = va_arg(tag->ap, int);
				tag->s[1] = '\0';
			}
			else if (tag->specifier == '%')
			{
				tag->s = (char *)malloc(sizeof(char) * 2);
				tag->s[0] = '%';
				tag->s[1] = '\0';
			}
			else if (tag->specifier == 's')
			{
				t = va_arg(tag->ap, char *);
				if (tag->precision != 0)
					tag->s = ft_substr(t, 0, tag->precision);
				else
					tag->s = ft_substr(t, 0, ft_strlen(t));
			}
			else if (tag->specifier == 'd' || tag->specifier == 'i')
				tag->s = ft_itoa(va_arg(tag->ap, int));
			else if (tag->specifier == 'x' || tag->specifier == 'X')
				tag->s = ft_dectohex(va_arg(tag->ap, int), tag->specifier);
			else if (tag->specifier == 'u')
			{
				int temp;

				temp = va_arg(tag->ap, int);
				if (temp < 0)
					tag->s = ft_itoa_unsigned(4294967295 + temp + 1);
				else
					tag->s = ft_itoa(temp);
			}
			else if (tag->specifier == 'p')
			{
				char *t;
				
				t = ft_dectohex(va_arg(tag->ap, unsigned long), 'x');
				tag->s = ft_strjoin("0x", t);
				free(t);
			}
			else if (tag->specifier == 'n')
			{
				int *t;

				t = va_arg(tag->ap, int *);
				*t = i;
				i++;
				continue ;
			}
			else if (tag->specifier == 'f')
			{
				f = va_arg(tag->ap, double);
				b_d = f - (double)((int)f);
				if (b_d < 0)
					b_d = b_d * (-1);
				dec = ft_itoa((int)f);

				if (tag->precision == 0)
					len = 6;
				else
					len = tag->precision;
				b_dec = (char *)malloc(sizeof(char) * (len + 1));
				idx = len;
				dou = 0.5;
				while (idx--)
					dou /= 10;
				idx = 0;
				while (idx < len)
				{
					b_d = (b_d + dou) * 10;
					b_dec[idx] = (int)b_d + '0';
					b_d = b_d - (double)((int)b_d);
					idx++;
				}
				b_dec[idx] = '\0';
				t = ft_strjoin(dec, ".");
				tag->s = ft_strjoin(t, b_dec);
				free(t);
				free(dec);
				free(b_dec);
			}
			else if (tag->specifier == 'g')
			{
				f = va_arg(tag->ap, double);
				b_d = f - (double)((int)f);
				if (b_d < 0)
					b_d = b_d * (-1);
				dec = ft_itoa((int)f);
				if (f < 0 && dec[0] == '0')
				{
					t = ft_strjoin("-", dec);
					free(dec);
					dec = ft_strdup(t);
					free(t);
				}
				if (tag->precision < ft_strlen(dec) && tag->precision != 0)
					tag->s = ft_substr(dec, 0, tag->precision);
				else
				{
					t = ft_strjoin(dec, ".");
					len = tag->precision - ft_strlen(dec);
					if (tag->precision == 0)
					{
						len = 6 - ft_strlen(dec);
						if ((f < 0 && dec[1] == '0') || dec[0] == '0')
							len++;
					}
					if (f < 0)
						len++;
					free(dec);
					dec = (char *)malloc(sizeof(char) * (len + 1));
					dou = 0.5;
					idx = len;
					while (idx--)
						dou /= 10;
					idx = 0;
					while (idx < len)
					{
						b_d = (b_d + dou) * 10;
						dec[idx] = (int)b_d + '0';
						b_d = b_d - (double)((int)b_d);
						idx++;
					}
					dec[idx] = '\0';
					tag->s = ft_strjoin(t, dec);
					free(t);
				}
				free(dec);
				idx = ft_strlen(tag->s) - 1;
				while (idx >= 0)
				{
					if (tag->s[idx] == '0')
						tag->s[idx] = '\0';
					else if (tag->s[idx] == '.')
						tag->s[idx] = '\0';
					else
						break ;
					idx--;
				}
				tag->precision = ft_strlen(tag->s);
			}
			else if (tag->specifier == 'e')
			{
				f = va_arg(tag->ap, double);
				b_d = f - (double)((int)f);
				dec = ft_itoa((int)f);
				//printf("f : %f, dec[%s]\n", f, dec);
				if (tag->precision == 0)
					len = 6;
				else
					len = tag->precision;
				if (f < 0 && (int)f != 0)
					len = len - ft_strlen(dec) + 2;
				else if (f > 0 && (int)f != 0)
					len = len - ft_strlen(dec) + 1;
				//printf("len : %d\n", len);
				if (len < 0)
					len = 0;
				dou = 0.5;
				idx = len + 1;
				while (idx--)
					dou /= 10;
				//printf("\ndou : %.10f, len : %d\n", dou, len);
				idx = 1;
				if (f < 0)
					b_d = b_d * (-1);
				if ((int)f == 0)
				{
					t = (char *)malloc(sizeof(char) * 3);
					b_d = (b_d + dou) * 10;
					idx = 0;
					if (f < 0)
						t[idx++] = '-';
					t[idx++] = (int)b_d + '0';
					t[idx++] = '\0';
					b_d = b_d - (double)((int)b_d);
				}
				else if (f < 0)
					t = ft_substr(dec, 0, ++idx);
				else
					t = ft_substr(dec, 0, 1);
				tag->s = ft_strjoin(t, ".");
				free(t);
				if (idx < ft_strlen(dec))
				{
					int new_len;

					new_len = 6;
					if (len == 0 && ft_strlen(dec) > tag->precision && tag->precision != 0)
						new_len = tag->precision;
					else if (ft_strlen(dec) < 6)
						new_len = ft_strlen(dec);
					//printf("new_lne : %d, declen : %d, precison : %d\n", new_len, (int)ft_strlen(dec), tag->precision);
					t = ft_strjoin(tag->s, ft_substr(dec, idx, new_len));
				}
				else
					t = ft_strdup(tag->s);
				free(tag->s);
				free(dec);
				dec = (char *)malloc(sizeof(char) * (len + 1));
				idx = 0;
				while(idx < len)
				{
					b_d = (b_d + dou) * 10;
					dec[idx] = (int)b_d + '0';
					b_d = b_d - (double)((int)b_d);
					idx++;
				}
				dec[idx] = '\0';
				tag->s = ft_strjoin(t, dec);
				//printf("\ns[%s]\n", tag->s);
				
				free(t);
				free(dec);
			}

			tag->str_len = ft_strlen(tag->s);
			//printf("\ntag->s[%s]\n", tag->s);

			//width > precision > strlen
 			if (tag->width >= tag->precision && tag->precision >= tag->str_len)
				tag->str_len = tag->width;
			//width > strlen > precison
			else if (tag->width >= tag->str_len && tag->str_len >= tag->precision)
				tag->str_len = tag->width;
			//precision > width > strlen
			else if (tag->precision >= tag->width && tag->width >= tag->str_len)
				tag->str_len = tag->precision;
			//precision > strlen > width
			else if (tag->precision >= tag->str_len && tag->str_len >= tag->width)
				tag->str_len = tag->precision;
			tag->str = (char *)malloc(sizeof(char) * (tag->str_len + 1));

			idx = 0;
			if (tag->flag != '-' && (tag->str_len == tag->width))
			{
				if (tag->precision > (int)ft_strlen(tag->s))
				{
					while (idx != tag->width - tag->precision)
						tag->str[idx++] = ' ';
				}
				else
				{
					while (idx != tag->width - (int)ft_strlen(tag->s))
						tag->str[idx++] = ' ';
				}
			}
			while ((idx < tag->str_len - (int)ft_strlen(tag->s)) && idx >= 0)
				tag->str[idx++] = '0';
			tag->str[idx] = '\0';

			char *tmp;
			tmp = ft_strjoin(tag->str, tag->s);
			idx = ft_strlen(tmp);
			char space[tag->str_len - idx];
			int s_i;
			if (tag->flag == '-' && (tag->str_len == tag->width))
			{
				s_i = 0;
				while (s_i < tag->str_len - idx)
					space[s_i++] = ' ';
				space[s_i] = '\0';
			}
			else
				space[0] = '\0';
			free(tag->str);
			tag->str = ft_strjoin(tmp, space);
			free(tmp);

			//printf("test2\n");
			//printf("a : [%s]\n",tag->str);
			//ft_write_tag
			ft_putstr_fd(tag->str, 1);

			//free
			if (tag->s)
				free(tag->s);
			free(tag->str);
			//tag initialization
			tag->flag = 0;
			tag->width = 0;
			tag->precision = 0;
			tag->str_len = 0;
			//tag->length[2]??
		}
		i++;
	}
	free(tag);
	va_end(tag->ap);
	return (0);
}

#include <limits.h>

int main()
{
	//cspdiuxX% nfge
	//-0.*	
	int d = 2147483647;
	char c = 'c';
	char s[] = "hello world";
	int b = 1234;
	double f = -345692345.2346;
	//3, 8
	//4, 6

	//c, s, p, d, i, u, x, X, %, n,  
	ft_printf("d:%.3d, c:%10c, s:%.5s\n", d, c, s);
	printf("d:%.3d, c:%10c, s:%.5s\n", d, c, s);
	/*
	printf("e	: [%e]\n", f);
	printf("14e	: [%14e]\n", f);
	printf(".8e	: [%.8e]\n", f);
	printf("10.8e	: [%10.8e]\n", f);
	printf("10.80e	: [%10.80e]\n", f);
	printf("100.8e	: [%100.8e]\n", f);
	*/
	//printf("g : [%10.100g]\n", f);
}
