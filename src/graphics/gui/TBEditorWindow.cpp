#include "src/graphics/gui/TBEditorWindow.h"

void TBEditorWindow::OnInstanceSizeChange(int width, int height)
{
    orig_view = sf::View(sf::FloatRect(0, 0, width, height));
    orig_view.setCenter(width / 2, height / 2);
    _window.setView(orig_view);
}

void TBEditorWindow::Zoom(float percent)
{
    if (percent > 1 || percent < 0)
        return;

    sf::View view = orig_view;
    view.zoom(percent);
    _window.setView(view);
}

void TBEditorWindow::MoveView(int delta_x, int delta_y)
{
    sf::Vector2f center = orig_view.getCenter();
    sf::Vector2f move_center(center.x + delta_x, center.y + delta_y);
    orig_view.setCenter(move_center);

    sf::View current_view = _window.getView();
    current_view.setCenter(move_center);
    _window.setView(current_view);
}