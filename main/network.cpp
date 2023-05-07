#include "constants.h"
#include "components.h"
#include "components.cpp"
#include <vector>
#include <random>
#include <string>
#include "path.h"
#include <tuple>
#include <algorithm>

///Containers
//Nodes
std::vector<std::shared_ptr<NODE>> RUContainer;
std::vector<std::shared_ptr<NODE>> DUContainer;
std::vector<std::shared_ptr<NODE>> CUContainer;

std::shared_ptr<ENDPOINT> endpoint = std::make_shared<ENDPOINT>(1); //Create Endpoint

//Edges
std::vector<std::shared_ptr<LINK<NODE>>> ENDPOINT_CU_List;
std::vector<std::shared_ptr<LINK<NODE>>> CU_DU_List;
std::vector<std::shared_ptr<LINK<NODE>>> DU_DU_List;
std::vector<std::shared_ptr<LINK<NODE>>> DU_RU_List;
std::vector<std::shared_ptr<LINK<NODE>>> RU_RU_List;

//Counters
long comparisons = 0;
long goodcomparisons = 0;

bool GetRandomBool()
{
    return rand() & 1;
}

template<typename T>
bool AdjacentExistsUp(std::vector<T> a, int i)
{
    return a[i+1] != nullptr;
}

template<typename T>
bool AdjacentExistsDown(std::vector<T> a, int i)
{
    return a[i-1] != nullptr;
}

int CreateRandomRate()
{
    std::vector<int> rates {10, 50, 100, 250, 500, 750, 1000};

    int r_pos = std::rand() % rates.size();
    return rates[r_pos];
}

int CreateRandomRateLinks()
{
    std::vector<int> rates {1000, 2000, 3000, 4000, 5000};

    int r_pos = std::rand() % rates.size();
    return rates[r_pos];
}

int CreateRandomDelay()
{
    std::vector<int> delays {1, 2, 3, 4, 5, 10, 20, 50, 100, 500};

    int r_pos = std::rand() % delays.size();
    return delays[r_pos];
}

int CreateRandomDelayLinks()
{
    std::vector<int> delays {1, 2, 3, 4, 5, 10};

    int r_pos = std::rand() % delays.size();
    return delays[r_pos];
}

void CreateRandomRU_RUConnections() //Should be okay
{
    for (int i = 0; i < RU_NUMBER; ++i) {
        std::shared_ptr<NODE> ru = RUContainer[i];
        int rate = CreateRandomRateLinks();
        int delay = CreateRandomDelayLinks();
        
        if (AdjacentExistsUp(RUContainer, i)) {
            if (GetRandomBool()) {
                std::shared_ptr<NODE> up = RUContainer[i+1];
                std::shared_ptr<LINK<NODE>> l = std::make_shared<LINK<NODE>>(i, rate, delay, up, ru);

                RU_RU_List.push_back(l);
                ru->add_sibling(l);
                up->add_sibling(l);
            }
        }
    }
}

void CreateRandomDU_DUConnections()
{
    for (int i = 0; i < DU_NUMBER; ++i) {
        std::shared_ptr<NODE> du = DUContainer[i];
        int rate = CreateRandomRateLinks();
        int delay = CreateRandomDelayLinks();
        
        if (AdjacentExistsUp(DUContainer, i)) {
            if (GetRandomBool()) {
                std::shared_ptr<NODE> up = DUContainer[i+1];
                std::shared_ptr<LINK<NODE>> l = std::make_shared<LINK<NODE>>(i, rate, delay, up, du);

                DU_DU_List.push_back(l);
                du->add_sibling(l);
                up->add_sibling(l);
            }
        }
    }
}

void CreateRandomDU_RUConnections()
{
    for (int i = 0; i < RU_NUMBER; ++i) {
        for (int j = 0; j < DU_NUMBER; ++j) {
            if (GetRandomBool()) {
                std::shared_ptr<NODE> ru = RUContainer[i];
                std::shared_ptr<NODE> du = DUContainer[j];
                int rate = CreateRandomRateLinks();
                int delay = CreateRandomDelayLinks();

                std::shared_ptr<LINK<NODE>> l = std::make_shared<LINK<NODE>>(i, rate, delay, du, ru);

                DU_RU_List.push_back(l);
                ru->add_up(l);
                du->add_down(l); //Segmentation fault
            }
        }
    }
}

