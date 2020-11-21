#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////

#define co cout<<
#define ci cin>>
#define en << endl
#define skip cout<<endl
#define cl system("cls")
#define s cout << setw(4)

////////////////////////////////////////////////////////////////////////////////////

class SortX
{
public:
	template<class T, class K, class R >
	static void Generate(T& arr, K size, R rnd, bool plus);

	template<class T, class K>
	static void Show(T arr, K size);

	/////////////////////////////////////////////

	static int comparison;
	static int assign;
	static int _swap;

	template<class T, class K>
	static bool com(T el1, K el2)
	{
		SortX::comparison += 1;
		return el1 < el2;
	}

	template<class T, class K, class Pred>
	static bool comPred(T el1, K el2, Pred pr)
	{
		SortX::comparison += 1;
		return pr(el1,el2);
	}

	template<class T, class K>
	static void ass(T &el1, K el2)
	{
		SortX::assign += 1;
		el1 = el2;
	}

	template<class T>
	static void swp(T& el1, T &el2)
	{
		SortX::_swap += 1;
		swap(el1, el2);
	}

	static void GetStat()
	{
		skip;
		co "Comparison: " << comparison en;
		co "Assign: " << assign en;
		co "Swp: " << _swap en;
		skip;
	}

	/////////////////////////////////////////////

	template<class T, class K>
	static void BubbleSort(T& arr, K size);

	template<class T, class K>
	static void SelectionSort(T& arr, K size);

	template<class T, class K>
	static void InsertionSort(T& arr, K size);

	template<class T, class K>
	static void MergeSort(T arr, K size);

	template<class T, class K>
	static void HeapSort(T& arr, K n);

	template<class T, class K>
	static void PigeonholeSort(T& arr, K n);

	template<class T, class K>
	static void QuickSort(T& arr, K size);

	template<class T, class K>
	static void ShellSort(T& arr, K size);

	template<class T, class K>
	static void BuccketSort(T arr, K size);

	template<class T, class K>
	static void RadixSort(T& arr, K size);

	template<class T, class K>
	static void ShakerSort(T& arr, K size);



	template<class T, class K>
	static void LinearSearch(T& arr, K n, K el);

	template<class T, class K>
	static void BinarySearch(T& arr, K n, K el);


private:
	template<class T, class K>
	static void Merge(T arr, K p, K q, K r);
	
	template<class T, class K>
	static void MergeX(T arr, K l, K r);

	/////////////////////////////////////////////

	template<class T, class K>
	static void Heapify(T& arr, K n, K i);

	/////////////////////////////////////////////

	template<class T, class K>
	static int QuickSortPart(T& arr, K low, K high);

	template<class T, class K>
	static void QuickSortX(T& arr, K low, K high);

	/////////////////////////////////////////////

	template<class T, class K>
	static K GetMax(T arr, K size);

	template<class T, class K>
	static bool GetMin(T arr, K size);

	template<class T, class K>
	static void BuccketRadix(T& arr, K size, K place, bool pluss);

	/////////////////////////////////////////////


};

int SortX::comparison = 0;
int SortX::assign = 0;
int SortX::_swap = 0;

////////////////////////////////////////////////////////////////////////////////////
//Generate

