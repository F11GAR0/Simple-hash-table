#include <QCoreApplication>
#include "main.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HashTable<std::string, int> hash_table;
    hash_table["test"] = 4;
    hash_table["another test"] = 91;
    std::cout<<hash_table["test"]<<std::endl;
    std::cout<<hash_table["another test"]<<std::endl;
    std::cin.get();
    return a.exec();
}
