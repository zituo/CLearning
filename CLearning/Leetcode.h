#pragma once
#include <map>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>
#include <queue>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};

struct sBoard
{
	char val;
	bool flag;
};

class Leetcode {
public:
	// not compelete
	int myAtoi(string s) {
		int stringLength = s.length();

		if (stringLength == 0)
		{
			return 0;
		}

		// first step
		int startIndex = 0;
		for (int i = 0; i < stringLength; i++)
		{
			if (s[i] != ' ')
			{
				startIndex = i;
				break;
			}
		}

		// second step
		bool isNegetive = s[startIndex] == '-'? true: false;
		bool isPositive = s[startIndex] == '+' ? true : false;

		if (isNegetive || isPositive)
		{
			startIndex += 1;
		}

		// third step
		map<int, int> map;
		bool startRecord = false;
		for (int i = startIndex; i < stringLength; i++)
		{
			int result = s[i] - '0';

			if (result == 0 && !startRecord)
				continue;

			if (result >= 0 && result <= 9)
			{
				startRecord = true;
				map.emplace(pair<int, int>(i, result));
			}
			else
			{
				break;
			}	
		}

		int calculateResult = 0;
		int numberSize = map.size() - 1;

		if (numberSize > 9)
		{
			if (isNegetive)
				return INT_MIN;
			else
				return INT_MAX;
		}

		bool doCheck = false;
		if (numberSize == 9)
		{
			doCheck = true;
		}

		for (auto i = map.begin(); i != map.end(); i++)
		{
			int temp = 1;
			for (int j = 0; j < numberSize; j++)
			{
				temp *= 10;
			}

			if (doCheck)
			{
				if (isNegetive)
				{
					if (i->second > (2147483648 / temp % 10))
					{
						return INT_MIN;
					}
				}
				else
				{
					if (i->second > (2147483647 / temp % 10))
					{
						return INT_MAX;
					}
				}
			}

			calculateResult += (temp * i->second);
			numberSize--;
		}

		if (isNegetive)
			calculateResult *= -1;

		return calculateResult;
	}

	int pivotIndex(vector<int>& nums) {
		int pivot = -1;

		//暴力算法
		/*for (int i = 0; i < nums.size(); i++)
		{
			int sum1 = 0;
			for (int m = 0; m < i; m++)
			{
				sum1 += nums[m];
			}

			int sum2 = 0;
			for (int n = i + 1; n < nums.size(); n++)
			{
				sum2 += nums[n];
			}

			if (sum1 == sum2)
			{
				pivot = i;
				break;
			}
		}*/

		// 暴力算法优化  如果数组和超过int范围怎么办？需要考虑
		int left = 0;
		int right = 0;
		for (int i = 1; i < nums.size(); i++)
		{
			right += nums[i];
		}

		for (int i = 0; i < nums.size(); i++)
		{
			if (i - 1 >= 0)
				left += nums[i - 1];

			if (left == right)
			{
				pivot = i;
				break;
			}

			if (i + 1 < nums.size())
				right -= nums[i + 1];
		}

		return pivot;
	}

