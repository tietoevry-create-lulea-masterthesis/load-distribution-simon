#include <iostream>
#include "components.h"

NODE::NODE(){
    this->connectedUEs = 0;
}

NODE::NODE(int id) {
    int i;
    this->connectedUEs = 0;
}

const void NODE::set_id(int i) {

}

const std::vector<std::shared_ptr<LINK<NODE>>> NODE::get_upList()
{
    return this->upList;
}

const std::vector<std::shared_ptr<LINK<NODE>>> NODE::get_downList()
{
    return this->downList;
}

const std::vector<std::shared_ptr<LINK<NODE>>> NODE::get_siblingList()
{
    return this->siblingList;
}

const void NODE::add_sibling(std::shared_ptr<LINK<NODE>> l)
{
    this->siblingList.push_back(l);
}

const void NODE::add_up(std::shared_ptr<LINK<NODE>> l)
{
    this->upList.push_back(l);
}

const void NODE::add_down(std::shared_ptr<LINK<NODE>> l)
{
    this->downList.push_back(l);
}

const void NODE::add_UE() {
    ++this->connectedUEs;
}

const int NODE::get_UE() {
    return this->connectedUEs;
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

const std::vector<std::shared_ptr<LINK<NODE>>> RU::get_upList()
{
    return this->upList;
}

const std::vector<std::shared_ptr<LINK<NODE>>> RU::get_downList()
{
    return this->downList;
}

const std::vector<std::shared_ptr<LINK<NODE>>> RU::get_siblingList()
{
    return this->siblingList;
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

const std::vector<std::shared_ptr<LINK<NODE>>> CU::get_upList()
{
    return this->upList;
}

const std::vector<std::shared_ptr<LINK<NODE>>> CU::get_downList()
{
    return this->downList;
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

const std::vector<std::shared_ptr<LINK<NODE>>> DU::get_upList()
{
    return this->upList;
}

const std::vector<std::shared_ptr<LINK<NODE>>> DU::get_downList()
{
    return this->downList;
}

const std::vector<std::shared_ptr<LINK<NODE>>> DU::get_siblingList()
{
    return this->siblingList;
}

//ENDPOINT//

ENDPOINT::ENDPOINT(int i){}


const void ENDPOINT::add_down(std::shared_ptr<LINK<NODE>> l) 
{
    this->downList.push_back(l);
}
