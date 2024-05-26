/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    Node*& tmp = find(root, key);
    if (tmp) return tmp->value;
    return V();
    
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if (subtree == nullptr || subtree->key == key) return subtree;
    if (subtree->key > key) return find(subtree->left, key);
    return find(subtree->right, key);
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value) { insert(root, key, value); }

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    Node*& to_insert = find(subtree, key);
    if (!to_insert) to_insert = new Node(key, value);
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::findIOP(Node*& node) {
    if (node->right == nullptr)
        return node;
    Node *n = node;
    while (n->right->right != nullptr)
        n = n->right;
    return n->right;
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    Node* tmp = first;
    first = second;
    second = tmp;
}

template <class K, class V>
void BST<K, V>::remove(const K& key) { remove(root, key); }

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key) {
    Node*& to_remove = find(subtree, key);
    if (!to_remove->right && !to_remove->left) { // no children
        delete to_remove;
        to_remove = nullptr;
    } else if ((!to_remove->right && to_remove->left)) { // only one child
        swap(to_remove, to_remove->left);
        delete to_remove->left;
        to_remove->left = nullptr;
    } else  if (to_remove->right && !to_remove->left) {
        swap(to_remove, to_remove->right);
        delete to_remove->left;
        to_remove->left = nullptr;
    } else {
        Node*& left = to_remove->left->left;
        Node*& IOP = findIOP(to_remove->left);
        swap(to_remove, IOP);
        if (IOP->right) { 
            to_remove->right = IOP->right;
        } else to_remove->right = nullptr;
         if (!to_remove->left) { 
            if (IOP->left) to_remove->left = IOP->left;
        } else to_remove->left = left;
        delete IOP;
        IOP = nullptr;
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K,V> tree;
    
    for (std::pair<K,V> tmp : inList) {
        tree.insert(tmp.first, tmp.second);
    }
    return tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> heights;
    heights.resize(inList.size());
    for (int i : heights) heights.at(i) = 0;

   std::sort(inList.begin(),inList.end());
    do {
        BST<K,V> tree = listBuild(inList);
        heights.at(tree.height()) = heights.at(tree.height())+1;
    } while ( std::next_permutation(inList.begin(),inList.end()) );
    return heights;
}