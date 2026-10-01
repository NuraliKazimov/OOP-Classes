#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

/*
    1. Preorder, Inorder, Postorder traversals using numbers
    2. Tree common operations (insert, search, traverse, delete node)
    3. Tree traversals (preorder, inorder, postorder, level order)
    4. Identify mistakes in using recursion where it can be avoided (no need for insertion, no need for node deletion).
    5. Tree Complexity
    6. Applications
    7. What about Heap Data Structure (DSA)?

    Tree Traversal Source:    https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
    Insert Node Source:       https://www.javatpoint.com/insertion-in-binary-search-tree
    Delete Node Source:       https://www.interviewbit.com/blog/delete-node-from-binary-search-tree/
    Binary Tree Applications: https://www.geeksforgeeks.org/applications-advantages-and-disadvantages-of-binary-tree/
*/

struct Node{
    int data;
    Node* left;
    Node* right;
    Node(int value){
        data=value;
        left=right=nullptr;
    }
};

class BinaryTree{
private:
    int height;
    Node* root;

    void printTree(const vector<const Node*const>&) const;
    void destroyTree(const Node*const);

public:
    BinaryTree();
    ~BinaryTree();
    vector<Node*> vector1;

    BinaryTree& insert(const int&);
    int getHeight(Node*) const;
    int getHeight() const;

    void preorder(const Node* train=nullptr) const;
    void inorder(const Node* train=nullptr) const;
    void postorder(const Node* train=nullptr) const;

    void levelorder() const;

    bool search(const int&) const;
    void deleteNode(const int&);
};

BinaryTree::BinaryTree(){
    root=nullptr;
    height=0;
}

BinaryTree& BinaryTree::insert(const int& a){
    Node* node=new Node(a);
    if (root==nullptr){
        root=node;
        vector1.push_back(node);
        return *this;
    }
    Node* train=root;
    while (true){
        if (node->data > train->data){
            if (train->right==nullptr){
                train->right=node;
                vector1.push_back(node);
                break;
            } else {
                train=train->right;
            }
        } else if (node->data < train->data){
            if (train->left==nullptr){
                train->left=node;
                vector1.push_back(node);
                break;
            } else {
                train=train->left;
            }
        } else {
            delete node;
            break;
        }
    }
    return *this;
}

bool BinaryTree::search(const int& value) const {
    bool search=false;
    for (Node* i : vector1) {
        if (i->data==value) { 
            search=true;
            break;
        }
    }
    return search;
}

BinaryTree::~BinaryTree(){
    cout << "[call of destructor]" << endl;
    for (Node* i : vector1){
        cout << "Delete: " << i->data << endl;
        delete i;
    }
}

void BinaryTree::deleteNode(const int& value){
    Node* node=nullptr;
    Node* parent=nullptr;
    Node* train=root;

    while (train!=nullptr){
        if (train->data==value) {
            node=train;
            break;
        }
        parent=train;
        if (value < train->data) {
            train=train->left;
        } else {
            train=train->right;
        }
    }
    if (node==nullptr){
        return;


    }
    vector1.erase(remove(vector1.begin(), vector1.end(), node), vector1.end());
    if (node->left!=nullptr && node->right!=nullptr) {
        Node* succParent=node;
        Node* succ=node->right;
        while (succ->left!=nullptr){
            succParent=succ;
            succ=succ->left;
        }
        node->data=succ->data;
        node=succ;
        parent=succParent;
    }
    Node* child=(node->left!=nullptr) ? node->left : node->right;
    if (node==root) {
        root=child;
    } else if (parent->left==node) {
        parent->left=child;
    } else {
        parent->right=child;
    }
    delete node;
}

void BinaryTree::preorder(const Node* train) const {
    if (train==nullptr) {
        train=root;
    }
    if (train==nullptr) {
        return;
    }

    cout << train->data;
    if (train->left!=nullptr) {
        cout << " -> ";
        preorder(train->left);
    }
    if (train->right!=nullptr){
        cout << " -> ";
        preorder(train->right);
    }
}

void BinaryTree::inorder(const Node* train) const {
    if (train==nullptr) {
        train=root;
    }
    if (train==nullptr){
        return;
    }

    if (train->left!=nullptr) {
        inorder(train->left);
        cout << " -> ";
    }
    cout << train->data;
    if (train->right!=nullptr) {
        cout << " -> ";
        inorder(train->right);
    }
}

void BinaryTree::postorder(const Node* train) const {
    if (train==nullptr){
        train=root;
    }
    if (train==nullptr) {
        return;
    }

    if (train->left!=nullptr){
        postorder(train->left);
        cout << " -> ";
    }
    if (train->right!=nullptr){
        postorder(train->right);
        cout << " -> ";
    }
    cout << train->data;
}


int BinaryTree::getHeight(Node* node) const {
    if (node==nullptr){
        return 0;
    }
    return 1 + max(getHeight(node->left), getHeight(node->right));
}

int BinaryTree::getHeight() const {
    return getHeight(this->root);
}

int main() {
    BinaryTree tree=BinaryTree();

    cout << endl;
    cout << "Height: " << tree.getHeight() << endl;
    tree.insert(50).insert(25).insert(75).insert(12).insert(30).insert(60).insert(85).insert(52).insert(70).insert(71);

    cout << endl << endl;
    cout << "Height: " << tree.getHeight() << endl;
    cout << (tree.search(13) ? "[13 found]" : "[13 not found]") << endl << endl;

    tree.deleteNode(50);

    cout << endl << endl;
    cout << "Height: " << tree.getHeight() << endl;
    tree.preorder();
    cout << endl;

    return 0;
}