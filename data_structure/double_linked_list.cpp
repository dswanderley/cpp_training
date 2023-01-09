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
    void printBackward() const;

    void push(const Data& data) { addNode(data, 0); };
    void append(const Data& data) { addNode(data, length); };
    void insertAt(const Data& data, uint idx) { addNode(data, idx); };

    Data pop() { return removeNode(length-1); };
    Data remove() { return removeNode(0); };
    Data removeFrom(int idx) { return removeNode(idx); };

  protected:
    void addNode(const Data& data, uint index);
    Data removeNode(int index);

  private:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    int length;

    static void advance(std::shared_ptr<Node>& node);
    static void goBack(std::shared_ptr<Node>& node);
    static std::shared_ptr<Node> take(std::shared_ptr<Node>& node);

    //void updateTail();
    void startList(std::shared_ptr<Node>& newNode);
    void insertAtInit(std::shared_ptr<Node>& newNode);
    void insertAtEnd(std::shared_ptr<Node>& newNode);
    void insertAtPos(std::shared_ptr<Node>& newNode, int index);

    Data removeSingle();
    Data removeFromInit();
    Data removeFromEnd();
    Data removeFromPos(int index);
};


DoubleLinkedList::DoubleLinkedList() : head(nullptr), tail(nullptr), length(0)
{
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

void DoubleLinkedList::printBackward() const
{
    std::shared_ptr<Node> temp = this->tail;

    std::cout << "Printing list of length " << length << "." << std::endl;

    int index = 0;
    while( temp != nullptr ) {
        std::cout << "(" << std::setw(2) << std::setfill('0') << index << ") ";
        std::cout << "id: "             << temp->data.id << ", ";
        std::cout << "description: "    << temp->data.description << std::endl;

        goBack(temp);
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

void DoubleLinkedList::goBack(std::shared_ptr<Node>& node)
{
    if (node != nullptr)
    {
        node = node->prev;
    }
}

std::shared_ptr<Node> DoubleLinkedList::take(std::shared_ptr<Node>& node)
{
    std::shared_ptr<Node> result = node;
    advance(node);
    return result;
}

/* INSERTIONS METHODS */

void DoubleLinkedList::addNode(const Data& data, uint index)
{
    if (index > length) {
        std::cout << "Invalid position." << std::endl;
        return;
    }

    std::shared_ptr<Node> newNode = std::make_shared<Node>();
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (head == nullptr && tail == nullptr) {
        startList(newNode);
    }
    else if (index == length) {
        insertAtEnd(newNode);
    }
    else if (index == 0) {
        insertAtInit(newNode);
    }
    else {
       insertAtPos(newNode, index);
    }

    length++;
}

void DoubleLinkedList::startList(std::shared_ptr<Node>& newNode)
{
    head = newNode;
    tail = newNode;
}

void DoubleLinkedList::insertAtInit(std::shared_ptr<Node>& newNode)
{
    // Update new data
    newNode->next = head;
    // Update head
    head->prev = newNode;
    head = newNode;
}

void DoubleLinkedList::insertAtEnd(std::shared_ptr<Node>& newNode)
{
    // Update new data
    newNode->prev = tail;
    // Update tail
    tail->next = newNode;
    tail = newNode;
}

void DoubleLinkedList::insertAtPos(std::shared_ptr<Node>& newNode, int index)
{
    std::shared_ptr<Node> currNode = head;
    int i = 0;
    while (i < index-1)
    {
        advance(currNode);
        i++;
    }
    // Update new node
    newNode->next = currNode->next;
    newNode->prev = currNode;
    // Update current node
    currNode->next = newNode;
}

/* REMOVALS METHODS */

Data DoubleLinkedList::removeNode(int index)
{
    Data data{};
    // Empty list case
    if (head == nullptr) {
        std::cout << "The list is empty." << std::endl << std::endl;
        return data;
    }
    // Invalid index
    if (index >= length) {
        std::cout << "Invalid position - index = " << index << std::endl << std::endl;
        return data;
    }
    // Removing node cases
    if (head->next == nullptr){
        data = removeSingle();
    }
    else if (index == length-1) {
        data = removeFromEnd();
    }
    else if (index == 0) {
        data = removeFromInit();
    }
    else{
        data = removeFromPos(index);
    }
    // Decrement list length
    length--;

    return data;
}

Data DoubleLinkedList::removeSingle()
{
    // Get data
    Data data = head->data;
    // Store node to be deleted
    std::weak_ptr<Node> tempNode = head;
    // Clear reference pointers
    head = nullptr;
    tail = nullptr;

    return data;
}

Data DoubleLinkedList::removeFromEnd()
{
    std::shared_ptr<Node> currNode = head;
    std::shared_ptr<Node> nextNode = head->next;        // needed to delete node pointer and keep only data
    // Iterate through nodes until next be the tail
    while (nextNode->next != nullptr)
    {
        currNode = take(nextNode);
    }
    // Get next (tail) data
    Data data = nextNode->data;
    // Update tail with current node
    tail = currNode;
    tail->next = nullptr;

    return data;
}

Data DoubleLinkedList::removeFromInit()
{
    // Get data
    Data data = head->data;
    // Set new head
    advance(head);
    head->prev = nullptr;

    return data;
}

Data DoubleLinkedList::removeFromPos(int idx)
{
    std::shared_ptr<Node> currNode = head;
    int i = 0;
    // Iterate through nodes until previous node
    while (i < idx) {
        advance(currNode);
        i++;
    }
    // Get data
    Data data = currNode->data;
    // Update next and prev nodes
    currNode->prev->next = currNode->next;
    currNode->next->prev = currNode->prev;

    return data;
}


int main()
{
    /* MY DATA */
    Data data0{"Zero ground", 0};
    Data data1{"First data", 1};
    Data data2{"Second data", 2};
    Data data3{"Third data", 3};
    Data data4{"Something generic", 4};

    /* DOUBLE LINKED LIST */
    DoubleLinkedList dlList = DoubleLinkedList();

    dlList.push(data2);
    dlList.push(data1);
    dlList.insertAt(data3, 2);
    dlList.insertAt(data4, 3);
    dlList.append(data0);

    dlList.print();
    dlList.printBackward();




    Data dataOut = dlList.pop();
    std::cout << "DATA REMOVED - id: " << dataOut.id << ", description: " << dataOut.description << std::endl << std::endl;

    dlList.print();
    dlList.printBackward();

    dataOut = dlList.removeFrom(2);
    std::cout << "DATA REMOVED - id: " << dataOut.id << ", description: " << dataOut.description << std::endl << std::endl;

    dataOut = dlList.removeFrom(1);
    std::cout << "DATA REMOVED - id: " << dataOut.id << ", description: " << dataOut.description << std::endl << std::endl;

    dlList.print();
    dlList.printBackward();

    dataOut = dlList.remove();
    std::cout << "DATA REMOVED - id: " << dataOut.id << ", description: " << dataOut.description << std::endl << std::endl;

    // Invalid remove postion
    dlList.removeFrom(2);

    dataOut = dlList.pop();
    std::cout << "DATA REMOVED - id: " << dataOut.id << ", description: " << dataOut.description << std::endl << std::endl;

    // Invalid remove postion
    dlList.remove();

    dlList.print();

    return 0;
}
