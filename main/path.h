#include <memory>
#include <vector>

template <typename T>
class PATH
{
    private:
        std::vector<std::shared_ptr<T>> nodes;
        std::vector<std::shared_ptr<T>> links;
        bool isComplete;
        int totalDelay;
    public:
        PATH();

        const void addNode(std::shared_ptr<T> node);
        const void addLink(std::shared_ptr<T> link);
        const void setComplete();
        const void addDelay(int delay);
};

#include "path.tpp"