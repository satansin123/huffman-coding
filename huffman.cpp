#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left, *right;
};

// Function to allocate a new tree node
Node *getNode(char ch, int freq, Node *left, Node *right)
{
    Node *node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

// Comparison object to order the heap
struct comp
{
    bool operator()(Node *l, Node *r)
    {
        return l->freq > r->freq;
    }
};

// Traverse the Huffman Tree and store Huffman Codes in a map
void encode(Node *root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right)
    {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// Traverse the Huffman Tree and decode the encoded string
void decode(Node *root, int &index, string str)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right)
    {
        cout << root->ch;
        return;
    }

    index++;

    if (str[index] == '0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}

// Builds Huffman Tree and decodes given input text
void buildHuffmanTree(const string &text)
{
    unordered_map<char, int> freq;
    for (char ch : text)
    {
        freq[ch]++;
    }

    priority_queue<Node *, vector<Node *>, comp> pq;
    for (auto pair : freq)
    {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    Node *root = pq.top();
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes are:\n";
    for (auto pair : huffmanCode)
    {
        cout << pair.first << " " << pair.second << '\n';
    }

    cout << "\nOriginal string:\n"
         << text << '\n';

    string encodedString = "";
    for (char ch : text)
    {
        encodedString += huffmanCode[ch];
    }

    cout << "\nEncoded string:\n"
         << encodedString << '\n';

    int index = -1;
    cout << "\nDecoded string:\n";
    while (index < (int)encodedString.size() - 2)
    {
        decode(root, index, encodedString);
    }
}

// Main function
int main()
{
    const string text = "Huffman coding is a data compression algorithm.";
    buildHuffmanTree(text);
    return 0;
}
