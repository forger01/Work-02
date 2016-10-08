// vvod.cpp: ���������� ����� ����� ��� ����������� ����������. 
// 

#include "stdafx.h" 
#include "stdio.h" 
#include "string.h" 
#include "malloc.h" 

void MakeMatrix(int *d, int a, int b)
{
	int a11 = 0; int a2 = 0; int a3 = 0;
	//��������� ��������� ������� ��� �������� ����������, ������� ���������
	for (int k = (a - 1); k >= 0; k--)//������� ������ ���������
	{
		int q = b - 1;
		for (int r = k; r<a; r++)//������� �� ��������� �� ������
		{
			for (int i = 0; i<r; i++)//����� � �������(�� ������� �������)
			{
				a11 = a11 + d[i*b + q];
			}
			for (int j = 0; j<q; j++)//����� � ������(�� ������� �������)
			{
				a2 = a2 + d[r*b + j];
			}
			int j = q;//������� � �������� ����� � ���������
			for (int i = r; i<a; i++)//������� ����� � ���������(������� �������)
			{
				a3 = a3 + d[i*b + j]; j--;
			}
			d[r*b + q] = a11 + a2 + a3;//������ ����� � ������
			a11 = 0; a2 = 0; a3 = 0;//��������� ���������
			q = q - 1;//������� � ���������� �������� ��������� �� �������
		}

	}
	//��������� ��������� ������� ��� �������� ����������, �� ������� ���������
	for (int h = (b - 2); h >= 0; h--)//������� ��������� �� ������
	{
		int k = 0;
		for (int r = h; r >= 0; r--)//������� �� �������
		{
			for (int i = 0; i<k; i++)//����� � �������(�� ������� �������)
			{
				a11 = a11 + *(d + i*b + r);
			}
			for (int j = 0; j<r; j++)//����� � ������(�� ������� �������)
			{
				a2 = a2 + *(d + b*k + j);
			}int i = k;
			for (int j = r; j >= 0; j--)//����� � ���������(������� �������)
			{
				a3 = a3 + *(d + i*b + j); i++;
			}
			*(d + k*b + r) = a11 + a2 + a3; //������ ����� � ������
			a11 = 0; a2 = 0; a3 = 0;//��������� ���������
			k++;//������� � ���������� �������� ��������� �� ������
		}

	}
	for (int i = 0; i<a; i++) // ������� ������ �� ����� 
	{
		for (int j = 0; j<b; j++)
		{
			printf("%5i ", *(d + i*b + j));
		}// 5 ��������� ��� ������� ������� 
		printf("\n");
	}

}
int * create(char* name)
{
	FILE *ff;
	ff = fopen(name, "r");
	int size[2];//size[0]=���-�� ����� �������; size[1]=���-�� �������� 
	if (ff == NULL)printf("Error: file does not exist. \n");
	else
	{
		for (int i = 0; i<2; i++) fscanf(ff, "%i", &size[i]);// ������� �� ����� ������ �������, ��� �������� ��� ����� �����(������ �������) ����� ������ 

		int *a; // ��������� �� ������ 
		a = (int*)malloc(size[0] * size[1] * sizeof(int));// ��������� ������ 

		for (int i = 0; i<size[0]; i++)
		for (int j = 0; j<size[1]; j++) // ��������� ������ �� ����� � ��������� ������. 
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
	char *fname = "C:/Users/������/Documents/Visual Studio 2013/Projects/collegues/collegues/Debug/matrix.txt";
	char *fname1 = "C:/Users/������/Documents/Visual Studio 2013/Projects/collegues/collegues/Debug/matrix1.txt";// ���a� � Debug 
	int *b; // ��������� �� ������ 
	b = create(fname);//��������� � b ������ �� "matrix.txt" 
	int size[2];
	sizemas(fname, size);//����� ������ ������� 
	MakeMatrix(b, size[0], size[1]);//�������� � ������
	write(fname1, size[0], size[1], b);//����� � ����
	/**/
}


