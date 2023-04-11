#include <iostream>
#include "components.h"

using namespace std;
using namespace chrono;

// ============
// RU Functions
// ============

// Default (will create invalid RU)
RU::RU()
{
}

RU::RU(int id) {
    this->id = id;
}

const int RU::get_id() {
    return this->id;
}

//CU METHODS//

const int CU::get_id()
{
    return this->id;
}

//DU METHODS//

DU::DU() 
{
}

DU::DU(int id) {
    this->id = id;
}

const int DU::get_id()
{
    return this->id;
}


// ============
// UE Functions
// ============

UE::UE(string uid, float coords[2])
{
    this->uid = uid;
    this->coords[0] = coords[0];
    this->coords[1] = coords[1];
}

const string UE::get_UID()
{
    return this->uid;
}

const float *UE::get_coords()
{
    return this->coords;
}

const int UE::get_demand()
{
    return this->prb_demand;
}

const RU_entry *UE::get_dist_arr()
{
    return this->dist_arr;
}

void UE::set_dist_arr(RU_entry new_dist_arr[UE_CLOSEST_RUS])
{
    for (size_t i = 0; i < UE_CLOSEST_RUS; i++)
    {
        this->dist_arr[i] = new_dist_arr[i];
    }
}