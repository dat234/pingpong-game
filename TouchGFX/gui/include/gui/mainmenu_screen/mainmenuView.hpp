#ifndef MAINMENUVIEW_HPP
#define MAINMENUVIEW_HPP

#include <gui_generated/mainmenu_screen/mainmenuViewBase.hpp>
#include <gui/mainmenu_screen/mainmenuPresenter.hpp>

class mainmenuView : public mainmenuViewBase
{
public:
    mainmenuView();
    virtual ~mainmenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // MAINMENUVIEW_HPP
