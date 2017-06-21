#ifndef UIOVERLAY_H
#define UIOVERLAY_H

//this needs to extend drawable
class UIOverlay
{
  public:
    UIOverlay(std::string path_to_template_file = "");
    void LoadFromTemplate(std::string path_to_template_file);
    void AddOverlayComponent(const OverlayComponenet *component); //this is how we will do things like a dialog or boss health
    DrawAble* AsDrawable(); //can I make the entire overlay one giant drawable rather than drawing the componenets individually?
  private:
    std::list<OverlayComponent *> _components;
};

#endif