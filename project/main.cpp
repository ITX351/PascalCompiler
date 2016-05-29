#include <cstdio>
#include <cstring>
#include <iostream>
#include "wordscanner.cpp"
#include "parser.cpp"
using namespace std;

//Love lemon_TsyD
//Miss lydrainbowcat
//By ITX351

int main()
{
    Scanner scanner;
    scanner.init();
    scanner.scan();
    scanner.close();

    Parser parser(scanner.result, scanner.signTable);
    parser.init();

    return 0;
}
