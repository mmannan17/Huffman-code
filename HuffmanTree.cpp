/*Mustafa Mannan U60366528*/



#include "HuffmanTree.hpp"

// Function to compress a string using Huffman encoding
std::string HuffmanTree::compress(const std::string inputStr) {
    // Map to keep track of the frequency of each character in the input string
    std::map<char, size_t> freqMap;
    for (auto &ch : inputStr) {
        freqMap[ch]++;
    }

    // Min-priority queue of HuffmanNodes
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> nodeQueue;
    
    for (auto &entry : freqMap) {
        nodeQueue.insert(new HuffmanNode(entry.first, entry.second));
    }

    // Build the Huffman tree
    while(nodeQueue.size() > 1) {
        HuffmanNode *node1 = nodeQueue.min();
        nodeQueue.removeMin();
        HuffmanNode *node2 = nodeQueue.min();
        nodeQueue.removeMin();
        
        HuffmanNode *parent = new HuffmanNode('\0', node1->getFrequency() + node2->getFrequency(), nullptr, node1, node2);
        nodeQueue.insert(parent);
    }

    rootNode = nodeQueue.min();
    
    // map to store the huffman code for each character
    std::map<char, std::string> codeMap;
    createEncodingMap(rootNode, "", codeMap);

    // encoding the input
    std::string result;
    for (auto &ch : inputStr) {
        result += codeMap[ch];
    }
    return result;
}

// recursive function creating a code for each character
void HuffmanTree::createEncodingMap(HuffmanNode *node, std::string code, std::map<char, std::string> &codeMap) {
    if (!node) return;
    if (node->isLeaf()) {
        codeMap[node->getCharacter()] = code;
    } else {
        createEncodingMap(node->left, code + "0", codeMap);
        createEncodingMap(node->right, code + "1", codeMap);
    }
}

// serialize huffman code into string
std::string HuffmanTree::serializeTree() const {
    return serializeHelper(rootNode);
}

// helperr function
std::string HuffmanTree::serializeHelper(HuffmanNode *node) const {
    if (!node) return "";
    if (node->isBranch()) {
        return serializeHelper(node->left) + serializeHelper(node->right) + "B";
    } 
    return "L" + std::string(1, node->getCharacter());
}

// reconstruct the huffman tree serialized string representation
HuffmanNode *HuffmanTree::buildTree(const std::string &treeData) const {
    std::stack<HuffmanNode*> nodeStack;
    for (auto it = treeData.rbegin(); it != treeData.rend(); ++it) {
        if (*it == 'L') {
            nodeStack.push(new HuffmanNode(*(++it), 0));
        } else {
            HuffmanNode *right = nodeStack.top(); nodeStack.pop();
            HuffmanNode *left = nodeStack.top(); nodeStack.pop();
            nodeStack.push(new HuffmanNode('\0', left->getFrequency() + right->getFrequency(), nullptr, left, right));
        }
    }
    return nodeStack.top();
}

// decompresses an encoded string 
std::string HuffmanTree::decompress(const std::string& inputCode, const std::string& serializedTree) {
    HuffmanNode *root = buildTree(serializedTree);
    HuffmanNode *current = root;
    std::string output;

    // Decode the input code
    for (auto &bit : inputCode) {
        current = (bit == '0') ? current->left : current->right;
        if (current->isLeaf()) {
            output.push_back(current->getCharacter());
            current = root;
        }
    }
    return output;
}
