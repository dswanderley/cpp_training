#include <iostream>
#include <string>


struct  Data
{
    unsigned int id;
    std::string name;
};


struct Node
{
    int data;
    Node *next;
};


class LinkedList
{
private:
    Node *head;
    Node *tail;
    unsigned int length;

protected:
    void addNode(const int &id);
    int removeNode();

public:
    LinkedList();
    ~LinkedList();

    void print() const;

};

LinkedList::LinkedList() : head(nullptr), tail(nullptr), length(0)
{
}

LinkedList::~LinkedList()
{
}

void LinkedList::print() const
{
    Node *temp = this->head;

    while( temp != nullptr ) {
        std::cout << temp->data << " | ";

        temp = temp->next;
    }
}


void LinkedList::addNode(const int &id)
{
    Node

}

int LinkedList::removeNode()
{
    return Node();
}




int main()
{
    LinkedList llist = LinkedList();



    return 0;
}