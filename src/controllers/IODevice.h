#ifndef IODEVICE_H
#define IODEVICE_H

#include <map>

class IODevice
{
    public:
        virtual void Poll() = 0;

        bool Get(int id)
        {
            if(HasTrigger(id))
                return _triggers.at(id);
            return false;
        }

        bool HasTrigger(int id)
        {
            return _triggers.find(id) != _triggers.end();
        }

    protected:
        void Set(int id, bool val)
        {
            if(HasTrigger(id))
                _triggers.find(id)->second = val;
            else
                _triggers.insert(std::make_pair(id,val));
        }
    private:
        std::map<int, bool> _triggers;
};

#endif 