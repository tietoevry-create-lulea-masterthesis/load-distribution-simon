#include <memory>

template <typename T, typename U>
PATH<T,U>::PATH()
{
    this->isComplete = false;
    this->totalDelay = 0;
}

template <typename T, typename U>
const void PATH<T,U>::addNode(std::shared_ptr<T> node)
{
    this->nodes.push_back(node);
}

template <typename T, typename U>
const void PATH<T,U>::addLink(std::shared_ptr<U> link)
{
    this->links.push_back(link);
}

template <typename T, typename U>
const void PATH<T, U>::setComplete()
{
    this->isComplete = true;
}

template <typename T, typename U>
const void PATH<T,U>::addDelay(int delay)
{
    this->totalDelay = (this->totalDelay + delay);
}


