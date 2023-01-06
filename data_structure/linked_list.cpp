#include <cassert>
#include <iostream>
#include <iomanip>      // std::setfill, std::setw
#include <string>


typedef unsigned int uint;


/**
 * Our data
*/
struct  Data
{
    std::string description;
    uint id;

    friend bool operator==(const Data& lhs, const Data& rhs) { return (lhs.id == rhs.id); };
    friend bool operator>(const Data& lhs, const Data& rhs)  { return (lhs.id > rhs.id); };
    friend bool operator<(const Data& lhs, const Data& rhs)  { return (lhs.id < rhs.id); };
    friend bool operator<=(const Data& lhs, const Data& rhs) { return (lhs.id <= rhs.id); };
    friend bool operator>=(const Data& lhs, const Data& rhs) { return (lhs.id >= rhs.id); };
    friend bool operator!=(const Data& lhs, const Data& rhs) { return (lhs.id != rhs.id); };
};


/**
 * Linked List node
*/
struct Node
{
    Data data;
    Node *next;
};


/**
 * Linked List class
*/
class LinkedList
{
private:
    Node *head;
    Node *tail;
    uint length;

    void startList(Node*& newNode);
    void insertAtInit(Node*& newNode);
    void insertAtEnd(Node*& newNode);
    void insertAtPos(Node*& newNode, uint index);
    void updateTail();

    Data removeSingle();
    Data removeFromInit();
    Data removeFromEnd();
    Data removeFromPos(uint index);

    static void advance(Node*& node);
    static Node* take(Node*& node);
    static void split(Node* source, Node*& nodeFront, Node*& nodeEnd);
    static Node* merge(Node*& node1, Node*& node2);
    static void mergeSort(Node*& startNode);

protected:
    void addNode(const Data& data, uint index);
    Data removeNode(uint index);

public:
    /**
     * Constructor
    */
    LinkedList();
    /**
     * Destructor
    */
    ~LinkedList();

    /**
     * Print list to console
    */
    void print() const;

    /**
     * @brief Insert new data at the begining of the list.
     *
     * @param data new data
     */
    void push(const Data &data) { addNode(data, 0); };

    /**
     * @brief Insert new data at the end of the list.
     *
     * @param data new data
     */
    void append(const Data &data) { addNode(data, length); };

    /**
     * @brief Insert new data at a given index postion.
     *
     * @param data new data
     * @param idx index/positon
     */
    void insertAt(const Data &data, uint idx) { addNode(data, idx); };

    /**
     * @brief Remove the last data from the list.
     *
     * @return Data removed data
     */
    Data pop() { return removeNode(length-1); };

    /**
     * @brief Remove the frist data from the list.
     *
     * @return Data removed data
     */
    Data remove() { return removeNode(0); };

    /**
     * @brief Remove data from the list given a index/position.
     *
     * @param idx index
     * @return Data removed data
     */
    Data removeFrom(uint idx) { return removeNode(idx); };

    /**
     * @brief Sort list by data using merge sort algorithm.
     *
     */
    void sort() { mergeSort(head); };
};


LinkedList::LinkedList() : head(nullptr), tail(nullptr), length(0)
{
}

LinkedList::~LinkedList()
{
}

/* PRINTING METHOD */

