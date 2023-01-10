#include <cassert>
#include <iostream>
#include <iomanip>      // std::setfill, std::setw
#include "data.hpp"

/**
 * Linked List class
*/
class CircularList
{
  public:
    /**
     * Constructor
    */
    CircularList();

    /**
     * Destructor
    */
    ~CircularList();

    struct Node
    {
        Data data;
        Node *next;
    };

    /**
     * Print list to console
    */
    void print() const;
    void print(int n) const;

    /**
     * @brief Insert new data at the end of the list.
     *
     * @param data new data
     */
    void append(const Data& data);

    Data remove();

    /**
     * @brief Sort list by data using merge sort algorithm.
     *
     */
    void sort();

  private:
    Node* head;
    Node* last;
    uint length;

    void startList(Node*& newNode);
    void insertAtEnd(Node*& newNode);
    void updateLast();

    Data removeSingle();
    Data removeFromEnd();

    static void advance(Node*& node);
    static void mergeSort(Node*& startNode);
    static void split(Node* source, Node*& nodeFront, Node*& nodeEnd);
    static Node* take(Node*& node);
    static Node* merge(Node*& node1, Node*& node2);
};

/* CONSTRUCTOR / DESTRUCTOR */

CircularList::CircularList() : head(nullptr), last(nullptr), length(0)
{
}

CircularList::~CircularList()
{
}


/* AUXILIAR METHODS */

void CircularList::advance(Node*& node)
{
    assert(node != nullptr);
    node = node->next;
}

CircularList::Node* CircularList::take(Node*& node)
{
    Node* result = node;
    advance(node);
    return result;
}

void CircularList::updateLast()
{
    Node* curr = head;
    // Iterate the whole list
    while (curr->next != nullptr && curr->next != curr)
    {
        advance(curr);
    }
    // Update tail
    last = curr;
    last->next = head;
}

void CircularList::print() const
{
    std::cout << "Printing list of length " << length << "." << std::endl;

    if (head != nullptr)
    {
        Node* temp = head;

        int index = 0;
        do {
            std::cout << "(" << std::setw(2) << std::setfill('0') << index << ") ";
            std::cout << "id: "             << temp->data.id << ", ";
            std::cout << "description: "    << temp->data.description << std::endl;

            advance(temp);
            index++;
        }
        while( temp != head );
    }

    std::cout << std::endl;
}


void CircularList::print(int n) const
{
    std::cout << "Printing list of length " << length << "." << std::endl;

    if (head != nullptr)
    {
        Node* temp = head;

        for (int i = 0; i < n; i++)
        {
            std::cout << "(" << std::setw(2) << std::setfill('0') << i % length << ") ";
            std::cout << "id: "             << temp->data.id << ", ";
            std::cout << "description: "    << temp->data.description << std::endl;

            advance(temp);
        }
    }
    std::cout << std::endl;
}


/* INSERTIONS METHODS */

void CircularList::append(const Data& data)
{
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;

    if (head == nullptr && last == nullptr) {
        startList(newNode);
    }
    else {
       insertAtEnd(newNode);
    }

    length++;
}

void CircularList::startList(Node*& newNode)
{
    head = newNode;
    head->next = last;
    last = newNode;
    last->next = head;
}

void CircularList::insertAtEnd(Node*& newNode)
{
    last->next = newNode;
    newNode->next = head;
    last = newNode;
}

/* REMOVALS METHODS */

Data CircularList::remove()
{
    Data data{};
    // Empty list case
    if (head == nullptr || length < 1) {
        std::cout << "The list is empty." << std::endl << std::endl;
        return data;
    }
    // Removing node cases
    if (head->next == head){
        data = removeSingle();
    }
    else{
        data = removeFromEnd();
    }
    // Decrement list length
    length--;

    return data;
}

Data CircularList::removeSingle()
{
    // Get data
    Data data = head->data;
    // Store node to be deleted
    Node* tempNode = head;
    // Clear reference pointers
    head = nullptr;
    last = nullptr;
    // Delete removed node
    delete tempNode;

    return data;
}

Data CircularList::removeFromEnd()
{
    Node* currNode = head;
    Node* nextNode = head->next;        // needed to delete node pointer and keep only data
    // Iterate through nodes until next be the tail
    while (nextNode->next != head && nextNode->next != nullptr)
    {
        currNode = take(nextNode);
    }
    // Get next (tail) data
    Data data = nextNode->data;
    // Update tail with current node
    last = currNode;
    last->next = head;
    // Clear removed node
    delete nextNode;

    return data;
}

/* SORT METHODS */

void CircularList::split(Node* source, Node*& nodeFront, Node*& nodeEnd)
{
    Node* fast = source->next;
    Node* slow = source;
    /* Iterate through the list to slow ptr achieve the middle. */
    while (fast != nullptr && fast != source)
    {
        advance(fast);
        if (fast != nullptr && fast != source)
        {
            advance(slow);      // Advance fast two nodes
            advance(fast);      // and slow one node
        }
    }
    // Update return
    nodeFront = source;
    nodeEnd = slow->next;
    slow->next = nullptr;       // Stop first part in the middle
}

CircularList::Node* CircularList::merge(Node*& node1, Node*& node2)
{
    if (node2 == nullptr)
        return node1;

    if (node1 == nullptr)
        return node2;

    Node* mergedHead = (node1->data <= node2->data) ? take(node1) : take(node2);
    Node* currNode = mergedHead;

    while (node1 != nullptr && node2 != nullptr)
    {
        // Get smallest data and update current node
        if (node1->data > node2->data)
        {  // Update current node and node 2
            currNode->next = take(node2);
        }
        else
        {  // Update current node and node 1
            currNode->next = take(node1);
        }
        // Update current node to next
        advance(currNode);
    }
    // In case of node 1 is not empty, complete the list with it
    if (node1 != nullptr)
        currNode->next = node1;
    // In case of node 2 is not empty, complete the list with it
    if (node2 != nullptr)
        currNode->next = node2;

    return mergedHead;
}

void CircularList::mergeSort(Node*& startNode)
{
    if (startNode == nullptr || startNode->next == nullptr || startNode->next == startNode)
        return;

    Node* frontNode;
    Node* middleNode;
    // Split list
    split(startNode, frontNode, middleNode);
    // Sort the splited lists recursively
    mergeSort(frontNode);
    mergeSort(middleNode);
    // Merge two sorted lists
    startNode = merge(frontNode, middleNode);
}

void CircularList::sort()
{
    last->next = nullptr; // Break the chain
    mergeSort(head);
    updateLast();
}


/**
 * @brief Main function
 *
 * @return int return condition
 */
int main()
{
    /* MY DATA */
    Data data0{"Zero ground", 0};
    Data data1{"First data", 1};
    Data data2{"Second data", 2};
    Data data3{"Third data", 3};
    Data data4{"Something generic", 4};

    /* LINKED LIST */
    CircularList clist = CircularList();


    clist.append(data1);
    clist.append(data4);
    clist.append(data3);
    clist.append(data2);
    clist.append(data0);

    clist.print();
    clist.print(15);

    /* Sort list by data */
    std::cout << "SORT LIST" << std::endl << std::endl;
    clist.sort();

    clist.print();
    clist.print(8);

    clist.remove();
    clist.print();

    clist.remove();
    clist.print();

    clist.remove();
    clist.print();

    clist.remove();
    clist.print();

    clist.remove();
    clist.print();

    return 0;
}