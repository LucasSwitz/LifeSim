#ifndef TBEDITORWINDOW_H
#define TBEDITORWINDOW_H

#include "src/graphics/gui/TBWindow.h"

class TBEditorWindow : public TBWindow
{
    public:
    TBEditorWindow(EventManager& manager) : TBWindow(manager) {}
    void OnInstanceSizeChange(int width, int height);

    void Zoom(float percent);

    void MoveView(int delta_x, int delta_y);

private:
    sf::View orig_view;
};

#endif