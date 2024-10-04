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
    HuffmanNode* leftChild;     // Pointer
    HuffmanNode* rightChild;    
    
    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), leftChild(nullptr), rightChild(nullptr) {}
};

// Comparison operator for priority queue
struct FrequencyComparator 
{
    bool operator()(HuffmanNode* leftNode, HuffmanNode* rightNode) 
    {
        return leftNode->frequency > rightNode->frequency; 
    }
};

// Function to generate Huffman Codes
void computeHuffmanCodes(HuffmanNode* rootNode, const string& codePath, unordered_map<char, string>& huffmanCodeMap) 
{
    if (!rootNode) return;
    // Leaf node: store the character and its code
    if (!rootNode->leftChild && !rootNode->rightChild) 
    {
        huffmanCodeMap[rootNode->character] = codePath; 
    }
    // Traverse left and right subtrees
    computeHuffmanCodes(rootNode->leftChild, codePath + "0", huffmanCodeMap); 
    computeHuffmanCodes(rootNode->rightChild, codePath + "1", huffmanCodeMap); 
}

// Function to build the Huffman Tree and generate codes
void buildHuffmanTreeAndGenerateCodes(const vector<char>& charSet, const vector<int>& charFrequencies) 
{
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, FrequencyComparator> minFrequencyHeap; 

    for (size_t i = 0; i < charSet.size(); i++) 
    {
        minFrequencyHeap.push(new HuffmanNode(charSet[i], charFrequencies[i]));
    }

    // Build the Huffman Tree
    while (minFrequencyHeap.size() > 1) 
    {
        HuffmanNode* leftNode = minFrequencyHeap.top(); minFrequencyHeap.pop(); 
        HuffmanNode* rightNode = minFrequencyHeap.top(); minFrequencyHeap.pop();

        HuffmanNode* internalNode = new HuffmanNode('$', leftNode->frequency + rightNode->frequency);
        internalNode->leftChild = leftNode;
        internalNode->rightChild = rightNode;

        minFrequencyHeap.push(internalNode); // Add the new node to the heap
    }

    // The remaining node is the root of the Huffman Tree
    HuffmanNode* huffmanTreeRoot = minFrequencyHeap.top(); minFrequencyHeap.pop();
    unordered_map<char, string> huffmanCodeMap;
    computeHuffmanCodes(huffmanTreeRoot, "", huffmanCodeMap);

    cout << "Output:\n";
    vector<char> Order = {'f', 'c', 'd', 'a', 'b', 'e'};
    for (char ch : Order) 
    {
        cout << huffmanCodeMap[ch] << "   "; 
    }
    cout << endl;
}

// Main function
int main() 
{
    vector<char> charSet = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> charFrequencies = {5, 9, 12, 13, 16, 45};

    buildHuffmanTreeAndGenerateCodes(charSet, charFrequencies); 
    return 0;
}
