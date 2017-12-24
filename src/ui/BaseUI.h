#ifndef BASEUI_H
#define BASEUI_H

#include <unordered_map>
#include "src/ui/UI.h"
#include "src/ui/BoxContainer.h"
#include "src/ui/RelativeLayout.h"

class BaseUI : public UI
{
    public:
        BaseUI(PMIDGWindow& window);

        BaseUI(int width, int height);

        void DoFormat();

        int GetBaseContainerID();

    private:
        std::unordered_map<int,ptr<UIElement>> _root_elements;
        ptr<BoxContainer> _root_box;
};
#endif