#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool* ThapSangNhi(int x)
{
	bool* a;
	a = (bool*) calloc (32,sizeof(bool));
	for(int i=31;i>=0;i--)
	{
		a[i]=(x>>(31-i))&1;
	}
	return a;
}


int NhiSangThap(bool* a)
{
	int x=0;
	for(int i=31;i>=0;i--)
	{
		x=x|(a[i]<<(31-i));
	}
	return x;
}

void XuatMang(bool *a)
{
	for(int i=0;i<32;i++)
		printf("%d",a[i]);
	printf("\n");
}

int main()
{
	int x = -5;
	bool *a;
	a = (bool*) calloc (32,sizeof(bool));
	a = ThapSangNhi(x);
	XuatMang(a);
	//printf("Gia tri thap phan cua x: ");
	//int y =0;
	//y = NhiSangThap(a);
	//printf("%d\n", &y);
	free(a);
}
