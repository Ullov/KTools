#ifndef KTOOLS_HTML_AST_H
#define KTOOLS_HTML_AST_H

#include <string>

namespace KTools::Html
{
    class Ast
    {
    public:
        Ast(const std::string &html);
        ~Ast();
    private:
        struct Tag
        {
            char *all = nullptr;
            std::size_t namePos = 0;
            std::size_t nameLen = 0;
            std::size_t openingPartPos = 0;
            std::size_t openingPartLen = 0;
            std::size_t endingPartPos = 0;
            std::size_t endingPartLen = 0;
            std::size_t innerSpacePos = 0;
            std::size_t innerSpaceLen = 0;
        };

        void processTag();
        //void readTagData();

        char *data = nullptr;
        std::size_t pos = 0;

        std::size_t tagStartPos = std::string::npos;
    };
}

#endif // KTOOLS_HTML_AST_H
