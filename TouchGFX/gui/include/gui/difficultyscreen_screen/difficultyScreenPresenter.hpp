#ifndef DIFFICULTYSCREENPRESENTER_HPP
#define DIFFICULTYSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class difficultyScreenView;

class difficultyScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    difficultyScreenPresenter(difficultyScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~difficultyScreenPresenter() {}
void setDifficulty(int speed)
    {
        model->setDifficulty(speed);
    }
private:
    difficultyScreenPresenter();

    difficultyScreenView& view;
};

#endif // DIFFICULTYSCREENPRESENTER_HPP
