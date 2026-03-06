#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class myNode{
    public:
    myNode(int key, char value){
        this->key = key;
        this->value = value;
        left = nullptr;
        right = nullptr;
    }

    bool isLeaf(){
        return left == nullptr && right == nullptr;
    }

    string nodeToString(){
        return "Key: " + to_string(key) + " Value: " + value;
    }

    myNode* next(char other){
        if(other < value){
            return left;
        } else {
            return right;
        }
    }

    myNode* left;
    myNode* right;
    int key;
    char value;
};

class binaryTree{
    public:
    myNode* root;

    binaryTree(){
        root = nullptr;
    }

    bool isEmpty(){
        return root == nullptr;
    }

    void clear(){
        root = nullptr;
    }

    myNode* search(char value){
        return search(root, value);
    }

    myNode* search(myNode* node, char value){
        if(node == nullptr){
            return nullptr; // end of the tree, value not found
        }
        if(node->value == value){
            return node; //found the value
        }
        return search(node->next(value), value); // continue searching in the correct subtree
    }

    void insert(int key, char value){
        if(search(value) !=nullptr){
            cout << "Value already exists in the tree." << endl;
            return;
        }
        root = insert(root, key, value);
    }

    myNode* insert(myNode* node, int key, char value){
        if(node == nullptr){
            return new myNode(key, value); // create a new node if we reached the end of the tree and return it to be linked to its parent (last step of the recursion)
        }
        if(value < node->value){
            node->left = insert(node->left, key, value); // insert in the left subtree
        } else {
            node->right = insert(node->right, key, value); // insert in the right subtree
        }
        return node; // return the unchanged node pointer
    }

    string toString(){
        if(root == nullptr) return "Empty tree";
        int h = getHeight(root); //get altura
        int width = (int)pow(2, h) - 1;
        vector<string> lines(h * 2 - 1, string(width, ' '));
        fillLines(root, lines, 0, 0, width - 1);
        string result;
        for(auto& line : lines) result += line + "\n";
        return result;
    }

    int getHeight(myNode* node){
        if(node == nullptr) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    void fillLines(myNode* node, vector<string>& lines, int level, int left, int right){
        if(node == nullptr) return;
        int mid = (left + right) / 2;
        lines[level * 2][mid] = node->value;
        if(node->left){
            lines[level * 2 + 1][mid - 1] = '/';
            fillLines(node->left, lines, level + 1, left, mid - 1);
        }
        if(node->right){
            lines[level * 2 + 1][mid + 1] = '\\';
            fillLines(node->right, lines, level + 1, mid + 1, right);
        }
    }

};

int main() {
    binaryTree tree;

    // insert
    tree.insert(1, 'e');
    tree.insert(2, 'b');
    tree.insert(3, 'g');
    tree.insert(4, 'a');
    tree.insert(5, 'd');
    tree.insert(6, 'f');
    tree.insert(7, 'h');

    // duplicate test
    tree.insert(8, 'e');

    // search
    myNode* found = tree.search('d');
    if(found)
        cout << "Found: " << found->nodeToString() << endl;
    else
        cout << "Not found" << endl;

    myNode* notFound = tree.search('z');
    if(notFound)
        cout << "Found: " << notFound->nodeToString() << endl;
    else
        cout << "Not found" << endl;

    // print
    cout << tree.toString() << endl;

    return 0;
}