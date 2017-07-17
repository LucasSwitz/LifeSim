#ifndef LUALIST_H
#define LUALIST_H

#include <list>
#include <map>

template <typename T>
struct LuaListNode
{
    LuaListNode(T new_data) : data(new_data){};

    RefCountedObjectPtr <T> data;
    LuaListNode<T> *next = nullptr;
};

template <typename T>
class LuaList
{

  public:
    void Add(T data)
    {
        _size++;
        LuaListNode<T> *new_LuaListNode = new LuaListNode<T>(data);

        if (!_tail)
        {
            _tail = new_LuaListNode;
        }
        else
        {
            _tail->next = new_LuaListNode;
            _tail = new_LuaListNode;
        }

        if (!_head)
            _head = _tail;
    }

    LuaListNode<T> *Iterator()
    {
        return _head;
    }

    int Size()
    {
        return _size;
    }

    template <typename key, typename value>
    static LuaList<value>* FromMapToLuaList(std::map<key, value> &map)
    {
        LuaList *list = new LuaList();

        for (auto it = map.begin(); it != map.end(); it++)
        {
            list->Add(it->second);
        }

        return list;
    }

    template <typename value>
    static void FromListToLuaList(std::list<value>& map, LuaList& list)
    {
        for (auto it = map.begin(); it != map.end(); it++)
        {
            list.Add(*it);
        }
    }

  private:
    LuaListNode<T> *_head = nullptr;
    LuaListNode<T> *_tail = nullptr;
    int _size = 0;
};

#endif