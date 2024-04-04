#include <iostream>
#include "Test.h"

void Test::print_test(){
    std::cout << "Test function called for once." << std::endl;
}

int main(int argc, char *argv[])
{
    Test my_test;
    my_test.print_test();
    return 0;
}
