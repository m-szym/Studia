#include <stdio.h>

int szukaj_max_4(int a, int b, int c, int d);

int main()
{
	//int x, y, z, wynik;
	int x = -1;
	int y = -24;
	int z = -79;
	int w = -12345;
	int wynik = 0;

	//printf("\nProszê podaæ trzy liczby ca³kowite ze znakiem: ");
	//scanf_s("%d %d %d", &x, &y, &z, 32);

	wynik = szukaj_max_4(x, y, z, w);

	printf("\nSpoœród podanych liczb %d, %d, %d, %d, liczba %d jest najwiêksza\n", x, y, z, w, wynik);
	return 0;
}