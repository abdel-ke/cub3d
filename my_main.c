#include <stdio.h>
int		ft_intcmp(int a, int b)
{
	return (a - b);
}

typedef int (*ptr)(int,int);
typedef int ra9m;

int main()
{
	ra9m a = 10;
	ra9m b = 4;
	ptr pointer_to_func = ft_intcmp;
	printf("%d\n",pointer_to_func(a, b));
	return (0);
}
