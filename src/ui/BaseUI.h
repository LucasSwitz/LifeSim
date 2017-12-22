#ifndef BASEUI_H
#define BASEUI_H
#include <unordered_map>
#include "src/ui/UI.h"
#include "src/ui/BoxContainer.h"
#include "src/ui/RelativeLayout.h"

class BaseUI : public UI
{
    public:
        BaseUI(PMIDGWindow& window)
        {
            sf::Vector2u sf_window_size = window.SFWindow().getSize();
            _root_box = std::make_shared<BoxContainer>();
            _root_box->SetLayout(std::make_shared<RelativeLayout>(0,0));
            _root_box->AddComponentValue("Graphics","width",(float)sf_window_size.x);
            _root_box->AddComponentValue("Graphics","height",(float)sf_window_size.y);
            AddRootElement(_root_box);
        }

    private:
        std::unordered_map<int,ptr<UIElement>> _root_elements;
        ptr<BoxContainer> _root_box;
};
#endif