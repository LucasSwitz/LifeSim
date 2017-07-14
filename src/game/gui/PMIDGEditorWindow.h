#ifndef PMIDGEDITORWINDOW_H
#define PMIDGEDITORWINDOW_H

#include "src/game/gui/PMIDGWindow.h"

class PMIDGEditorWindow : public PMIDGWindow
{
    public:
    void OnInstanceSizeChange(int width, int height)
    {
        orig_view = sf::View(sf::FloatRect(0, 0, width, height));
        _window.setView(orig_view);
    }

    void Zoom(float percent)
    {
        if(percent > 1 || percent < 0)
            return;
        
        sf::View view = orig_view;
        view.zoom(percent);
        _window.setView(view);
    }

private:
    sf::View orig_view;
};

#endif