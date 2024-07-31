#pragma once
#include <iostream>
#include <map>
#include <queue>
#include <fstream>
#include<istream>
#include <string>

using namespace std;

// TreeNode class representing each node in the binary tree
class TreeNode 
{
public:
    char data;
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode* HuffmanLeft;
    TreeNode* HuffmanRight;

    TreeNode(int val = 0, char data = ' ');
};

// MinHeap class implementing the heap operations
class MinHeap 
{
private:
    TreeNode* root;
    int size;

    void heapifyUp(TreeNode* node);

    void heapifyDown(TreeNode* node);

    TreeNode* getLastNode();

    void swapValues(TreeNode* node1, TreeNode* node2);

public:
    MinHeap();

    int getSize();

    TreeNode* getRoot();

    void insert(char data, int value, TreeNode* HuffmanLeft, TreeNode* HuffmanRight);

    TreeNode* deleteMin();

    bool isEmpty();
};

map<char, int> buildFrequencyTable(const string& text);
void printFrequencyTable(const map<char, int>& frequencyTable);
TreeNode* buildHuffmanTree(const map<char, int>& frequencyTable);
map<char, string> parseCodesFromFile(const string& filename);
TreeNode* buildHuffmanTreeFromCodes(const map<char, string>& huffmanCodes);
void printHuffmanCodes(TreeNode* root, string code);
void storeHuffmanCodes(TreeNode* root, const string& code, ofstream& outfile);
void writeHuffmanCodesToFile(TreeNode* root, const string& filename = "codes.txt");
void readTextFromFile(const string& filename, string& text);
void decodeText(TreeNode* root);
void generateHuffmanCodes(TreeNode* root, string code, map<char, string>& huffmanCodes);
void encodeText(const string& text, const map<char, string>& huffmanCodes, const string& encodedFilename);

