#include <iostream>
#include <string>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

//////////////////////////////////////////////////////////////////////

// ������ ��������� ������ ����� ������
template <class t>
void print(t);
// ������ ��������� ������ � ���� ���������
template <class t>
void printBraces(t);


// ���������� �� ����������� ���� ��������� ������
string sort(string);
// �������� ������������� ��������� ������
string clean(string);


// ������� 17; Bin - ��� ������ � ������������������� ���������
string arrayR(string, string, string);
string arrayRBin(string, string, string);
// A / B
string razn(string, string);
string raznBin(string, string);
// A ��� B
string AorB(string, string);
string AorBBin(string, string);
// �������� ������������������� �������
string makeVector(string, string);

//////////////////////////////////////////////////////////////////////

class Stroka
{
private:
	string str;	// ����������� ������
	string a;	// ������-�������
public:
	Stroka();

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

	Stroka A;
	Stroka B;
	Stroka C;

	// �������� ��������� R (������� 17)
	cout << "R = ";
	printBraces(arrayR(A.get(), B.get(), C.get()));

	// ������ "�������"
	string u = AorB(A.get(), B.get());
	u = AorB(u, C.get());
	print(u);
	string av = makeVector(u, A.get());
	string bv = makeVector(u, B.get());
	string cv = makeVector(u, C.get());
	print(av);
	print(bv);
	print(cv);
	print(arrayRBin(av, bv, cv));

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

string raznBin(string a, string b)
{
	string r;
	int i = 0;
	while (i < a.length())
	{
		if (a[i] == b[i]) r.push_back('0');
		else r.push_back(a[i]);
		++i;
	}
	return r;
}
string AorBBin(string a, string b)
{
	string r;
	int i = 0;
	while (i < a.length())
	{
		if (a[i] == '1' || b[i] == '1') r.push_back('1');
		else r.push_back('0');
		++i;
	}
	return r;
}
string arrayRBin(string a, string b, string c)
{
	string r;
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
string makeVector(string a1, string a2)
{
	string v;
	int i = 0, j = 0;
	while (i < a1.length())
	{
		if (j >= a2.length())
		{
			v.push_back('0');
			++i;
		}
		else if (a1[i] == a2[j])
		{
			v.push_back('1');
			++i;
			++j;
		}
		else if (a1[i] < a2[j])
		{
			v.push_back('0');
			++i;
		}
		else
		{
			v.push_back('0');
			++j;
		}
	}
	return v;
}

//////////////////////////////////////////////////////////////////////

Stroka::Stroka()
{
	set();
	a = sort(str);
	a = clean(a);
}