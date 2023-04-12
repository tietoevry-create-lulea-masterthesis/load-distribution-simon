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

class UE
{
private:
    std::string uid;
    float coords[2]; // x, y coords

    int prb_demand = 2;                    // amount of physical resource blocks that the traffic of this UE demands
    RU_entry dist_arr[UE_CLOSEST_RUS]; // array of n closest RUs

public:
    UE(std::string uid, float coords[2]);

    const std::string get_UID();
    const float *get_coords();
    const int get_demand();
    const RU_entry *get_dist_arr();

    bool operator==(UE const &ue)
    {
        return (ue.uid.compare(this->uid) == 0);
    }

    void set_dist_arr(RU_entry *new_dist_arr);
};

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
    const void add_down(std::shared_ptr<LINK_DU_RU> l)
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
    const void add_down(std::shared_ptr<LINK_CU_DU> l)
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

//LINKS//

class LINK_CU_DU
{
    private:
        int id;
        int rate;
        int delay;
        std::shared_ptr<CU> up;
        std::shared_ptr<DU> down;
    public:
        LINK_CU_DU();
        LINK_CU_DU(int id, int rate, int delay, std::shared_ptr<CU> up, std::shared_ptr<DU> down);

        const int get_id();
        const int get_rate();
        const int get_delay();
        const std::shared_ptr<CU> get_upper();
        const std::shared_ptr<DU> get_lower();

        const void add_rate(int rate);
        const void add_delay(int delay);
        const void add_up(std::shared_ptr<CU> up);
        const void add_down(std::shared_ptr<DU> down);
};

class LINK_DU_RU
{
    private:
        int id;
        int rate;
        int delay;
        std::shared_ptr<DU> up;
        std::shared_ptr<RU> down;
    public:
        LINK_DU_RU();
        LINK_DU_RU(int id, int rate, int delay, std::shared_ptr<DU> up, std::shared_ptr<RU> down);

        const int get_id();
        const int get_rate();
        const int get_delay();
        const std::shared_ptr<DU> get_upper();
        const std::shared_ptr<RU> get_lower();

        const void add_rate(int rate);
        const void add_delay(int delay);
        const void add_up(std::shared_ptr<DU> up);
        const void add_down(std::shared_ptr<RU> down);
};

class LINK_DU_DU
{
    private:
        int id;
        int rate;
        int delay;
        std::shared_ptr<DU> up;
        std::shared_ptr<DU> down;
    public:
        LINK_DU_DU();
        LINK_DU_DU(int id, int rate, int delay, std::shared_ptr<DU> up, std::shared_ptr<DU> down);

        const int get_id();
        const int get_rate();
        const int get_delay();
        const std::shared_ptr<DU> get_upper();
        const std::shared_ptr<DU> get_lower();

        const void add_rate(int rate);
        const void add_delay(int delay);
        const void add_up(std::shared_ptr<DU> up);
        const void add_down(std::shared_ptr<DU> down);
};

class LINK_RU_RU
{
    private:
        int id;
        int rate;
        int delay;
        std::shared_ptr<RU> up;
        std::shared_ptr<RU> down;
    public:
        LINK_RU_RU();
        LINK_RU_RU(int id, int rate, int delay, std::shared_ptr<RU> up, std::shared_ptr<RU> down);

        const int get_id();
        const int get_rate();
        const int get_delay();
        const std::shared_ptr<RU> get_upper();
        const std::shared_ptr<RU> get_lower();

        const void add_rate(int rate);
        const void add_delay(int delay);
        const void add_up(std::shared_ptr<RU> up);
        const void add_down(std::shared_ptr<RU> down);
};

class LINK_ENDPOINT_CU
{
    private:
        int id;
        int rate;
        int delay;
        std::shared_ptr<ENDPOINT> up;
        std::shared_ptr<CU> down;
    public:
        LINK_ENDPOINT_CU(int id, std::shared_ptr<ENDPOINT> up, std::shared_ptr<CU> down);

        const int get_id();
        const int get_rate();
        const int get_delay();
        const std::shared_ptr<ENDPOINT> get_upper();
        const std::shared_ptr<CU> get_lower();

        const void add_up(std::shared_ptr<ENDPOINT> up);
        const void add_down(std::shared_ptr<CU> down);
};