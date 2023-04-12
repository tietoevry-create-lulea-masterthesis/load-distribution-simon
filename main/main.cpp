#include <random>
#include <string>
#include <InfluxDBFactory.h>
#include "constants.h"
#include "components.h"
#include "sim.h"
#include <unistd.h>
#incldue <vector>

using namespace std;

RU sim_RUs[RU_NUM];
list<UE> sim_UEs;
list<UE> RU_conn[RU_NUM]; // Array of lists, one list for each RU that keeps track of all UEs connected to it


///Containers
//Nodes
std::vector<std::shared_ptr<RU>> RUContainer;
std::vector<std::shared_ptr<DU>> DUContainer;
std::vector<std::shared_ptr<CU>> CUContainer;

std::shared_ptr<ENDPOINT> endpoint = std::make_shared<ENDPOINT>(); //Create Endpoint

//Edges
std::vector<std::shared_ptr<LINK_ENDPOINT_CU>> ENDPOINT_CU_List;
std::vector<std::shared_ptr<LINK_CU_DU>> CU_DU_List;
std::vector<std::shared_ptr<LINK_DU_DU>> DU_DU_List;
std::vector<std::shared_ptr<LINK_DU_RU>> DU_RU_List;
std::vector<std::shared_ptr<LINK_RU_RU>> RU_RU_List;


//const float max_coord = 5000; // Determines the maximum x and y coordinate of the simulation map

//unsigned int seed = 42;

srand(34);

bool GetRandomBool()
{
    return rand() & 1;
}

template<typename T>
bool AdjacentExistsUp(std::vector<T> a, int i)
{
    return a[i+1] != null;
}

template<typename T>
bool AdjacentExistsDown(std::vector<T> a, int i)
{
    return a[i-1] != null;
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

void CreateRandomRU_RUConnections()
{
    for (int i = 0; i < RU_NUMBER; ++i) {
        std::shared_ptr<RU> ru = RUContainer[i];
        int rate = CreateRandomRate();
        int delay = CreateRandomDelay();
        
        if (AdjacentExistsUp(RUContainer, i)) {
            if (GetRandomBool()) {
                std::shared_ptr<RU> up = RUContainer[i+1];
                std::shared_ptr<LINK_RU_RU> l = std::make_shared<LINK_RU_RU>(i, rate, delay, up, ru);

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
        std::shared_ptr<DU> du = DUContainer[i];
        int rate = CreateRandomRate();
        int delay = CreateRandomDelay();
        
        if (AdjacentExistsUp(DUContainer, i)) {
            if (GetRandomBool()) {
                std::shared_ptr<DU> up = DUContainer[i+1];
                std::shared_ptr<LINK_DU_DU> l = std::make_shared<LINK_DU_DU>(i, rate, delay, up, du);

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
                std::shared_ptr<RU> ru = RUContainer[i];
                std::shared_ptr<DU> du = DUContainer[j];
                int rate = CreateRandomRate();
                int delay = CreateRandomDelay();

                std::shared_ptr<LINK_DU_RU> l = std::make_shared<LINK_DU_RU>(i, rate, delay, du, ru);

                DU_RU_List.push_back(l);
                du->add_down(l);
                ru->add_up(l);
            }
        }
    }
}

void CreateRandomCU_DUConnections()
{
    for (int i = 0; i < DU_NUMBER; ++i) {
        for (int j = 0; j < CU_NUMBER; ++j) {
            if (GetRandomBool()) {
                std::shared_ptr<DU> du = DUContainer[i];
                std::shared_ptr<CU> cu = CUContainer[j];
                int rate = CreateRandomRate();
                int delay = CreateRandomDelay();

                std::shared_ptr<LINK_CU_DU> l = std::make_shared<LINK_CU_DU>(i, rate, delay, cu, du);

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
        std::shared_ptr<CU> cu = CUContainer[i];

        std::shared_ptr<LINK_ENDPOINT_CU> l = std::make_shared<LINK_ENDPOINT_CU>(i, endpoint, cu);

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

extern int main(int argc, char **argv)
{

    // Place RUs
    // for (size_t y = 0; y < sqrt(RU_NUM); y++)
    // {
    //     for (size_t x = 0; x < sqrt(RU_NUM); x++)
    //     {
    //         // Forms an even grid of RUs in coordinate space
    //         sim_RUs[ru_i] = *new RU("RU_" + to_string(ru_i), new float[2]
    //         {
    //             // if coord space = 0-100 and RU_NUM = 100,
    //             // coords go from 5, 10, 15 ... 95, i.e. equal margins on all sides
    //             x * max_coord / sqrtf(RU_NUM) + max_coord / sqrtf(RU_NUM) / 2,
    //             y * max_coord / sqrtf(RU_NUM) + max_coord / sqrtf(RU_NUM) / 2
    //         },
    //         4, 4000000);

    //         ru_i++; // iterate ru_i for each RU created
    //     }
    // }

    // Spawn UEs
    // for (size_t i = 0; i < 100; i++)
    // {
    //     sim_UEs.push_back(*new UE("UE_" + to_string(i), new float[2]{fmodf(rand(), max_coord), fmodf(rand(), max_coord)}));
    // }

    // Debug RU placement
    /* for (auto &&ru : sim_RUs)
    {
        cout << "ru UID: " + ru.get_UID() + ", coords: " + to_string(ru.coords[0]) + "," + to_string(ru.coords[1]) << "\n";
    } */

    // Connect each UE to closest RU
    // for (auto &&ue : sim_UEs)
    // {
    //     string closest = find_closest_rus(&ue, 5); // very idiotic and O(n) time for each UE
    //     RU_conn[stoi(closest.substr(3))].push_back(ue);
    // }

    // Calculate resulting load for each RU
    // for (size_t i = 0; i < RU_NUM; i++)
    // {
    //     sim_RUs[i].set_alloc_PRB(calc_alloc_PRB(i));
    // }
    
    

    /* cout << "Connections to RU_52: \n";
    for (auto &&i : RU_conn[52])
    {
        const std::map<std::string, float> dmap = i.get_dist_map();
        cout << i.get_UID() << ", entries: " << dmap.size() << "\n";
        for (auto &&val : dmap)
        {
            cout << val.first << ", dist: " << val.second << "\n";
        }
    } */
    

    // hand over via bool checks, to see if errors happen
    /* if (!handover("UE_95", 0, 8)) {
        cout << "ERROR while handing over\n";
    } */

    // pthread_t sim_thread; // create the threrhede at some point ig
    // pthread_create(&sim_thread, NULL, &sim_loop, NULL);

    // Connects to database and inserts points for each RU and UE
    //auto influxdb = influxdb::InfluxDBFactory::Get("http://root:rootboot@localhost:8086?db=RIC-Test");
    
    /* influxdb->write(influxdb::Point{"sim_RU"}
    .addTag("uid", sim_RUs[52].get_UID())
    .addField("connections", (int) RU_conn[52].size())
    );
    influxdb->write(influxdb::Point{"sim_UE"}
    .addTag("uid", sim_UEs.front().get_UID())
    .addField("closest RUs", (int) sim_UEs.front().get_dist_map().size())
    ); */

    // u most choose
    //sim_loop(nullptr);    // enter loop forever, or
    sleep(999);             // go 2 sleep forever (16 minutes)
    
    return 0;
}