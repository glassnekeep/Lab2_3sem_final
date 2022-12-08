#include "Tests.h"

bool testBinSearch(ArraySequence<int> arrSeq) {
	bool a = BinSearh<int, ArraySequence<int>>::bin_Search(&arrSeq, 5);
	bool b = BinSearh<int, ArraySequence<int>>::bin_Search(&arrSeq, 125);

	if (a && !b)
		return true;
	return false;
}

bool testBinTree(BinaryTree<int> tree) {
	bool a = tree.find(7);
	bool b = tree.find(127);

	if (a && !b)
		return true;
	return false;
}

string startTests() {
	int* arr = new int[10];
	for (int i = 0; i < 10; i++)
		arr[i] = i + 1;
	
	ArraySequence<int> arrSeq(arr, 10);
	BinaryTree<int> tree(arr, 10);

	HashTable<int> hashTable(arr, 10);
	
	string res = "";
	if (testBinSearch(arrSeq))
		res += "Bin Search - OK\n";
	else
		res += "Bin Search - NO\n";
	
	if (testBinTree(tree))
		res += "Bin Tree - OK\n";
	else
		res += "Bin Tree - NO\n";
	
	if (hashTable.find("4") && !hashTable.find("124"))
		res += "Hash Table - OK\n\n";
	else
		res += "Hash Table - NO\n\n";
	
	return res;
}