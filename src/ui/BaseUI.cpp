#include "src/ui/BaseUI.h"

BaseUI::BaseUI(TBWindow &window)
{
    sf::Vector2u sf_window_size = window.SFWindow().getSize();
    _root_box = std::make_shared<BoxContainer>();
    _root_box->SetLayout(std::make_shared<RelativeLayout>());
    _root_box->AddComponentValue("Graphics", "width", (float)sf_window_size.x);
    _root_box->AddComponentValue("Graphics", "height", (float)sf_window_size.y);
    AddRootElement(_root_box);
}

BaseUI::BaseUI(int width, int height)
{
    _root_box = std::make_shared<BoxContainer>();
    _root_box->SetLayout(std::make_shared<RelativeLayout>());
    _root_box->AddComponentValue("Graphics", "width", (float)width);
    _root_box->AddComponentValue("Graphics", "height", (float)height);
    AddRootElement(_root_box);
}

void BaseUI::DoFormat()
{
    _root_box->DoFormat();
}

int BaseUI::GetBaseContainerID()
{
    return _root_box->ID();
}
