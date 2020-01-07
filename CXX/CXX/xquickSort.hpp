#pragma once

#include <vector>
#include <iostream>

//数组打印
void printArray(std::vector<int>& a)
{
	for (int i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	std::cout << std::endl;
}

//获取主元--Pivot
int getPivot(std::vector<int>& vecs) {
	int size = vecs.size();
	if (size > 3)
	{
		int m = size / 2;
		return m;
	}
	else {
		return 0;
	}
}


//快速排序（从小到大）
void quickSort(int left, int right, std::vector<int>& arr)
{
	if (left >= right)
		return;
	int i, j, base, temp;
	i = left, j = right;
	//int index = getPivot(arr);
	base = arr[left];
	while (i < j)
	{
		while (arr[j] >= base && i < j)
			j--;
		while (arr[i] <= base && i < j)
			i++;
		if (i < j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	//基准数归位
	arr[left] = arr[i];
	arr[i] = base;
	quickSort(left, i - 1, arr);//递归左边
	quickSort(i + 1, right, arr);//递归右边
}