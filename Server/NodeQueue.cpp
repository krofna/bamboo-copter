#include "NodeQueue.hpp"
#include "Node.hpp"
#include <utility>

NodeQueue::NodeQueue()
{
    Clear();
}

bool NodeQueue::Empty()
{
    return Size == 0;
}

void NodeQueue::Clear()
{
    Size = 0;
}

void NodeQueue::Insert(Node* pNode)
{
    if (Size <= A.size())
        A.push_back(pNode);
    else
        A[Size] = pNode;
    
    pNode->i = Size++;

    DecreaseKey(Size);
}

void NodeQueue::DecreaseKey(size_t i)
{
    while (i > 0 && A[Parent(i)]->Cost > A[i]->Cost)
    {
        std::swap(A[Parent(i)]->i, A[i]->i);
        std::swap(A[Parent(i)], A[i]);
        i = Parent(i);
    }
}

Node* NodeQueue::ExtractMin()
{
    if (Size == 0)
        return nullptr;

    Node* Min = A[0];
    A[0] = A[--Size];
    A[0]->i = 0;
    Heapify(0);

    return Min;
}

void NodeQueue::Heapify(size_t i)
{
    size_t l = Left(i);
    size_t r = Right(i);
    size_t min;

    if (l < Size && A[l]->Cost < A[i]->Cost)
        min = l;
    else
        min = i;
    if (r < Size && A[r]->Cost < A[min]->Cost)
        min = r;
    if (min != i)
    {
        std::swap(A[i]->i, A[min]->i);
        std::swap(A[i], A[min]);
        Heapify(min);
    }
}
