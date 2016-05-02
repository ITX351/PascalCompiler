#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

const int KEYWORD_NUM = 37, BUFFER_SIZE = 4095;

typedef enum
{
	T_AND = 0, T_ARRAY, T_BEGIN, T_CASE, T_CONST, T_DIV, T_DO, T_DOWNTO, T_ELSE, T_END,
	T_FILE, T_FOR, T_FUNCTION, T_GOTO, T_IF, T_IN, T_LABEL, T_MOD, T_NIL, T_NOT,
	T_OF, T_OR, T_PACKED, T_PRODEDURE, T_PROGRAM, T_RECORD, T_REPEAT, T_SET, T_THEN, T_TO,
	T_TYPE, T_UNTIL, T_VAR, T_WHILE, T_WITH, T_INTTYPE, T_REALTYPE,

	T_ADD, T_SUB, T_MUL, T_ADDE, T_SUBE, T_MULE, T_DIVE, T_POW,
	T_EQL, T_NEQ, T_GT, T_GTE, T_LT, T_LTE,
	T_COMMA, T_COLON, T_SEMICL, T_SLASH, T_EXC, T_QUES,
	T_SHRP, T_PERIOD, T_CONT, T_LPAR, T_RPAR, T_LBRKPAR, T_RBRKPAR, T_SINQUOTA,
	T_DOUQUOTA, T_ASS,
	T_IDN, T_INT, T_REAL, T_STR, T_DOUBLEPERIOD
} TokenType;

static const char* keywordList[] = {
	"and", "array", "begin", "case", "const", "div", "do", "downto", "else", "end",
	"file", "for", "function", "goto", "if", "in", "label", "mod", "nil", "not",
    "of", "or", "packed", "prodedure", "program", "record", "repeat", "set", "then", "to",
    "type", "until", "var", "while", "with", "integer", "real"
};

#endif // CONSTANTS_H_INCLUDED


/*  T_DIVE, T_EXC, T_QUES,
	T_SHRP, T_CONT, T_SINQUOTA,	T_DOUQUOTA */
