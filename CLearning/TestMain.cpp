#include<iostream>
#include "Leetcode.h"
#include "./src/Headers/SortingAlgorithms.h"

//#include "EndBrace.h"

using namespace std;


//void test1(vector<int>& inputArray)
//{
//	for (auto i = inputArray.begin(); i != inputArray.end(); ++i) {
//		std::cout << *i << ' ';
//	}
//}
//
//void test2(vector<int>& inputArray)
//{
//	for (auto i = inputArray.begin(); i != inputArray.end(); ++i) {
//		std::cout << *i << ' ';
//	}
//}

int main()
{
	Leetcode* leetcode = new Leetcode();

	ListNode* list1 = new ListNode(1);
	list1->next = new ListNode(3);
	list1->next->next = new ListNode(5);

	ListNode* list2 = new ListNode(2);
	/*list2->next = new ListNode(3);
	list2->next->next = new ListNode(4);*/
	//list2->next->next->next = new ListNode(6);

	leetcode->getIntersectionNode(list1, list2);

	/*Node* head = new Node(1);
	Node* node1 = new Node(2);
	Node* node2 = new Node(3);
	Node* node3 = new Node(4);

	head->next = node1;
	head->random = node2;

	node1->next = node2;

	node2->next = node3;
	node2->random = head;

	node3->random = node1;
	leetcode->copyRandomList(head);*/

	TreeNode* treeNode1 = new TreeNode(7);

	TreeNode* treeNode2 = new TreeNode(0);

	TreeNode* treeNode3 = new TreeNode(-1);

	TreeNode* treeNode4 = new TreeNode(-6);

	TreeNode* treeNode5 = new TreeNode(1);

	TreeNode* treeNode6 = new TreeNode(-7);

	TreeNode* treeNode7 = new TreeNode(-1);

	treeNode1->left = treeNode2;
	//treeNode1->right = treeNode3;

	treeNode2->left = treeNode3;
	treeNode2->right = treeNode4;

	//treeNode4->left = treeNode7;

	treeNode3->right = treeNode5;

	treeNode5->left = treeNode6;

	leetcode->treeToDoublyList(treeNode1);

	int a = 2;
	//leetcode->kthLargest(treeNode3, a);

	/*treeNode1->left = treeNode2;
	treeNode1->right = treeNode3;
	treeNode2->left = treeNode4;
	treeNode2->right = treeNode5;*/

	TreeNode* treeNodeww1 = new TreeNode(1);

	TreeNode* treeNodeww2 = new TreeNode(2);

	TreeNode* treeNodeww3 = new TreeNode(3);

	TreeNode* treeNodeww4 = new TreeNode(4);

	TreeNode* treeNodeww5 = new TreeNode(5);

	treeNodeww1->left = treeNodeww2;
	//treeNodeww2->left = treeNodeww3;
	treeNodeww2->left = treeNodeww4;
	treeNodeww2->right = treeNodeww5;
	
	//treeNode3->left = treeNode4;

	//cout<< "1111===" << leetcode->mirrorTree(treeNode1) << endl;
	leetcode->findContinuousSequence(5);
	cout << "1111===" << leetcode->myPow(2., 5) << endl;


	//int result = leetcode->myAtoi("-2147483648");

	vector<int> inputArray = { 1,3,-1,-3,5,3,6,7 };
	leetcode->maxSlidingWindow(inputArray, 3);

	vector<int> preorder = { 2, 1, 0};
	vector<int> inorder = { 1, 2, 0 };

	leetcode->validateStackSequences(preorder, inorder);

	/*for (auto i = inputArray.begin(); i != inputArray.end(); ++i) {
		std::cout << *i << ' ';
	}*/

	//cout << result << endl;

	//system("pause");

	//int a = 10, b = 20;

	//mutiple(a, b);

	//return 0;

	//CQueue* cq = new CQueue();

	/*cq->appendTail(1);
	cq->appendTail(2);
	cq->appendTail(3);
	cout << cq->deleteHead() << endl;
	cq->appendTail(4);
	cq->appendTail(5);
	cout << cq->deleteHead() << endl;
	cout << cq->deleteHead() << endl;
	cout << cq->deleteHead() << endl;*/
	//cout << cq->deleteHead() << endl;

	/*MinStack* m = new MinStack();

	m->push(0);
	m->push(1);
	m->push(0);
	cout << m->min() << endl;
	m->pop();
	cout << m->min() << endl;*/

	vector<vector<char>> test;

	test.push_back(vector<char>({ 'A', 'B', 'C', 'E'}));
	test.push_back(vector<char>({ 'S', 'F', 'E', 'S'}));
	test.push_back(vector<char>({ 'A', 'D', 'E', 'E'}));
	/*test.push_back(vector<char>({ 'A', 'A', 'A', 'A', 'A', 'A' }));
	test.push_back(vector<char>({ 'A', 'A', 'A', 'A', 'A', 'A' }));
	test.push_back(vector<char>({ 'A', 'A', 'A', 'A', 'A', 'A' }));*/

	//leetcode->exist(test, "ABCESEEEFS");

	leetcode->movingCount(16, 8, 4);


	MySortingAlgorithms* mySort = new MySortingAlgorithms();

	vector<int> temp{2,9,6,4,5,8,7};
	mySort->mySelectionSorting(temp);
}
