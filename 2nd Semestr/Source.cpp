#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

vector<bool> nextShuffleBin(vector<bool>, bool&);
vector<bool> shuffleBin(int, int);

template <class t>
ostream& operator<< (ostream& os, const vector<t>& a);
template <class t>
istream& operator>> (istream& os, vector<t>& a);



int main()
{
	int n, k;
	cin >> n >> k;
	vector<bool> a = shuffleBin(n, k);
	cout << a << endl;

	bool hasNextShuffle = true;
	vector<bool> b;
	b.resize(n);
	while (hasNextShuffle)
	{
		b = nextShuffleBin(a, hasNextShuffle);
		a = b;
		if (hasNextShuffle) cout << b << endl;
	}

	return 0;
}



vector<bool> nextShuffleBin(vector<bool> a, bool &hasNextShuffle)
{
	int i = a.size() - 1;
	int first = -1;
	int second;

	// ??????? ??????????? ??????????????????
	int count = 0;
	for (i; i > 0; --i)
	{
		if (a[i] && !count) second = i;
		if (a[i]) ++count;
		if (a[i] > a[i - 1])
		{
			first = i - 1;
			break;
		}
	}

	if (first == -1) hasNextShuffle = false;
	else
	{
		// ?????? ????????
		a[first] = true;
		a[second] = false;
		// ????????? count ?? 1, ?????? ??? ???? 1 ???? ?? ??????????? ? ????? ??????????????????
		--count;
		for (i = a.size() - 1; i > first; --i)
		{
			if (count)
			{
				a[i] = true;
				--count;
			}
			else a[i] = false;
		}
	}
	return a;
}

vector<bool> shuffleBin(int n, int k)
{
	vector<bool> a;
	a.resize(n);
	for (int i = n - 1; i > 0; --i)
	{
		if (i >= n - k) a[i] = true;
		else a[i] = false;
	}
	return a;
}

template <class t>
ostream& operator<< (ostream& os, const vector<t>& a)
{
	for (int i = 0; i < a.size(); ++i) os << a[i];
	return os;
}
template <class t>
istream& operator>> (istream& is, vector<t>& a)
{
	string s;
	cin >> s;
	a.resize(s.size());
	for (int i = 0; i < s.size(); ++i) a[i] = s[i] - 48;
	return is;
}