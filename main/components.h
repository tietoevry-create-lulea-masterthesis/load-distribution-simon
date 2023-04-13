#pragma once
#include <chrono>
#include <map>
#include "constants.h"
#include <memory>
#include <vector>

template <typename T>
class LINK
{
    private:
        int id;
        int rate;
        int delay;
        std::shared_ptr<T> up;
        std::shared_ptr<T> down;
    public:
        LINK(int id, int rate, int delay, std::shared_ptr<T> up, std::shared_ptr<T> down);

        const int get_rate();
        const int get_delay();
        const std::shared_ptr<T> get_upper();
        const std::shared_ptr<T> get_lower();

        const void add_up(std::shared_ptr<T> up);
        const void add_down(std::shared_ptr<T> down);
};

class NODE
{
    private:
        int id;
        std::vector<std::shared_ptr<LINK<NODE>>> upList;
        std::vector<std::shared_ptr<LINK<NODE>>> downList;
    public:
        NODE();
        NODE(int id);

        const void add_up(std::shared_ptr<LINK<NODE>> l);
        const void add_down(std::shared_ptr<LINK<NODE>> l);
        const void set_id(int i);
};

class CU: public NODE
{
private:
public:
    CU(int id);

    const void add_up(std::shared_ptr<LINK<NODE>> l);
    const void add_down(std::shared_ptr<LINK<NODE>> l);
};

class DU: public NODE
{
private:
    std::vector<std::shared_ptr<LINK<NODE>>> siblingList;
public:
    DU(int id);

    const void add_sibling(std::shared_ptr<LINK<NODE>> l);
    const void add_up(std::shared_ptr<LINK<NODE>> l);
    const void add_down(std::shared_ptr<LINK<NODE>> l);
};
class RU: public NODE
{
private:
    std::vector<std::shared_ptr<LINK<NODE>>> siblingList;
public:
    RU(int id);

    const void add_sibling(std::shared_ptr<LINK<NODE>> l);
    const void add_up(std::shared_ptr<LINK<NODE>> l);
    const void add_down(std::shared_ptr<LINK<NODE>> l);
};

class ENDPOINT: public NODE{
    private:
        int connectedUEs;
    public:
        ENDPOINT(int id);
        const void add_down(std::shared_ptr<LINK<NODE>> l);
}

#include 'components.tpp'
