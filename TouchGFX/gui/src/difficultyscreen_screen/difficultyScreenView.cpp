#include <gui/difficultyscreen_screen/difficultyScreenView.hpp>

difficultyScreenView::difficultyScreenView()
{

}

void difficultyScreenView::setupScreen()
{
    difficultyScreenViewBase::setupScreen();
}

void difficultyScreenView::tearDownScreen()
{
    difficultyScreenViewBase::tearDownScreen();
}
void difficultyScreenView::playEasy()
{
    presenter->setDifficulty(1); // Cấp độ 1 (Dễ)
    application().gotogameScreenNoTransition();
}

void difficultyScreenView::playNormal()
{
    presenter->setDifficulty(2); // Cấp độ 2 (Trung bình)
    application().gotogameScreenNoTransition();
}

void difficultyScreenView::playHard()
{
    presenter->setDifficulty(3); // Cấp độ 3 (Khó)
    application().gotogameScreenNoTransition();
}
