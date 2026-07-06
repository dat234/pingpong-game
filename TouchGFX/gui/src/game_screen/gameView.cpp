#include <gui/game_screen/gameView.hpp>
#include <stdlib.h> // Thêm thư viện này để dùng hàm ngẫu nhiên rand()
gameView::gameView()
{

}
void gameView::setupScreen()
{
    gameViewBase::setupScreen();

    // Lấy cấp độ từ màn hình trước (1, 2 hoặc 3)
    int diffLevel = presenter->getDifficulty();

    // Cài đặt tốc độ theo từng cấp độ
    if (diffLevel == 1) { // EASY
        aiSpeed = 2;              // AI chậm
        initialBallSpeed = 1.5f;  // Bóng chậm
    }
    else if (diffLevel == 2) { // NORMAL
        aiSpeed = 4;              // AI vừa
        initialBallSpeed = 2.5f;  // Bóng vừa
    }
    else { // HARD
        aiSpeed = 6;              // AI rất nhanh
        initialBallSpeed = 3.5f;  // Bóng cực nhanh
    }

    playerScore = 0;
    aiScore = 0;
    updateScoreText();
    resetBall();
}


void gameView::resetBall()
{
    ball.setXY(112, 152); 
    
    // Gán tốc độ hiện tại bằng tốc độ gốc của chế độ đang chơi
    currentBallSpeed = initialBallSpeed;
    
    // Sinh số ngẫu nhiên 0 hoặc 1. Nếu là 0 thì hướng bay là -1, nếu là 1 thì hướng bay là 1
    int randDirectionX = (rand() % 2 == 0) ? 1 : -1;
    int randDirectionY = (rand() % 2 == 0) ? 1 : -1;

    // Nhân tốc độ với hướng ngẫu nhiên
    ballVx = currentBallSpeed * randDirectionX;
    ballVy = currentBallSpeed * randDirectionY;
    
    ball.invalidate(); 
}
// Hàm tiện ích: Cập nhật chữ điểm số
void gameView::updateScoreText()
{
    // Sử dụng Unicode::snprintf để truyền biến int vào chuỗi Wildcard
    Unicode::snprintf(txtScorePlayerBuffer, TXTSCOREPLAYER_SIZE, "%d", playerScore);
    Unicode::snprintf(txtScoreAIBuffer, TXTSCOREAI_SIZE, "%d", aiScore);
    
    // Báo cho TouchGFX vẽ lại 2 ô text
    txtScorePlayer.invalidate();
    txtScoreAI.invalidate();
}
void gameView::handleDragEvent(const DragEvent& event)
{
    // Nhân 2 độ lệch để thanh đỡ di chuyển nhanh và nhạy gấp đôi
    int deltaX = event.getDeltaX() * 4;
    int newX = paddlePlayer.getX() + deltaX;

    // Giới hạn không cho văng khỏi màn hình
    if (newX < 0) {
        newX = 0;
    } 
    else if (newX > (240 - paddlePlayer.getWidth())) {
        newX = 240 - paddlePlayer.getWidth();
    }

    paddlePlayer.invalidate();
    paddlePlayer.setX(newX);
    paddlePlayer.invalidate();
}

void gameView::tearDownScreen()
{
    gameViewBase::tearDownScreen();
}
// Hàm kiểm tra nếu có người đạt 5 điểm
void gameView::checkWinner()
{
    if (playerScore >= 5 || aiScore >= 5) {
        // Nếu ai đó đạt 5 điểm, kết thúc game và chuyển sang màn hình gameover
        application().gotogameoverScreenNoTransition();
    } else {
        // Nếu chưa, reset bóng ra giữa để đánh hiệp tiếp theo
        resetBall();
    }
}

