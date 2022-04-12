#include <iostream>
#include <vector>
#include <Windows.h>

using std::cout;
using std::cin;
using std::vector;

void printBin(vector<int>);
vector<int> makeR(vector<int>);

class Array
{
private:
	vector<int> arr;

public:
	Array(int);
	void set();
	vector<int> get() { return arr; }
	void sort();
	void checkRepeat();
	bool inArr(int, int);
};



int main()
{
	int N;
	cin >> N;
	Array A(N);
	vector<int> R = makeR(A.get());
	printBin(R);

	return 0;
}



Array::Array(int n)
{
	arr.resize(n);
	set();
	checkRepeat();
	sort();
}

void Array::set()
{
	for (int i = 0; i < arr.size(); ++i)
	{
		cin >> arr[i];
	}
}
void Array::sort()
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
void Array::checkRepeat()
{
	int a;
	for (int i = 0; i < arr.size(); ++i)
	{
		while (inArr(arr[i], 2))
		{
			cout << "Ѕыл введен повтор€ющийс€ элемент.\n¬ведите еще число: ";
			cin >> a;
			if (!inArr(a, 1)) arr[i] = a;
		}
	}
}
bool Array::inArr(int a, int count)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		if (a == arr[i]) --count;
		if (count <= 0) return true;
	}
	return false;
}

vector<int> makeR(vector<int> arr)
{
	vector<int> r;
	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = 0; j < arr.size(); ++j)
		{
			if ((arr[i] - arr[j]) % 3 == 0 && arr[i] != arr[j])
			{
				r.push_back(arr[i]);
				r.push_back(arr[j]);
			}
		}
	}
	return r;
}
void printBin(vector<int> a)
{
	for (int i = 0; i < a.size(); i += 2)
	{
		cout << '(' << a[i] << ", " << a[i + 1] << ')';
	}
}