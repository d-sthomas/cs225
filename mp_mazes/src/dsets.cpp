/* Your code here! */
#include "dsets.h"
#include <iostream>

/*
    Creates n unconnected root nodes at the end of the vector.
    num: number of nodes to create
*/
void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        up_tree.push_back(-1);
    }
}

/*
    This function should compress paths and works as described in lecture.
    Returns the index of the root of the up-tree in which the parameter element resides   
*/
int DisjointSets::find(int elem) { 
    if (up_tree[elem] < 0) return elem;
    else {
        return find(up_tree[elem]);
    }
}

/*
    This function should be implemented as union-by-size. That is, when you setunion two disjoint sets, 
    the smaller (in terms of number of nodes) should point at the larger. This function works as described 
    in lecture, except that you should not assume that the arguments to setunion are roots of existing uptrees.
    Your setunion function SHOULD find the roots of its arguments before combining the trees. If the two sets 
    are the same size, make the tree containing the second argument point to the tree containing the first. 
    (Note that normally we could break this tie arbitrarily, but in this case we want to control things for grading.)
    
    a: Index of the first element to union
    b: Index of the second element to union

*/
void DisjointSets::setunion(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);
    if (root_a == root_b) return;
    if (size(root_a) < size(root_b)) {
        up_tree[root_b] -= size(root_a);
        up_tree[root_a] = root_b;
    } else {
        up_tree[root_a] -= size(root_b);
        up_tree[root_b] = root_a;
    }
 }

/*
    This function should return the number of nodes in the up-tree containing the element.
    Returns number of nodes in up-tree containing the element
*/
int DisjointSets::size(int elem) {
    return -1*up_tree[find(elem)];
 }