// Vòng lặp Game (Chạy 60 khung hình/giây)
void gameView::handleTickEvent()
{
    // 1. Xóa hình ảnh bóng và AI ở vị trí cũ (tránh lưu vệt trên màn hình)
    ball.invalidate();
    paddleAI.invalidate();

    // 2. Cập nhật vị trí bóng theo vận tốc
    ball.setXY(ball.getX() + ballVx, ball.getY() + ballVy);

    // 3. Logic AI (Máy tự động đuổi theo bóng theo chiều ngang X)
    int aiCenter = paddleAI.getX() + (paddleAI.getWidth() / 2);
    int ballCenter = ball.getX() + (ball.getWidth() / 2);

    if (aiCenter < ballCenter) {
        paddleAI.setX(paddleAI.getX() + aiSpeed); // Chạy sang phải
    } else if (aiCenter > ballCenter) {
        paddleAI.setX(paddleAI.getX() - aiSpeed); // Chạy sang trái
    }

    // Giới hạn không cho AI chạy lọt ra ngoài mép màn hình
    if (paddleAI.getX() < 0) paddleAI.setX(0);
    if (paddleAI.getX() > (240 - paddleAI.getWidth())) paddleAI.setX(240 - paddleAI.getWidth());

    // 4. Xử lý va chạm 2 vách tường (Trái / Phải)
    if (ball.getX() <= 0) {
        ball.setX(0);
        ballVx = -ballVx; // Đổi hướng trục X
    } else if (ball.getX() >= (240 - ball.getWidth())) {
        ball.setX(240 - ball.getWidth());
        ballVx = -ballVx; // Đổi hướng trục X
    }

    // 5. Xử lý va chạm Thanh đỡ Người chơi (Phía dưới)
    if (ball.getY() + ball.getHeight() >= paddlePlayer.getY() &&
        ball.getY() <= paddlePlayer.getY() + paddlePlayer.getHeight() &&
        ball.getX() + ball.getWidth() >= paddlePlayer.getX() &&
        ball.getX() <= paddlePlayer.getX() + paddlePlayer.getWidth()) 
    {
        // Đẩy bóng lên để không bị dính vào thanh đỡ
        ball.setY(paddlePlayer.getY() - ball.getHeight());
        ballVy = -ballVy; // Nảy ngược lên trên

        // Tính góc phản xạ: Phụ thuộc vào việc bóng chạm vị trí nào trên thanh đỡ
        int hitPoint = (ball.getX() + ball.getWidth()/2) - (paddlePlayer.getX() + paddlePlayer.getWidth()/2);
        ballVx = (hitPoint * 0.15f); // Hệ số 0.15 giúp chỉnh góc nghiêng vừa phải
        
        // Tăng tốc độ bóng lên một chút sau mỗi cú đánh trúng (tối đa là 8.0)
        if(currentBallSpeed < 8.0f) { 
            currentBallSpeed += 0.5f; 
        }
        // Đảm bảo quả bóng bay với đúng tốc độ mới
        if(ballVy < 0) ballVy = -currentBallSpeed;
    }

    // 6. Xử lý va chạm Thanh đỡ AI (Phía trên)
    if (ball.getY() <= paddleAI.getY() + paddleAI.getHeight() &&
        ball.getY() + ball.getHeight() >= paddleAI.getY() &&
        ball.getX() + ball.getWidth() >= paddleAI.getX() &&
        ball.getX() <= paddleAI.getX() + paddleAI.getWidth()) 
    {
        ball.setY(paddleAI.getY() + paddleAI.getHeight()); 
        ballVy = -ballVy; // Nảy ngược xuống dưới
        
        int hitPoint = (ball.getX() + ball.getWidth()/2) - (paddleAI.getX() + paddleAI.getWidth()/2);
        ballVx = (hitPoint * 0.15f);
        
        if(currentBallSpeed < 8.0f) { currentBallSpeed += 0.5f; }
        if(ballVy > 0) ballVy = currentBallSpeed;
    }

    // 7. Ghi điểm (Khi bóng vượt ra khỏi mép trên hoặc mép dưới)
    if (ball.getY() + ball.getHeight() < 0) {
        playerScore++;        // Mép trên -> Người chơi ăn điểm
        updateScoreText();
        checkWinner();
    } else if (ball.getY() > 320) {
        aiScore++;            // Mép dưới -> AI ăn điểm
        updateScoreText();
        checkWinner();
    }

    // 8. Vẽ lại bóng và AI ở tọa độ mới
    ball.invalidate();
    paddleAI.invalidate();
}
