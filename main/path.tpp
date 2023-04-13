#include <memory>

template <typename T>
PATH<T>::PATH()
{
    this->isComplete = false;
    this->totalDelay = 0;
}

template <typename T>
PATH<T>::addNode(std::shared_ptr<T> node)
{
    this->nodes.push_back(node);
}

template <typename T>
PATH<T>::addLink(std::shared_ptr<T> link)
{
    this->links.push_back(link);
}

template <typename T>
PATH<T>::setComplete()
{
    this->isComplete = true;
}

template <typename T>
PATH<T>::addDelay(int delay)
{
    this->totalDelay = (this->totalDelay + delay);
}


