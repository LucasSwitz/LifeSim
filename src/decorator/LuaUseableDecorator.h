#ifndef LUAUSEABLEDECORATOR_H
#define LUAUSEABLEDECORATOR_H
#include "src/decorator/UseableDecorator.h"

class LuaUseableDecorator : public UseableDecorator
{
    public:

    static LuaUseableDecorator* FromLuaRef(const LuaRef& parent_table, const LuaRef& _useable_table)
    {
        LuaUseableDecorator* d = new LuaUseableDecorator();

        d->_parent_table = std::make_shared<LuaRef>(parent_table);

        if (_useable_table.isTable())
        {
            if (_useable_table["Use"])
            {
                d->_use_function = std::make_unique<LuaRef>(_useable_table["Use"]);
            }
        }

    }

    void Use(int user_id) override
    {
        if(_use_function)
        {
            (*_use_function)(_parent_table,user);
        }
    }

    private:

    std::shared_ptr<LuaRef> _parent_table = nullptr;
    std::shared_ptr<LuaRef> _use_function = nullptr;
};

#endif