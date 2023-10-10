#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"
#include <cctype>
#include <ctype.h>
#include <string>
#include <cstring>
using namespace std;

LexicalAnalyzer::LexicalAnalyzer(ifstream *scf)
{
    currentChar = ' ';
    currentCharIndex = 0;
    sourceCodeFile = scf;
    line = "";
}

bool LexicalAnalyzer::isEOI()
{
    return (currentCharIndex == line.length() && sourceCodeFile->eof());
}

void LexicalAnalyzer::readNextLine()
{
    getline(*sourceCodeFile, line);
    line += "\n";
}

void LexicalAnalyzer::getNextChar()
{

    if (currentCharIndex == line.length())
    {
        readNextLine();
        currentCharIndex = 0;
    }

    currentChar = line.at(currentCharIndex);
    currentCharIndex++;
}


Token *LexicalAnalyzer::getNextToken()
{
    Token *t;
    while (isspace(currentChar) && !isEOI())
    {
        getNextChar();
    }

    if (isEOI())
    {
        t = new Token(EOI, "");
    }

    else if (isalpha(currentChar))
    {
        string lexeme = "";

        while (isalnum(currentChar) && !isEOI())
        {
            lexeme += currentChar;
            getNextChar();
        }

        if (lexeme == "bool")
        {
            t = new Token(BOOLSYM, lexeme);
        }
        else if (lexeme == "do")
        {
            t = new Token(DOSYM, lexeme);
        }
        else if (lexeme == "else")
        {
            t = new Token(ELSESYM, lexeme);
        }
        else if (lexeme == "false")
        {
            t = new Token(FALSESYM, lexeme);
        }
        else if (lexeme == "float")
        {
            t = new Token(FLOATSYM, lexeme);
        }
        else if (lexeme == "for")
        {
            t = new Token(FORSYM, lexeme);
        }
        else if (lexeme == "if")
        {
            t = new Token(IFSYM, lexeme);
        }
        else if (lexeme == "int")
        {
            t = new Token(INTSYM, lexeme);
        }
        else if (lexeme == "printf")
        {
            t = new Token(PRINTFSYM, lexeme);
        }
        else if (lexeme == "return")
        {
            t = new Token(RETURNSYM, lexeme);
        }
        else if (lexeme == "scanf")
        {
            t = new Token(SCANFSYM, lexeme);
        }
        else if (lexeme == "true")
        {
            t = new Token(TRUESYM, lexeme);
        }
        else if (lexeme == "void")
        {
            t = new Token(VOIDSYM, lexeme);
        }
        else if (lexeme == "while")
        {
            t = new Token(WHILESYM, lexeme);
        }
        else
        {
            t = new Token(IDENT, lexeme);
        }
    }
    else if (isdigit(currentChar))
    {
        string lexeme = "";
        while ((isdigit(currentChar) || currentChar == '.') && !isEOI())
        {
            lexeme += currentChar;
            getNextChar();
        }
        t = new Token(NUMLIT, lexeme);
    }
    else if (currentChar == '.')
    {
        string lexeme = "0.";
        getNextChar();
        while (isdigit(currentChar) && !isEOI())
        {
            lexeme += currentChar;
            getNextChar();
        }
        t = new Token(NUMLIT, lexeme);
    }
    else
    {
        switch (currentChar)
        {
        case '+':
            t = new Token(PLUS, "+");
            getNextChar();
            break;
        case '-':
            t = new Token(MINUS, "-");
            getNextChar();
            break;
        case '*':
            t = new Token(TIMES, "*");
            getNextChar();
            break;
        case '/':
            t = new Token(SLASH, "/");
            getNextChar();
            break;
        case '%':
            t = new Token(MOD, "%");
            getNextChar();
            break;
        case '(':
            t = new Token(LPAREN, "(");
            getNextChar();
            break;
        case ')':
            t = new Token(RPAREN, ")");
            getNextChar();
            break;
        case '{':
            t = new Token(LBRACE, "{");
            getNextChar();
            break;
        case '}':
            t = new Token(RBRACE, "}");
            getNextChar();
            break;
        case ';':
            t = new Token(SEMICOLON, ";");
            getNextChar();
            break;
        case ',':
            t = new Token(COMMA, ",");
            getNextChar();
            break;
        case '<':
            getNextChar();
            if (currentChar == '=')
            {
                t = new Token(LEQ, "<=");
                getNextChar();
            }
            else
            {
                t = new Token(LSS, "<");
            }
            break;
        case '>':
            getNextChar();
            if (currentChar == '=')
            {
                t = new Token(GEQ, ">=");
                getNextChar();
            }
            else
            {
                t = new Token(GTR, ">");
            }
            break;
        case '=':
            getNextChar();
            if (currentChar == '=')
            {
                t = new Token(EQL, "==");
                getNextChar();
            }
            else
            {
                t = new Token(ASSIGN, "=");
            }
            break;
        case '!':
            getNextChar();
            if (currentChar == '=')
            {
                t = new Token(NEQ, "!=");
                getNextChar();
            }
            else
            {
                t = new Token(NOT, "!");
            }
            break;
        case '|':
            getNextChar();
            if (currentChar == '|')
            {
                t = new Token(OR, "||");
                getNextChar();
            }
            else
            {
                t = new Token(NAL, "|");
            }
            break;
        case '&':
            getNextChar();
            if (currentChar == '&')
            {
                t = new Token(AND, "&&");
                getNextChar();
            }
            else
            {
                t = new Token(NAL, "&");
            }
            break;
        case EOF:
            t = new Token(EOI, "");
            break;
        }
    }
    return t;
}
