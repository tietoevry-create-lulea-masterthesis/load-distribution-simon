#pragma once
#include <chrono>
#include <map>
#include "constants.h"
#include <memory>
#include <vector>

class RU
{
private:
    int id;
    int bandwidth = 4000000; // default: 4 MHz

    std::vector<std::shared_ptr<LINK_DU_RU>> upList;
    std::vector<std::shared_ptr<LINK_RU_RU>> siblingList;

public:
    RU();
    RU(int id);

    const int get_id();
    const void add_sibling(std::shared_ptr<LINK_RU_RU> l);
    const void add_up(std::shared_ptr<LINK_DU_RU> l);

};

// RU entry for use in the dist_list in UE class
// struct RU_entry
// {
//     std::string ru_uid;
//     float dist;

//     RU_entry() {
//         ru_uid = "NULL";
//         dist = INT32_MAX;
//     }

//     RU_entry(std::string ru_uid, float dist) : ru_uid(ru_uid), dist(dist)
//     {
//     }

//     bool operator<(RU_entry const &e)
//     {
//         return (this->dist < e.dist);
//     }
// };

class DU
{
private:
    int id;
    int bandwidth = 4000000; // default: 4 MHz
    std::vector<std::shared_ptr<LINK_CU_DU>> upList;
    std::vector<std::shared_ptr<LINK_DU_RU>> downList;
    std::vector<std::shared_ptr<LINK_DU_DU>> siblingList;

public:
    //DU();
    DU(int id);

    const int get_id();

    const void add_sibling(std::shared_ptr<LINK_DU_DU> l);
    const void add_up(std::shared_ptr<LINK_CU_DU> l);
    const void add_down(std::shared_ptr<LINK_DU_RU> l);
};

class CU
{
private:
    int id;
    int bandwidth = 4000000; // default: 4 MHz

    std::vector<std::shared_ptr<LINK_ENDPOINT_CU>> upList;
    std::vector<std::shared_ptr<LINK_CU_DU>> downList;

public:
    CU();
    CU(int id);

    const int get_id();

    const void add_up(std::shared_ptr<LINK_ENDPOINT_CU> l);
    const void add_down(std::shared_ptr<LINK_CU_DU> l);
};

class ENDPOINT //Fictional node representing connection to the wider internet from CUs. 
{
private:
    int connected_UEs;

    std::vector<std::shared_ptr<LINK_ENDPOINT_CU>> downList;

public:
    ENDPOINT();
    
    const int get_connected_UE_number();
    const void add_down(std::shared_ptr<LINK_ENDPOINT_CU> l);
    
};

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
        LINK(int id, std::shared_ptr<T> up, std::shared_ptr<T> down);

        const int get_rate();
        const int get_delay();
        const std::shared_ptr<T> get_upper();
        const std::shared_ptr<T> get_lower();

        const void add_up(std::shared_ptr<T> up);
        const void add_down(std::shared_ptr<T> down);
}