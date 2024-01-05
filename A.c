#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define N 10

struct calcValues
{
	float plosPot;//������� �������
	float stenaShir;//����� ����� ��� �������
	float stenaDlin;//����� �����
	float stenaVisota;//������ �����
	float summPloshadiSten;//����� �������� ����
	float proemDlina;//����� ������
	float proemVisota;//������ ������
	float ProemSummPlosh;//������� ������
	int choosenMaterial;
	//��������� ��������� ������� ���� � ������� ������� � ������ ������� �������
};

typedef struct calcValues t_CalcVal;

struct material {
	char name[50];
	float vis;
	float dlina;
};


typedef struct material t_Material;

t_CalcVal materialChose(t_CalcVal countstruct, t_Material mats[]);
t_CalcVal S_counter(t_CalcVal countstruct, t_Material mats[]);
t_CalcVal S_Proemov(t_CalcVal countstruct, t_Material mats[]);
t_CalcVal calculatorWalls(t_CalcVal countstruct, t_Material mats[]);
t_CalcVal finalResult(int finres, t_CalcVal countstruct, t_Material mats[]);
int writeInFile(t_CalcVal countstruct);
int printMats(t_Material mats[], int size);
int readfromFile(t_Material mats[]);
t_CalcVal calcEnd(t_CalcVal countstruct, t_Material mats[]);

int main()//������� �������, � ������� ��������� ����� ���������
{
	setlocale(LC_ALL, "RUS");
	puts("����������� ��� ������� ���������� ������������\n��� ������� ���� � �������� � �������� � ������ �������� �������,\n���� � ������� �������");
	int whileActive = 0;

	t_CalcVal calcValuesC;
	calcValuesC.plosPot = 0;
	//calcValuesC.counter = 1;
	calcValuesC.summPloshadiSten = 0;
	calcValuesC.ProemSummPlosh = 0;
	calcValuesC.choosenMaterial = 0;
	t_Material mats[N];
	int menuPnumb = 0;
	//calcValuesC = menu(calcValuesC, mats);
	while (whileActive!=1)
	{
		int yesNo;
		puts("\n-----------����-----------\n1. ����� ���������\n2. ���� ������ �������\n3. ���� ������ ����\n4. ���� ������ �������\n5. ������ ��������� ����������\n6. ��������� ���������\n");
		scanf("%d", &menuPnumb);
		//getchar();
		switch (menuPnumb)
		{
		case 1:
			calcValuesC = materialChose(calcValuesC, mats);
			//return calcValuesC;
			break;
		case 2:
			calcValuesC = S_counter(calcValuesC, mats);
			//return calcValuesC;
			break;
		case 3:
			calcValuesC = calculatorWalls(calcValuesC, mats);
			//return calcValuesC;
			break;
		case 4:
			calcValuesC = S_Proemov(calcValuesC, mats);
			//return calcValuesC;
			break;
		case 5:
			calcValuesC = calcEnd(calcValuesC, mats);
			//return calcValuesC;
			break;
		case 6:
			puts("\n�� ������������� ������ ��������� ������ ���������?\n1) ��\n2) ���");
			scanf("%d", &yesNo);
			switch (yesNo)
			{
			case 1:
				puts("������ ��������� ���������.");
				return;
				break;
			case 2:
				puts("����������� ������ ���������");
				//break;
			default:
				break;
			}
			break;
		default:
			puts("�� ������� �������������� �����. �������� ����� �� 1 �� 6");

			break;
		}
	}
	return 0;

	
}
int readfromFile(t_Material mats[])
{
	FILE* file;
	
	char fname[20] = "data.txt";
	if ((file = fopen(fname, "r")) == NULL) {
		printf("������ �������� ����� ��� ������");
		return 0;
	}
	int size = 0;
	fscanf(file, "%d", &size);
	for (int i = 1; i < size+1; i++)
	{
		fscanf(file, "%s %f %f", &mats[i].name, &mats[i].vis, &mats[i].dlina);
	}
	printMats(mats, size);
	fclose(file);
	return size;
}

int printMats(t_Material mats[], int size)
{
	puts("\n�������� �������� ���� � �������");
	for (int j = 1; j < size; j++) {
		printf("%d)\n������������: %s, ������: %.2f, ������: %.2f\n", j+0, mats[j].name, mats[j].vis, mats[j].dlina);
	}
}

