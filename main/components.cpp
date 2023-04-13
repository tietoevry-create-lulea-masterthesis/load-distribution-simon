#include <iostream>
#include "components.h"

NODE::NODE(){}

NODE::NODE(int id) {
    int i;
}

const void NODE::set_id(int i) {

}

// ============
// RU Functions
// ============


RU::RU(int id) {
    this->set_id(id);
}

const void RU::add_sibling(std::shared_ptr<LINK<NODE>> l)
{
    this->siblingList.push_back(l);
}

const void RU::add_up(std::shared_ptr<LINK<NODE>> l)
{
    this->upList.push_back(l);
}

//CU METHODS//

CU::CU(int id) {
    this->set_id(id);
}

const void CU::add_down(std::shared_ptr<LINK<NODE>> l)
{
    this->downList.push_back(l);
}

const void CU::add_up(std::shared_ptr<LINK<NODE>> l)
{
    this->upList.push_back(l);
}

//DU METHODS//

DU::DU(int id) {
    this->set_id(id);
}

const void DU::add_up(std::shared_ptr<LINK<NODE>> l)
{
    this->upList.push_back(l);
}

const void DU::add_sibling(std::shared_ptr<LINK<NODE>> l)
{
    this->siblingList.push_back(l);
}

const void DU::add_down(std::shared_ptr<LINK<NODE>> l)
{
    this->downList.push_back(l);
}

//ENDPOINT//

ENDPOINT::ENDPOINT(int i){}


const void ENDPOINT::add_down(std::shared_ptr<LINK<NODE>> l) 
{
    this->downList.push_back(l);
}
