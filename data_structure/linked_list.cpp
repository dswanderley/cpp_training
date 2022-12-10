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
    void addNode(const Data &data);
    Data removeNode();

public:
    LinkedList();
    ~LinkedList();

    void print() const;

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


void LinkedList::addNode(const Data &data)
{
    Node Node{data, nullptr};

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



    return 0;
}