#include "./ast.h"

#include <cstring>
#include <iostream>

KTools::Html::Ast::Ast(const std::string &html)
{
    data = (char*)malloc(html.size());
    strcpy(data, html.c_str());
    processTag();
}

KTools::Html::Ast::~Ast()
{
    if (data != nullptr)
        free(data);
}

void KTools::Html::Ast::processTag()
{
    std::size_t dataLen = strlen(data);
    while (pos < dataLen)
    {
        switch(data[pos])
        {
            case '<':
            {
                //readTagData();
                /*if (tagStartPos == std::string::npos)
                    tagStartPos = pos;
                pos++;*/
                break;
            }
            /*case '>':
            {
                if (tagStartPos != std::string::npos)
                {
                    printf("%.*s", (pos - tagStartPos) + 1, data + tagStartPos);
                    std::cout << std::endl;
                    tagStartPos = std::string::npos;
                }
                pos++;
                break;
            }*/
            default:
            {
                pos++;
            }
        }
    }
}

/*void KTools::Html::Ast::readTagData()
{
    char *name = (char*)malloc(1024);
    char now = 0;
    while (data[pos] != '>')
    {
        if (data[pos] == ' ' || data[pos] == '\t' || data[pos] == '\n' || data[pos] == '\r')
            pos++;
        else if (isalpha(now))
        {
            name[strlen(name) + 1] = now;
        }
    }
}*/
