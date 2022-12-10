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

    void append(const Data &data) { addNode(data, length); };
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

    Node *temp;
    Node *node = new Node();
    node->data = data;
    node->next = nullptr;

    if (head == nullptr && tail == nullptr) {
        head = node;
        tail = node;

        length++;
    }
    else if (index == length) {
        tail->next = node;
        tail = node;

        length++;
    }
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

    llist.append(data0);
    llist.print();

    llist.append(data1);
    llist.print();
    
    llist.append(data2);
    llist.print();

    return 0;
}