void CreateRandomCU_DUConnections()
{
    for (int i = 0; i < DU_NUMBER; ++i) {
        for (int j = 0; j < CU_NUMBER; ++j) {
            if (GetRandomBool()) {
                std::shared_ptr<NODE> du = DUContainer[i];
                std::shared_ptr<NODE> cu = CUContainer[j];
                int rate = CreateRandomRateLinks();
                int delay = CreateRandomDelayLinks();

                std::shared_ptr<LINK<NODE>> l = std::make_shared<LINK<NODE>>(i, rate, delay, cu, du);

                CU_DU_List.push_back(l);
                cu->add_down(l);
                du->add_up(l);
            }
        }
    }
}

void CreateEndpointConnections()
{
    for (int i = 0; i < CU_NUMBER; ++i) {
        std::shared_ptr<NODE> cu = CUContainer[i];

        std::shared_ptr<LINK<NODE>> l = std::make_shared<LINK<NODE>>(i, 9999, 0, endpoint, cu);

        ENDPOINT_CU_List.push_back(l);
        endpoint->add_down(l);
        cu->add_up(l);

    }
}

void CreatePredefinedConnections(){}


void CreateRandomConnections()
{   
    CreateRandomRU_RUConnections();
    CreateRandomDU_RUConnections();
    CreateRandomDU_DUConnections();
    CreateRandomCU_DUConnections();
    CreateEndpointConnections();
}

void CreateNodes()
{
    //Create RUs
    for (int i = 0; i < RU_NUMBER; ++i) {
        std::shared_ptr<RU> r = std::make_shared<RU>(i);
        RUContainer.push_back(r);
    }

    //Create DUs
    for (int i = 0; i < DU_NUMBER; ++i) {
        std::shared_ptr<DU> d = std::make_shared<DU>(i);
        DUContainer.push_back(d);
    }

    //Create CUs
    for (int i = 0; i < CU_NUMBER; ++i) {
        std::shared_ptr<CU> c = std::make_shared<CU>(i);
        CUContainer.push_back(c);
    }
}

void TestPrint()
{
    int rus = RUContainer.size();
    int dus = DUContainer.size();
    int cus = CUContainer.size();

    int ru_ru = RU_RU_List.size();
    int du_ru = DU_RU_List.size();
    int du_du = DU_DU_List.size();
    int cu_du = CU_DU_List.size();
    int end = ENDPOINT_CU_List.size();

    

    std::cout << "Number of RUs: " << rus << "\n";
    std::cout << "Number of DUs: " << dus << "\n";
    std::cout << "Number of CUs: " << cus << "\n";

    std::cout << "-------------------------------------\n";

    std::cout << "Number of RU-RU Links: " << ru_ru << "\n";
    std::cout << "Number of DU-RU Links: " << du_ru << "\n";
    std::cout << "Number of DU-DU Links: " << du_du << "\n";
    std::cout << "Number of CU-DU Links: " << cu_du << "\n";
    std::cout << "Number of ENDPOINT-CU Links: " << end << "\n";

    std::cout << "-------------------------------------\n";

    std::cout << "Number of Comparisons: " << goodcomparisons << "\n";

    std::cout << "-------------------------------------\n";

    std::cout << "Fully Connected UEs: " << endpoint->get_UE() << "\n";
}

///////////////////////
//                   //
// First Valid Conn  //
//                   //
///////////////////////

std::pair<bool, int> FirstValidConnectionCheck(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, std::shared_ptr<LINK<NODE>> con, int rate, int allowedDelay, int currentLevel) {
            auto b = p->getBannedLinks();

            if(std::find(b.begin(), b.end(), con) != b.end()) {
                return std::pair<bool, int>(false, allowedDelay);
            }

            if (con->get_rate() >= rate && con->get_delay() <= allowedDelay) {
                allowedDelay = allowedDelay - con->get_delay();

                //Maintain Link
                con->use_rate(rate);

                //Maintain Path
                p->addDelay(con->get_delay());
                p->addLink(con);
                p->addBannedLink(con);
                p->addNode(con->get_lower()); //Gets us duplicates :/
                p->addNode(con->get_upper());
                
                return std::pair<bool, int>(true, allowedDelay);
            } else {
                return std::pair<bool, int>(false, allowedDelay);
            }
}

