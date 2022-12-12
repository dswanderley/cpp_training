#include <iostream>
#include <iomanip>      // std::setfill, std::setw
#include <string>


/**
 * Our data
*/
struct  Data
{
    unsigned int id;
    std::string description;
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
    unsigned int length;

    void startList(Node *&newNode);
    void insertAtInit(Node *&newNode);
    void insertAtEnd(Node *&newNode);
    void insertAtPos(Node *&newNode, unsigned int index);

    Data removeSingle();
    Data removeFromInit();
    Data removeFromEnd();
    Data removeFromPos(unsigned int index);

protected:
    void addNode(const Data &data, unsigned int index);
    Data removeNode(unsigned int index);

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
    void insertAt(const Data &data, unsigned int idx) { addNode(data, idx); };

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
    Data removeFrom(unsigned int idx) { return removeNode(idx); };
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

        temp = temp->next;
    }

    std::cout << std::endl;
}


/* INSERTIONS METHODS */

void LinkedList::addNode(const Data &data, unsigned int index)
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

void LinkedList::startList(Node *&newNode)
{
    head = newNode;
    tail = newNode;
}

void LinkedList::insertAtInit(Node *&newNode)
{
    newNode->next = head;
    head = newNode;
}

void LinkedList::insertAtEnd(Node *&newNode)
{
    tail->next = newNode;
    tail = newNode;
}

void LinkedList::insertAtPos(Node *&newNode, unsigned int index)
{
    Node *currNode = head;
    int i = 0;
    while (i < index-1)
    {
        currNode = currNode->next;
        i++;
    }
    newNode->next = currNode->next;
    currNode->next = newNode;
}


/* REMOVALS METHODS */

Data LinkedList::removeNode(unsigned int index)
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
        nextNode = nextNode->next;
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
    // Create a tempNode to be deleted
    Node *tempNode = head;
    // Set new head
    head = head->next;
    // Delete old head
    delete tempNode;

    return data;
}

Data LinkedList::removeFromPos(unsigned int idx)
{
    Node *currNode = head;
    Node *nextNode = head->next;
    unsigned int i = 0;
    // Iterate through nodes until previous node
    while (i < idx-1) {
        currNode = currNode->next;
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


/**
 * @brief Main function
 *
 * @return int return condition
 */
int main()
{
    /* MY DATA */
    Data data0{0, "Zero ground"};
    Data data1{1, "First data"};
    Data data2{2, "Second data"};
    Data data3{3, "Third data"};
    Data data4{4, "Something generic"};

    /* LINKED LIST */
    LinkedList llist = LinkedList();
    llist.print();

    /* Add data */

    llist.append(data1);
    llist.print();

    llist.append(data4);
    llist.print();

    llist.push(data0);
    llist.print();

    llist.insertAt(data2, 2);
    llist.print();

    llist.insertAt(data3, 3);
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