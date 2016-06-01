#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <stack>
#include "signtable.cpp"
using namespace std;

//Love lemon_TsyD
//Miss lydrainbowcat
//By ITX351

class Parser
{
private:
    typedef enum
    {
        C_X_ASS_Y_OP_Z = 0, C_X_ASS_OP_Y, C_X_ASS_Y, C_GOTO_X,
        C_IF_X_GOTO, C_IF_X_RELOP_Y_GOTO, C_PARAM_X, C_CALL_P_N
    } CommandType;

    typedef pair < int, string > IS;
    typedef pair < int, int > II;

//    map < string, int > signTable;
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

    char str[51], str2[131];

    struct Node
    {
        int lineNumber;
        int status;
        string signName;
        vector < int > truelist, falselist, nextlist;

        Node(int _status) { status = _status; }
    };
    stack < int > s1;
    stack < Node > s2;
    signtable signTable;

    struct Command
    {
        CommandType type;
        string arg1, arg2, op, result;
    };
    vector < Command > commands;

    int nextquad;
    void gencode(CommandType _type, const string& _result, const string& _arg1,
                 const string& _op, const string& _arg2)
    {
        Command cmd;
        cmd.type = _type; cmd.arg1 = _arg1; cmd.arg2 = _arg2;
        cmd.op = _op; cmd.result = _result;
        nextquad++;
    }

public:
    Parser(vector < IS > _words)
    {
        words = _words;
    }

    void init()
    {
        reduceTable.clear();
        terminalTable.clear();
        parseTable.clear();
        commands.clear();
        nextquad = 0;

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

    int work()
    {
        FILE *fp_parser = fopen("parser_result.txt", "w");

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
                fprintf(fp_parser, "ACCEPT!\n");
                return -1;
            }

            if (parseTable.find(II(a, b)) == parseTable.end())
            {
                fprintf(fp_parser, "ERROR PARSE(ACTION) %d, %d\n", a, b);
                return i;
            }

            int c = parseTable[II(a, b)];
            if (c > 0) // shift
            {
                s1.push(c);
                s2.push(Node(b));
                i++;

                fprintf(fp_parser, "Status move in %d, Alphas move in %d.\n", a, b);
            }
            else // reduce
            {
                c = -c;
                if (c < 0 || c >= (int)reduceTable.size())
                {
                    fprintf(fp_parser, "ERROR IN FOUND REDUCE %d.\n", c);
                    return i;
                }
                fprintf(fp_parser, "REDUCED By %d.\n", c);

                Reduce reduce = reduceTable[c];
                fprintf(fp_parser, "POP");
                for (int j = 0; j < (int)reduce.signs.size(); j++)
                {
                    fprintf(fp_parser, " (%d, %d)", s1.top(), s2.top().status);
                    s1.pop(); s2.pop();
                }

                int non_terminal = reduce.aim;
                s2.push(non_terminal);

                if (parseTable.find(II(s1.top(), non_terminal)) == parseTable.end())
                {
                    fprintf(fp_parser, "\nERROR PARSE(GOTO) (%d, %d)", s1.top(), non_terminal);
                    return i;
                }
                int Goto = parseTable[II(s1.top(), non_terminal)];
                fprintf(fp_parser, " and PUSH %d, GOTO %d.\n", non_terminal, Goto);
                s1.push(Goto);
            }
        }
        return 0;
    }
};
