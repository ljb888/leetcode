#include <iostream>

using namespace std;

struct Node {
    int val;
    Node *left, *right;

    Node(int v): val(v), left(nullptr), right(nullptr) {}
};

Node* upSideDownTree(Node* root) {
    if (!root || (!root->left)) return root;

    auto sibling = root->right;
    auto parent = root;
    Node* result = root->left;
    parent->left = parent->right = nullptr;

    while (result) {
        auto nSibling = result->right;
        auto nResult = result->left;
        result->left = sibling;
        result->right = parent;
        parent = result;
        sibling = nSibling;
        if (! nResult) break;
        result = nResult;
   }

   return result;
}

void printTree(Node *root)
{
    while (root) {
        cout << root->val;
	if (root->left) cout << "  " << root->left->val ;
	if (root->right) cout << "  " << root->right->val;
	cout << endl;
	root = root->right;
    }
}

Node* getTree() {
    auto root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    auto n = root->left;
    n->left = new Node(4);
    n->right = new Node(5);

    return root;
}

int main() {
    auto root = getTree();
    auto ntree = upSideDownTree(root);
    printTree(ntree);

    return 0;
}
