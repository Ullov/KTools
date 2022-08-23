#ifndef KTOOLS_HTML_TAG_H
#define KTOOLS_HTML_TAG_H

#include <string>

namespace KTools::Html
{
    class Tag
    {
    public:
        Tag();
        ~Tag();
    private:
        char *data = nullptr;
        std::size_t namePos = 0;
        std::size_t nameLen = 0;
        std::size_t openingPartPos = 0;
        std::size_t openingPartLen = 0;
        std::size_t endingPartPos = 0;
        std::size_t endingPartLen = 0;
        std::size_t innerSpacePos = 0;
        std::size_t innerSpaceLen = 0;
    };
}

#endif // KTOOLS_HTML_TAG_H