void LinkedList::print() const
{
    Node *temp = this->head;

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

/* INSERTIONS METHODS */

void LinkedList::addNode(const Data& data, uint index)
{
    if (index > length) {
        std::cout << "Invalid position." << std::endl;
        return;
    }

    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;

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

void LinkedList::startList(Node*& newNode)
{
    head = newNode;
    tail = newNode;
}

void LinkedList::insertAtInit(Node*& newNode)
{
    newNode->next = head;
    head = newNode;
}

void LinkedList::insertAtEnd(Node*& newNode)
{
    tail->next = newNode;
    tail = newNode;
}

void LinkedList::insertAtPos(Node*& newNode, uint index)
{
    Node *currNode = head;
    int i = 0;
    while (i < index-1)
    {
        advance(currNode);
        i++;
    }
    newNode->next = currNode->next;
    currNode->next = newNode;
}

/* REMOVALS METHODS */

Data LinkedList::removeNode(uint index)
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

Data LinkedList::removeSingle()
{
    // Get data
    Data data = head->data;
    // Store node to be deleted
    Node *tempNode = head;
    // Clear reference pointers
    head = nullptr;
    tail = nullptr;
    // Delete removed node
    delete tempNode;

    return data;
}

Data LinkedList::removeFromEnd()
{
    Node *currNode = head;
    Node *nextNode = head->next;        // needed to delete node pointer and keep only data
    // Iterate through nodes until next be the tail
    while (nextNode->next != nullptr)
    {
        currNode = nextNode;
        advance(nextNode);
    }
    // Get next (tail) data
    Data data = nextNode->data;
    // Update tail with current node
    tail = currNode;
    tail->next = nullptr;
    // Clear removed node
    delete nextNode;

    return data;
}

Data LinkedList::removeFromInit()
{
    // Get data
    Data data = head->data;
    // Set new head
    advance(head);

    return data;
}

Data LinkedList::removeFromPos(uint idx)
{
    Node *currNode = head;
    Node *nextNode = head->next;
    uint i = 0;
    // Iterate through nodes until previous node
    while (i < idx-1) {
        advance(currNode);
        nextNode = currNode->next;
        i++;
    }
    // Get data
    Data data = nextNode->data;
    // Update next node
    currNode->next = nextNode->next;
    // Delete removed node
    delete nextNode;

    return data;
}

/* SORT MEHTODS */

void LinkedList::split(Node* source, Node*& nodeFront, Node*& nodeEnd)
{
    Node* fast = source->next;
    Node* slow = source;
    /* Iterate through the list to slow ptr achieve the middle. */
    while (fast != nullptr)
    {
        advance(fast);
        if (fast != nullptr)
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

Node* LinkedList::merge(Node*& node1, Node*& node2)
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

void LinkedList::mergeSort(Node*& startNode)
{
    if (startNode == nullptr || startNode->next == nullptr)
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

/* AUXILIAR Methods */

void LinkedList::advance(Node*& node)
{
    assert(node != nullptr);
    node = node->next;
}

Node* LinkedList::take(Node*& node)
{
    Node* result = node;
    advance(node);
    return result;
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
    LinkedList llist = LinkedList();
    llist.print();

    /* Add data */

    llist.append(data0);
    llist.print();

    llist.append(data1);
    llist.print();

    llist.push(data2);
    llist.print();

    llist.insertAt(data3, 2);
    llist.print();

    llist.insertAt(data4, 3);
    llist.print();

    /* Sort list by data */

    llist.sort();
    llist.print();

    /* Remove data */

    Data dataOut = llist.remove();
    std::cout << "DATA REMOVED - id: " << dataOut.id << ", description: " << dataOut.description << std::endl;
    llist.print();

    dataOut = llist.removeFrom(2);
    std::cout << "DATA REMOVED - id: " << dataOut.id << ", description: " << dataOut.description << std::endl;
    llist.print();

    dataOut = llist.removeFrom(1);
    std::cout << "DATA REMOVED - id: " << dataOut.id << ", description: " << dataOut.description << std::endl;
    llist.print();

    dataOut = llist.pop();
    std::cout << "DATA REMOVED - id: " << dataOut.id << ", description: " << dataOut.description << std::endl;
    llist.print();

    // Invalid remove postion
    llist.removeFrom(2);

    dataOut = llist.pop();
    std::cout << "DATA REMOVED - id: " << dataOut.id << ", description: " << dataOut.description << std::endl;
    llist.print();

    // Invalid remove postion
    llist.remove();

    return 0;
}