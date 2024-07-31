#pragma once
#include "Huffman.h"

TreeNode::TreeNode(int val, char data)
{
    this->data = data;
    this->value = val;
    left = right = HuffmanRight = HuffmanLeft = parent = NULL;
}

void MinHeap::heapifyUp(TreeNode* node)
{
    while (node->parent && node->value < node->parent->value)
    {
        swapValues(node, node->parent);
        node = node->parent;
    }
}

void MinHeap::heapifyDown(TreeNode* node)
{
    while (node->left)
    {
        TreeNode* smallerChild = node->left;
        if (node->right && node->right->value < node->left->value)
            smallerChild = node->right;

        if (node->value <= smallerChild->value)
            break;
        swapValues(node, smallerChild);
        node = smallerChild;
    }
}

TreeNode* MinHeap::getLastNode()
{
    if (!root)
        return nullptr;
    int path = size;
    TreeNode* node = root;
    int depth = -1;
    while (path > 0)
    {
        path /= 2;
        depth++;
    }
    path = size;
    for (int i = depth - 1; i >= 0; --i)
    {
        if (path & (1 << i))
            node = node->right;
        else
            node = node->left;
    }
    return node;
}

void MinHeap::swapValues(TreeNode* node1, TreeNode* node2)
{
    TreeNode* HuffmanLeftTemp = node1->HuffmanLeft;
    TreeNode* HuffmanRightTemp = node1->HuffmanRight;
    int temp = node1->value;
    char tempp = node1->data;
    node1->HuffmanLeft = node2->HuffmanLeft;
    node1->HuffmanRight = node2->HuffmanRight;
    node1->value = node2->value;
    node1->data = node2->data;
    node2->HuffmanLeft = HuffmanLeftTemp;
    node2->HuffmanRight = HuffmanRightTemp;
    node2->value = temp;
    node2->data = tempp;
}

MinHeap::MinHeap()
{
    root = NULL;
    size = 0;
}

int MinHeap::getSize()
{
    return size;
}

TreeNode* MinHeap::getRoot()
{
    return root;
}

void MinHeap::insert(char data, int value, TreeNode* HuffmanLeft, TreeNode* HuffmanRight)
{
    getLastNode();
    TreeNode* newNode = new TreeNode(value, data);
    newNode->HuffmanLeft = HuffmanLeft;
    newNode->HuffmanRight = HuffmanRight;

    if (!root)
        root = newNode;
    else
    {
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode* node = q.front();
            q.pop();

            if (!node->left)
            {
                node->left = newNode;
                newNode->parent = node;
                break;
            }
            else if (!node->right)
            {
                node->right = newNode;
                newNode->parent = node;
                break;
            }
            else
            {
                q.push(node->left);
                q.push(node->right);
            }
        }
    }
    size++;
    heapifyUp(newNode);
}

TreeNode* MinHeap::deleteMin()
{
    if (!root)
    {
        cout << "Heap is empty." << endl;
        return NULL;
    }
    TreeNode* minValue = new TreeNode(root->value, root->data);
    minValue->HuffmanLeft = root->HuffmanLeft;
    minValue->HuffmanRight = root->HuffmanRight;
    if (size == 1)
    {
        delete root;
        root = nullptr;
    }
    else
    {
        TreeNode* lastNode = getLastNode();
        swapValues(root, lastNode);
        if (lastNode->parent->right == lastNode)
            lastNode->parent->right = nullptr;
        else
            lastNode->parent->left = nullptr;

        delete lastNode;
        lastNode = nullptr;
        heapifyDown(root);
    }
    size--;
    return minValue;
}

bool MinHeap::isEmpty()
{
    return size == 0;
}

// Function to build frequency table
map<char, int> buildFrequencyTable(const string& text)
{
    map<char, int> frequencyTable;

    for (char ch : text)
    {
        frequencyTable[ch]++;
    }

    return frequencyTable;
}

// Function to print the frequency table
void printFrequencyTable(const map<char, int>& frequencyTable)
{
    cout << "Character Frequencies:" << endl;
    for (const auto& entry : frequencyTable)
    {
        cout << "'" << entry.first << "': " << entry.second << endl;
    }
}

