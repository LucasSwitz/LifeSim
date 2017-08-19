#ifndef Controller_H
#define Controller_H

#include <map>

class Controller
{
    public:
        Controller(int id) : _id(id){};

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

        int ID(){return _id;}


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
        int _id = -1;
};

#endif 