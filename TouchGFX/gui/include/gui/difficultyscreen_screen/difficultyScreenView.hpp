#ifndef DIFFICULTYSCREENVIEW_HPP
#define DIFFICULTYSCREENVIEW_HPP

#include <gui_generated/difficultyscreen_screen/difficultyScreenViewBase.hpp>
#include <gui/difficultyscreen_screen/difficultyScreenPresenter.hpp>

class difficultyScreenView : public difficultyScreenViewBase
{
public:
    difficultyScreenView();
    virtual ~difficultyScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void playEasy();
    virtual void playNormal();
    virtual void playHard();
protected:
};

#endif // DIFFICULTYSCREENVIEW_HPP