	// 移动0
	void moveZeroes(vector<int>& nums) {
		int lastMoveIndex = -1;
		
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] != 0)
			{
				if (lastMoveIndex != -1)
				{
					nums[lastMoveIndex] = nums[i];
					nums[i] = 0;
					lastMoveIndex++;
				}
			}
			else
			{
				if (lastMoveIndex == -1)
					lastMoveIndex = i;
			}
		}
	}

	// 删除数组元素
	int removeElement(vector<int>& nums, int val) {
		int lastMoveIndex = -1;
		int arrayLength = 0;

		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] != val)
			{
				if (lastMoveIndex != -1)
				{
					nums[lastMoveIndex] = nums[i];
					nums[i] = val;
					lastMoveIndex++;
				}

				arrayLength++;
			}
			else
			{
				if (lastMoveIndex == -1)
					lastMoveIndex = i;
			}
		}

		return arrayLength;
	}

	// 移除增续数组重复元素
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() == 1)
		{
			return 1;
		}

		//重复元素只能保留一个
		/*int curValidIndex = 1;
		int repeatNum = nums[0];

		for (int i = 1; i < nums.size(); i++)
		{
			if (nums[i] != repeatNum)
			{
				repeatNum = nums[i];

				nums[curValidIndex] = repeatNum;
				curValidIndex++;
			}
		}

		return curValidIndex;*/

		// 重复元素保留两个
		int curValidIndex = 1;
		int repeatNum = nums[0];
		int repeatCount = 0;

		for (int i = 1; i < nums.size(); i++)
		{
			if (nums[i] != repeatNum)
			{
				repeatNum = nums[i];

				if (curValidIndex != i)
					nums[curValidIndex] = repeatNum;

				curValidIndex++;
				repeatCount = 0;
			}
			else
			{
				if (repeatCount == 0)
				{
					repeatCount = 1;
					nums[curValidIndex] = repeatNum;
					curValidIndex++;
				}
			}
		}

		return curValidIndex;
	}

	// 颜色排序
	void sortColors(vector<int>& nums) {
		if (nums.size() == 1)
		{
			return;
		}

		int zeroIndex = 0;
		int twoIndex = nums.size() - 1;

		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] == 0)
			{
				zeroIndex++;
			}
			else if (nums[i] == 2)
			{
				twoIndex--;
			}
		}

		for (int i = 0; i < nums.size(); i++)
		{
			if (i < zeroIndex)
			{
				nums[i] = 0;
			}
			else if (i >= zeroIndex && i <= twoIndex)
			{
				nums[i] = 1;
			}
			else if (i > twoIndex)
			{
				nums[i] = 2;
			}
		}
	}

	// 排序
	int findKthLargest(vector<int>& nums, int k) {
		if (k > nums.size())
		{
			return 0;
		}

		if (nums.size() == 1)
		{
			return nums[0];
		}

		// 垃圾写法
		/*map<int, int> result;

		for (int i = 0; i < nums.size(); i++)
		{
			if (result.count(nums[i]) == 0)
			{
				result.insert(pair<int, int>(nums[i], 1));
			}
			else
			{
				result.find(nums[i])->second++;
			}
		}

		auto it = result.rbegin();

		while (it != result.rend())
		{
			k -= it->second;

			if (k <= 0)
			{
				return it->first;
			}

			it++;
		}*/



		return 0;
	}

	// 快速排序
	void QuickSort(vector<int>& nums)
	{
		// 选取第一个参数作为锚点
		
	}

	// 反向输出
	vector<int> reversePrint(ListNode* head) {
		vector<int> result;

		if (!head)
			return result;

		ListNode* tail = head;
		ListNode* preNode = nullptr;

		while (tail->next)
		{
			preNode = head;
			head = tail->next;
			tail->next = head->next;
			head->next = preNode;
		}

		while (head)
		{
			result.push_back(head->val);
			head = head->next;
		}

		return result;
	}

	ListNode* reverseList(ListNode* head) {
		ListNode* tail = head;
		ListNode* preNode = nullptr;

		while (tail->next)
		{
			preNode = head;
			head = tail->next;
			tail->next = head->next;
			head->next = preNode;
		}

		return head;
	}

	Node* copyRandomList(Node* head) {
		if (!head)
			return nullptr;

		Node* originalHead = head;
		Node* curNode = nullptr;
		Node* newHead = nullptr;

		map<Node*, Node*> random;

		while (head)
		{
			Node* nextHead = new Node(head->val);

			if (curNode)
				curNode->next = nextHead;

			if (!newHead)
				newHead = nextHead;

			curNode = nextHead;
				
			random.insert(make_pair(head, curNode));

			head = head->next;
		}

		head = originalHead;
		while (head)
		{
			if (head->random)
			{
				random.find(head)->second->random = random.find(head->random)->second;
			}

			head = head->next;
		}

		return newHead;
	}

	vector<string> mySplit(string s, const char pattern)
	{
		vector<string> result;
		
		if (s.length() > 0)
		{
			int cIndex = 0;
			for (int i = 0; i < s.length(); i++)
			{
				if (s[i] == pattern)
				{
					if (i > 0)
						result.push_back(s.substr(cIndex, i));

					cIndex = i + 1;
				}
			}

			if (cIndex < s.length() - 1)
			{
				result.push_back(s.substr(cIndex, s.length()));
			}
		}

		return result;
	}

	string replaceSpace(string s) {
		string str = "";

		if (s.length() > 0)
		{
			int cIndex = 0;
			for (int i = 0; i < s.length(); i++)
			{
				if (s[i] == ' ')
				{
					if (i > 0)
					{
						str = str + s.substr(cIndex, (i - cIndex)) + "%20";
					}
					else
					{
						str = "%20";
					}

					cIndex = i + 1;
				}
			}

			if (cIndex < s.length())
			{
				str = str + s.substr(cIndex, (s.length() - cIndex));
			}
		}

		return str;
	}

	string reverseLeftWords(string s, int n) {
		string sub1 = s.substr(0, n);
		string sub2 = s.substr(n, (s.length() - n));

		return sub2 + sub1;
	}

	int findRepeatNumber(vector<int>& nums) {
		/*set<int> map;

		for (int i = 0; i < nums.size(); i++)
		{
			if (map.count(nums[i]) > 0)
			{
				return nums[i];
			}

			map.insert(nums[i]);
		}*/

		int temp = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			while (nums[i] != i)
			{
				if (nums[nums[i]] == nums[i])
					return nums[i];

				temp = nums[nums[i]];
				nums[nums[i]] = nums[i];
				nums[i] = temp;
			}
		}

		return -1;
	}

	int search(vector<int>& nums, int target) {
		int count = 0;
		bool isFind = false;

		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] == target)
			{
				isFind = true;
				count++;
			}
			else
			{
				if (isFind)
					break;
			}
		}

		return count;
		// 可以使用二分查找法
	}

	int missingNumber(vector<int>& nums) {
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] != i)
				return i;
		}

		return nums.size();
	}

	bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
			{
				if (matrix[i][j] == target)
				{
					return true;
				}
			}
		}

		return false;

		// 把数组转成图的方法
	}

	char firstUniqChar(string s) {
		if (s.length() == 1)
			return s[0];

		if (s.length() > 1)
		{
			//set<int> unValueIndexs;

			for (int i = 0; i < s.length(); i++)
			{
				/*if (unValueIndexs.count(i) > 0)
					continue;*/

				for (int j = 0; j < s.length(); j++)
				{
					/*if (unValueIndexs.count(j) > 0)
						continue;*/

					if (i != j && s[i] == s[j]) 
					{
						break;
					}

					if (j == s.length() - 1)
						return s[i];
				}
			}
		}

		return ' ';
	}

	// 打印二叉树
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> result;

		if (!root)
		{
			return result;
		}

		stack<TreeNode*> left2RightMap;
		stack<TreeNode*> right2LeftMap;

		left2RightMap.push(root);

		bool left2Right = true;
		int size = left2RightMap.size();

		while (size > 0)
		{
			vector<int> layer;

			if (left2Right)
			{
				for (int i = 0; i < size; i++)
				{
					layer.push_back(left2RightMap.top()->val);

					if (left2RightMap.top()->left)
						right2LeftMap.push(left2RightMap.top()->left);

					if (left2RightMap.top()->right)
						right2LeftMap.push(left2RightMap.top()->right);

					left2RightMap.pop();
				}

				size = right2LeftMap.size();
			}
			else
			{
				for (int i = 0; i < size; i++)
				{
					layer.push_back(right2LeftMap.top()->val);

					if (right2LeftMap.top()->right)
						left2RightMap.push(right2LeftMap.top()->right);

					if (right2LeftMap.top()->left)
						left2RightMap.push(right2LeftMap.top()->left);
					
					right2LeftMap.pop();
				}
				size = left2RightMap.size();
			}
			/*for (int i = 0; i < size; i++)
			{
				layer.push_back(map.top()->val);

				TreeNode* left = map.top()->left;
				TreeNode* right = map.top()->right;

				map.pop();

				if (left2Right)
				{
					if (left)
						map.push(left);

					if (right)
						map.push(right);
				}
				else
				{
					if (right)
						map.push(right);

					if (left)
						map.push(left);
				}
			}*/

			result.push_back(layer);

			left2Right = !left2Right;
		}

		return result;
	}

	// 前序遍历
	void levelFrontForeach(vector<int>& result, TreeNode* root)
	{
		result.push_back(root->val);

		if (root->left)
			levelFrontForeach(result, root->left);

		if (root->right)
			levelFrontForeach(result, root->right);

	}
	// 中序遍历
	void levelMidForeach(vector<int>& result, TreeNode* root)
	{
		result.push_back(root->val);

		if (root->left)
			levelMidForeach(result, root->left);	

		if (root->right)
			levelMidForeach(result, root->right);

	}

	// 后序遍历

	bool isSymmetric(TreeNode* root) {
		if (!root)
			return true;

		if (!root->left && !root->right)
			return true;

		bool result = true;
		special(result, root->left, root->right);

		return result;
	}

	void special(bool& result, TreeNode* leftRoot, TreeNode* rightRoot)
	{
		if (!result)
			return;

		if (!leftRoot || !rightRoot)
		{
			result = false;
			return;
		}

		if (leftRoot->val != rightRoot->val)
			result = false;

		if ((!leftRoot->left && rightRoot->right) || (leftRoot->left && !rightRoot->right))
			result = false;

		if ((!leftRoot->right && rightRoot->left) || (leftRoot->right && !rightRoot->left))
			result = false;

		if (leftRoot->left && rightRoot->right)
			special(result, leftRoot->left, rightRoot->right);

		if (leftRoot->right && rightRoot->left)
			special(result, leftRoot->right, rightRoot->left);
	}

	// 树的子结构
	bool isSubStructure(TreeNode* A, TreeNode* B) {
		if (!A)
			return false;

		if (!B)
			return false;

		return findIsSubStrcture(A, B)? true : (isSubStructure(A->left, B) || isSubStructure(A->right, B));
	}

	bool findIsSubStrcture(TreeNode* A, TreeNode* B)
	{
		if (!A)
			return !B;

		if (!B)
			return true;

		return A->val == B->val && findIsSubStrcture(A->left, B->left) && findIsSubStrcture(A->right, B->right);
	}

	TreeNode* mirrorTree(TreeNode* root) {
		if (!root)
			return NULL;

		queue<TreeNode*> reverseMap;
		reverseMap.push(root);

		while (!reverseMap.empty())
		{
			if (reverseMap.front()->left)
				reverseMap.push(reverseMap.front()->left);

			if (reverseMap.front()->right)
				reverseMap.push(reverseMap.front()->right);

			TreeNode* temp = reverseMap.front()->left;
			reverseMap.front()->left = reverseMap.front()->right;
			reverseMap.front()->right = temp;

			reverseMap.pop();
		}

		return root;
	}

	/// 动态规划
	int pre1 = 0, pre2 = 1;

	int fib(int n) {
		if (n == 0)
			return 0;

		if (n == 1)
			return 1;

		for (int i = 2; i <= n; i++)
		{
			int temp = (pre1 + pre2) % 1000000007;
			pre1 = pre2;
			pre2 = temp;
		}

		return pre2;
	}

	int numWays(int n) {
		if (n == 0)
			return 1;

		if (n == 1)
			return 1;

		if (n == 2)
			return 2;

		int pre1 = 1, pre2 = 2;

		for (int i = 3; i <= n; i++)
		{
			int temp = (pre1 + pre2) % 1000000007;
			pre1 = pre2;
			pre2 = temp;
		}

		return pre2;
	}

	int maxProfit(vector<int>& prices) {
		if (prices.size() < 2)
			return 0;

		// 暴力算法
		/*int maxProfit = 0;
		int minBuyPriceIndex = 0;

		for (int i = 0; i < prices.size() - 1; i++)
		{
			if (prices[i] > prices[minBuyPriceIndex])
				continue;

			for (int j = i + 1; j < prices.size(); j++)
			{
				if (prices[j] - prices[i] > maxProfit)
				{
					maxProfit = prices[j] - prices[i];
					minBuyPriceIndex = i;
				}
			}
		}*/
		//////////////////////////////////////////////////////

		// 自己想的动态规划
		int maxProfit = 0;
		int minBuyPriceIndex = 0;

		for (int i = 1; i < prices.size(); i++)
		{
			maxProfit = max(prices[i] - prices[minBuyPriceIndex], maxProfit);

			if (prices[i] < prices[minBuyPriceIndex])
				minBuyPriceIndex = i;
		}

		return maxProfit;
	}

	int maxSubArray(vector<int>& nums) {
		/*int maxNum = nums[0];
		int subSum = nums[0];
		int startIndex = 0;

		for (int i = 1; i < nums.size(); i++)
		{
			subSum += nums[i];
			if (nums[i] > maxNum && nums[i] > subSum)
			{
				maxNum = nums[i];
				subSum = nums[i];
				startIndex = i;

			}
			else if (subSum > maxNum)
			{
				maxNum = subSum;
			}
		}

		return maxNum;*/

		int pre = 0, maxAns = nums[0];
		for (const auto& x : nums) {
			pre = max(pre + x, x);
			maxAns = max(maxAns, pre);
		}
		return maxAns;
	}

	int maxValue(vector<vector<int>>& grid) {
		vector<vector<int>> maxMap;

		int maxValue = 0;

		for (int i = 0; i < grid.size(); i++)
		{
			vector<int> row;
			for (int j = 0; j < grid[i].size(); j++)
			{
				int temp = 0;

				if (i == 0 && j == 0)
				{
					maxValue = grid[i][j];
					row.push_back(maxValue);
				}
				else if (i == 0)
				{
					temp = row[j - 1] + grid[i][j];
					row.push_back(temp);
					if (temp > maxValue)
						maxValue = temp;
				}
				else if (j == 0 && i > 0)
				{
					temp = maxMap[i - 1][j] + grid[i][j];
					row.push_back(temp);
					if (temp > maxValue)
						maxValue = temp;
				}
				else if(i > 0 && j > 0)
				{
					temp = max(maxMap[i - 1][j], row[j - 1]) + grid[i][j];
					row.push_back(temp);
					if (temp > maxValue)
						maxValue = temp;
				}
			}

			maxMap.push_back(row);
		}

		return maxValue;

		// 可以优化内存空间
	}

	int lengthOfLongestSubstring(string s) {
		if (s.length() == 0)
			return 0;

		unordered_map<char, int> map;
		map.insert(make_pair(s[0], 0));
		int pre = 1, maxLength = 1;

		for (int i = 1; i < s.length(); i++)
		{
			if (map.count(s[i]) == 0)
			{
				pre += 1;
				map.insert(make_pair(s[i], i));
			}
			else
			{
				if (i - map.find(s[i])->second < pre)
				{
					pre = 1;
				}
				
				map.find(s[i])->second = i;
			}
			
			maxLength = max(maxLength, pre);
		}

		return maxLength;
	}

	int translateNum(int num) {
		if (num < 10)
			return 1;

		vector<int> nums;

		while (num > 0)
		{
			nums.push_back(num % 10);
			num = num / 10;
		}

		int pre1 = 1, pre2 = 1;
		
		for (int i = nums.size() - 2; i >= 0; i--)
		{
			if ((nums[i + 1] * 10 + nums[i]) <= 25 && nums[i + 1] > 0)
			{
				int temp = pre1 + pre2;
				pre2 = pre1;
				pre1 = temp;
			}
			else
			{
				pre2 = pre1;
			}
		}

		return pre1;
	}

	ListNode* deleteNode(ListNode* head, int val) {
		if (!head)
			return nullptr;

		ListNode* preNode = nullptr;
		ListNode* curNode = head;

		while (curNode)
		{
			if (curNode->val == val)
			{
				if (!preNode)
				{
					head = curNode->next;
				}
				else
					preNode->next = curNode->next;

				break;
			}

			preNode = curNode;
			curNode = curNode->next;
		}

		return head;
	}

	ListNode* getKthFromEnd(ListNode* head, int k) {
		if (!head)
			return NULL;

		ListNode* leftNode = head;
		ListNode* rightNode = head;

		while (rightNode->next)
		{
			if (k > 1)
			{
				rightNode = rightNode->next;
				k--;
				continue;
			}

			rightNode = rightNode->next;
			leftNode = leftNode->next;
		}

		return leftNode;
	}

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (!l1)
			return l2;

		if (!l2)
			return l1;

		ListNode* head;
		ListNode* preNode;
		ListNode* curNode;

		if (l1->val < l2->val)
		{
			head = l1;
			l1 = l1->next;
		}
		else
		{
			head = l2;
			l2 = l2->next;
		}

		preNode = head;
		curNode = head;

		while (l1 || l2)
		{
			if (!l1)
			{
				preNode->next = l2;
				break;
			}

			if (!l2)
			{
				preNode->next = l1;
				break;
			}

			if (l1->val == l2->val)
			{
				curNode = l1;
				l1 = l1->next;

				preNode->next = curNode;

				curNode = l2;
				l2 = l2->next;

				preNode->next->next = curNode;
			}
			else if (l1->val < l2->val)
			{
				curNode = l1;
				l1 = l1->next;

				preNode->next = curNode;
			}
			else if (l1->val > l2->val)
			{
				curNode = l2;
				l2 = l2->next;

				preNode->next = curNode;
			}

			preNode = curNode;
		}

		return head;
	}

	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		if (!headA || !headB)
			return NULL;

		ListNode* temp1 = headA;
		ListNode* temp2 = headB;
		
		while (temp1 || temp2)
		{
			if (temp1 == temp2)
				return temp1;

			if (temp1->next == NULL && temp2->next == NULL)
				return NULL;

			if (temp1->next == NULL)
			{
				temp1 = headB;
				temp2 = temp2->next;
			}
			else if (temp2->next == NULL)
			{
				temp1 = temp1->next;
				temp2 = headA;
			}
			else
			{
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}

		return NULL;
	}

	vector<int> exchange(vector<int>& nums) {
		if (nums.size() <= 1)
			return nums;

		int temp1 = -1;

		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] % 2 == 0 && temp1 == -1)
			{
				temp1 = i;
			}

			if (nums[i] % 2 == 1 && temp1 != -1)
			{
				int temp2 = nums[temp1];
				nums[temp1] = nums[i];
				nums[i] = temp2;
				temp1++;
			}
		}

		return nums;
	}

	vector<int> twoSum(vector<int>& nums, int target) {
		int start = 0, end = nums.size() - 1;

		vector<int> result;

		while (start < end)
		{
			if (nums[start] + nums[end] > target)
			{
				end--;
			}
			else if (nums[start] + nums[end] < target)
			{
				start++;
			}
			else
			{
				result.push_back(nums[start]);
				result.push_back(nums[end]);
				break;
			}
		}

		return result;
	}

	string reverseWords(string s) {
		int left = s.size() - 1, right = -1;
		string result = "";

		while (left >= 0)
		{
			if (s[left] == ' ')
			{
				if (right != -1)
				{
					if (result.size() > 0)
						result.append(" ");

					result.append(s.substr(left + 1, right - left));
					
					right = -1;
				}
			}
			else
			{
				if (right == -1)
				{
					right = left;
				}
			}

			if (left == 0)
			{
				if (result.size() > 0 && right != -1)
					result.append(" ");

				result.append(s.substr(left, right - left + 1));
			}

			left--;
		}

		return result;
	}

	string minNumber(vector<int>& nums) {
		string result;

		// Insertion Sort
		int preIndex, curNum;

		for (int i = 1; i < nums.size(); i++)
		{
			preIndex = i - 1;
			curNum = nums[i];
			while (preIndex >= 0 && isABigger(nums[preIndex], curNum))
			{
				nums[preIndex + 1] = nums[preIndex];
				preIndex--;
			}

			nums[preIndex + 1] = curNum;
		}

		/*for (int i = 0; i < nums.size(); i++)
		{
			result += std::to_string(nums[i]);
		}*/

		return result;
	}

	bool isABigger(int a, int b)
	{
		if (a == 0)
		{
			return false;
		}

		if (b == 0)
		{
			return true;
		}

		vector<int> A;
		vector<int> B;

		while (a)
		{
			A.insert(A.begin(), a % 10);
			a /= 10;
		}

		while (b)
		{
			B.insert(B.begin(), b % 10);
			b /= 10;
		}

		int AIndex = 0, BIndex = 0;
		for (int i = 0; i < A.size() + B.size(); i++)
		{
			AIndex = i;
			BIndex = i;
			if (AIndex >= A.size())
			{
				AIndex = AIndex % A.size();
			}

			if (BIndex >= B.size())
			{
				BIndex = BIndex % B.size();
			}

			if (A[AIndex] != B[BIndex])
			{
				return A[AIndex] > B[BIndex];
			}
		}

		return false;
	}

	int sumNums(int n) {
		n && (n += sumNums(n - 1));
		return n;
	}

	vector<int> getLeastNumbers(vector<int>& arr, int k) {
		vector<int> result;

		// insertion sort
		//int preIndex, curNum;
		/*for (int i = 1; i < arr.size(); i++)
		{
			preIndex = i - 1;
			curNum = arr[i];

			while (preIndex >= 0 && arr[preIndex] > curNum)
			{
				arr[preIndex + 1] = arr[preIndex];
				preIndex--;
			}

			arr[preIndex + 1] = curNum;
		}*/

		// selection sort
		int minIndex = 0, minValue;
		for (int i = 0; i < k; i++)
		{
			minValue = arr[i];
			minIndex = i;
			for (int j = i + 1; j < arr.size(); j++)
			{
				if (arr[j] < minValue)
				{
					minValue = arr[j];
					minIndex = j;
				}
			}

			if (i != minIndex)
			{
				arr[minIndex] = arr[i];
				arr[i] = minValue;
			}
			
			result.push_back(arr[i]);
		}

		//result.insert(result.begin(), arr.begin(), arr.begin() + k);

		return result;
	}

	bool isStraight(vector<int>& nums) {
		bool result = true;

		sort(nums.begin(), nums.end());

		int zero = 0;
		int curNum = -1;

		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] == 0)
			{
				zero++;
				continue;
			}

			if (curNum == -1)
				curNum = nums[i];
			else
			{
				if (nums[i] - curNum == 1)
				{
					curNum++;
					continue;
				}
				else if (nums[i] - curNum - 1 > zero)
				{
					result = false;
					break;
				}
				else if (nums[i] - curNum <= 0)
				{
					result = false;
					break;
				}
				else
				{
					zero -= (nums[i] - curNum - 1);
					curNum = nums[i];
				}
			}
		}
		return result;
	}

	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		vector<TreeNode*> path_p;
		vector<TreeNode*> path_q;

		lookingForBinaryTreePath(root, p, path_p);
		lookingForBinaryTreePath(root, q, path_q);

		/*for (int i = 0; i < path_p.size() && i < path_q.size(); i++)
		{
			if (path_p[i] != path_q[i])
			{
				return path_p[i - 1];
			}

			if (i == path_p.size() - 1)
				return path_p[i];

			if (i == path_q.size() - 1)
				return path_q[i];
		}*/

		for (int i = path_p.size() - 1, j = path_q.size() - 1; i >= 0 && j >= 0; i--, j--)
		{
			if (path_p[i] != path_q[j])
			{
				return path_p[i + 1];
			}

			if (i == 0)
				return path_p[i];

			if (j == 0)
				return path_q[j];
		}

		return NULL;
	}

	void lookingForBinarySerchTreePath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path)
	{
		path.push_back(root);
		if (target->val < root->val)
		{
			lookingForBinarySerchTreePath(root->left, target, path);
		}
		else if (target->val > root->val)
		{
			lookingForBinarySerchTreePath(root->right, target, path);
		}
	}

	bool lookingForBinaryTreePath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path)
	{
		if (!root)
			return false;

		if (root->val != target->val)
		{
			if (lookingForBinaryTreePath(root->left, target, path))
			{
				path.push_back(root);
				return true;
			}	

			if (lookingForBinaryTreePath(root->right, target, path))
			{
				path.push_back(root);
				return true;
			}
		}
		else
		{
			path.push_back(root);
			return true;
		}

		return false;
	}

	int maxDepth(TreeNode* root) {
		if (!root)
			return 0;

		if (!root->left && !root->right)
		{
			return 1;
		}

		return max(maxDepth(root->left) + 1, maxDepth(root->right) + 1);
	}

	int minDepth(TreeNode* root) {
		if (!root)
			return 0;

		if (!root->left && !root->right)
		{
			return 1;
		}

		return min(maxDepth(root->left) + 1, maxDepth(root->right) + 1);
	}

	bool isBalanced(TreeNode* root) {
		int a = maxDepth(root);
		int b = minDepth(root);
		return abs(maxDepth(root) - minDepth(root)) <= 1;
	}

	int kthLargest(TreeNode* root, int k) {
		if (!root)
			return 0;
		int result = 0;
		findKthLargest(root, k, result);
		return result;
	}

	void findKthLargest(TreeNode* root, int& k, int& result)
	{
		if (root->right)
			findKthLargest(root->right, k, result);

		k--;

		if (k == 0)
			result = root->val;

		if (root->left)
			findKthLargest(root->left, k, result);
	}

	bool exist(vector<vector<char>>& board, string word) {
		vector<vector<sBoard>> mBoard;

		for (int i = 0; i < board.size(); i++)
		{
			vector<sBoard> temp;
			for (int j = 0; j < board[i].size(); j++)
			{
				sBoard s = { board[i][j], false };
				temp.push_back(s);
			}

			mBoard.push_back(temp);
		}

		bool result = false;
		int startIndex = 0;

		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[i].size(); j++)
			{
				findWsordExist(mBoard, word, i, j, 0, result);
				if (result)
					return true;
				else
				{
					resetMBoard(mBoard);
				}
			}
		}

		return false;
	}

	void resetMBoard(vector<vector<sBoard>>& mBoard)
	{
		for (int i = 0; i < mBoard.size(); i++)
		{
			for (int j = 0; j < mBoard[i].size(); j++)
			{
				mBoard[i][j].flag = false;
			}
		}
	}

	void findWsordExist(vector<vector<sBoard>>& mBoard, string word, int m, int n, int index, bool& reslut)
	{
		if (mBoard[m][n].val == word[index])
		{
			mBoard[m][n].flag = true;
			index++;

			if (index == word.length())
			{
				reslut = true;
				return;
			}

			if (m + 1 < mBoard.size() && !mBoard[m + 1][n].flag && !reslut)
			{
				findWsordExist(mBoard, word, m + 1, n, index, reslut);
			}
			
			if (m - 1 >= 0 && !mBoard[m - 1][n].flag && !reslut)
			{
				findWsordExist(mBoard, word, m - 1, n, index, reslut);
			}

			if (n + 1 < mBoard[m].size() && !mBoard[m][n + 1].flag && !reslut)
			{
				findWsordExist(mBoard, word, m, n + 1, index, reslut);
			}

			if (n - 1 >= 0 && !mBoard[m][n - 1].flag && !reslut)
			{
				findWsordExist(mBoard, word, m, n - 1, index, reslut);
			}

			if (!reslut)
				mBoard[m][n].flag = false;
		}
	}

	/*bool check(vector<vector<char>>& board, vector<vector<int>>& visited, int i, int j, string& s, int k) {
		if (board[i][j] != s[k]) {
			return false;
		}
		else if (k == s.length() - 1) {
			return true;
		}
		visited[i][j] = true;
		vector<pair<int, int>> directions{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
		bool result = false;
		for (const auto& dir : directions) {
			int newi = i + dir.first, newj = j + dir.second;
			if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size()) {
				if (!visited[newi][newj]) {
					bool flag = check(board, visited, newi, newj, s, k + 1);
					if (flag) {
						result = true;
						break;
					}
				}
			}
		}
		visited[i][j] = false;
		return result;
	}

	bool exist(vector<vector<char>>& board, string word) {
		int h = board.size(), w = board[0].size();
		vector<vector<int>> visited(h, vector<int>(w));
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				bool flag = check(board, visited, i, j, word, 0);
				if (flag) {
					return true;
				}
			}
		}
		return false;
	}*/

	int get(int x) {
		int res = 0;
		for (; x; x /= 10) {
			res += x % 10;
		}
		return res;
	}

	int movingCount(int m, int n, int k) {
		if (!k) return 1;
		queue<pair<int, int> > Q;
		// 向右和向下的方向数组
		int dx[2] = { 0, 1 };
		int dy[2] = { 1, 0 };
		vector<vector<int> > vis(m, vector<int>(n, 0));
		Q.push(make_pair(0, 0));
		vis[0][0] = 1;
		int ans = 1;
		while (!Q.empty()) {
			int x = Q.front().first, y = Q.front().second;
			Q.pop();
			for (int i = 0; i < 2; ++i) {
				int tx = dx[i] + x;
				int ty = dy[i] + y;
				if (tx < 0 || tx >= m || ty < 0 || ty >= n || vis[tx][ty] || get(tx) + get(ty) > k) continue;
				Q.push(make_pair(tx, ty));
				vis[tx][ty] = 1;
				ans++;
			}
		}
		return ans;
	}

	vector<vector<int>> pathSum(TreeNode* root, int target) {
		vector<vector<int>> result;

		if (!root)
			return result;

		vector<int> temp;

		temp.push_back(root->val);
		int sum = root->val;

		if (sum == target && !root->left && !root->right)
		{
			result.push_back(temp);
		}

		searchPathSum(root->left, target, sum, temp, result);
		searchPathSum(root->right, target, sum, temp, result);

		return result;
	}

	void searchPathSum(TreeNode* root, int target, int& sum, vector<int>& path, vector<vector<int>>& result)
	{
		if (!root)
			return;

		sum += root->val;
		path.push_back(root->val);

		if (!root->left && !root->right)
		{
			if (sum == target)
			{
				vector<int> temp;
				temp.insert(temp.end(), path.begin(), path.end());

				result.push_back(temp);
			}

			sum -= root->val;;
			path.pop_back();

			return;
		}

		if (root->left)
			searchPathSum(root->left, target, sum, path, result);

		if (root->right)
			searchPathSum(root->right, target, sum, path, result);

		sum -= root->val;
		path.pop_back();

	}

	TreeNode* treeToDoublyList(TreeNode* root) {
		if (!root)
			return NULL;

		vector<TreeNode*> path;
		middleOrder(root, path);

		for (int i = 0; i < path.size(); i++)
		{
			if (i == 0)
			{
				path[i]->left = path[path.size() - 1];
			}
			else
			{
				path[i]->left = path[i - 1];
			}

			if (i == path.size() - 1)
			{
				path[i]->right = path[0];
			}
			else
			{
				path[i]->right = path[i + 1];
			}
		}

		return path[0];
	}

	// 中序遍历
	void middleOrder(TreeNode* root, vector<TreeNode*>& path)
	{
		if (!root)
			return;

		middleOrder(root->left, path);
		path.push_back(root);
		middleOrder(root->right, path);
	}


	map<int, int> inorderMap;
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.size() == 0)
			return NULL;

		//TreeNode head(preorder[0]);
		/*int rootIndex = -1;
		for (int i = 0; i < inorder.size(); i++)
		{
			if (inorder[i] == preorder[0])
			{
				rootIndex = i;
				break;
			}
		}

		int startIndex = 1*/
		//gotoBuildTree(&head, preorder, inorder, startIndex, );

		for (int i = 0; i < inorder.size(); i++)
		{
			inorderMap[inorder[i]] = i;
		}

		//int startIndex = 1;
		//gotoBuildTree(&head, preorder, inorderMap, startIndex);

		return gotoBuildTree(0, 0, inorder.size() - 1, preorder, inorder);
	}

	TreeNode* gotoBuildTree(int root, int left, int right, const vector<int>& preorder, const vector<int>& inorder)
	{
		if (left > right) return nullptr;                        // 递归终止
		TreeNode* node = new TreeNode(preorder[root]);          // 建立根节点
		int i = inorderMap[preorder[root]];                      // 划分根节点、左子树、右子树
		node->left = gotoBuildTree(root + 1, left, i - 1, preorder, inorder);              // 开启左子树递归
		node->right = gotoBuildTree(root + i - left + 1, i + 1, right, preorder, inorder); // 开启右子树递归
		return node;
	}

	double myPow(double x, int n) {
		double ans = 1.0;

		for (int i = n; i != 0; i /= 2)
		{
			if (i % 2 != 0)
			{
				ans *= x;
			}

			x *= x;
		}

		return n < 0? 1 / ans : ans;
	}

	// 判断是否是二叉搜索树的后序遍历
	bool verifyPostorder(vector<int>& postorder) {
		return isPostorder(0, postorder.size() - 1, postorder);
	}

	bool isPostorder(int leftIndex, int rightIndex, const vector<int>& postorder)
	{
		if (leftIndex >= rightIndex)
			return true;

		int mid = leftIndex;
		int root = postorder[rightIndex];

		while (postorder[mid] < root)
			mid++;

		int temp = mid;

		while (temp < rightIndex) {
			if (postorder[temp++] < root)
				return false;
		}

		return isPostorder(leftIndex, mid - 1, postorder) && isPostorder(mid, rightIndex - 1, postorder);
	}

	vector<int> singleNumbers(vector<int>& nums) {
		int res = 0;
		for (int n : nums)
		{
			res ^= n;
		}

		int mark = 1;
		while ((res & mark) == 0)
		{
			mark <<= 1;
		}

		int a = 0, b = 0;

		for (int n : nums)
		{
			if (n & mark)
			{
				a ^= n;
			}
			else
			{
				b ^= n;
			}
		}

		return vector<int>{a, b};
	}

	vector<vector<int>> findContinuousSequence(int target) {
		if (target <= 2)
			return vector<vector<int>> {};

		vector<vector<int>> result;

		int sum = 3;
		int left = 1, right = 2;
		while (left < right && right < target)
		{
			if (sum < target)
			{
				right++;
				sum += right;
			}
			else if (sum > target)
			{
				sum -= left;
				left++;
			}
			else if (sum == target)
			{
				vector<int> temp;
				for (int i = left; i <= right; i++)
				{
					temp.push_back(i);
				}

				result.push_back(temp);

				right++;
				sum += right;
			}
		}

		return result;
	}

	static constexpr int directions[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		if (matrix.size() == 0 || matrix[0].size() == 0) {
			return {};
		}

		int rows = matrix.size(), columns = matrix[0].size();
		vector<vector<bool>> visited(rows, vector<bool>(columns));
		int total = rows * columns;
		vector<int> order(total);

		int row = 0, column = 0;
		int directionIndex = 0;
		for (int i = 0; i < total; i++) {
			order[i] = matrix[row][column];
			visited[row][column] = true;
			int nextRow = row + directions[directionIndex][0], nextColumn = column + directions[directionIndex][1];
			if (nextRow < 0 || nextRow >= rows || nextColumn < 0 || nextColumn >= columns || visited[nextRow][nextColumn]) {
				directionIndex = (directionIndex + 1) % 4;
			}
			row += directions[directionIndex][0];
			column += directions[directionIndex][1];
		}
		return order;
	}

	vector<int> printNumbers(int n) {
		vector<int> result;

		int count = pow(10, n);
		for (int i = 1; i < count; i++)
		{
			result.push_back(i);
		}

		return result;
	}

	int reversePairs(vector<int>& nums) {
		int ans = 0;

		for (int i = nums.size() - 2; i >= 0; i--)
		{
			for (int j = i + 1; j < nums.size(); j++)
			{
				if (nums[i] > nums[j])
				{
					ans += 1;
				}
			}
		}

		return ans;
	}

	bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
		stack<int> map;

		int i = 0, j = 0;

		while (i < pushed.size() && j < popped.size())
		{
			if (pushed[i] != popped[j])
			{
				if (map.size() > 0 && map.top() == popped[j])
				{
					map.pop();
					j++;
				}
				else
				{
					map.push(pushed[i]);
					i++;
				}
			}
			else if (pushed[i] == popped[j])
			{
				i++;
				j++;
			}
			
		}

		for (; j < popped.size(); j++)
		{
			if (map.top() == popped[j])
			{
				map.pop();
			}
		}

		return map.empty();
	}

	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		int n = nums.size();
		priority_queue<pair<int, int>> q;
		for (int i = 0; i < k; ++i) {
			q.emplace(nums[i], i);
		}
		vector<int> ans = { q.top().first };
		for (int i = k; i < n; ++i) {
			q.emplace(nums[i], i);
			while (q.top().second <= i - k) {
				q.pop();
			}
			ans.push_back(q.top().first);
		}
		return ans;
	}

	int singleNumber(vector<int>& nums) {
		int ones = 0, twos = 0;
		for (int num : nums) {
			ones = ones ^ num & ~twos;
			twos = twos ^ num & ~ones;
		}
		return ones;
	}

	int hammingWeight(uint32_t n) {
		int ans = 0;
		toBinary(n, ans);

		return ans;
	}

	void toBinary(uint32_t n, int& ans)
	{
		if (n / 2 != 0) {
			toBinary(n / 2, ans);
		}

		if (n % 2 == 1)
		{
			ans++;
		}
	}

	int negative(int a)
	{
		return add(~a, 1);
	}

	int add(int a, int b) {
		

		return (b == 0) ? a : add(a ^ b, (a & b) << 1);
	}
};

class CQueue {
private:
	std::stack<int> sIn, sOut;

public:
	CQueue() {
		sIn.empty();
		sOut.empty();
	}

	void appendTail(int value) {
		sIn.push(value);
	}

	int deleteHead() {
		int returnValue = -1;

		if (sOut.size() <= 0)
		{
			while (sIn.size() > 1)
			{
				sOut.push(sIn.top());
				sIn.pop();
			}

			if (sIn.size() == 1)
			{
				returnValue = sIn.top();
				sIn.pop();
			}

			return returnValue;
		}
		else
		{
			returnValue = sOut.top();
			sOut.pop();
		}

		return returnValue;
	}
};

class MinStack {
private:
	multiset<int> minValues;
	vector<int> myStack;

public:
	/** initialize your data structure here. */
	MinStack() {
		myStack.clear();
		minValues.clear();
	}

	void push(int x) {
		minValues.insert(x);
		myStack.push_back(x);
	}

	void pop() {
		minValues.erase(minValues.find(myStack.back()));
		myStack.pop_back();
	}

	int top() {
		return myStack.back();
	}

	int min() {
		return *minValues.begin();
	}
};