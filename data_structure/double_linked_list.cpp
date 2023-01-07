#include <iostream>
#include <iomanip>      // std::setfill, std::setw
#include <memory>
#include "data.hpp"

/**
 * Linked List node
*/
struct Node
{
    Data data;
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;
};


class DoubleLinkedList
{
  public:
    DoubleLinkedList(/* args */);
    ~DoubleLinkedList();

    void print() const;


  private:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    int length;

    static void advance(std::shared_ptr<Node>& node);
    static std::shared_ptr<Node> take(std::shared_ptr<Node>& node);
};


DoubleLinkedList::DoubleLinkedList(/* args */)
{
    head = std::make_shared<Node>();
    tail = std::make_shared<Node>();
    length = 0;

    tail->prev = head;
    head->next = tail;
}

DoubleLinkedList::~DoubleLinkedList()
{
}

/* PRINTING METHOD */

void DoubleLinkedList::print() const
{
    std::shared_ptr<Node> temp = this->head;

    std::cout << "Printing list of length " << length << "." << std::endl;

    int index = 0;
    while( temp != nullptr ) {
        std::cout << "(" << std::setw(2) << std::setfill('0') << index << ") ";
        std::cout << "id: "             << temp->data.id << ", ";
        std::cout << "description: "    << temp->data.description << std::endl;

        advance(temp);
    }

    std::cout << std::endl;
}


/* AUXILIAR METHODS */

void DoubleLinkedList::advance(std::shared_ptr<Node>& node)
{
    if (node != nullptr)
    {
        node = node->next;
    }
}

std::shared_ptr<Node> DoubleLinkedList::take(std::shared_ptr<Node>& node)
{
    std::shared_ptr<Node> result = node;
    advance(node);
    return result;
}



int main()
{
    DoubleLinkedList dlList();



    return 0;
}