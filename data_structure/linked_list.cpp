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

    //void clearList();
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

    Data pop() { return removeNode(length-1); };
    Data remove() { return removeNode(0); };
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
    if (index < 0 || index > length) {
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

    if (index < 0 || index >= length) {
        std::cout << "Invalid position." << std::endl;
        return data;
    }

    if (head == nullptr) {
        std::cout << "The list is empty." << std::endl;
        return data;
    }

    if (index == length) {
        //data = removeFromEnd();
    }
    else if (index == 0) {
        data = removeFromInit();
    }
    else{
        //data = removeFromPos(index);
    }

    return data;
}


Data LinkedList::removeFromInit()
{
    Data data = head->data;
    head = head->next;

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

    Data dataOut = llist.remove();
    std::cout << "id: " << dataOut.id << ", description: " << dataOut.description << std::endl;
    llist.print();

    return 0;
}