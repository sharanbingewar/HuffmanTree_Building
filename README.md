# HuffmanTree_Building

This project implements the **Huffman Tree Algorithm** in C++, a technique used for efficient data compression. Given a set of characters and their frequencies, the program builds a binary tree where more frequent characters have shorter binary codes. It uses a priority queue (min-heap) to ensure that the least frequent characters are combined first, forming a tree where each path from the root to a character assigns a unique binary code. These codes are printed in **pre-order traversal** to meet the assignment requirements.

The program also includes input validation to check that the character and frequency arrays are aligned. Multiple test cases are provided to demonstrate the functionality, ensuring that it works for different input values. This Huffman coding algorithm efficiently reduces data size and is widely used in file compression and communication systems.

## Inputs  
Character S = "abcdef" 
Frequencies f= {5, 9, 12, 13, 16, 45}
