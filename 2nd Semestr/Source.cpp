#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <Windows.h>

using std::cout;
using std::cin;
using std::vector;
using std::string;


void printBraces(vector<int>&);
template<class t>
void printSpaces(t, int);
void printSpaces(int);
void sort(vector<int>&);
void multiMatrix(vector<vector<bool>>, vector<vector<bool>>);


class Array
{
private:
	vector<int> arr;
	vector<int> R;
	vector<vector<bool>> matrixR;
	string Reflexivity;
	string Symmetry;
	string Transitivity;

public:
	Array(int);
	void set();
	void checkRepeat();
	void makeR();
	void makeMatrixR();
	void printMatrix();
	void properties();
	bool inArr(int, int, int);
	vector<int> getArr() { return arr; }
	vector<int> getR() { return R; }
	vector<vector<bool>> getMatrixR() { return matrixR; }
};

//////////////////////////////////////////////////////////////////////

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cin >> N;
	Array A(N);

	cout << '\n';
	A.printMatrix();

	return 0;
}

//////////////////////////////////////////////////////////////////////

Array::Array(int n)
{
	arr.resize(n);
	set();
	checkRepeat();
	sort(arr);
	makeR();
	makeMatrixR();
}
void Array::set()
{
	for (int i = 0; i < arr.size(); ++i)
	{
		cin >> arr[i];
	}
}
void Array::checkRepeat()
{
	int a;
	for (int i = 0; i < arr.size(); ++i)
	{
		while (inArr(arr[i], 2, i))
		{
			cout << "Был введен повторяющийся элемент.\nВведите еще число: ";
			cin >> a;
			if (!inArr(a, 1, 0)) arr[i] = a;
		}
	}
}
void Array::makeR()
{
	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = 0; j < arr.size(); ++j)
		{
			if ((arr[i] - arr[j]) % 3 == 0 && arr[i] != arr[j])
			{
				R.push_back(arr[i]);
				R.push_back(arr[j]);
			}
		}
	}
}
void Array::makeMatrixR()
{
	for (int i = 0, k = 0; i < arr.size(); ++i)
	{
		vector<bool> matrixRi;
		for (int j = 0; j < arr.size(); ++j)
		{
			if (k != R.size())
			{
				if (arr[i] == R[k] && arr[j] == R[k + 1])
				{
					matrixRi.push_back(true);
					k += 2;
				}
				else
				{
					matrixRi.push_back(false);
				}
			}
			else
			{
				matrixRi.push_back(false);
			}
		}
		matrixR.push_back(matrixRi);
	}
}
void Array::printMatrix()
{
	// maxLenCount хранит длину для печати элемента матрицы (максимальное кол-во цифр в числе + 1 для пробела)
	int maxLenCount = 1;
	for (int i = arr[arr.size() - 1]; i > 0; i /= 10) ++maxLenCount;

	// Печатаем первую строку с перечислением всех элементов
	printSpaces(maxLenCount);
	for (int i = 0; i < arr.size(); ++i)
	{
		cout << '|';
		printSpaces(arr[i], maxLenCount);
	}
	cout << '\n';

	// Печатаем строку из дефисов
	for (int i = 0; i < (maxLenCount + 1) * arr.size() + maxLenCount; ++i) cout << '-';
	cout << '\n';

	// Печатаем саму матрицу с перечислением всех элементов
	for (int i = 0; i < arr.size(); ++i)
	{
		printSpaces(arr[i], maxLenCount);
		cout << '|';
		for (int j = 0; j < arr.size(); ++j)
		{
			printSpaces(matrixR[i][j], maxLenCount);
			if (j < arr.size() - 1) cout << ' ';
		}
		cout << '\n';
	}
}
void Array::properties()
{
	int countRef = 0, countSym = 0, countTran = 0;
	bool ref = true, sym = true, tran = true, flag = true;
	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = 0; j < arr.size(); ++j)
		{
			// Проверка на рефлексивность
			if (!matrixR[i][i]) ref = false;
			else ++countRef;

			// Проверка на симметричность
			if (matrixR[i][j] != matrixR[j][i]) sym = false;
			else ++countSym;

			if (countRef > 0 && countSym > 0 && !ref && !sym)
			{
				flag = false;
				break;
			}
		}
		if (!flag) break;
	}

	if (ref) Reflexivity = "Рефлексивно";
	else if (ref == false && countRef > 0) Reflexivity = "Нерефлексивно";
	else Reflexivity = "Антирефлексивно";

	if (sym) Symmetry = "Симметрично";
	else if (sym == false && countSym > 0) Symmetry = "Несимметрично";
	else Symmetry = "Антисимметрично";

	// Проверка на транзитивность
}
bool Array::inArr(int a, int count, int beg)
{
	for (int i = beg; i < arr.size(); ++i)
	{
		if (a == arr[i]) --count;
		if (count <= 0) return true;
	}
	return false;
}


void sort(vector<int>& arr)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		bool flag = false;
		for (int j = 0; j < arr.size() - 1; ++j)
		{
			if (arr[j + 1] < arr[j])
			{
				arr[j + 1] += arr[j];
				arr[j] = arr[j + 1] - arr[j];
				arr[j + 1] -= arr[j];
				flag = true;
			}
		}
		if (!flag) break;
	}
}
void printBraces(vector<int> &a)
{
	for (int i = 0; i < a.size(); i += 2)
	{
		if (i > 0) cout << ' ';
		cout << '(' << a[i] << ", " << a[i + 1] << ')';
	}
}
template<class t>
void printSpaces(t a, int len)
{
	int lenA = 0;
	if (a == false || a == true) lenA = 1;
	else
	{
		for (int i = a; i > 0; i /= 10) ++lenA;
	}
	for (int i = 0; i < len - lenA; ++i) cout << ' ';
	cout << a;
}
void printSpaces(int len)
{
	for (int i = 0; i < len; ++i) cout << ' ';
}