#include <iostream>


struct Item {
    unsigned int index;
};



class ArraySimple {

    private:
        /* List current length */
        unsigned int length;
        /* Pointer to list */
        Item *list;

    protected:
        /** Print list function **/
        void printList() {
            std::cout << "List length: " << length << std::endl;
            for (int i = 0; i < length; i++) {
                std::cout << "| " << list[i].index << " ";
            }
            if (length > 0)
                std::cout << "|" << std::endl;
            std::cout << "--------------------------" << std::endl;
        };

        /**
         * Insert an item at the end of the list.
         *
         * @param item
        */
        void push (Item item, unsigned int index) {
            // Init temporary list
            Item *tempList = new Item[length + 1];
            // Fill temporary list
            for (int i = 0; i < index; i++) {
                tempList[i] = list[i];
            }
            // Insert new item
            tempList[index] = item;
            // Complete list
            for (int i = index; i < length; i++) {
                tempList[i+1] = list[i];
            }
            // Update private properties
            length++;
            list = tempList;
        }

    public:
        /** Constructor **/
        ArraySimple() : length(0), list(new Item[0]) {}

        /**
         * Insert an item at the end of the list.
         *
         * @param item
        */
        void append(Item item) { push(item, length); };

        /**
         * Insert an item at the begining of the list.
         *
         * @param item
        */
        void insertInit(Item item) { push(item, 0); };

        /**
         * Insert an item at the given index position.
         *
         * @param item
         * @param index
        */
       void insert(Item item, unsigned int index) { push(item, index); };

        /**
         * Print list to console.
        */
        void print(void) { printList(); };

        /**
         * Get list length
         *
         * @return length
        */
        int getLength() { return length; };

};






int main() {

    Item item1{1};
    Item item2{2};
    Item item3{3};
    Item item4{4};
    Item item5{5};
    Item item6{6};

    ArraySimple array;
    array.print();

    array.append(item4);
    array.print();

    array.append(item5);
    array.print();

    array.insertInit(item1);
    array.print();

    array.insert(item2, 1);
    array.print();

    array.insert(item3, 2);
    array.print();

    array.append(item6);
    array.print();

    return 0;
}
