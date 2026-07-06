#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    // Hàm set/get độ khó (tốc độ AI)
    void setDifficulty(int speed) { aiSpeed = speed; }
    int getDifficulty() { return aiSpeed; }
protected:
    ModelListener* modelListener;
    int aiSpeed; // Biến lưu tốc độ của máy
};

#endif // MODEL_HPP
