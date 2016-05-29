#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

//Love lemon_TsyD
//Miss lydrainbowcat
//By ITX351

class Parser
{
private:
    typedef pair < int, string > IS;
    map < string, int > signTable;
    vector < IS > words;

    struct Reduce
    {
        int aim;
        vector < int > signs;
        Reduce(int _aim) { aim = _aim; signs.clear(); }
    };
    vector < Reduce > reduceTable;
    map < string, int > terminalTable;
public:
    Parser(vector < IS > _words, map < string, int > _signTable)
    {
        signTable = _signTable;
        words = _words;
    }

    char str[51], str2[131];

    void init()
    {
        terminalTable.clear();
        reduceTable.clear();

        int num = 0; FILE *fp;

        fp = fopen("..\\terminal.txt", "r");
        while (fscanf(fp, "%s", str) > 0)
            terminalTable[string(str)] = num++;
        fclose(fp);
        fp = fopen("..\\nonterminal.txt", "r");
        while (fscanf(fp, "%s", str) > 0)
            terminalTable[string(str)] = num++;
        fclose(fp);

        terminalTable["program'"] = num++;

        fp = fopen("..\\grammar_list.txt", "r");
        while (fgets(str2, 131, fp) != NULL)
        {
            istringstream is(str2);
            is >> str;
            string tmp(str);
            Reduce reduce(terminalTable[tmp]);

            is >> str;

            while (is >> str)
            {
                string tmp(str);
                reduce.signs.push_back(terminalTable[tmp]);
            }
            reduceTable.push_back(reduce);
        }
        fclose(fp);

//        for (map < string, int > :: iterator it = terminalTable.begin(); it != terminalTable.end(); it++)
//            printf("%s %d\n", it->first.c_str(), it->second);
//        for (vector < Reduce > :: iterator it = reduceTable.begin(); it != reduceTable.end(); it++)
//        {
//            printf("%d =>", it->aim);
//            for (vector < int > :: iterator it2 = it->signs.begin(); it2 != it->signs.end(); it2++)
//                printf(" %d", *it2);
//            printf("\n");
//        }
    }

    void work()
    {

    }
};
