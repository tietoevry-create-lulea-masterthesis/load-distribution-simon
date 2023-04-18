#include <random>
#include <string>
//#include <InfluxDBFactory.h>
//#include "constants.h"
//#include "components.h"
//#include "components.cpp"
#include "network.cpp"
#include "path.h"
//#include "sim.h"
#include <unistd.h>
#include <vector>
#include <iostream>


//const float max_coord = 5000; // Determines the maximum x and y coordinate of the simulation map

//unsigned int seed = 42;

extern int main(int argc, char **argv)
{

    srand(34);

    CreateNodes();

    CreateRandomConnections();

    TestPrint();

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