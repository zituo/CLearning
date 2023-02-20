#pragma once
#include <map>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>
#include <queue>

using namespace std;

class MySortingAlgorithms
{
public:
	MySortingAlgorithms();
	~MySortingAlgorithms();

public:
	vector<int>& myBubbleSorting(vector<int>& nums);
	vector<int>& mySelectionSorting(vector<int>& nums);
	vector<int>& myInsertionSorting(vector<int>& nums);
};

MySortingAlgorithms::MySortingAlgorithms()
{
}

MySortingAlgorithms::~MySortingAlgorithms()
{
}

// bubble sorting(stable)
vector<int>& MySortingAlgorithms::myBubbleSorting(vector<int>& nums)
{
	// 已排序的区域不用再判断
	int unSortedArea = nums.size() - 1;

	bool flag = 0;
	for (int i = 0; i < unSortedArea; i++)
	{
		flag = 1;
		for (int j = 0; j < unSortedArea; j++)
		{
			if (nums[j] > nums[j + 1])
			{
				int temp = nums[j + 1];
				nums[j + 1] = nums[j];
				nums[j] = temp;
				flag = 0;
			}
		}

		if (flag)
			break;

		unSortedArea--;
	}

	return nums;
}

// selection sort(stable)
inline vector<int>& MySortingAlgorithms::mySelectionSorting(vector<int>& nums)
{
	int minIndex = 0, temp;

	for (int i = 0; i < nums.size(); i++)
	{
		minIndex = i;
		for (int j = i + 1; j < nums.size(); j++)
		{
			if (nums[j] < nums[minIndex])
			{
				minIndex = j;
			}
		}

		temp = nums[minIndex];
		nums[minIndex] = nums[i];
		nums[i] = temp;
	}
	return nums;

	// 优化方法可以在一次循环中找出最小和最大值，当前+1为最大值意味着已经有序
}

// insertion sort
inline vector<int>& MySortingAlgorithms::myInsertionSorting(vector<int>& nums)
{
	
}
