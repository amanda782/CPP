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
        height = 1;
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
    int height;
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
            node->left = insert(node->left, key, value);
        } else {
            node->right = insert(node->right, key, value);
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return node;
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
        return node == nullptr ? 0 : node->height;
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

    void deleteNode(char value){
        root = deleteNode(root, value);
    }

    myNode* deleteNode(myNode* node, char value){
        if(node == nullptr) return nullptr;

        if(value < node->value){
            node->left = deleteNode(node->left, value);
        } else if(value > node->value){
            node->right = deleteNode(node->right, value);
        } else {
            if(node->isLeaf()){                         // caso 1: folha
                delete node;
                return nullptr;
            } else if(node->left == nullptr){           // caso 2: só filho direito
                myNode* temp = node->right;
                delete node;
                return temp;
            } else if(node->right == nullptr){          // caso 3: só filho esquerdo
                myNode* temp = node->left;
                delete node;
                return temp;
            } else {                                    // caso 4: dois filhos
                return deleteByCopy(node);
            }
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return node;
    }

    myNode* deleteByCopy(myNode* node){
        if(node->left == nullptr || node->right == nullptr){
            cout << "Node does not have two children." << endl;
            return node;
        }
        myNode* maxLeft = node->left;
        while(maxLeft->right != nullptr) maxLeft = maxLeft->right; // acha o maior da subárvore esquerda
        node->key   = maxLeft->key;                                // copia os dados
        node->value = maxLeft->value;
        node->left  = deleteNode(node->left, maxLeft->value);      // deleta o nó copiado
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return node;
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