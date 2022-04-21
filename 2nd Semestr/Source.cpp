#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;


void printBraces(const vector<int>&);
template<class t>
void printSpaces(t, int, bool);
void sort(vector<int>&);

// �������� * ����������� �������
vector<vector<bool>> operator*(const vector<vector<bool>>&, const vector<vector<bool>>&);
// �������� <= ������������ "���������� � ..."
bool operator<=(const vector<vector<bool>>&, const vector<vector<bool>>&);


class Relation
{
private:

	vector<int> arr;					// ���������, �� ������� ���������� ���������
	vector<int> R;						// ���������
	vector<vector<bool>> matrixBin;		// ������� ���������
	string Reflexivity;
	string Symmetry;
	string Transitivity;
	int Size;

public:
	Relation() { Size = 0; };
	void set(int);
	void checkRepeat();
	void makeR();
	void makeMatrix();
	void properties();
	void printMatrix();
	bool inArr(int, int, int);
	void printProperties();
	vector<int> getArr() { return arr; }
	vector<int> getR() { return R; }

};

//////////////////////////////////////////////////////////////////////

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Relation A;
	int N;

	cin >> N;
	A.set(N);
	printBraces(A.getR());
	cout << endl;
	A.printMatrix();
	cout << endl;
	A.printProperties();

	return 0;
}

//////////////////////////////////////////////////////////////////////

void Relation::set(int N)
{
	Size = N;
	arr.resize(Size);
	matrixBin.resize(Size);
	for (int i = 0; i < arr.size(); ++i)
	{
		cin >> arr[i];
	}
	checkRepeat();
	sort(arr);
	makeR();
	makeMatrix();
	properties();
}
void Relation::checkRepeat()
{
	int a, i = 0;
	for (int i = 0; i < Size; ++i)
	{
		while (inArr(arr[i], 2, i))
		{
			cout << "��� ������ ������������� �������.\n������� ��� �����: ";
			cin >> a;
			if (!inArr(a, 1, 0)) arr[i] = a;
		}
	}
}
void Relation::makeR()
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
void Relation::makeMatrix()
{
	int k = 0;
	for (int i = 0; i < Size; ++i)
	{
		vector<bool> a;
		a.resize(Size);
		for (int j = 0; j < Size; ++j)
		{
			if (k < R.size()) a[j] = (arr[i] == R[k]) && (arr[j] == R[k + 1]);
			else a[j] = false;
			if (a[j] == true) k += 2;
		}
		matrixBin[i] = a;
	}
}
bool Relation::inArr(int a, int count, int beg)
{
	for (int i = beg; i < arr.size(); ++i)
	{
		if (a == arr[i]) --count;
		if (count <= 0) return true;
	}
	return false;
}
void Relation::printProperties()
{
	cout << Reflexivity << endl;
	cout << Symmetry << endl;
	cout << Transitivity << endl;
}
void Relation::properties()
{
	bool ref = true, sym = true;
	int countref = 0, countsym = 0;
	vector<vector<bool>> c = matrixBin * matrixBin;

	for (int i = 0; i < Size; ++i)
	{
		// �������� �� ��������������
		if (!matrixBin[i][i]) ref = false;
		else ++countref;

		// �������� �� ��������������
		for (int j = 0; j < Size; ++j)
		{
			if (matrixBin[i][j] != matrixBin[j][i]) sym = false;
			else ++countsym;
		}
	}

	if (ref) Reflexivity = "�����������";
	else if (!countref) Reflexivity = "���������������";
	else Reflexivity = "�������������";

	if (sym) Symmetry = "�����������";
	else if (!countsym) Symmetry = "���������������";
	else Symmetry = "�������������";

	if (c <= matrixBin) Transitivity = "�����������";
	else Transitivity = "�������������";
}
void Relation::printMatrix()
{
	// maxLenCount ������ ����� ��� ������ �������� ������� (������������ ���-�� ���� � ����� + 1 ��� �������)
	int maxLenCount = 1;
	for (int i = arr[arr.size() - 1]; i > 0; i /= 10) ++maxLenCount;

	// �������� ������ ������ � ������������� ���� ���������
	for (int i = 0; i < maxLenCount; ++i) cout << ' ';
	for (int i = 0; i < arr.size(); ++i)
	{
		cout << '|';
		printSpaces(arr[i], maxLenCount, false);
	}
	cout << '\n';

	// �������� ������ �� �������
	for (int i = 0; i < (maxLenCount + 1) * arr.size() + maxLenCount; ++i) cout << '-';
	cout << '\n';

	// �������� ���� ������� � ������������� ���� ���������
	for (int i = 0; i < arr.size(); ++i)
	{
		printSpaces(arr[i], maxLenCount, false);
		cout << '|';
		for (int j = 0; j < arr.size(); ++j)
		{
			printSpaces(matrixBin[i][j], maxLenCount, true);
			if (j < arr.size() - 1) cout << ' ';
		}
		cout << '\n';
	}
}


void printBraces(const vector<int> &a)
{
	for (int i = 0; i < a.size(); i += 2)
	{
		if (i > 0) cout << ' ';
		cout << '(' << a[i] << ", " << a[i + 1] << ')';
	}
	cout << endl;
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
vector<vector<bool>> operator*(const vector<vector<bool>>& a, const vector<vector<bool>>& b)
{
	vector<vector<bool>> c;
	c.resize(a.size());
	for (int i = 0; i < a.size(); ++i)
	{
		vector<bool> ci;
		ci.resize(a.size());
		for (int j = 0; j < ci.size(); ++j)
		{
			for (int k = 0; k < ci.size(); ++k)
			{
				ci[j] = a[i][k] && b[k][j];
				if (ci[j]) break;
			}
		}
		c[i] = ci;
	}
	return c;
}
bool operator<=(const vector<vector<bool>>& a, const vector<vector<bool>>& b)
{
	for (int i = 0; i < a.size(); ++i)
	{
		for (int j = 0; j < a.size(); ++j)
		{
			if (!a[i][j] && b[i][j]) return false;
		}
	}
	return true;
}


template<class t>
void printSpaces(t a, int len, bool flag = false)
{
	int lenA;
	if (flag) lenA = 1;
	else
	{
		lenA = 0;
		for (int i = a; i > 0; i /= 10) ++lenA;
	}
	for (int i = 0; i < len - lenA; ++i) cout << ' ';
	cout << a;
}