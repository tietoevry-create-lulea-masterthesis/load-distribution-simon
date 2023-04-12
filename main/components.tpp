#include <memory>

template <typename T>
LINK<T>::LINK(int id, int rate, int delay, std::shared_ptr<T> up, std::shared_ptr<T> down) {
    this->id = id;
    this->rate = rate;
    this->delay = delay;
    this->up = up;
    this->down = down;
}

template <typename T>
const void LINK<T>::add_up(std::shared_ptr<T> up){
    this->up = up;
}

template <typename T>
const void LINK<T>::add_down(std::shared_ptr<T> down){
    this->down = down;
}