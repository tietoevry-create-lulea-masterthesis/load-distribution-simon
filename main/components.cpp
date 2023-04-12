#include <iostream>
#include "components.h"

NODE::NODE(int id) {
    int i;
}

const void NODE::add_up(std::shared_ptr<LINK<NODE>> up) {
    this->upList.push_back(up);
}

const void NODE::set_id(int i) {
    
}

// ============
// RU Functions
// ============


RU::RU(int id) {
    this->
}

const void RU::add_sibling(std::shared_ptr<LINK<NODE>> l)
{
    this->siblingList.push_back(l);
}

const void RU::add_up(std::shared_ptr<LINK<NODE>> l)
{
    this->add_up(l);
}

//CU METHODS//

CU::CU(int id) {}

const void CU::add_down(std::shared_ptr<LINK<NODE>> l)
{
    this->add_down(l);
}

const void CU::add_up(std::shared_ptr<LINK<NODE>> l)
{
    this->add_up(l);
}

//DU METHODS//

DU::DU(int id) {}

const void DU::add_up(std::shared_ptr<LINK<NODE>> l)
{
    this->add_up(l);
}

const void DU::add_sibling(std::shared_ptr<LINK<NODE>> l)
{
    this->add_sibling(l);
}

const void DU::add_down(std::shared_ptr<LINK<NODE>> l)
{
    this->add_down(l);
}

//ENDPOINT//

ENDPOINT::ENDPOINT(){}


const void ENDPOINT::add_down(std::shared_ptr<LINK<NODE>> l) 
{
    this->add_down(l);
}
