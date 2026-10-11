
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char ch, int f) {
        data = ch;
        freq = f;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void printCodes(Node* root, string code) {
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr) {
        cout << root->data << " : "
             << (code.empty() ? "0" : code) << endl;
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    priority_queue<Node*, vector<Node*>, Compare> pq;

    char ch;
    int freq;

    cout << "Enter each character and its frequency:\n";

    for (int i = 0; i < n; i++) {
        cin >> ch >> freq;
        pq.push(new Node(ch, freq));
    }

    // Build the Huffman tree
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* merged = new Node(
            '$', left->freq + right->freq
        );

        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    Node* root = pq.top();

    cout << "\nHuffman Codes:\n";
    printCodes(root, "");

    return 0;
}
