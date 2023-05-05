#include <memory>
#include <vector>

template <typename T, typename U>
class PATH
{
    private:
        std::vector<std::shared_ptr<T>> nodes;
        std::vector<std::shared_ptr<U>> links;
        std::vector<std::shared_ptr<U>> bannedlinks;
        bool isComplete;
        int totalDelay;
        int remainingDelay;
    public:
        PATH();

        const void addNode(std::shared_ptr<T> node);
        const void addLink(std::shared_ptr<U> link);
        const void addBannedLink(std::shared_ptr<U> link);
        const void setComplete();
        const void addDelay(int delay);
        const void consumeDelay(int d);
        const void deleteWrongPath();

        const std::vector<std::shared_ptr<T>> getNodes();
        const std::vector<std::shared_ptr<U>> getLinks();
        const std::vector<std::shared_ptr<U>> getBannedLinks();
        const int getRemainingDelay();
};

#include "path.tpp"