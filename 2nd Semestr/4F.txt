#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

template <class t>
t max_elem_pos(vector<t> a);
template <class t>
t min_elem_pos(vector<t> a);

int main()
{
	vector<int> arr;
	int max_pos, min_pos, n;
	cin >> n;
	arr.resize(n);
	for (int i = 0; i < n; ++i) cin >> arr[i];

	max_pos = max_elem_pos(arr);
	min_pos = min_elem_pos(arr);
	if (max_pos + min_pos <= arr.size()) cout << arr[max_pos + min_pos - 1];
	else cout << "Vne massiva";

	return 0;
}

template <class t>
t max_elem_pos(vector<t> a)
{
	int pos = 0, max = -1;
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] > max)
		{
			max = a[i];
			pos = i;
		}
	}
	return ++pos;
}
template <class t>
t min_elem_pos(vector<t> a)
{
	int pos = 0, min = 1000;
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] < min)
		{
			min = a[i];
			pos = i;
		}
	}
	return ++pos;
}