template<class T, class K, class R >
static void SortX::Generate(T& arr, K size, R rnd, bool plus)
{
	int k = 0;
	k > size;
	srand(time(nullptr));

	for (K i = 0; i < size; i++)
	{
		if (plus)
		{
			arr[i] = rand() % rnd;
		}
		else
		{
			arr[i] = (rand() % rnd) - rnd/2;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
//Show

template<class T, class K>
static void SortX::Show(T arr, K size)
{
	skip;
	co "___________________________________________________________________________________________________" en;
	skip;

	for (K i = 0; i < size; i++)
	{
		co arr[i] << " ";
	}

	skip;
	co "___________________________________________________________________________________________________" en;
	skip;
}

////////////////////////////////////////////////////////////////////////////////////
//BubbleSort

template<class T, class K>
static void SortX::BubbleSort(T& arr, K size)
{
	for (K i = 0; i < size - 1; i++)
		for (K j = i; j < size; j++)
			if (SortX::comPred(arr[j], arr[i], [](auto x, auto y) {return x > y; })) SortX::swp(arr[j], arr[i]);
}

////////////////////////////////////////////////////////////////////////////////////
	//SelectionSort

template<class T, class K>
static void SortX::SelectionSort(T& arr, K size)
{
	K g;
	for (K i = 0; i < size - 1; i++)
	{
		g = i;

		for (K j = i + 1; j < size; j++)
		{
			if (SortX::comPred(arr[g],arr[j],[](auto x, auto y) {return x > y; })) g = j;
		}
		SortX::swp(arr[g], arr[i]);
	}
}

////////////////////////////////////////////////////////////////////////////////////
//InsertionSort

template<class T, class K>
static void SortX::InsertionSort(T& arr, K size)
{
	K g, tmp;

	for (K i = 1; i < size; i++)
	{
		g = i - 1;
		SortX::ass(tmp,arr[i]);

		while (g >= 0 && SortX::comPred(tmp, arr[g], [](auto x, auto y) {return x < y; }))
		{
			SortX::swp(arr[g], arr[g + 1]);
			--g;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
//QuickSort

template<class T, class K>
static int SortX::QuickSortPart(T& arr, K low, K high)
{
	K pivot = arr[high];
	K g = low - 1;

	for (size_t i = low; i < high; i++)
	{
		if (SortX::comPred(arr[i], pivot, [](auto x, auto y) {return x <= y; }))
		{
			g++;
			swp(arr[g], arr[i]);
		}
	}
	swp(arr[g + 1], arr[high]);
	return(g + 1);
}

template<class T, class K>
static void SortX::QuickSortX(T& arr, K low, K high)
{
	if (low < high)
	{
		K pi = QuickSortPart(arr, low, high);

		QuickSortX(arr, pi + 1, high);
		QuickSortX(arr, low, pi - 1);

	}
}

template<class T, class K>
static void SortX::QuickSort(T& arr, K size)
{
	QuickSortX(arr, static_cast<K>(0), size - 1);
}

////////////////////////////////////////////////////////////////////////////////////
	//ShellSort

template<class T, class K>
static void SortX::ShellSort(T& arr, K size)
{
	for (K interval = size / 2; interval > 0; interval /= 2)
	{
		for (K i = interval; i < size; i++)
		{
			K tmp = arr[i];
			K j = i;

			for (; j >= interval && SortX::com(arr[j - interval], tmp); j -= interval)
			{
				SortX::ass(arr[j], arr[j - interval]);
			}

			SortX::ass(arr[j],tmp);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
	//RadixSort

template<class T, class K>
static K SortX::GetMax(T arr, K size)
{
	K max = arr[0];
	for (K i = 1; i < size; i++) if (arr[i] > max) max = arr[i];
	return max;
}

template<class T, class K>
static bool SortX::GetMin(T arr, K size)
{
	for (K i = 0; i < size; i++) if (arr[i] < 0) return false;
}

template<class T, class K>
static void SortX::BuccketRadix(T& arr, K size, K place, bool pluss)
{
	vector<K> output(size);

	if (!pluss)
	{
		K countPlus[10] = { 0,0,0,0,0,0,0,0,0,0 };
		K countMinus[10] = { 0,0,0,0,0,0,0,0,0,0 };

		K j = 0;
		for (K i = 0; i < size; i++)
		{
			if (arr[i] > 0)
			{
				countPlus[(arr[i] / place) % 10]++;
			}
			else
			{
				countMinus[(abs(arr[i]) / place) % 10]++;
				++j;
			}
		}
		countPlus[0] += j;
		for (K i = 1; i < 10; i++)
		{
			countPlus[i] += countPlus[i - 1];
			countMinus[9 - i] += countMinus[9 - i + 1];
		}

		for (K i = size - 1; i >= 0; i--)
		{
			if (arr[i] >= 0)
			{
				output[countPlus[(arr[i] / place) % 10] - 1] = arr[i];
				countPlus[(arr[i] / place) % 10]--;
			}
			else
			{
				output[countMinus[(abs(arr[i]) / place) % 10] - 1] = arr[i];
				countMinus[(abs(arr[i]) / place) % 10]--;
			}
		}

		for (K i = 0; i < size; i++) arr[i] = output[i];
	}
	else
	{
		K count[10] = { 0,0,0,0,0,0,0,0,0,0 };

		for (K i = 0; i < size; i++) count[(abs(arr[i]) / place) % 10]++;
		for (K i = 1; i < 10; i++) count[i] += count[i - 1];


		for (K i = size - 1; i >= 0; i--)
		{
			output[count[(abs(arr[i]) / place) % 10] - 1] = arr[i];
			count[(abs(arr[i]) / place) % 10]--;
		}

		for (K i = 0; i < size; i++) arr[i] = output[i];
	}
}

template<class T, class K>
static void SortX::RadixSort(T& arr, K size)
{
	K max = GetMax(arr, size);
	bool plus = GetMin(arr, size);

	for (K place = 1; max / place > 0; place *= 10)
	{
		BuccketRadix(arr, size, place, plus);
	}
}

////////////////////////////////////////////////////////////////////////////////////
//MergerSort

template<class T, class K>
static void SortX::Merge(T arr, K p, K q, K r) 
{
	// Create L ← A[p..q] and M ← A[q+1..r]
	int n1 = q - p + 1;
	int n2 = r - q;

	T L(n1), M(n2);

	for (int i = 0; i < n1; i++)
		L[i] = arr[p + i];
	for (int j = 0; j < n2; j++)
		M[j] = arr[q + 1 + j];

	// Maintain current index of sub-arrays and main array
	int i, j, k;
	i = 0;
	j = 0;
	k = p;

	// Until we reach either end of either L or M, pick larger among
	// elements L and M and place them in the correct position at A[p..r]
	while (i < n1 && j < n2) {
		if (L[i] <= M[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = M[j];
			j++;
		}
		k++;
	}

	// When we run out of elements in either L or M,
	// pick up the remaining elements and put in A[p..r]
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = M[j];
		j++;
		k++;
	}
}

template<class T, class K>
static void SortX::MergeX(T arr, K l, K r) 
{
	if (l < r)
	{
		K m = l + (r - l) / 2;

		MergeX(arr, l, m);
		MergeX(arr, m + 1, r);

		Merge(arr, l, m, r);
	}
}

template<class T, class K>
static void SortX::MergeSort(T arr, K size)
{
	MergeX(arr, static_cast<K>(0), size - 1);
}


////////////////////////////////////////////////////////////////////////////////////
//BuccketSort

template<class T, class K>
static void SortX::BuccketSort(T arr, K size)
{
	cl; co "Eto polnyy kalich, yuzayte Radix, budte normal'nymi rebyatami" en;
}

////////////////////////////////////////////////////////////////////////////////////
//HeapSort

template<class T, class K>
static void SortX::Heapify(T& arr, K n, K i)
{
	K largest = i;
	K left = 2 * i + 1;
	K right = 2 * i + 2;

	if (left < n && arr[left] > arr[largest])
		largest = left;

	if (right < n && arr[right] > arr[largest])
		largest = right;

	// Swap and continue heapifying if root is not largest
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		Heapify(arr, n, largest);
	}
}

template<class T, class K>
static void SortX::HeapSort(T& arr, K n)
{
	// Build max heap
	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(arr, n, i);

	// Heap sort
	for (int i = n - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);

		// Heapify root element to get highest element at root again
		Heapify(arr, i, static_cast<K>(0));
	}
}

////////////////////////////////////////////////////////////////////////////////////
//PigeonholeSort

template<class T, class K>
static void SortX::PigeonholeSort(T& arr, K n)
{
	int min = arr[0], max = arr[0];

	for (int i = 1; i < n; i++)
	{
		if (arr[i] < min)
			min = arr[i];
		if (arr[i] > max)
			max = arr[i];
	}
	int range = max - min + 1;

	vector<int> buccket(n);  for (size_t i = 0; i < n; i++) buccket[i] = 0;
	vector<int> holes(range);

	for (int i = 0; i < n; i++)
	{
		if (holes[arr[i] - min] == arr[i]) buccket[arr[i]] += 1;
		else holes[arr[i] - min] = arr[i];
	}

	arr.clear();

	for (int i = 0; i < range; i++)
	{
		while (buccket[holes[i]] > 0)
		{
			arr.push_back(holes[i]);
			buccket[holes[i]]--;
		}

		arr.push_back(holes[i]);
	}
}

////////////////////////////////////////////////////////////////////////////////////
//ShakerSort

template<class T, class K>
static void SortX::ShakerSort(T& arr, K n)
{
	K left = 0;		
	K right = arr.size() - 1;
	while (left < right)
	{
		for (K i = left; i < right; i++) {
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
			}
		}
		right--;
		for (K i = right; i > left; i--) {
			if (arr[i] < arr[i - 1])
			{
				swap(arr[i], arr[i - 1]);
			}
		}
		left++;
	};
}

////////////////////////////////////////////////////////////////////////////////////
//NextgenSort





////////////////////////////////////////////////////////////////////////////////////
//LinearSearch

template<class T, class K>
static void SortX::LinearSearch(T& arr, K n, K el)
{
	for (K i = 0; i < n; i++)
	{
		if (arr[i] == el) {
			co "Yep" en; return;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
//BinarySearch

template<class T, class K>
static void SortX::BinarySearch(T& arr, K n, K el)
{
	SortX::QuickSort(arr, n);

	int mid = n / 2;

	if (arr[mid] == el) {
		co "Yep" en; return;
	}

	if (arr[mid] < el)
	{
		for (size_t i = mid; i < n; ++i)
		{
			if (arr[i] == el) {
				co "Yep" en; return;
			}
		}
	}
	else
	{
		for (size_t i = mid; i >= 0; --i)
		{
			if (arr[i] == el) {
				co "Yep" en; return;
			}
		}
	}
}
