#include <stdio.h>
#include <stdarg.h> //va_start, va_arg, va_copy, va_end
#include "Libft/libft.h"
#include <limits.h>
#include "ft_printf.h"

int main()
{
	//cspdiuxX% nfge
	//-0.*	
	int d = INT_MIN + 1;
	char c = 'c';
	char s[] = "hello world";
	unsigned int u = 1234;
	int p = 123;
	int n = 1;
	int rtn;
	double f = 23.00041;
	long int li = 31234567890;
	unsigned char uch_pos_1 = 100;
	unsigned short ush_pos_1 = 3047;
	unsigned int ui_pos_1 = 878023;
	unsigned long ul_pos_1 = 22337203685477;
	unsigned long long ull_pos_1 = 22337203685477;
	unsigned long long ullmax = 9223372036854775807;

	char a01;
	unsigned char a02;
	short a03;
	unsigned short a04;
	int a05;
	unsigned int a06;
	long a07;
	unsigned long a08;
	long long a09;
	unsigned long long a10;
	char *a11;
	void *a12;


	//3, 8
	//4, 6

	//c, s, p, d, i, u, x, X, %, n,  
	//rtn = ft_printf("u:%50.3u, p:%10p, n:%n, d:%d, c:%c, s:%s\n", u, &p, &n, d, c, s);
	//printf("n : %d, rtn : %d\n", n, rtn);
	//rtn = printf("u:%50.3u, p:%10p, n:%n, d:%d, c:%c, s:%s\n", u, &p, &n, d, c, s);
	//printf("n : %d, rtn : %d\n", n, rtn);


	//iduxX
	//l : long int, unsigned long int
	//ll : long long int, unsigned long long int
	//h : short int, unsigined short int, 
	//hh : signed char, unsigned char
	//u, i, d,,,,f
	unsigned long ul = 123;

	rtn = printf("%.3f", f);
	printf("rtn : %d\n", rtn);
	rtn = ft_printf("%.3f", f);
	printf("rtn : %d\n", rtn);

}

/*
void printN(int args, ...)
{
	va_list ap;
	va_list ap2;

	int n;
	va_start(ap,  args);
	va_copy(ap2, ap);
	for(int i = 0; i < args; i++)
	{
		n = va_arg(ap, int);
		printf("%d ",n);
	}
	va_end(ap);
	for(int i = 0; i < args; i++)
	{
		n = va_arg(ap2, int);
		printf("/%d ",n);
	}
	va_end(ap2);
	printf("\n");
}

int main()
{
	//cspiuxX
	//-0.*

	int a;
	a = -15;
	printf("X : %X\n", a);
	printf("x : %x\n", a);
	printf("u : %u\n", a);
	printf("d : %d\n", a);
	printf("i : %i\n", a);
	printf("%%\n");

	printN(1, 10);
	printN(2, 10, 20);

	
	int b = 123456;
	printf("d[%-3.3d]\n", b);
	printf("d[%-*.7d]\n", 8, b);
	printf("d[%*.*d]\n", 8, 7, b);
	printf("d[%*.*d]\n", 7, 8, b);
	printf("d[%7.8d]\n", b);

	char str[] = "1234";
	printf("%ld\n", ft_strlen(str));

	return 0;
}
*/
