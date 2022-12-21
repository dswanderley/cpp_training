#include <iostream>
#include <sstream>
#include <iomanip>


struct MyStruct
{
    double d;
    float f;
    int i;
};


class MyClass
{
  public:
    MyClass(int y, int m, int d) : year(y), month(m), day(d) {};
    ~MyClass() {};
    std::string getDate();

  private:
    int year;
    int month;
    int day;
};

std::string MyClass::getDate()
{
    std::ostringstream oStr;

    oStr << std::setw(4) << std::setfill('0') << year;
    oStr << std::setw(2) << std::setfill('0') << month;
    oStr << std::setw(2) << std::setfill('0') << day;

    return oStr.str();
}



int main ()
{
    /* STACK MEMORY */
    int sInt = 100;
    int sArray[5] = {1, 2, 3, 4, 5};
    MyStruct sStruct = {5.0005, 1.1, 200};
    MyClass sClass(2022, 12, 21);

    std::cout << "STACK MEMORY" << std::endl;
    std::cout << "sInt:    " << &sInt    << " - " << &sInt + 1 << std::endl;
    std::cout << "sArray:  " << &sArray  << " - " << &sArray[5] + 1 << std::endl;
    std::cout << "sStruct: " << &sStruct << " - " << &sStruct + 1 << std::endl;
    std::cout << "sClass:  " << &sClass  << " - " << &sClass + 1 <<  std::endl << std::endl;

    /* HEAP MEMORY */
    int* hInt = new int(100);
    int* hArray = new int[5];
    hArray[0] = 1;
    hArray[1] = 2;
    hArray[2] = 3;
    hArray[3] = 4;
    hArray[4] = 5;
    MyStruct* hStruct = new MyStruct{5.0005, 1.1, 200};
    MyClass* hClass = new MyClass(2022, 12, 21);

    std::cout << "Pointers" << std::endl;
    std::cout << "hInt:    " << &hInt    << " - " << &hInt + 1 << std::endl;
    std::cout << "hArray:  " << &hArray  << " - " << &hArray + 1 << std::endl;
    std::cout << "hStruct: " << &hStruct << " - " << &hStruct + 1 << std::endl;
    std::cout << "hClass:  " << &hClass  << " - " << &hClass + 1 << std::endl << std::endl;

    std::cout << "HEAP MEMORY" << std::endl;
    std::cout << "hInt:    " << hInt    << " - " << hInt + 1 << std::endl;
    std::cout << "hArray:  " << hArray  << " - " << hArray + 5 << std::endl;
    std::cout << "hStruct: " << hStruct << " - " << hStruct + 1 << std::endl;
    std::cout << "hClass:  " << hClass  << " - " << hClass + 1 << std::endl;

    // Clear heap
    delete hInt;
    delete[] hArray;
    delete hStruct;
    delete hClass;

    return 0;
}