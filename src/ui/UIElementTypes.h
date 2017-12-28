#ifndef UIELEMENTTYPES_H
#define UIELEMENTTYPES_H

#include <unordered_map>

const int UIELEMENT_CONTAINER = 0;
const int UIELEMENT_GRAPHIC = 1;

const std::unordered_map<std::string, int> uie_type_map = 
{
    {"Container",UIELEMENT_CONTAINER},
    {"Graphic",UIELEMENT_GRAPHIC}
};

#endif