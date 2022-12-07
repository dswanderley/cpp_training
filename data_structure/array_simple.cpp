#include <iostream>


struct Item {
    unsigned int index;
};



class ArraySimple {

    private:
        int length;
        Item *list;



    protected:

        void printList() {
            for (int i = 0; i < length; i++) {
                std::cout << list[i].index << std::endl;
            }
        };

        /**
         * Insert an item at the end of the list.
         *
         * @param item
        */
        void push (Item item) {
            // Init temporary list
            Item *tempList = new Item[length + 1];
            tempList[length] = item;
            // Fill temporary list
            for (int i = 0; i < length; i++){
                tempList[i] = list[i];
            }
            // Update private properties
            length++;
            list = tempList;
        };



    public:

        ArraySimple() : length(0), list(new Item[0]) {}

        void append(Item item) { push(item); };

        void print(void) { printList(); };

        int getLength() { return length; };


};






int main() {

    Item item1{1};
    Item item2{2};

    ArraySimple array;

    array.append(item1);
    array.append(item2);

    array.print();

    return 0;
}
