#include <iostream>
#include "BinaryTree.h"

int main()
{
    iLab::Tree<std::string> tree;
    tree.Scan();
    tree.GraphDump();

    iLab::Tree<std::string> one;
    one.Scan("1");
    one = tree;
    one.GraphDump("1");


}
