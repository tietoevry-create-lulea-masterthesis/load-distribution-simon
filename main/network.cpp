#include "constants.h"
#include "components.h"
#include "components.cpp"
#include <vector>
#include <random>
#include <string>
#include "path.h"

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

int CreateRandomDelay()
{
    std::vector<int> delays {1, 2, 3, 4, 5, 10, 20, 50, 100, 500};

    int r_pos = std::rand() % delays.size();
    return delays[r_pos];
}

void CreateRandomRU_RUConnections() //Should be okay
{
    for (int i = 0; i < RU_NUMBER; ++i) {
        std::shared_ptr<NODE> ru = RUContainer[i];
        int rate = CreateRandomRate();
        int delay = CreateRandomDelay();
        
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
        int rate = CreateRandomRate();
        int delay = CreateRandomDelay();
        
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
                int rate = CreateRandomRate();
                int delay = CreateRandomDelay();

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
                int rate = CreateRandomRate();
                int delay = CreateRandomDelay();

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

        std::shared_ptr<LINK<NODE>> l = std::make_shared<LINK<NODE>>(i, 99999999, 0, endpoint, cu);

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
}

void CreateSingleFirstPath() {
    std::shared_ptr<PATH<NODE,LINK<NODE>>> p = std::make_shared<PATH<NODE,LINK<NODE>>>();
}

// void CreateSingleFirstPathRecursive(std::shared_ptr<PATH<NODE,LINK<NODE>>> p, int currentLevel) { // For basic testing. Forward only

//     int levelTotalNodes = 0;

//     switch (currentLevel) {
//         case 0: //RU
//             levelTotalNodes = RU_NUMBER;
//             nodes = RUContainer;
//             break;
//         case 1: //DU
//             levelTotalNodes = DU_NUMBER;
//             nodes = DUContainer;
//             break;
//         case 2: //CU
//             levelTotalNodes = CU_NUMBER;
//             connections = ENDPOINT_CU_List;
//             break;
//         case 3: //ENDPOINT
//             p->setComplete();
//             return;
//         default:
//             std::cout << "Something wrong with single path recursive";
//             return;    
//     }


//     for (int i = 0; i < levelTotalNodes; ++i) {
//         for (int j = 0; j < )
//     }
// }