#ifndef GAMEOVERVIEW_HPP
#define GAMEOVERVIEW_HPP

#include <gui_generated/gameover_screen/gameoverViewBase.hpp>
#include <gui/gameover_screen/gameoverPresenter.hpp>

class gameoverView : public gameoverViewBase
{
public:
    gameoverView();
    virtual ~gameoverView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // GAMEOVERVIEW_HPP
