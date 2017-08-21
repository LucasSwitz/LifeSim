#ifndef PMIDGEDITORWINDOW_H
#define PMIDGEDITORWINDOW_H

#include "src/graphics/gui/PMIDGWindow.h"

class PMIDGEditorWindow : public PMIDGWindow
{
    public:
    void OnInstanceSizeChange(int width, int height);

    void Zoom(float percent);

    void MoveView(int delta_x, int delta_y);

private:
    sf::View orig_view;
};

#endif