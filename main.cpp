#include <iostream>
#include <map>
#include <queue>
#include <fstream>
#include <istream>
#include <string>
#include "Huffman.h"

using namespace std;

// Color codes
const string RESET = "\033[0m";
const string HEADER_BG = "\033[44m"; // Blue background for header
const string HEADER_FG = "\033[37m"; // White text color for header
const string MENU_ITEM = "\033[36m"; // Cyan text color for menu items
const string SECTION_TITLE = "\033[33m"; // Yellow text color for section titles
const string SUCCESS = "\033[32m"; // Green text color for success messages
const string ERROR = "\033[31m"; // Red text color for error messages
const string INFO = "\033[34m"; // Blue text color for informational messages

void displayMenu() {
    cout << HEADER_BG << HEADER_FG << "\nHuffman Coding Program" << RESET << endl;
    cout << HEADER_BG << HEADER_FG << "=========================" << RESET << endl;
    cout << MENU_ITEM << "1. Read text from file" << RESET << endl;
    cout << MENU_ITEM << "2. Build frequency table" << RESET << endl;
    cout << MENU_ITEM << "3. Build Huffman tree" << RESET << endl;
    cout << MENU_ITEM << "4. Print Huffman codes" << RESET << endl;
    cout << MENU_ITEM << "5. Save Huffman codes to file" << RESET << endl;
    cout << MENU_ITEM << "6. Encode text to file (encoded.txt)" << RESET << endl;
    cout << MENU_ITEM << "7. Decode text from file (encoded.txt)" << RESET << endl;
    cout << MENU_ITEM << "8. Exit" << RESET << endl;
    cout << HEADER_BG << HEADER_FG << "=========================" << RESET << endl;
    cout << INFO << "Enter your choice: " << RESET;
}

int main()
{
    string text;
    map<char, int> frequencyTable;
    TreeNode* huffmanTree = nullptr;
    map<char, string> huffmanCodes;

    while (true)
    {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            text = "";
            string filename;
            cout << INFO << "Enter the filename to read text (or type 'input' to enter text manually): " << RESET;
            cin >> filename;

            if (filename == "input") 
            {
                cout << INFO << "Enter text (type 'END' on a new line to finish):" << RESET << endl;
                string line;
                cin.ignore(); // Ignore the newline character left in the input buffer
                while (getline(cin, line) && line != "END") 
                {
                    text += line;
                }
            }
            else 
            {
                readTextFromFile(filename, text);
            }
            cout << SECTION_TITLE << "Text read:" << RESET << endl;
            cout << text << endl;
            break;
        }
        case 2:
        {
            frequencyTable = buildFrequencyTable(text);
            cout << SECTION_TITLE << "Frequency Table:" << RESET << endl;
            printFrequencyTable(frequencyTable);
            break;
        }
        case 3:
        {
            huffmanTree = buildHuffmanTree(frequencyTable);
            cout << SUCCESS << "Huffman Tree built successfully." << RESET << endl;
            break;
        }
        case 4:
        {
            if (huffmanTree)
            {
                cout << SECTION_TITLE << "Huffman Codes:" << RESET << endl;
                printHuffmanCodes(huffmanTree, "");
            }
            else
            {
                cout << ERROR << "Huffman Tree is not built yet." << RESET << endl;
            }
            break;
        }
        case 5:
        {
            if (huffmanTree)
            {
                string codesFilename = "codes.txt";
                writeHuffmanCodesToFile(huffmanTree, codesFilename);
                cout << SUCCESS << "Huffman codes saved to " << codesFilename << RESET << endl;
            }
            else
            {
                cout << ERROR << "Huffman Tree is not built yet." << RESET << endl;
            }
            break;
        }
        case 6:
        {
            if (huffmanTree)
            {
                generateHuffmanCodes(huffmanTree, "", huffmanCodes);
                string encodedFilename = "encoded.txt";
                encodeText(text, huffmanCodes, encodedFilename);

                // Calculate original and encoded sizes
                double originalSize = text.size();
                double encodedSize = 0;
                for (char ch : text) 
                {
                    encodedSize += huffmanCodes.at(ch).size();
                }
                encodedSize /= 8; // Convert bits to bytes

                cout << SUCCESS << "Text encoded and saved to " << encodedFilename << RESET << endl;
                cout << INFO << "Original Size: " << originalSize << " bytes" << RESET << endl;
                cout << INFO << "Encoded Size: " << encodedSize << " bytes" << RESET << endl;
                cout << INFO << "Compression Ratio: " << (originalSize / encodedSize) << ":" << RESET << endl;
            }
            else
            {
                cout << ERROR << "Huffman Tree is not built yet." << RESET << endl;
            }
            break;

        }
        case 7:
        {
            if (huffmanTree)
            {
                decodeText(huffmanTree);

                // Compare original and decoded text
                string decodedText;
                ifstream decodedFile("decoded.txt");
                getline(decodedFile, decodedText, '\0'); // Read entire file
                decodedFile.close();

                if (text == decodedText)
                {
                    cout << SUCCESS << "Text successfully decoded and matches the original." << RESET << endl;
                }
                else
                {
                    cout << ERROR << "Decoded text does not match the original." << RESET << endl;
                }
                cout << SUCCESS << "Text decoded and saved to decoded.txt" << RESET << endl;
            }
            else
            {
                cout << ERROR << "Huffman Tree is not built yet." << RESET << endl;
            }
            break;
        }
        case 8:
        {
            cout << SUCCESS << "Exiting program. Goodbye!" << RESET << endl;
            return 0;
        }
        default:
        {
            cout << ERROR << "Invalid choice. Please try again." << RESET << endl;
            break;
        }
        }
    }

    return 0;
}
