#include <stdio.h>

void plus_jeden(int* a);
void liczba_przeciwna(int* a);

int main()
{
	int m;
	m = 315;
	//plus_jeden(&m);
	liczba_przeciwna(&m);
	printf("\n m = %d\n", m);
	return 0;
}