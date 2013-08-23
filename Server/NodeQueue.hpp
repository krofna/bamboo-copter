#ifndef NODE_QUEUE_HPP
#define NODE_QUEUE_HPP

#include "Shared/BasicTypes.hpp"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cstring>
#include <limits>

class Node;

class NodeQueue
{
public:
    NodeQueue();
    
    bool Empty();
    void Clear();
    void Insert(Node* pNode);
    void DecreaseKey(size_t i);
    Node* ExtractMin();

private:
    void Heapify(size_t i);

    inline size_t Parent (size_t i) { return (i - 1) / 2; }
    inline size_t Left   (size_t i) { return (i * 2) + 1; }
    inline size_t Right  (size_t i) { return (i * 2) + 2; }
    
    size_t Size;
    std::vector<Node*> A;
};

#endif
