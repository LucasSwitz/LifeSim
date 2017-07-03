#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include  <unordered_map>

class KeyboardController
{
    public:
    const bool& Get(const std::string& key_name) const
    {
        return keys.at(key_name);
    }

    static KeyboardController* Instance()
    {
        static KeyboardController instance;
        return instance;
    }
    
    private:
    std::unordered_map<std::string, bool> keys = {{"W",false},
                                                  {"A",false},
                                                  {"S",false},
                                                  {"D",false}}
};                                                                      
#endif