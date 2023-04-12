#include <iostream>
#include "components.h"

NODE::NODE(int id) {
    int i;
}

LINK<NODE>::LINK(){}

template <typename T>
LINK<T>::LINK(int id, int rate, int delay, std::shared_ptr<T> up, std::shared_ptr<T> down) {
    this->id = id;
    this->rate = rate;
    this->delay = delay;
    this->up = up;
    this->down = down;
}
template <typename T>
const void LINK<T>::add_up(std::shared_ptr<T> up){
    this->up = up;
}

template <typename T>
const void LINK<T>::add_down(std::shared_ptr<T> down){
    this->down = down;
}

// ============
// RU Functions
// ============


RU::RU(int id) {

}

const void RU::add_sibling(std::shared_ptr<LINK> l)
{
    this->siblingList.push_back(l);
}

const void RU::add_up(std::shared_ptr<LINK> l)
{
    this->upList.push_back(l);
}

//CU METHODS//

CU::CU(int id) {
    this->id = id;
}

const int CU::get_id()
{
    return this->id;
}

const void CU::add_down(std::shared_ptr<LINK<T>> l)
{
    this->downList.push_back(l);
}

const void CU::add_up(std::shared_ptr<LINK<T>> l)
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

const void DU::add_up(std::shared_ptr<LINK<T>> l)
{
    this->upList.push_back(l);
}

const void DU::add_sibling(std::shared_ptr<LINK<T>> l)
{
    this->siblingList.push_back(l);
}

const void DU::add_down(std::shared_ptr<LINK<T>> l)
{
    this->downList.push_back(l);
}

//ENDPOINT//

ENDPOINT::ENDPOINT(){}


const void ENDPOINT::add_down(std::shared_ptr<LINK> l) 
{
    this->downList.push_back(l);
}