std::pair<bool, int> FirstValidConnectionRU(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, int rate, int allowedDelay, int currentLevel) {
    int i = rand() % RU_NUMBER;

    int cSize = RUContainer[i]->get_upList().size();
    auto list = RUContainer[i]->get_upList();

    for (int j = 0; j < cSize; ++j) {
        ++comparisons;
        auto con = list[j];
        std::pair<bool, int> res = FirstValidConnectionCheck(p, con, rate, allowedDelay, currentLevel);

        if (res.first) {
            return res;
        }
    }

    //No Connection found
    return std::pair<bool, int>(false, allowedDelay);
}

//Nodes other than RU
std::pair<bool, int> FirstValidConnectionNODE(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, int rate, int allowedDelay, int currentLevel) {
    int cSize = p->getNodes().back()->get_upList().size();
    auto list = p->getNodes().back()->get_upList();
   
    for (int j = 0; j < cSize; ++j) {
            ++comparisons;
            auto con = list[j];

            std::pair<bool, int> res = FirstValidConnectionCheck(p, con, rate, allowedDelay, currentLevel);

            if (res.first) {
                return res;
            }
    }

    //No Connection Found

    return std::pair<bool, int>(false, allowedDelay);
}

bool FirstValidConnectionRecursive(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, int currentLevel, int rate, int allowedDelay) { // For basic testing. Forward only

    int levelTotalNodes = 0;

    std::vector<std::shared_ptr<NODE>> container;

    std::pair<bool, int> res;

    switch (currentLevel) {
        case 0: //RU
            res = FirstValidConnectionRU(p, rate, allowedDelay, currentLevel);
            if (res.first) {
                FirstValidConnectionRecursive(p, currentLevel+1, rate, res.second);
            } else {
                return false;
            }
            break;
        case 1: //DU
            res = FirstValidConnectionNODE(p, rate, allowedDelay, currentLevel);
            if (res.first) {
                FirstValidConnectionRecursive(p, currentLevel+1, rate, res.second);
            } else {
                p->deleteWrongPath();
                FirstValidConnectionRecursive(p, currentLevel-1, rate, res.second);
            }
            break;
        case 2: //CU
            res = FirstValidConnectionNODE(p, rate, allowedDelay, currentLevel);
            if (res.first) {
                FirstValidConnectionRecursive(p, currentLevel+1, rate, res.second);
            } else {
                p->deleteWrongPath();
                FirstValidConnectionRecursive(p, currentLevel-1, rate, res.second);
            }
            break;
        case 3: //ENDPOINT
            p->getNodes().back()->add_UE();
            p->setComplete();
            return true;
            break;
        default:
            std::cout << "Something wrong with single path recursive";
            return false;    
    }
}

bool FirstValidConnection(int rate, int allowedDelay) {
    std::shared_ptr<PATH<NODE,LINK<NODE>>> p = std::make_shared<PATH<NODE,LINK<NODE>>>();
    return FirstValidConnectionRecursive(p, 0, rate, allowedDelay);
}

///////////////////////
//                   //
//    Naive WAC      //
//                   //
///////////////////////

std::pair<bool, int> NaiveWACConnection(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, std::vector<std::shared_ptr<LINK<NODE>>> connections, int rateRequirement, int delayRequirement) {
    std::shared_ptr<LINK<NODE>> chosenConnection = nullptr;
    int currentRate = 999999;
    int currentDelay = 0;
    
    for (int i = 0; i < connections.size(); ++i) {

        auto b = p->getBannedLinks();
        
        auto con = connections[i];

        if(std::find(b.begin(), b.end(), con) != b.end()) { //Check for banned link
                return std::pair<bool, int>(false, delayRequirement);
        }

        ++comparisons;

        if (con->get_rate() >= rateRequirement && con->get_rate() <= currentRate) {
            if (con->get_delay() <= delayRequirement && con->get_delay() >= currentDelay) {
                currentDelay = con->get_delay();
                currentRate = con->get_rate();
                chosenConnection = con;
            }
        }
    }
    delayRequirement = delayRequirement - currentDelay;

    if (chosenConnection == nullptr) {
        return std::pair<bool, int>(false, delayRequirement);
    }

    //Maintain delay
    delayRequirement = delayRequirement - currentDelay;

    //Maintain Links.
    chosenConnection->use_rate(rateRequirement);

    //Maintain Path
    p->addDelay(currentDelay);
    p->addLink(chosenConnection);
    p->addBannedLink(chosenConnection);
    p->addNode(chosenConnection->get_lower());
    p->addNode(chosenConnection->get_upper());

    return std::pair<bool, int>(true, delayRequirement);
}

