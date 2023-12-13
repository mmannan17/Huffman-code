#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

class HuffmanNode {
public:
    HuffmanNode(char ch, int freq, HuffmanNode* parent = nullptr, HuffmanNode* left = nullptr, HuffmanNode* right = nullptr) 
        : character(ch), frequency(freq), parent(parent), left(left), right(right) {}

    char getCharacter() const { return character; }
    int getFrequency() const { return frequency; }
    bool isLeaf() const { return left == nullptr && right == nullptr; }

    

private:
    char character;
    int frequency;
    HuffmanNode* parent;
    HuffmanNode* left;
    HuffmanNode* right;
};

#endif // HUFFMAN_NODE_H
