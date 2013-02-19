
/*! \file RoutingTable.cpp
 *  \brief     Implementation of RoutingTable.
 *  \details   
 *  \author    Antti Siirilä, 501449
 *  \version   1.0
 *  \date      Tue Feb 19 08:44:06 2013
 */


#include "RoutingTable.hpp"


RoutingTable::RoutingTable(sc_module_name p_ModName):sc_module(p_ModName)
{

  //make the inner bindings
    export_ToRoutingTable(m_ReceivingBuffer); //export the receiving
                                             //buffer's input
                                             //interface for the data plane

    
    SC_THREAD(routingTableMain);
    sensitive << port_Clk.pos();
}

RoutingTable::~RoutingTable()
{
}


void RoutingTable::routingTableMain(void)
{

    //debugging 
    cout << name() << " starting at time" << sc_time_stamp()  << endl;



  //The main thread of routing table module starts
    while(true)
    {
        wait();
    }
}

