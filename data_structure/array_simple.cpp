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
        };

        /**
         * Insert an item at the end of the list.
         *
         * @param index
         * @return The item
        */
        Item pop(unsigned int index, bool &valid) {
            // Output item
            Item item;
            // Validate index
            if (length > 0 && index < length && index >=0 ) {
                // Init temporary list
                Item *tempList = new Item[length + 1];
                // Get output item
                item = list[index];
                // Fill first part - before index
                for (int i = 0; i < index; i++) {
                    tempList[i] = list[i];
                }
                // Fill second part - after index
                for (int i = index + 1; i < length; i++) {
                    tempList[i-1] = list[i];
                }
                // Update private variables
                length--;
                list = tempList;
                // Set valid variable
                valid = true;
            }
            else {
                valid = false;
            }

            return item;
        };

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
        bool insert(Item item, unsigned int index) {
            bool ret = false;
            if (index >=0 && index < length) {
                push(item, index);
                ret = true;
            }

            return ret;
        };

        /**
         * Remove the first item from the list.
         *
         * @param valid
         * @return item
        */
        Item removeFirst(bool &valid) { return pop(0, valid); };

        /**
         * Remove the last item from the list.
         *
         * @param valid
         * @return item
        */
        Item removeLast(bool &valid) { return pop(length-1, valid); };

        /**
         * Remove an item from the list given an index.
         *
         * @param valid
         * @param index
         * @return item
        */
        Item remove(unsigned int index, bool &valid) { return pop(index, valid); };

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

        /**
         * Implementation of [] operator.
         *
         * @param index
         * @return List index value
        */
        Item& operator[](unsigned int index) {
            // Check index
            if (index < 0 || index >= length){
                std::cout << "Array index out of bound.";
                exit(0);
            }

            return list[index];
        }
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

    /* ADD ITEMS */
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


    /* VERIFY VALUE */
    Item itemVal;

    itemVal = array[0];
    std::cout << "\n index: " << itemVal.index << std::endl;

    itemVal = array[3];
    std::cout << "\n index: " << itemVal.index << std::endl;

    itemVal = array[5];
    std::cout << "\n index: " << itemVal.index << std::endl;

    /* REMOVE ITEMS */
    Item itemOut;
    bool valid;

    itemOut = array.removeFirst(valid);  // 1
    if (valid)
        std::cout << "\nItem removed - index: " << itemOut.index << std::endl;
    else
        std::cout << "\nItem not removed - the list is empty." << std::endl;
    array.print();

    itemOut = array.removeLast(valid);   // 6
    if (valid)
        std::cout << "\nItem removed - index: " << itemOut.index << std::endl;
    else
        std::cout << "\nItem not removed - the list is empty." << std::endl;
    array.print();

    itemOut = array.remove(2, valid);      // 4
    if (valid)
        std::cout << "\nItem removed - index: " << itemOut.index << std::endl;
    else
        std::cout << "\nItem not removed - index not valid." << std::endl;
    array.print();

    itemOut = array.remove(2, valid);      // 4
    if (valid)
        std::cout << "\nItem removed - index: " << itemOut.index << std::endl;
    else
        std::cout << "\nItem not removed - index not valid." << std::endl;
    array.print();

    itemOut = array.remove(2, valid);      // 4
    if (valid)
        std::cout << "\nItem removed - index: " << itemOut.index << std::endl;
    else
        std::cout << "\nItem not removed - index not valid." << std::endl;
    array.print();

    return 0;
}
