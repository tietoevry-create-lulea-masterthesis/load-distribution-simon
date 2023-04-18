#include <memory>
#include <vector>

template <typename T, typename U>
class PATH
{
    private:
        std::vector<std::shared_ptr<T>> nodes;
        std::vector<std::shared_ptr<U>> links;
        bool isComplete;
        int totalDelay;
    public:
        PATH();

        const void addNode(std::shared_ptr<T> node);
        const void addLink(std::shared_ptr<U> link);
        const void setComplete();
        const void addDelay(int delay);
};

#include "path.tpp"