std::pair<bool, int> NaiveWACConnectionRU(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, int rateRequirement, int delayRequirement) {
    int i = rand() % RU_NUMBER;

    auto list = RUContainer[i]->get_upList();
    
    return NaiveWACConnection(p, list, rateRequirement, delayRequirement);
}

std::pair<bool, int> NaiveWACConnectionNODE(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, int rateRequirement, int delayRequirement) {
    auto list = p->getNodes().back()->get_upList();

    return NaiveWACConnection(p, list, rateRequirement, delayRequirement);
}

bool NaiveWACLevelSelect(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, int currentLevel, int rateRequirement, int delayRequirement) {

    bool r = true;

    std::pair<bool, int> res;

    switch (currentLevel)
    {
        case 0:
            res = NaiveWACConnectionRU(p, rateRequirement, delayRequirement);
            if (res.first) {
                NaiveWACLevelSelect(p, currentLevel+1, rateRequirement, res.second);
            } else {
                r = false;
                return r;
            }
            break;
        case 1:
            res = NaiveWACConnectionNODE(p, rateRequirement, delayRequirement);
            if (res.first) {
                NaiveWACLevelSelect(p, currentLevel+1, rateRequirement, res.second);
            } else {
                p->deleteWrongPath();
                NaiveWACLevelSelect(p, currentLevel-1, rateRequirement, res.second);
            }
            break;
        case 2:
            res = NaiveWACConnectionNODE(p, rateRequirement, delayRequirement);
            if (res.first) {
                NaiveWACLevelSelect(p, currentLevel+1, rateRequirement, res.second);
            } else {
                p->deleteWrongPath();
                NaiveWACLevelSelect(p, currentLevel-1, rateRequirement, res.second);
            }
            break;
        case 3:
            p->getNodes().back()->add_UE();
            p->setComplete();
            r = true;
            return r;
            break;
        default:
            std::cout << "Something wrong with Naive WAC selection";
            r = false;
            return r;
    }
}


bool NaiveWAC(int rate, int delay) {
    std::shared_ptr<PATH<NODE,LINK<NODE>>> p = std::make_shared<PATH<NODE,LINK<NODE>>>();
    bool r = NaiveWACLevelSelect(p, 0, rate, delay);
    return r;
}

///////////////////////
//                   //
// PARAMETERIZED WAC //
//                   //
///////////////////////

std::pair<bool, int> SideWACConnection(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, std::shared_ptr<NODE> node, int rateRequirement, int delayRequirement) {
    std::shared_ptr<LINK<NODE>> chosenConnection = nullptr;
    std::shared_ptr<LINK<NODE>> chosenSiblingConnection = nullptr;
    int currentRate = 999999;
    int currentDelay = 0;
    
    auto connections = node->get_upList();
    
    //Current nodes
    for (int i = 0; i < connections.size(); ++i) {
        ++comparisons;

        auto con = connections[i];

        if (con->get_rate() >= rateRequirement && con->get_rate() <= currentRate) {
            if (con->get_delay() <= delayRequirement && con->get_delay() >= currentDelay) {
                currentDelay = con->get_delay();
                currentRate = con->get_rate();
                chosenConnection = con;
            }
        }
    }

    //Siblings
    auto siblings = node->get_siblingList();

    for (int n = 0; n < siblings.size(); ++n) {
        std::vector<std::shared_ptr<LINK<NODE>>> sibUp;
        std::shared_ptr<LINK<NODE>> sibCon = siblings[n];

        if (siblings[n]->get_lower() == node) {
            sibUp = siblings[n]->get_upper()->get_upList();
        } else {
            sibUp = siblings[n]->get_lower()->get_upList();
        }


        for (int i = 0; i < sibUp.size(); ++i) {
            ++comparisons;

            auto con = sibUp[i];

            if (con->get_rate() >= rateRequirement && sibCon->get_rate() >= rateRequirement && con->get_rate() <= currentRate) {
                if ((con->get_delay() + sibCon->get_delay()) <= delayRequirement && (con->get_delay() + sibCon->get_delay()) >= currentDelay) {
                    currentDelay = con->get_delay() + sibCon->get_delay();
                    currentRate = con->get_rate();
                    chosenConnection = con;
                }
            }
        }
    }

    delayRequirement = delayRequirement - currentDelay;

    if (chosenConnection == nullptr) {
        return std::pair<bool, int>(false, delayRequirement);
    }

    //Maintain delay
    delayRequirement = delayRequirement - currentDelay;

    //Maintain Links.
    chosenConnection->use_rate(rateRequirement);
    if(chosenSiblingConnection != nullptr) {
        chosenSiblingConnection->use_rate(rateRequirement);
    }

    //Maintain Path
    p->addDelay(currentDelay);
    if(chosenSiblingConnection != nullptr) {
        p->addLink(chosenConnection);
        p->addLink(chosenSiblingConnection);
        if (chosenSiblingConnection->get_lower() == node) {
            p->addNode(chosenSiblingConnection->get_upper());
            p->addNode(chosenSiblingConnection->get_lower());
        } else {
            p->addNode(chosenSiblingConnection->get_lower());
            p->addNode(chosenSiblingConnection->get_upper());
        }
        p->addNode(chosenConnection->get_upper());
    } else {
        p->addLink(chosenConnection);
        p->addNode(chosenConnection->get_lower());
        p->addNode(chosenConnection->get_upper());
    }

    return std::pair<bool, int>(true, delayRequirement);
}

