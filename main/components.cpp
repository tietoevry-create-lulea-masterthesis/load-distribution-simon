#include <iostream>
#include "components.h"

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

DU::DU(int id) {
    this->id = id;
}

const int CU::get_id()
{
    return this->id;
}

const void CU::add_down(std::shared_ptr<LINK_CU_DU> l)
{
    this->downList.push_back(l);
}

const void CU::add_up(std::shared_ptr<LINK_ENDPOINT_CU> l)
{
    this->upList.push_back(l);
}

//DU METHODS//

DU::DU(int id) {
    this->id = id;
}

const int DU::get_id()
{
    return this->id;
}

const void DU::add_up(std::shared_ptr<LINK_CU_DU> l)
{
    this->upList.push_back(l);
}

const void DU::add_sibling(std::shared_ptr<LINK_DU_DU> l)
{
    this->siblingList.push_back(l);
}

const void DU::add_down(std::shared_ptr<LINK_DU_RU> l)
{
    this->downList.push_back(l);
}

//ENDPOINT//

ENDPOINT::ENDPOINT(){}

const void ENDPOINT::add_down(std::shared_ptr<LINK_ENDPOINT_CU> l) 
{
    this->downList.push_back(l);
}

/////////////////////////////////////////////////////////////
template <typename T>

LINK::LINK(int id, std::shared_ptr<T> up, std::shared_ptr<T> down) {
    this->id = id;
    this->up = up;
    this->down = down;
}

const void LINK::
