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

protected:
    void addNode(const Data &data, unsigned int index);
    Data removeNode();

public:
    LinkedList();
    ~LinkedList();

    void print() const;

    void push(const Data &data) { addNode(data, 0); };
    void append(const Data &data) { addNode(data, length); };
    void insertAt(const Data &data, unsigned int idx) { addNode(data, idx); }
};

/**
 * Constructor
*/
LinkedList::LinkedList() : head(nullptr), tail(nullptr), length(0)
{
}

/**
 * Destructor
*/
LinkedList::~LinkedList()
{
}

/**
 * Print list to console
*/
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
        head = newNode;
        tail = newNode;
    }
    else if (index == length) {
        tail->next = newNode;
        tail = newNode;
    }
    else if (index == 0) {
        newNode->next = head;
        head = newNode;
    }
    else {
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

    length++;
}

Data LinkedList::removeNode()
{
    return Data();
}


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

    return 0;
}