#include "./tag.h"

KTools::Html::Tag::Tag() {}

KTools::Html::Tag::~Tag()
{
    if (data != nullptr)
        free(data);
}