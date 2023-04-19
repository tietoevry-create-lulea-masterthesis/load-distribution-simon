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
        int connectedUEs; //For endpoint

        std::vector<std::shared_ptr<LINK<NODE>>> upList;
        std::vector<std::shared_ptr<LINK<NODE>>> downList;
        std::vector<std::shared_ptr<LINK<NODE>>> siblingList;
    public:
        NODE();
        NODE(int id);
        const void set_id(int i);

        const void add_sibling(std::shared_ptr<LINK<NODE>> l);
        const void add_up(std::shared_ptr<LINK<NODE>> l);
        const void add_down(std::shared_ptr<LINK<NODE>> l);
        const void add_UE();

        const std::vector<std::shared_ptr<LINK<NODE>>> get_siblingList();
        const std::vector<std::shared_ptr<LINK<NODE>>> get_upList();
        const std::vector<std::shared_ptr<LINK<NODE>>> get_downList();
};

class CU: public NODE
{
private:
    std::vector<std::shared_ptr<LINK<NODE>>> upList;
    std::vector<std::shared_ptr<LINK<NODE>>> downList;
public:
    CU(int id);

    const void add_up(std::shared_ptr<LINK<NODE>> l);
    const void add_down(std::shared_ptr<LINK<NODE>> l);

    const std::vector<std::shared_ptr<LINK<NODE>>> get_upList();
    const std::vector<std::shared_ptr<LINK<NODE>>> get_downList();
};

class DU: public NODE
{
private:
    std::vector<std::shared_ptr<LINK<NODE>>> upList;
    std::vector<std::shared_ptr<LINK<NODE>>> downList;
    std::vector<std::shared_ptr<LINK<NODE>>> siblingList;
public:
    DU(int id);

    const void add_sibling(std::shared_ptr<LINK<NODE>> l);
    const void add_up(std::shared_ptr<LINK<NODE>> l);
    const void add_down(std::shared_ptr<LINK<NODE>> l);

    const std::vector<std::shared_ptr<LINK<NODE>>> get_upList();
    const std::vector<std::shared_ptr<LINK<NODE>>> get_downList();
    const std::vector<std::shared_ptr<LINK<NODE>>> get_siblingList();
};
class RU: public NODE
{
private:
    std::vector<std::shared_ptr<LINK<NODE>>> upList;
    std::vector<std::shared_ptr<LINK<NODE>>> downList;
    std::vector<std::shared_ptr<LINK<NODE>>> siblingList;
public:
    RU(int id);

    const void add_sibling(std::shared_ptr<LINK<NODE>> l);
    const void add_up(std::shared_ptr<LINK<NODE>> l);
    const std::vector<std::shared_ptr<LINK<NODE>>> get_upList();
    const std::vector<std::shared_ptr<LINK<NODE>>> get_downList();
    const std::vector<std::shared_ptr<LINK<NODE>>> get_siblingList();
};

class ENDPOINT: public NODE{
    private:
    int connectedUEs;
    std::vector<std::shared_ptr<LINK<NODE>>> downList;

    public:
        ENDPOINT(int id);
        const void add_down(std::shared_ptr<LINK<NODE>> l);
};

#include "components.tpp"
