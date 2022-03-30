#include <iostream>

#include "circular-linked-list.hpp"
#include<iostream>
int main() {
    
    CircularLinkedList<char> CL;
    /*
    std::cout << CL << std::endl;
    std::cout << "head adress: " << CL.GetHead() << std::endl;
    std::cout << "tail adress: " << CL.GetTail() << std::endl;*/

    CL.InsertInOrder('a');
    CL.InsertInOrder('b');
    CL.InsertInOrder('b');
    CL.InsertInOrder('c');
    //CL.InsertInOrder('c');
    //CL.InsertInOrder('b');
    //CL.InsertInOrder('d');
    //CL.InsertInOrder('e');
    std::cout << CL << std::endl;
    std::cout << "head adress: " << CL.GetHead() << std::endl;
    std::cout << "tail adress: " << CL.GetTail() << std::endl;
    //CL.Reverse();
    //std::cout << CL << std::endl;
    //std::cout << "tail points to: " << CL.GetTail()->next->data << std::endl;
    /*
    CircularLinkedList<int> CL_copy;
    CL_copy.ChangeOrder();
    CL_copy.InsertInOrder(33);
    CL_copy.InsertInOrder(22);
    CL_copy.InsertInOrder(11);
    CL_copy.InsertInOrder(55);
    CL_copy.InsertInOrder(44);
    std::cout << CL_copy << std::endl;
    std::cout << "head adress: " << CL_copy.GetHead() << std::endl;
    std::cout << "tail adress: " << CL_copy.GetTail() << std::endl;*/
}
