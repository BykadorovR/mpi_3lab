#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <mmsystem.h>
#include "geometryOfHulls.h"
#include "point.h"
#include "line.h"
#include <vector>
//Подключаем библиотеку
#pragma comment(lib,"winmm.lib")
//Определяем путь файла
#define NAME_OF_FILE "C:\\mpi_3lab\\linearseparability.txt"
#define NAME_OF_FILE_MANUAL_INPUT "C:\\mpi_3lab\\manualinput.txt"

using namespace std;

int main (int argc, const char *argv[]) {
	int countOfPoints1=0, countOfPoints2=0;
	fstream fileStream;
	DWORD timeStart;
	GeometryOfHulls geom;
	vector<point> s1;
	vector<point> s2;
	srand(1);
	//Записываем начальные значения width, height и coeff

	int mode;
	cout<<"Enter mode"<<endl;
	cin>>mode;

	//Запускаем таймер
	timeStart = timeGetTime();

	if (mode == 1) {
		if (argc>1){
			countOfPoints1 = atoi(argv[1]);
			countOfPoints2 = atoi(argv[2]);
		}

		s1 = vector<point> (countOfPoints1);
		s2 = vector<point> (countOfPoints2);
		//Открываем файл для записи
		fileStream.open(NAME_OF_FILE, ios::in | ios::out | ios::binary | ios::trunc);
		if (fileStream.fail()){
			cout<<"Error opening "<<NAME_OF_FILE<<endl;
			exit(1);
		}

		//Инициализируем случайными значениями
		for (int i=0; i<countOfPoints1; i++)
			s1[i].setPosition(static_cast<double>((1+rand()%1000)*0.1), static_cast<double>((1+rand()%1000)*0.1));


		for (int i=0; i<countOfPoints2; i++)
			s2[i].setPosition(static_cast<double>((1+rand()%1000)*0.1), static_cast<double>((1+rand()%1000)*0.1));


		//Записываем матрицу в файл
		fileStream<<"Координаты первого множества";
		fileStream<<"\r\n";
		for (int i=0; i<countOfPoints1; i++){
			fileStream<<s1[i].getX()<<" ";
			fileStream<<s1[i].getY()<<" ";
			fileStream<<"\r\n";
		}

		fileStream<<"Координаты второго множества";
		fileStream<<"\r\n";
		for (int i=0; i<countOfPoints2; i++){
			fileStream<<s2[i].getX()<<" ";
			fileStream<<s2[i].getY()<<" ";
			fileStream<<"\r\n";
		}

	} else if (mode == 2) {

	//Открываем файл для чтения
		fileStream.open(NAME_OF_FILE_MANUAL_INPUT);
		if (fileStream.fail()){
			cout<<"Error opening "<<NAME_OF_FILE_MANUAL_INPUT<<endl;
			exit(1);
		}
		fileStream>>countOfPoints1;
		//cout<<countOfPoints1<<" ";
		s1 = vector<point>(countOfPoints1);
		for (int i=0; i<countOfPoints1; i++) {
			double valueFromFile;
			fileStream>>valueFromFile;
			s1[i].setPosition(valueFromFile, s1[i].getY());
			fileStream>>valueFromFile;
			s1[i].setPosition(s1[i].getX(), valueFromFile);

		}
		fileStream>>countOfPoints2;
		//cout<<countOfPoints2<<" ";
		s2 = vector<point>(countOfPoints2);
		for (int i=0; i<countOfPoints2; i++) {
			double valueFromFile;
			fileStream>>valueFromFile;
			s2[i].setPosition(valueFromFile, s2[i].getY());
			fileStream>>valueFromFile;
			s2[i].setPosition(s2[i].getX(), valueFromFile);
		}
	}
	vector<int> hull1;
	geom.quickHull(s1, hull1);


    for (int i=0; i<hull1.size(); i++)
    	cout<<hull1[i]<<endl;
	DWORD timeEnd=timeGetTime();
	DWORD time=timeEnd-timeStart;
	//Выводим время выполнения
	cout<<"Elapsed time: "<< (double) time/1000<<endl;
	//Закрываем файл
	fileStream.close();
	getch();
	return 0;
}