t_CalcVal materialChose(t_CalcVal countstruct, t_Material mats[])
{
	
	int whileActive = 0;
	int size;
	
	size = readfromFile(mats);
	scanf("%d", &countstruct.choosenMaterial);
	if (countstruct.choosenMaterial < size)
	{
		printf("\n�� ������� �������� ��� ������� %d)\n������������: %s,\n������: %.2f,\n������: %.2f\n", countstruct.choosenMaterial, mats[countstruct.choosenMaterial].name, mats[countstruct.choosenMaterial].vis, mats[countstruct.choosenMaterial].dlina);
		
		//menu(countstruct, mats);
		return countstruct;
	}
	else
	{
		puts("��������� ��� ������ ������� �� ����������.");
		countstruct.choosenMaterial = 0;
		//menu(countstruct, mats);
		return countstruct;
	}

}
t_CalcVal S_counter(t_CalcVal countstruct, t_Material mats[])// � ������ ������� ���������� ������� ������� �������
{
	countstruct.plosPot = 1;
	setlocale(LC_ALL, "RUS");
	puts("������� ���������� ������� �������. ������� ����� ����� (���� �� �� ������ ������� �������\n ��� �� ��������� ���� ������ ��� �������, ������ ������� 0");
	//----------------------------������� ������� �������-------------------------------------
	for (int i = 0;; i++)
	{

		scanf("%f", &countstruct.stenaShir);//������ ����� �����
		if (countstruct.stenaShir != 0)//���� ��������� �������� �� ����� ����, �� �� �������� ��� �� ������� plosPot
		{
			countstruct.plosPot *= countstruct.stenaShir;//

		}
		else
		{
			//plosPot = stenaShir;
			break;//����� ���� ����������� � �� ��������� � ����������
		}
	}
	if (countstruct.plosPot != 1)
	{
		//printf("������� ������� %f �2\n", countstruct.plosPot);//��������� ������� �������

	}
	else
	{
		puts("�� ���������� ������� ������ ��� �������");
		countstruct.plosPot = 0;

	}
	//menu(countstruct, mats);
	return countstruct;

}
t_CalcVal calculatorWalls(t_CalcVal countstruct, t_Material mats[])//������ ������� ����� ������� ��������
{
	
	int counter = 1;
	countstruct.summPloshadiSten = 0;
	puts("\n������� ���������� ������� ���� (��� ������ �������)");
	//----------------------------������� ������� ����-------------------------------------
	for (int i = 0;; i++)
	{
		printf("\n������� ����� %d �����: ", counter);

		scanf("%f", &countstruct.stenaDlin);//������ ����� �����
		if (countstruct.stenaDlin == 0)//���� ����� ����� ����� ����, �� �������� ����������� � ��������� ���������
		{
			break;
		}
		printf("\n������� ������ %d �����: ", counter);
		scanf("%f", &countstruct.stenaVisota);//������ ������ �����
		if (countstruct.stenaVisota == 0)//���� �� ������ ����� ����� ����, �� �������� ����� ����������� � ��������� ���������
		{
			break;
		}

		countstruct.summPloshadiSten += countstruct.stenaDlin * countstruct.stenaVisota;/*����� � ������ ����� ���������� ��� ��������� �������
													� ����� ��������� � ��������, ������� ���������� ������� ���� ����*/
		counter++;//� ������ ������ ������������� �� 1 ��� ������ ������ �����, ��� ������� �� ��������� ������� ��������
	}
	if (countstruct.summPloshadiSten != 0)//��������� �� ����� �� ����� �������� ����
	{
	//	printf("������� ���� ��� ������ ������� %f\n", countstruct.summPloshadiSten);//��� ��������� ������� ���� ��� ����� �������

	}
	else
	{
		puts("�� �� ����� �� ���� ����� �����.");
		//menu(countstruct, mats);
		//����� ���� ����� ����, �� ��������� ����� ����
		return;//��� ������� �������� ������� �� ����, ��������� �����������
	}
	//menu(countstruct, mats);
	return countstruct;

}

