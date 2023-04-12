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

const void RU::add_sibling(std::shared_ptr<LINK_RU_RU> l)
{
    this->siblingList.push_back(l);
}

const void RU::add_up(std::shared_ptr<LINK_DU_RU> l)
{
    this->upList.push_back(l);
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

// const RU_entry *UE::get_dist_arr()
// {
//     return this->dist_arr;
// }

// void UE::set_dist_arr(RU_entry new_dist_arr[UE_CLOSEST_RUS])
// {
//     for (size_t i = 0; i < UE_CLOSEST_RUS; i++)
//     {
//         this->dist_arr[i] = new_dist_arr[i];
//     }
// }

//List functions//

//RU-RU//

LINK_RU_RU::LINK_RU_RU()
{
}

LINK_RU_RU::LINK_RU_RU(int id, int rate, int delay, std::shared_ptr<RU> up, std::shared_ptr<RU> down)
{
    this->id = id;
    this->rate = rate;
    this->delay = delay;
    this->up = up;
    this->down = down;
}

const int LINK_RU_RU::get_id()
{
    return this->id;
}

const int LINK_RU_RU::get_rate()
{
    return this->rate;
}

const int LINK_RU_RU::get_delay()
{
    return this->delay;
}

const std::shared_ptr<RU> LINK_RU_RU::get_upper()
{
    return this->up;
}

const std::shared_ptr<RU> LINK_RU_RU::get_lower()
{
    return this->down;
}

const void LINK_RU_RU::add_rate(int rate)
{
    this->rate = rate;
}

const void LINK_RU_RU::add_delay(int delay)
{
    this->delay = delay;
}

const void LINK_RU_RU::add_up(std::shared_ptr<RU> up)
{
    this->up = up;
}

const void LINK_RU_RU::add_down(std::shared_ptr<RU> down)
{
    this->down = down;
}

//DU-RU

LINK_DU_RU::LINK_DU_RU()
{
}

LINK_DU_RU::LINK_DU_RU(int id, int rate, int delay, std::shared_ptr<DU> up, std::shared_ptr<RU> down)
{
    this->id = id;
    this->rate = rate;
    this->delay = delay;
    this->up = up;
    this->down = down;
}

const int LINK_DU_RU::get_id()
{
    return this->id;
}

const int LINK_DU_RU::get_rate()
{
    return this->rate;
}

const int LINK_DU_RU::get_delay()
{
    return this->delay;
}

const std::shared_ptr<DU> LINK_DU_RU::get_upper()
{
    return this->up;
}

const std::shared_ptr<RU> LINK_DU_RU::get_lower()
{
    return this->down;
}

const void LINK_DU_RU::add_rate(int rate)
{
    this->rate = rate;
}

const void LINK_DU_RU::add_delay(int delay)
{
    this->delay = delay;
}

const void LINK_DU_RU::add_up(std::shared_ptr<DU> up)
{
    this->up = up;
}

const void LINK_DU_RU::add_down(std::shared_ptr<RU> down)
{
    this->down = down;
}

//DU-DU//

LINK_DU_DU::LINK_DU_DU()
{
}

LINK_DU_DU::LINK_DU_DU(int id, int rate, int delay, std::shared_ptr<DU> up, std::shared_ptr<DU> down)
{
    this->id = id;
    this->rate = rate;
    this->delay = delay;
    this->up = up;
    this->down = down;
}

const int LINK_DU_DU::get_id()
{
    return this->id;
}

const int LINK_DU_DU::get_rate()
{
    return this->rate;
}

const int LINK_DU_DU::get_delay()
{
    return this->delay;
}

const std::shared_ptr<DU> LINK_DU_DU::get_upper()
{
    return this->up;
}

const std::shared_ptr<DU> LINK_DU_DU::get_lower()
{
    return this->down;
}

const void LINK_DU_DU::add_rate(int rate)
{
    this->rate = rate;
}

const void LINK_DU_DU::add_delay(int delay)
{
    this->delay = delay;
}

const void LINK_DU_DU::add_up(std::shared_ptr<DU> up)
{
    this->up = up;
}

const void LINK_DU_DU::add_down(std::shared_ptr<DU> down)
{
    this->down = down;
}

//CU-DU//

LINK_CU_DU::LINK_CU_DU()
{
}

LINK_CU_DU::LINK_CU_DU(int id, int rate, int delay, std::shared_ptr<CU> up, std::shared_ptr<DU> down)
{
    this->id = id;
    this->rate = rate;
    this->delay = delay;
    this->up = up;
    this->down = down;
}

const int LINK_CU_DU::get_id()
{
    return this->id;
}

const int LINK_CU_DU::get_rate()
{
    return this->rate;
}

const int LINK_CU_DU::get_delay()
{
    return this->delay;
}

const std::shared_ptr<CU> LINK_CU_DU::get_upper()
{
    return this->up;
}

const std::shared_ptr<DU> LINK_CU_DU::get_lower()
{
    return this->down;
}

const void LINK_CU_DU::add_rate(int rate)
{
    this->rate = rate;
}

const void LINK_CU_DU::add_delay(int delay)
{
    this->delay = delay;
}

const void LINK_CU_DU::add_up(std::shared_ptr<CU> up)
{
    this->up = up;
}

const void LINK_CU_DU::add_down(std::shared_ptr<DU> down)
{
    this->down = down;
}