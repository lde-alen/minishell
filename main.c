#include <stdio.h>
#include <limits.h>
#include <unistd.h>

int	main(void)
{
	size_t	i;

	i = 18446744073709551614;
	printf("%zu\n", i);
	return (0);
}
