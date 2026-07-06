#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <gui_generated/game_screen/gameViewBase.hpp>
#include <gui/game_screen/gamePresenter.hpp>

class gameView : public gameViewBase
{
public:
    gameView();
    virtual ~gameView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    // Ghi đè hàm Tick (chạy 60 hình/giây)
    virtual void handleTickEvent();

    // Ghi đè hàm nhận diện ngón tay vuốt trên màn hình
    virtual void handleDragEvent(const DragEvent& event);
protected:
// Các biến trạng thái game
    float ballVx;
    float ballVy;
    float currentBallSpeed;
    int aiSpeed;
    
    int playerScore;
    int aiScore;

    // Các hàm tiện ích
    void resetBall();
    void updateScoreText();
    void checkWinner();
    float initialBallSpeed; //  lưu tốc độ gốc
};

#endif // GAMEVIEW_HPP
