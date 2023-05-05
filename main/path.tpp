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
const void PATH<T,U>::addBannedLink(std::shared_ptr<U> link)
{
    this->bannedlinks.push_back(link);
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

template <typename T, typename U>
const void PATH<T,U>::consumeDelay(int d)
{
    this->remainingDelay = (this->remainingDelay - d);
}

template <typename T, typename U>
const void PATH<T,U>::deleteWrongPath()
{
    this->links.pop_back();
    this->nodes.pop_back();
    this->nodes.pop_back();
}

template <typename T, typename U>
const std::vector<std::shared_ptr<T>> PATH<T,U>::getNodes()
{
    return this->nodes;
}

template <typename T, typename U>
const std::vector<std::shared_ptr<U>> PATH<T,U>::getLinks()
{
    return this->links;
}

template <typename T, typename U>
const std::vector<std::shared_ptr<U>> PATH<T,U>::getBannedLinks()
{
    return this->bannedlinks;
}

template <typename T, typename U>
const int PATH<T,U>::getRemainingDelay()
{
    return this->remainingDelay;
}
