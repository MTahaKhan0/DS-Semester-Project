# DS-Semester-Project
File Compression and Decompression Program
This project implements a Huffman coding algorithm in C++. Huffman coding is a compression algorithm used to reduce the size of files by encoding characters with variable-length codes based on their frequency of occurrence.
Features
•	Read Text from File: Load text data from a specified file.
•	Build Frequency Table: Generate a frequency table from the text data.
•	Build Huffman Tree: Construct a Huffman tree based on the frequency table.
•	Print Huffman Codes: Display the generated Huffman codes for each character.
•	Save Huffman Codes to File: Save the Huffman codes to a file.
•	Encode Text to File: Encode the text data using Huffman codes and save it to a file.
•	Decode Text from File: Decode the encoded text using the Huffman tree and save the decoded text to a file.
Files
Huffman.h and Huffman.cpp: Contains the implementation of the Huffman coding algorithm including the TreeNode and MinHeap classes, and various helper functions.
main.cpp: The main file that contains the menu-driven interface for the program.

Follow the Menu Options:
1: Read text from a file.
2: Build frequency table.
3: Build Huffman tree.
4: Print Huffman codes.
5: Save Huffman codes to file.
6: Encode text to file (encoded.txt).
7: Decode text from file (encoded.txt).
8: Exit the program.
Example
1.	Read a text.
2.	Build the frequency table.
3.	Build the Huffman tree.
4.	Print and save the Huffman codes to codes.txt.
5.	Encode the text and save it to encoded.txt.
6.	Decode the text from encoded.txt and save the output to decoded.txt.
Dependencies
Standard C++ libraries (iostream, map, queue, fstream, istream, string).
Contact
For any questions or issues, please open an issue on this repository or contact the author at i220828@nu.edu.pk OR i221203@nu.edu.pk .