// Function to build Huffman Tree
TreeNode* buildHuffmanTree(const map<char, int>& frequencyTable)
{
    MinHeap heap;
    for (const auto& entry : frequencyTable)
    {
        heap.insert(entry.first, entry.second, NULL, NULL);
    }

    while (heap.getSize() > 1)
    {
        TreeNode* left = heap.deleteMin();
        TreeNode* right = heap.deleteMin();

        TreeNode* newNode = new TreeNode(left->value + right->value, '\0');
        /*newNode->HuffmanLeft = left;
        newNode->HuffmanRight = right;*/

        left->parent = newNode;
        right->parent = newNode;

        heap.insert(newNode->data, newNode->value, left, right);
    }

    return heap.getRoot();
}

// Function to parse codes from file
map<char, string> parseCodesFromFile(const string& filename)
{
    map<char, string> huffmanCodes;
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line.length() > 3) // At least one char, one colon, one space, one code
            {
                char ch = line[0];
                string code = line.substr(3);
                huffmanCodes[ch] = code;
            }
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file " << filename << endl;
    }
    return huffmanCodes;
}

// Function to build Huffman Tree from codes
TreeNode* buildHuffmanTreeFromCodes(const map<char, string>& huffmanCodes)
{
    TreeNode* root = new TreeNode();
    for (const auto& pair : huffmanCodes)
    {
        char ch = pair.first;
        string code = pair.second;
        TreeNode* currentNode = root;
        for (char bit : code)
        {
            if (bit == '0')
            {
                if (!currentNode->HuffmanLeft)
                {
                    currentNode->HuffmanLeft = new TreeNode();
                }
                currentNode = currentNode->HuffmanLeft;
            }
            else if (bit == '1')
            {
                if (!currentNode->HuffmanRight)
                {
                    currentNode->HuffmanRight = new TreeNode();
                }
                currentNode = currentNode->HuffmanRight;
            }
        }
        currentNode->data = ch;
    }
    return root;
}

// Function to print Huffman codes
void printHuffmanCodes(TreeNode* root, string code)
{
    if (!root) return;

    if (root->data != '\0')
    {
        cout << root->data << ": " << code << endl;
    }

    printHuffmanCodes(root->HuffmanLeft, code + "0");
    printHuffmanCodes(root->HuffmanRight, code + "1");
}

void storeHuffmanCodes(TreeNode* root, const string& code, ofstream& outfile)
{
    if (!root) return;

    if (root->data != '\0')
    {
        outfile << root->data << ": " << code << endl;
    }

    storeHuffmanCodes(root->HuffmanLeft, code + "0", outfile);
    storeHuffmanCodes(root->HuffmanRight, code + "1", outfile);
}

void writeHuffmanCodesToFile(TreeNode* root, const string& filename)
{
    ofstream outfile(filename);
    if (outfile.is_open())
    {
        storeHuffmanCodes(root, "", outfile);
        outfile.close();
    }
    else
    {
        cout << "Unable to open file " << filename << endl;
    }
}

void readTextFromFile(const string& filename, string& text)
{
    ifstream file(filename);

    if (file.is_open())
    {
        char ch;
        while (file.get(ch))
        {
            text += ch;
        }
        file.close();
    }
    else
    {
        cout << "Unable to open the file." << endl;
    }
}

void decodeText(TreeNode* root)
{
    ifstream encodedFile("encoded.txt");
    ofstream decodedFile("decoded.txt");
    TreeNode* curr = root;
    char bit;
    while (encodedFile.get(bit))
    {
        if (bit == '0')
        {
            curr = curr->HuffmanLeft;
        }
        else if (bit == '1')
        {
            curr = curr->HuffmanRight;
        }
        if (curr->HuffmanLeft == NULL && curr->HuffmanRight == NULL)
        {
            decodedFile << curr->data;
            curr = root;
        }
    }
}

void generateHuffmanCodes(TreeNode* root, string code, map<char, string>& huffmanCodes)
{
    if (!root)
        return;

    if (root->data != '\0')
        huffmanCodes[root->data] = code;

    generateHuffmanCodes(root->HuffmanLeft, code + "0", huffmanCodes);
    generateHuffmanCodes(root->HuffmanRight, code + "1", huffmanCodes);
}

void encodeText(const string& text, const map<char, string>& huffmanCodes, const string& encodedFilename)
{
    ofstream encodedFile(encodedFilename);
    if (encodedFile.is_open())
    {
        for (char ch : text)
        {
            encodedFile << huffmanCodes.at(ch);
        }
        encodedFile.close();
    }
    else
    {
        cout << "Unable to open file " << encodedFilename << endl;
    }
}