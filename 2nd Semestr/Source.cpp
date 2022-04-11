#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

//////////////////////////////////////////////////////////////////////

// ������ ��������� ������ ����� ������
template <class t>
void print(t);
// ������ ��������� ������ � ���� ���������
template <class t>
void printBraces(t);
// ���������� ���� ���������� ���������-����� ��� ������ ���������
template <class t1, class t2>
void printBraces(t1, t2);


// ���������� �� ����������� ���� ��������� ������
string sort(string);
// �������� ������������� ��������� ������
string clean(string);


// ������� 17; Bin - ��� ������ � ������������������� ���������
string arrayR(string, string, string);
vector<bool> arrayRBin(vector<bool>, vector<bool>, vector<bool>);
// A / B
string razn(string, string);
vector<bool> raznBin(vector<bool>, vector<bool>);
// A ��� B
string AorB(string, string);
vector<bool> AorBBin(vector<bool>, vector<bool>);
// �������� ������������������� �������
vector<bool> makeVector(string, string);

//////////////////////////////////////////////////////////////////////

class Alphabet
{
private:
	string str;	// ����������� ������
	string a;	// ������-�������
public:
	Alphabet();

	// ������ ������
	void set() { cin >> str; }
	// ���������� ������-�������
	string get() { return a; }
};

//////////////////////////////////////////////////////////////////////

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Alphabet A;
	Alphabet B;
	Alphabet C;

	string u = AorB(A.get(), B.get());
	u = AorB(u, C.get());
	vector<bool> av = makeVector(u, A.get());
	vector<bool> bv = makeVector(u, B.get());
	vector<bool> cv = makeVector(u, C.get());
	vector<bool> rv = arrayRBin(av, bv, cv);
	printBraces(u, rv);

	system("pause");
	return 0;
}

//////////////////////////////////////////////////////////////////////

template <class t>
void print(t str)
{
	for (int i = 0; i < str.size(); ++i)
	{
		if (i < str.size() - 1) cout << str[i] << ' ';
		else cout << str[i];
	}
	cout << endl;
}
template <class t>
void printBraces(t str)
{
	cout << "{";
	for (int i = 0; i < str.size(); ++i)
	{
		if (i < str.size() - 1) cout << str[i] << ", ";
		else cout << str[i] << "}" << endl;
	}
}
template <class t1, class t2>
void printBraces(t1 str, t2 mask)
{
	int i = 0;
	bool firstElement = true;
	cout << '{';
	for (i; i < str.size(); ++i)
	{
		if (mask[i] == '1' || mask[i] == 1 || mask[i] == true)
		{
			if (!firstElement) cout << ", ";
			if (i < str.size() - 1) cout << str[i];
			firstElement = false;
		}
	}
	if (mask[i - 1] == '1' || mask[i - 1] == 1 || mask[i - 1] == true)
		cout << str[i - 1] << '}' << endl;
	else cout << '}' << endl;
}

string razn(string a, string b)
{
	string r;
	int i = 0, j = 0;
	while (j < b.length())
	{
		if (a[i] == b[j])
		{
			++i;
			++j;
		}
		else if (a[i] < b[j])
		{
			r.push_back(a[i]);
			++i;
		}
		else if (a[i] > b[j])
		{
			++j;
		}
	}
	return r;
}
string AorB(string a, string b)
{
	string r;
	int i = 0, j = 0;
	while (i < a.length() && j < b.length())
	{
		if (a[i] < b[j])
		{
			r.push_back(a[i]);
			++i;
		}
		else if (a[i] == b[j])
		{
			r.push_back(a[i]);
			++i;
			++j;
		}
		else if (a[i] > b[j])
		{
			r.push_back(b[j]);
			++j;
		}
	}
	if (i == a.length())
		for (j; j < b.length(); ++j) r.push_back(b[j]);
	else
		for (i; i < a.length(); ++i) r.push_back(a[i]);
	return r;
}
string arrayR(string a, string b, string c)
{
	string r;
	r = razn(c, b);
	r = AorB(r, a);
	return r;
}

vector<bool> raznBin(vector<bool> a, vector<bool> b)
{
	vector<bool> r;
	r.resize(a.size());
	int i = 0;
	while (i < a.size())
	{
		if (a[i] == b[i]) r[i] = false;
		else r[i] = a[i];
		++i;
	}
	return r;
}
vector<bool> AorBBin(vector<bool> a, vector<bool> b)
{
	vector<bool> r;
	r.resize(a.size());
	int i = 0;
	while (i < a.size())
	{
		if (a[i] == true || b[i] == true) r[i] = true;
		else r[i] = false;
		++i;
	}
	return r;
}
vector<bool> arrayRBin(vector<bool> a, vector<bool> b, vector<bool> c)
{
	vector<bool> r;
	r = raznBin(c, b);
	r = AorBBin(r, a);
	return r;
}

string sort(string a)
{
	for (int i = 0; i < a.length(); ++i)
	{
		bool flag = false;
		for (int j = 0; j < a.length() - 1; ++j)
		{
			if (a[j + 1] < a[j])
			{
				a[j + 1] += a[j];
				a[j] = a[j + 1] - a[j];
				a[j + 1] -= a[j];
				flag = true;
			}
		}
		if (!flag) break;
	}
	return a;
}
string clean(string a)
{
	string clean_a;
	int i;
	for (i = 0; i < a.length() - 1; ++i)
	{
		if (a[i] != a[i + 1]) clean_a.push_back(a[i]);
	}
	clean_a.push_back(a[i]);
	return clean_a;
}
vector<bool> makeVector(string a1, string a2)
{
	vector<bool> v;
	v.resize(a1.size());
	int i = 0, j = 0, count = 0;
	while (i < a1.length())
	{
		if (j >= a2.length() || a1[i] < a2[j])
		{
			v[count] = false;
			++i;
		}
		else if (a1[i] == a2[j])
		{
			v[count] = true;
			++i;
			++j;
		}
		else
		{
			v[count] = false;
			++j;
		}
		++count;
	}
	return v;
}

//////////////////////////////////////////////////////////////////////

Alphabet::Alphabet()
{
	set();
	a = sort(str);
	a = clean(a);
}