t_CalcVal S_Proemov(t_CalcVal countstruct, t_Material mats[])
{
	puts("������� ��������� ����� �������� ���� �������");
	int counter = 1;//������� ���������� ���� ���������� ������ ������� � ���������� ��������� �������
	//----------------------------������� ������� �������-------------------------------------
	for (int i = 0;; i++)
	{
		printf("\n������� ����� %d ������: ", counter);

		scanf("%f", &countstruct.proemDlina);//�������� ����� ������
		if (countstruct.proemDlina == 0)//���� ��������� ����� ����� ����, �� ���� ����������� 
		{
			break;
		}
		printf("\n������� ������ %d ������: ", counter);
		scanf("%f", &countstruct.proemVisota);
		if (countstruct.proemVisota == 0)//���� ��������� ������ ����� ����, �� ���� ����������� 
		{
			break;
		}


		countstruct.ProemSummPlosh += countstruct.proemDlina * countstruct.proemVisota;/*����� � ������ ������ ���������� ��� ��������� �������
													� ����� ��������� � ��������, ������� ���������� ������� ���� �������*/
		counter++;
	}
	if (countstruct.ProemSummPlosh != 0)//���� ����� �������� ������� �� ����� ���� �� ������� ��������� ����� �������� �������
	{
		//printf("������� ������� %f �2\n", countstruct.ProemSummPlosh);
	}
	else
	{
		puts("�� ���������� �� ����� �������");//����� ������� ������ ���������
	}
	//menu(countstruct, mats);
	return countstruct;
}

t_CalcVal calcEnd(t_CalcVal countstruct, t_Material mats[])
{
	float PloshPoverh = countstruct.plosPot + (countstruct.summPloshadiSten - countstruct.ProemSummPlosh);/*��������� ��������� �������������� ������ �������.
																�� ����� �������� ���� ���������� ����� �������� �������,
															� ����� ������������ ��������� � ������� �������*/
	int finalRes = (int)ceil(PloshPoverh / (mats[countstruct.choosenMaterial].vis * mats[countstruct.choosenMaterial].dlina));
	finalResult(finalRes, countstruct, mats);
	return countstruct;
}

t_CalcVal finalResult(int finalRes, t_CalcVal countstruct, t_Material mats[])
{
	//----------------------------���������� ����������-------------------------------------
	

	if(countstruct.choosenMaterial!=0 && (countstruct.plosPot!=0 || countstruct.summPloshadiSten!=0))
	{
		puts("--------------------------������������� ������-------------------------");
		printf("������� ������� %0.3f �2\n", countstruct.plosPot);//��������� ������� �������

		printf("������� ������� %0.3f �2\n", countstruct.ProemSummPlosh);//��������� ������� ����

		printf("������� ���� ��� ������ ������� %0.3f\n", countstruct.summPloshadiSten);//��� ��������� ������� ���� ��� ����� �������

		char lists[20];
		strcpy(lists, (finalRes == 1 ? "����" : (finalRes > 1 && finalRes < 5) ? "�����" : "������"));
		puts("\n--------------------------------����-----------------------------------");
		printf("\n����� ��� ����������� %d %s ������������ �������� '%s'\n", finalRes, lists, mats[countstruct.choosenMaterial].name);//��������� ���������	
		char a[6][100];//char a[7][100];
		
		sprintf(a[0], "\n\n\n--------------------------������������� ������-------------------------\n");
		sprintf(a[1], "������� ������� %0.3f �2\n", countstruct.plosPot);
		sprintf(a[2], "������� ������� %0.3f �2\n", countstruct.ProemSummPlosh);//��������� ������� ����
		sprintf(a[3], "������� ���� ��� ������ ������� %0.3f\n", countstruct.summPloshadiSten);
		sprintf(a[4],"\n--------------------------------����-----------------------------------");
		sprintf(a[5],"\n����� ��� ����������� %d %s ������������ �������� '%s'\n", finalRes, lists, mats[countstruct.choosenMaterial].name);
		puts("\n���������� �������� � ����");
		for (int i = 0; i < 6; i++)
		{
			writeInFile(countstruct, a[i]);
		}
		
	}
	else if(countstruct.choosenMaterial == 0)
	{
		puts("�� �� ������� ��� ������������");
		return;
	//	menu(countstruct, mats);
	}
	else
	{
		puts("�� ����� ������������ ������, ����������� ��� �������.");
		return;

		//menu(countstruct, mats);
	}
	//menu(countstruct, mats);
	return countstruct;
	
}

int writeInFile(t_CalcVal countstruct, char str[])//Void � Int
{
	FILE* out;
	char fname[20] = "dataVal.txt";

	if ((out = fopen(fname, "a")) == NULL) {
		printf("������ �������� ����� ��� ������");
		return 0;
	}
	fprintf(out,str);
	fclose(out);
	return 0;
}