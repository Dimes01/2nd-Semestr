#include <iostream>
#include <vector>
#include <string>
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


class Array
{
protected:
	vector<int> arr;
	vector<int> R;
	int Size;

public:
	Array();
	void set(int);
	void checkRepeat();
	void makeR();
	bool inArr(int, int, int);
	vector<int> getArr() { return arr; }
	vector<int> getR() { return R; }
	int getSize() { return Size; }
};


class Matrix : public Array
{
private:
	vector<vector<bool>> mtrx;
	string Reflexivity;
	string Symmetry;
	string Transitivity;


public:
	Matrix() {}
	Matrix(const Array&);
	void properties();
	void printMatrix();
	Matrix operator * (const Matrix&);
	Matrix & operator = (const Matrix&);

};

//////////////////////////////////////////////////////////////////////

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Array A;
	int N;

	cin >> N;
	A.set(N);
	A.makeR();

	Matrix M(A);
	M.printMatrix();

	return 0;
}

//////////////////////////////////////////////////////////////////////

Array::Array()
{
	Size = 0;
}
void Array::set(int N)
{
	Size = N;
	arr.resize(Size);
	for (int i = 0; i < arr.size(); ++i)
	{
		cin >> arr[i];
	}
	checkRepeat();
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
bool Array::inArr(int a, int count, int beg)
{
	for (int i = beg; i < arr.size(); ++i)
	{
		if (a == arr[i]) --count;
		if (count <= 0) return true;
	}
	return false;
}


Matrix::Matrix(const Array & A)
{
	for (int i = 0; i < Size; ++i)
	{
		vector<bool> a;
		a.resize(Size);
		for (int j = 0, k = 0; i < Size; ++j)
		{
			if (k < R.size()) a[j] = (i == R[k] && j == R[k + 1]);
			else a[j] = false;
			if (a[j] == true) k += 2;
		}
		mtrx[i] = a;
	}
}
void Matrix::properties()
{
	bool ref = true, sym = true;
	int countref = 0, countsym = 0;

	for (int i = 0; i < Size; ++i)
	{
		// Проверка на рефлексивность
		if (!mtrx[i][i]) ref = false;
		else ++countref;

		// Проверка на симметричность
		for (int j = 0; j < Size; ++j)
		{
			if (mtrx[i][j] != mtrx[j][i]) sym = false;
			else ++countsym;
		}
	}

	if (ref) Reflexivity = "Рефлексивно";
	else if (!countref) Reflexivity = "Антирефлексивно";
	else Reflexivity = "Нерефлексивно";

	if (sym) Symmetry = "Симметрично";
	else if (!countsym) Symmetry = "Антисимметрично";
	else Symmetry = "Несимметрично";
}
void Matrix::printMatrix()
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
			printSpaces(mtrx[i][j], maxLenCount);
			if (j < arr.size() - 1) cout << ' ';
		}
		cout << '\n';
	}
}
Matrix Matrix::operator* (const Matrix& other)
{
	Matrix temp;
	this->Size = other.Size;
	this->Reflexivity = other.Reflexivity;
	arr.resize(this->Size);
	for (int i = 0; i < this->Size; ++i)
	{
		vector<bool> m;
		m.resize(this->Size);
		for (int j = 0; j < this->Size; ++j)
		{
			for (int k = 0; k < this->Size; ++k)
			{
				m[j] = mtrx[j][k] && mtrx[k][j];
				if (m[j]) break;
			}
		}
		mtrx[i] = m;
	}
	return temp;
}
Matrix & Matrix::operator= (const Matrix& other)
{
	this->Size = other.Size;
	for (int i = 0; i < this->Size; ++i)
	{
		for (int j = 0; i < this->Size; ++j)
		{
			this->mtrx[i][j] = other.mtrx[i][j];
		}
	}

	return *this;
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