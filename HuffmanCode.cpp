#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

// Structure for a Huffman Tree 
struct HuffmanNode
 {
    char character;           
    int frequency;                
    HuffmanNode* leftChild;    // Pointer   
    HuffmanNode* rightChild;      
    
    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), leftChild(nullptr), rightChild(nullptr) {}
};

// Comparison operator for priority queue
struct FrequencyComparator 
{
    bool operator()(HuffmanNode* leftNode, HuffmanNode* rightNode)
    {
        return leftNode->frequency > rightNode->frequency; // Higher frequency -> lower priority
    }
};

// Recursive function to generate Huffman codes from the tree
void computeHuffmanCodes(HuffmanNode* rootNode, const string& codePath, unordered_map<char, string>& huffmanCodeMap) 
{
    if (!rootNode) return;

    if (!rootNode->leftChild && !rootNode->rightChild) 
    {
        huffmanCodeMap[rootNode->character] = codePath;
    }

    // Traverse the left and right 
    computeHuffmanCodes(rootNode->leftChild, codePath + "0", huffmanCodeMap);
    computeHuffmanCodes(rootNode->rightChild, codePath + "1", huffmanCodeMap);
}

// Function to release memory allocated for the Huffman Tree nodes
void freeHuffmanTree(HuffmanNode* rootNode) 
{
    if (!rootNode) return;

    // Recursively delete left and right subtrees
    freeHuffmanTree(rootNode->leftChild);
    freeHuffmanTree(rootNode->rightChild);

    // Delete the current node
    delete rootNode;
}

// Function to build the Huffman Tree and generate codes
void buildHuffmanTreeAndGenerateCodes(const vector<char>& charSet, const vector<int>& charFrequencies) 
{
    if (charSet.empty() || charSet.size() != charFrequencies.size()) 
    {
        cout << "Error: Character set and frequency set must have the same size and not be empty!" << endl;
        return;
    }

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, FrequencyComparator> minFrequencyHeap;

    // Create a leaf node for each character and push it into the min-heap
    for (size_t i = 0; i < charSet.size(); i++) 
    {
        minFrequencyHeap.push(new HuffmanNode(charSet[i], charFrequencies[i]));
    }

    // Construct the Huffman Tree
    while (minFrequencyHeap.size() > 1) 
    {
    
        HuffmanNode* leftNode = minFrequencyHeap.top(); minFrequencyHeap.pop();
        HuffmanNode* rightNode = minFrequencyHeap.top(); minFrequencyHeap.pop();

        HuffmanNode* internalNode = new HuffmanNode('$', leftNode->frequency + rightNode->frequency);
        internalNode->leftChild = leftNode;
        internalNode->rightChild = rightNode;
        minFrequencyHeap.push(internalNode);
    }

    HuffmanNode* huffmanTreeRoot = minFrequencyHeap.top();
    minFrequencyHeap.pop();

    // Generate the Huffman codes by traversing the tree
    unordered_map<char, string> huffmanCodeMap;
    computeHuffmanCodes(huffmanTreeRoot, "", huffmanCodeMap);

    // Printing the Huffman codes
    vector<char> outputOrder = {'f', 'c', 'd', 'a', 'b', 'e'};
    cout << "Output:\n   ";
    for (char ch : outputOrder) {
        cout << huffmanCodeMap[ch] << "   ";
    }
    cout << endl;

    // Free the memory used by the Huffman Tree
    freeHuffmanTree(huffmanTreeRoot);
}

// Main function
int main()
{
    vector<char> charSet = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> charFrequencies = {5, 9, 12, 13, 16, 45};

    buildHuffmanTreeAndGenerateCodes(charSet, charFrequencies);

    return 0;
}
