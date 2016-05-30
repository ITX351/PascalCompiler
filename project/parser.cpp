#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <stack>
using namespace std;

//Love lemon_TsyD
//Miss lydrainbowcat
//By ITX351

class Parser
{
private:
    typedef pair < int, string > IS;
    typedef pair < int, int > II;

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
    map < II, int > parseTable;

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
        parseTable.clear();

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

        fp = fopen("..\\table.txt", "r");
        int a, b, c;
        while (fscanf(fp, "%d%d%d", &a, &b, &c) > 0)
            parseTable[II(a, b)] = c;
        fclose(fp);
    }

    stack < int > s1, s2;
    int work()
    {
        while (!s1.empty())
            s1.pop();
        while (!s2.empty())
            s2.pop();
        s1.push(0);

        int i = 0;
        while (i < (int)words.size())
        {
            int a = s1.top(), b = words[i].first;
            if (a == 1 && b == 38) // 1, 38 ACC
            {
                printf("ACCEPT!\n");
                return -1;
            }

            if (parseTable.find(II(a, b)) == parseTable.end())
            {
                printf("ERROR PARSE(ACTION) %d, %d\n", a, b);
                return i;
            }

            int c = parseTable[II(a, b)];
            if (c > 0) // shift
            {
                s1.push(c);
                s2.push(b);
                i++;

                printf("Status move in %d, Alphas move in %d.\n", a, b);
            }
            else // reduce
            {
                c = -c;
                if (c < 0 || c >= (int)reduceTable.size())
                {
                    printf("ERROR IN FOUND REDUCE %d.\n", c);
                    return i;
                }
                printf("REDUCED By %d.\n", c);

                Reduce reduce = reduceTable[c];
                printf("POP");
                for (int j = 0; j < (int)reduce.signs.size(); j++)
                {
                    printf(" (%d, %d)", s1.top(), s2.top());
                    s1.pop(); s2.pop();
                }

                int non_terminal = reduce.aim;
                s2.push(non_terminal);

                if (parseTable.find(II(s1.top(), non_terminal)) == parseTable.end())
                {
                    printf("\nERROR PARSE(GOTO) (%d, %d)", s1.top(), non_terminal);
                    return i;
                }
                int Goto = parseTable[II(s1.top(), non_terminal)];
                printf(" and PUSH %d, GOTO %d.\n", non_terminal, Goto);
                s1.push(Goto);
            }
        }
        return 0;
    }
};
