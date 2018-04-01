// MyOpenKeys.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "iostream"
#include <vector>

using namespace std;

unsigned long long findSimilarElement(unsigned long long);
unsigned long long newOpenKey(unsigned long long, unsigned long long, unsigned long long);
unsigned long long myPow(unsigned long long, unsigned long long);

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	cout << "������� p:" << endl;
	unsigned long long p;
	cin >> p;
	unsigned long long a;
	a = findSimilarElement(p);
	cout << "��������� ����������� ������� ��������� ���� (a): " << a << endl;
	cout << "������� ��������� ����� ����� " << "(1 < x < " << p-1 << ")" << ": " << endl;
	unsigned long long xA;
	cin >> xA;
	cout << "������� ��������� ����� ���� " << "(1 < x < " << p-1 << ")" << ": " << endl;
	unsigned long long xB;
	cin >> xB;
	unsigned long long yA = newOpenKey(a, xA, p);
	cout << "��������� �������� ���� ����� - " << yA << endl;
	unsigned long long yB = newOpenKey(a, xB, p);
	cout << "��������� �������� ���� ���� - " << yB << endl;
	unsigned long long zA = newOpenKey(yB, xA, p);
	cout << "��������� ��������� ���� �����/��� - " << zA << endl;
	unsigned long long zB = newOpenKey(yA, xB, p);
	cout << "��������� ��������� ���� ���/����� - " << zB << endl;
	system("pause");
	return 0;
}

unsigned long long findSimilarElement(unsigned long long p){
	for(unsigned long long iter = 2; iter <= p; iter++){
		vector<bool> vectorOfNumbers(p);
		try{
			for(unsigned long long x = 1; x <= p - 1; x++){
				unsigned long long curentNumber = newOpenKey(iter, x, p);
				if(vectorOfNumbers[curentNumber] != 0)
					throw(false);
				vectorOfNumbers[curentNumber] = true;
			}
		}
		catch(bool answer){
			continue;
		}
		return iter;
	}
}

unsigned long long newOpenKey(unsigned long long a, unsigned long long x, unsigned long long p){
	//��������� �������� ���� �������� �� �������� ���������
	vector<unsigned long long> beginMasOfDegrees; 
	vector<unsigned long long> finalMasOfDegrees;
	beginMasOfDegrees.push_back(1); //������� �������
	beginMasOfDegrees.push_back(a); //������ �������
	unsigned long long higherDegree;
	for(higherDegree = 2; higherDegree <= x; higherDegree = higherDegree * 2)
		beginMasOfDegrees.push_back(myPow(beginMasOfDegrees.back(), 2) % p);

	//�������� ������ ��� �������
	unsigned long long currentX = x;
	if(x % 2 != 0){ //���� ��������� ������� - ��������,
		finalMasOfDegrees.push_back(a); //�� ������ � �������� ������ a
		currentX--;
	}
	for(unsigned long long iter = beginMasOfDegrees.size(), currentDegree = higherDegree; iter > 1; iter--, currentDegree = currentDegree / 2)
		if(currentDegree <= currentX){ //���� ������� ������� ������ ������ ��� ����� x,
			finalMasOfDegrees.push_back(beginMasOfDegrees[iter]); //�� ������� � �������� ������ ��������������� ������� �� ���������� �������
			currentX = currentX - currentDegree; //� �������� ��� ���������� �������
		}

	//��������� ������������ ��������� ��������
	unsigned long long finalNumber = 1;
	for(unsigned long long iter = 0; iter < finalMasOfDegrees.size(); iter++)
		finalNumber = (finalNumber * finalMasOfDegrees[iter]) % p;

	return finalNumber;
}

unsigned long long myPow(unsigned long long a, unsigned long long x){
	unsigned long long result = 1;
	for(unsigned long long iter = 0; iter < x; iter++)
		result = result * a;
	return result;
}