std::pair<bool, int> SideWACConnectionRU(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, int rateRequirement, int delayRequirement) {
    int i = rand() % RU_NUMBER;

    auto node = RUContainer[i];

    return SideWACConnection(p, node, rateRequirement, delayRequirement);
}

std::pair<bool, int> SideWACConnectionNODE(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, int rateRequirement, int delayRequirement) {
    auto node = p->getNodes().back();

    return SideWACConnection(p, node, rateRequirement, delayRequirement);
}

bool SideWACLevelSelect(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, int currentLevel, int rateRequirement, int delayRequirement) {

    std::pair<bool, int> res;

    switch (currentLevel)
    {
        case 0:
            res = SideWACConnectionRU(p, rateRequirement, delayRequirement);
            if (res.first) {
                SideWACLevelSelect(p, currentLevel+1, rateRequirement, res.second);
            } else {
                return false;
            }
            break;
        case 1:
            res = SideWACConnectionNODE(p, rateRequirement, delayRequirement);
            if (res.first) {
                SideWACLevelSelect(p, currentLevel+1, rateRequirement, res.second);
            } else {
                return false;
            }
            break;
        case 2:
            res = SideWACConnectionNODE(p, rateRequirement, delayRequirement);
            if (res.first) {
                SideWACLevelSelect(p, currentLevel+1, rateRequirement, res.second);
            } else {
                return false;
            }
            break;
        case 3:
            p->getNodes().back()->add_UE();
            p->setComplete();
            return true;
        default:
            std::cout << "Something wrong with Naive WAC selection";
            return false;
    }
    return false;
}

bool SideWAC(int rate, int delay) {
    std::shared_ptr<PATH<NODE,LINK<NODE>>> p = std::make_shared<PATH<NODE,LINK<NODE>>>();
    return SideWACLevelSelect(p, 0, rate, delay);
}

void PushRandomLoad(int UENumber, int algo)  {
    int x = 0;
    int earlyStop = 0;
    int earlyStopLimit = 10;
    goodcomparisons = 0;

    for (int i = 0; i < UENumber; ++i) {
        comparisons = 0;
        if (earlyStop == earlyStopLimit) {
            return;
        }

        switch (algo)
        {
        case 1:
            if(FirstValidConnection(CreateRandomRate(), CreateRandomDelay())){
                earlyStop = 0;
                goodcomparisons = goodcomparisons + comparisons;
            } else {
                ++earlyStop;
            }
            break;
        case 2:
            if(NaiveWAC(CreateRandomRate(), CreateRandomDelay())) {
                earlyStop = 0;
                goodcomparisons = goodcomparisons + comparisons;
            } else {
                ++earlyStop;
            }
            break;
        case 3:
            if(SideWAC(CreateRandomRate(), CreateRandomDelay())) {
                earlyStop = 0;
            } else {
                ++earlyStop;
            }
            break;
        default:
            break;
        }
    }

    x = x + 1;
    std::cout << "\r" << (x/UENumber);
}

//For testing
void checkload(int algo) {
    for (int i = 0; i < 100; ++i) {
        PushRandomLoad(i+1, algo);
        std::cout << "[" << i+1 << "] - " << endpoint->get_UE() << "\n";
    }
}