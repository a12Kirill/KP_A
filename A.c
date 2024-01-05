#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define N 10

struct calcValues
{
	float plosPot;//Площадь потолка
	float stenaShir;//Длина стены для потолка
	float stenaDlin;//Длина стены
	float stenaVisota;//Высота стены
	float summPloshadiSten;//Сумма площадей стен
	float proemDlina;//ДЛина проема
	float proemVisota;//Высота проема
	float ProemSummPlosh;//Площадь проема
	int choosenMaterial;
	//Финальный результат площади стен и потолка комнаты с учетом дверных проемов
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

int main()//Главная функция, в которой находится выбор материала
{
	setlocale(LC_ALL, "RUS");
	puts("Калькулятор для расчета количества гипсокартона\nдля обшивки стен и потолков в комнатах с учетом размеров комнаты,\nокон и дверных проемов");
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
		puts("\n-----------МЕНЮ-----------\n1. Выбор материала\n2. Ввод данных потолка\n3. Ввод данных стен\n4. Ввод данных проемов\n5. Расчет конечного результата\n6. Завершить программу\n");
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
			puts("\nВы действительно хотите завершить работу программы?\n1) Да\n2) Нет");
			scanf("%d", &yesNo);
			switch (yesNo)
			{
			case 1:
				puts("Работа программы завершена.");
				return;
				break;
			case 2:
				puts("Продолжение работы программы");
				//break;
			default:
				break;
			}
			break;
		default:
			puts("Вы выбрали несуществующий пункт. Выберите пункт от 1 до 6");

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
		printf("Ошибка открытия файла для записи");
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
	puts("\nВыберите материал стен и потолка");
	for (int j = 1; j < size; j++) {
		printf("%d)\nНаименование: %s, Высота: %.2f, Ширина: %.2f\n", j+0, mats[j].name, mats[j].vis, mats[j].dlina);
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
		printf("\nВы выбрали материал под номером %d)\nНаименование: %s,\nВысота: %.2f,\nШирина: %.2f\n", countstruct.choosenMaterial, mats[countstruct.choosenMaterial].name, mats[countstruct.choosenMaterial].vis, mats[countstruct.choosenMaterial].dlina);
		
		//menu(countstruct, mats);
		return countstruct;
	}
	else
	{
		puts("Материала под данным номером не существует.");
		countstruct.choosenMaterial = 0;
		//menu(countstruct, mats);
		return countstruct;
	}

}
t_CalcVal S_counter(t_CalcVal countstruct, t_Material mats[])// В данной функции происходит рассчет площади потолка
{
	countstruct.plosPot = 1;
	setlocale(LC_ALL, "RUS");
	puts("Давайте рассчитаем площадь потолка. Введите длину стены (Если вы не хотите считать потолок\n или вы завершили ввод данных для потолка, просто введите 0");
	//----------------------------Рассчет площади потолка-------------------------------------
	for (int i = 0;; i++)
	{

		scanf("%f", &countstruct.stenaShir);//Вводим длину стены
		if (countstruct.stenaShir != 0)//Если введенное значение не равно нулю, то мы умножаем его на счетчик plosPot
		{
			countstruct.plosPot *= countstruct.stenaShir;//

		}
		else
		{
			//plosPot = stenaShir;
			break;//Иначе цикл завершается и мы переходим к результату
		}
	}
	if (countstruct.plosPot != 1)
	{
		//printf("Площадь потолка %f м2\n", countstruct.plosPot);//Результат площади потолка

	}
	else
	{
		puts("Вы отказались вводить данные для потолка");
		countstruct.plosPot = 0;

	}
	//menu(countstruct, mats);
	return countstruct;

}
t_CalcVal calculatorWalls(t_CalcVal countstruct, t_Material mats[])//Данная функция ведет главные рассчеты
{
	
	int counter = 1;
	countstruct.summPloshadiSten = 0;
	puts("\nДавайте рассчитаем площадь стен (без учетов проемов)");
	//----------------------------Рассчет площади стен-------------------------------------
	for (int i = 0;; i++)
	{
		printf("\nВведите длину %d стены: ", counter);

		scanf("%f", &countstruct.stenaDlin);//Вводим длину стены
		if (countstruct.stenaDlin == 0)//Если длина стены равна нулю, то рассчеты завершаются и выводится результат
		{
			break;
		}
		printf("\nВведите высоту %d стены: ", counter);
		scanf("%f", &countstruct.stenaVisota);//Вводим высоту стены
		if (countstruct.stenaVisota == 0)//Если же высота стены равна нулю, то рассчеты также завершаются и выводится результат
		{
			break;
		}

		countstruct.summPloshadiSten += countstruct.stenaDlin * countstruct.stenaVisota;/*Длина и высота стены умножаются для получения площади
													и далее плюсуется к счетчику, который складывает площади всех стен*/
		counter++;//С каждым циклом увеличивается на 1 для вывода номера стены, для которой мы планируем вводить значение
	}
	if (countstruct.summPloshadiSten != 0)//Проверяем не равна ли сумма площадей нулю
	{
	//	printf("Площадь стен без учетов проемов %f\n", countstruct.summPloshadiSten);//Тут выводится площадь стен без учета проемов

	}
	else
	{
		puts("Вы не ввели ни одну длину стены.");
		//menu(countstruct, mats);
		//Иначе если равна нулю, то результат будет ноль
		return;//Раз никаких значений введено не было, программа завершается
	}
	//menu(countstruct, mats);
	return countstruct;

}

t_CalcVal S_Proemov(t_CalcVal countstruct, t_Material mats[])
{
	puts("Давайте посчитаем сумму площадей всех проемов");
	int counter = 1;//Счетчик количества стен становится равным единице и становится счетчиком проемов
	//----------------------------Рассчет площади проемов-------------------------------------
	for (int i = 0;; i++)
	{
		printf("\nВведите длину %d проема: ", counter);

		scanf("%f", &countstruct.proemDlina);//Вводится длина проема
		if (countstruct.proemDlina == 0)//Если введенная длина равна нулю, то цикл завершается 
		{
			break;
		}
		printf("\nВведите высоту %d проема: ", counter);
		scanf("%f", &countstruct.proemVisota);
		if (countstruct.proemVisota == 0)//Если введенная высота равна нулю, то цикл завершается 
		{
			break;
		}


		countstruct.ProemSummPlosh += countstruct.proemDlina * countstruct.proemVisota;/*Длина и высота проема умножаются для получения площади
													и далее плюсуется к счетчику, который складывает площади всех проемов*/
		counter++;
	}
	if (countstruct.ProemSummPlosh != 0)//если сумма площадей проемов не равна нулю то выводим результат суммы площадей проемов
	{
		//printf("Площадь проемов %f м2\n", countstruct.ProemSummPlosh);
	}
	else
	{
		puts("Вы отказались от ввода проемов");//Иначе выводим данное сообщение
	}
	//menu(countstruct, mats);
	return countstruct;
}

t_CalcVal calcEnd(t_CalcVal countstruct, t_Material mats[])
{
	float PloshPoverh = countstruct.plosPot + (countstruct.summPloshadiSten - countstruct.ProemSummPlosh);/*Финальный результат рассчитывается данным образом.
																От суммы площадей стен отнимаются суммы площадей проемов,
															а далее получившееся плюсуется к площади потолка*/
	int finalRes = (int)ceil(PloshPoverh / (mats[countstruct.choosenMaterial].vis * mats[countstruct.choosenMaterial].dlina));
	finalResult(finalRes, countstruct, mats);
	return countstruct;
}

t_CalcVal finalResult(int finalRes, t_CalcVal countstruct, t_Material mats[])
{
	//----------------------------Подведение результата-------------------------------------
	

	if(countstruct.choosenMaterial!=0 && (countstruct.plosPot!=0 || countstruct.summPloshadiSten!=0))
	{
		puts("--------------------------Промежуточные данные-------------------------");
		printf("Площадь потолка %0.3f м2\n", countstruct.plosPot);//Результат площади потолка

		printf("Площадь проемов %0.3f м2\n", countstruct.ProemSummPlosh);//Результат площади стен

		printf("Площадь стен без учетов проемов %0.3f\n", countstruct.summPloshadiSten);//Тут выводится площадь стен без учета проемов

		char lists[20];
		strcpy(lists, (finalRes == 1 ? "лист" : (finalRes > 1 && finalRes < 5) ? "листа" : "листов"));
		puts("\n--------------------------------Итог-----------------------------------");
		printf("\nИтого вам понадобится %d %s гипсокартона названия '%s'\n", finalRes, lists, mats[countstruct.choosenMaterial].name);//Выводится результат	
		char a[6][100];//char a[7][100];
		
		sprintf(a[0], "\n\n\n--------------------------Промежуточные данные-------------------------\n");
		sprintf(a[1], "Площадь потолка %0.3f м2\n", countstruct.plosPot);
		sprintf(a[2], "Площадь проемов %0.3f м2\n", countstruct.ProemSummPlosh);//Результат площади стен
		sprintf(a[3], "Площадь стен без учетов проемов %0.3f\n", countstruct.summPloshadiSten);
		sprintf(a[4],"\n--------------------------------Итог-----------------------------------");
		sprintf(a[5],"\nИтого вам понадобится %d %s гипсокартона названия '%s'\n", finalRes, lists, mats[countstruct.choosenMaterial].name);
		puts("\nРезультаты записаны в файл");
		for (int i = 0; i < 6; i++)
		{
			writeInFile(countstruct, a[i]);
		}
		
	}
	else if(countstruct.choosenMaterial == 0)
	{
		puts("Вы не выбрали вид гипсокартона");
		return;
	//	menu(countstruct, mats);
	}
	else
	{
		puts("Вы ввели недостаточно данных, необходимых для расчета.");
		return;

		//menu(countstruct, mats);
	}
	//menu(countstruct, mats);
	return countstruct;
	
}

int writeInFile(t_CalcVal countstruct, char str[])//Void в Int
{
	FILE* out;
	char fname[20] = "dataVal.txt";

	if ((out = fopen(fname, "a")) == NULL) {
		printf("Ошибка открытия файла для записи");
		return 0;
	}
	fprintf(out,str);
	fclose(out);
	return 0;
}