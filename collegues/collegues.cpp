// vvod.cpp: определяет точку входа для консольного приложения. 
// 

#include "stdafx.h" 
#include "stdio.h" 
#include "string.h" 
#include "malloc.h" 

void MakeMatrix(int *d, int a, int b)
{
	int a11 = 0; int a2 = 0; int a3 = 0;
	//изменение элементов матрицы под побочной диагональю, включая диагональ
	for (int k = (a - 1); k >= 0; k--)//задание начала диагонали
	{
		int q = b - 1;
		for (int r = k; r<a; r++)//переход по диагонали по строке
		{
			for (int i = 0; i<r; i++)//сумма в столбце(не включая элемент)
			{
				a11 = a11 + d[i*b + q];
			}
			for (int j = 0; j<q; j++)//сумма в строке(не включая элемент)
			{
				a2 = a2 + d[r*b + j];
			}
			int j = q;//переход к подсчету суммы в диагонали
			for (int i = r; i<a; i++)//подсчет суммы в диагонали(включая элемент)
			{
				a3 = a3 + d[i*b + j]; j--;
			}
			d[r*b + q] = a11 + a2 + a3;//запись суммы в массив
			a11 = 0; a2 = 0; a3 = 0;//обнуление слагаемых
			q = q - 1;//переход к следующему элементу диагонали по столбцу
		}

	}
	//изменение элементов матрицы над побочной диагональю, не включая диагональ
	for (int h = (b - 2); h >= 0; h--)//переход диагонали по строке
	{
		int k = 0;
		for (int r = h; r >= 0; r--)//переход по столбцу
		{
			for (int i = 0; i<k; i++)//сумма в столбце(не включая элемент)
			{
				a11 = a11 + *(d + i*b + r);
			}
			for (int j = 0; j<r; j++)//сумма в строке(не включая элемент)
			{
				a2 = a2 + *(d + b*k + j);
			}int i = k;
			for (int j = r; j >= 0; j--)//сумма в диагонали(включая элемент)
			{
				a3 = a3 + *(d + i*b + j); i++;
			}
			*(d + k*b + r) = a11 + a2 + a3; //запись суммы в массив
			a11 = 0; a2 = 0; a3 = 0;//обнуление слагаемых
			k++;//переход к следующему элементу диагонали по строке
		}

	}
	for (int i = 0; i<a; i++) // выводим массив на экран 
	{
		for (int j = 0; j<b; j++)
		{
			printf("%5i ", *(d + i*b + j));
		}// 5 знакомест под элемент массива 
		printf("\n");
	}

}
int * create(char* name)
{
	FILE *ff;
	ff = fopen(name, "r");
	int size[2];//size[0]=кол-во строк матрицы; size[1]=кол-во столбцов 
	if (ff == NULL)printf("Error: file does not exist. \n");
	else
	{
		for (int i = 0; i<2; i++) fscanf(ff, "%i", &size[i]);// считали из файла первую строчку, где записаны два целых числа(размер матрицы) через пробел 

		int *a; // указатель на массив 
		a = (int*)malloc(size[0] * size[1] * sizeof(int));// Выделение памяти 

		for (int i = 0; i<size[0]; i++)
		for (int j = 0; j<size[1]; j++) // считываем данные из файла в двумерный массив. 
			fscanf(ff, "%i", (a + i*size[1] + j));
		fclose(ff);
		return a;
	}
	fclose(ff);
}

void sizemas(char* name, int size[2])
{
	FILE *ff;
	ff = fopen(name, "r");
	if (ff == NULL)printf("Error: file does not exist. \n");
	else
	{
		for (int i = 0; i<2; i++) fscanf(ff, "%i", &size[i]);
	}
	fclose(ff);
}

void write(char* name, int n, int m, int* b)
{
	FILE *ff;
	ff = fopen(name, "w");
	if (ff == NULL)printf("Error: file does not exist. \n");
	else
	{
		for (int i = 0; i<n; i++)
		{
			for (int j = 0; j<m; j++)
			{
				fprintf(ff, "%i ", b[i*m + j]);
			}
			fprintf(ff, "\n");
		}
	}fclose(ff);
}
void main()
{
	char *fname = "C:/Users/Михаил/Documents/Visual Studio 2013/Projects/collegues/collegues/Debug/matrix.txt";
	char *fname1 = "C:/Users/Михаил/Documents/Visual Studio 2013/Projects/collegues/collegues/Debug/matrix1.txt";// лежaт в Debug 
	int *b; // указатель на массив 
	b = create(fname);//прочитали в b массив из "matrix.txt" 
	int size[2];
	sizemas(fname, size);//нашли размер матрицы 
	MakeMatrix(b, size[0], size[1]);//описание в методе
	write(fname1, size[0], size[1], b);//вывод в файл
	/*---*/
}


