#include <iostream>
#include <cassert>
#include "model/array/Sequence.h"
#include "model/array/ArraySequence.h"
#include "model/HashTable1.h"
#include "model/BinaryTree.h"
#include "model/BinSearch.h"

Sequence<int>* formSequence() {
    Sequence<int>* sequence = new ArraySequence<int>(0);
    for (int i = 0; i < 10; i++) {
        sequence -> append(rand() % 100);
    }
    return sequence;
}

Sequence<int>* formSequenceWithSameElement() {
    Sequence<int>* sequence = new ArraySequence<int>(0);
    for (int i = 0; i < 10; i++) {
        sequence -> append(5);
    }
    return sequence;
}

Sequence<int>* formSequenceWithAlmostTheSameElement() {
    Sequence<int>* sequence = new ArraySequence<int>(0);
    for (int i = 0; i < 10; i++) {
        bool flag = rand() % 2;
        if (flag) {
            sequence -> append(5);
        }
        sequence -> append(rand() % 100);
    }
    return sequence;
}

void testHashMapAddingAndRemoving() {
    Sequence<int>* sequence = new ArraySequence<int>(0);
    sequence -> append(1);
    sequence -> append(2);
    sequence -> append(3);
    IMap<int, int>* map = new HashMap<int, int>(sequence, 3);
    map -> put(4, 4);
    sequence -> append(4);
    for (int i = 0; i < 4; i++) {
        assert(map -> find(sequence -> get(i)));
    }
    map -> remove(3);
    map -> remove(2);
    map -> remove(1);
    map -> remove(4);
    assert(!map -> find(1));
    assert(!map -> find(2));
    assert(!map -> find(3));
    assert(!map -> find(4));
    map -> put(1, 1);
    assert(!map -> find(5));
    assert(map -> find(1));
}

void tests() {
    Sequence<int>* sequence = formSequence();
    Sequence<int>* sequenceWithSameElements = formSequenceWithSameElement();
    Sequence<int>* sequenceWithAlmostTheSameElement = formSequenceWithAlmostTheSameElement();
    int size = 10;
    IMap<int, int>* map = new HashMap<int, int>(sequence, size);
    IMap<int, int>* map1 = new HashMap<int, int>(sequenceWithSameElements, size);
    IMap<int, int>* map2 = new HashMap<int, int>(sequenceWithAlmostTheSameElement, size);
    auto* tree = new BinaryTree<int>(sequence, size);
    auto* tree1 = new BinaryTree<int>(sequenceWithSameElements, size);
    auto* tree2 = new BinaryTree<int>(sequenceWithAlmostTheSameElement, size);
    for (int i = 0; i < size; i++) {
        assert(map -> find(sequence -> get(i)));
        assert(map1 -> find(sequenceWithSameElements -> get(i)));
        assert(map2 -> find(sequenceWithAlmostTheSameElement -> get(i)));
        //bool a = BinSearch<int, Sequence<int>>::bin_Search(sequence, sequence -> get(i));
        //bool b = BinSearch<int, Sequence<int>>::bin_Search(sequenceWithSameElements, sequenceWithSameElements -> get(i));
        //bool c = BinSearch<int, Sequence<int>>::bin_Search(sequenceWithAlmostTheSameElement, sequenceWithAlmostTheSameElement -> get(i));
        //assert(a);
        //assert(b);
        //assert(c);
//        assert(tree -> find(sequence -> get(i)));
//        assert(tree1 -> find(sequenceWithSameElements -> get(i)));
//        int k = sequence -> get(i);
//        assert(tree2 -> find(sequenceWithAlmostTheSameElement -> get(i)));
    }
    testHashMapAddingAndRemoving();
}
int main() {
    tests();
    return 0;
}
