#include <cstddef>
#include<iostream>
#include<fstream>

using namespace std;

//node
struct Node{
    int data;
    Node *left;
    Node *right;

    Node(int val){
        data = val;
        left = right = NULL;

    }
};

//insert
Node *insert(Node *root, int val){
    if(root == NULL)
        return new Node(val);

    if(val < root->data){
        root->left = insert(root->left,val);
    }
    else {
        root->right = insert(root->right,val);
    }

    return root;
}

// inorder
void inorder(Node *root){
    if(root == NULL) return;

    inorder(root->left);
    cout<< root->data<< " ";
    inorder(root->right);
}

// void preorder(Node *root)
int search(Node* root, int key) {
    if (root == NULL) return 0;

    if (root->data == key) return 1;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}
// count leaf nodes
int countLeaves(Node *root){
    if(root == NULL) return 0;

    if(root->left == NULL && root->right ==NULL){
        return 1;
    }
    return countLeaves(root->left)+ countLeaves(root->right);
}

// count nodes
int countNodes(Node *root){
    if(root==NULL) return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}


int main(){
    Node *root = NULL;
    int n, val;

    fstream file("tree.txt");
    file>>n;

    for(int i=0;i<n;i++){
        file>>val;
        root = insert(root,val);
    }


    cout<<"inorder: ";
    inorder(root);

    int leaves = countLeaves(root);
    cout << "\n" <<leaves;


    int nodes = countNodes(root);
    cout << "no of nodes: " <<nodes;


    int found = search(root,90);
    if(found){
        cout<<"\nelement found";

    }
    else
        cout<<"\nnot found";
    return 0;


}
