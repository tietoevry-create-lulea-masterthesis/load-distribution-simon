#pragma once
#include <chrono>
#include <map>
#include "constants.h"
#include <memory>
#include <vector>

class ENDPOINT //Fictional node representing connection to the wider internet from CUs. 
{
private:
    int connected_UEs;

    std::vector<std::shared_ptr<LINK>> downList;

public:
    ENDPOINT();
    
    const int get_connected_UE_number();
    const void add_down(std::shared_ptr<LINK> l);
    
};

template <class T>
class LINK
{
    private:
        int id;
        int rate;
        int delay;
        std::shared_ptr<T> up;
        std::shared_ptr<T> down;
    public:
        LINK();
        LINK(int id, int rate, int delay, std::shared_ptr<T> up, std::shared_ptr<T> down);

        const int get_rate();
        const int get_delay();
        const std::shared_ptr<T> get_upper();
        const std::shared_ptr<T> get_lower();

        const void add_up(std::shared_ptr<T> up);
        const void add_down(std::shared_ptr<T> down);
}

class NODE
{
    private:
        int id;
        int rate;
        int delay;
        std::vector<std::shared_ptr<LINK>> upList;
        std::vector<std::shared_ptr<LINK>> downList;
    public:
        Node();

        const void add_up(std::shared_ptr<LINK> l);
        const void add_down(std::shared_ptr<LINK> l);
};
}

class CU: public NODE
{
private:
public:
    CU(int id);

}

class DU: public NODE
{
private:
    std::vector<std::shared_ptr<LINK>> siblingList;
public:
    DU(int id);

    const void add_sibling(std::shared_ptr<LINK> l);
}
class RU: public NODE
{
private:
    std::vector<std::shared_ptr<LINK>> siblingList;
public:
    RU(int id);

    const void add_sibling(std::shared_ptr<LINK> l);
}
