#ifndef PMIDGEDITORWINDOW_H
#define PMIDGEDITORWINDOW_H

#include "src/graphics/gui/PMIDGWindow.h"

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

    void MoveView(int delta_x, int delta_y)
    {
        sf::Vector2f center = orig_view.getCenter();
        sf::Vector2f move_center(center.x + delta_x, center.y + delta_y);
        orig_view.setCenter(move_center);

        sf::View current_view = _window.getView();
        current_view.setCenter(move_center);
        _window.setView(current_view);
    }

private:
    sf::View orig_view;
};

#endif