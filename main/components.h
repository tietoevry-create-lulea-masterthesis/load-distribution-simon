#pragma once
#include <chrono>
#include <map>
#include "constants.h"
#include <memory>
#include <vector>

class RU
{
private:
    std::string uid;
    float coords[2];         // x, y coords
    int antennae = 4;        // default: 4T4R
    int bandwidth = 4000000; // default: 4 MHz
    int num_PRB;             // number of physical resource blocks, depends on the bandwidth
    int alloc_PRB;           // number of physical resource blocks that have been allocated to UE

    float p = 3;                                            // power consumption, dependent on current traffic load, default = sleep power consumption, 3 mW or smth
    float p_tot = 0;                                        // total power consumption since t = 0
    std::chrono::_V2::system_clock::time_point last_meas_t; // time since last delta measurement of power consumption

public:
    RU();
    RU(std::string uid, float coords[2], int antennae, int bandwidth);

    const std::string get_UID();
    const float *get_coords();
    const int get_num_PRB();
    const int get_alloc_PRB();
    float calc_delta_p();
    const float get_p();
    const float get_p_tot();
    void set_alloc_PRB(int a_PRB);
};

// RU entry for use in the dist_list in UE class
struct RU_entry
{
    std::string ru_uid;
    float dist;

    RU_entry() {
        ru_uid = "NULL";
        dist = INT32_MAX;
    }

    RU_entry(std::string ru_uid, float dist) : ru_uid(ru_uid), dist(dist)
    {
    }

    bool operator<(RU_entry const &e)
    {
        return (this->dist < e.dist);
    }
};

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
    //int num_PRB;             // number of physical resource blocks, depends on the bandwidth
    //int alloc_PRB;           // number of physical resource blocks that have been allocated to UE

    //float p = 3;                                            // power consumption, dependent on current traffic load, default = sleep power consumption, 3 mW or smth
    //float p_tot = 0;                                        // total power consumption since t = 0
    //std::chrono::_V2::system_clock::time_point last_meas_t; // time since last delta measurement of power consumption

public:
    DU();
    DU(int id, int bandwidth);

    const int get_id();
};

class CU
{
private:
    int id;
    int bandwidth = 4000000; // default: 4 MHz

    std::vector<std::shared_ptr<LINK_ENDPOINT_CU>> upList;
    std::vector<std::shared_ptr<LINK_CU_DU>> downList;

    //int num_PRB;             // number of physical resource blocks, depends on the bandwidth
    //int alloc_PRB;           // number of physical resource blocks that have been allocated to UE

    //float p = 3;                                            // power consumption, dependent on current traffic load, default = sleep power consumption, 3 mW or smth
    //float p_tot = 0;                                        // total power consumption since t = 0
    //std::chrono::_V2::system_clock::time_point last_meas_t; // time since last delta measurement of power consumption

public:
    CU();
    CU(int id, float coords[2], int antennae, int bandwidth);

    const int get_id();
};

class ENDPOINT //Fictional node representing connection to the wider internet from CUs. 
{
private:
    int connected_UEs;

    std::vector<std::shared_ptr<LINK_ENDPOINT_CU>> downList;

public:
    ENDPOINT();
    
    const int get_connected_UE_number();
    
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
        LINK_DU_RU(int id, int rate, int delay, CU* up, DU* down);

        const int get_id();
        const int get_rate();
        const int get_delay();
        const std::shared_ptr<DU> get_upper();
        const std::shared_ptr<RU> get_lower();
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
        LINK_DU_DU(int id, int rate, int delay, CU* up, DU* down);

        const int get_id();
        const int get_rate();
        const int get_delay();
        const std::shared_ptr<DU> get_upper();
        const std::shared_ptr<DU> get_lower();
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
        LINK_RU_RU(int id, int rate, int delay, CU* up, DU* down);

        const int get_id();
        const int get_rate();
        const int get_delay();
        const std::shared_ptr<RU> get_upper();
        const std::shared_ptr<RU> get_lower();
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
        LINK_ENDPOINT_CU();
        LINK_ENDPOINT_CU(int id, int rate, int delay, std::shared_ptr<ENDPOINT> up, std::shared_ptr<CU> down);

        const int get_id();
        const int get_rate();
        const int get_delay();
        const std::shared_ptr<ENDPOINT> get_upper();
        const std::shared_ptr<CU> get_lower();
};