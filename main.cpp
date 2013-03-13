/*! 
 *  \file main.cpp
 *  \brief    The sc_main
 *  \details Start point of the simulation.
 *  \author    Antti Siirilä, 501449
 *  \version   1.0
 *  \date      28.1.2013
 */


#include "Simulation.hpp"



//!Defines the file name for the VCD output.
//#define VCD_FILE_NAME "anjosi_ex3_vcd"


using namespace std;
using namespace sc_core;
using namespace sc_dt;

#define SIMULATION_DURATION 200

/*!
 * \brief sc_main
 * \details Initiates the Simulation module, which builds up the Router modules and starts the simulation.
 */

const char* g_DebugID = "Level_debug:";
const char* g_ReportID = "Level_info:";
const char* g_SimulationVersion = "Test run";

int sc_main(int argc, char * argv [])
{
    /// Establish a socket connection with GUI

    ServerSocket SimulationServer ( 30000 ); 
    ServerSocket GUISocket; 
    cout << "Waiting the GUI to connect..." << endl;
    SimulationServer.accept ( GUISocket ); 
    string DataWord;
    bool setupLoop = true;
    cout << "Receiving from the GUI..." << endl;
    try
        {
            while(setupLoop)
                {
                    GUISocket >> DataWord;
                    
                    if(DataWord.compare("SETUP") == 0)
                        cout << "Set-up received" << endl;
                    else if(DataWord.compare("START") == 0)
                        {
                            cout << "Start received" << endl;
                            DataWord = "Simulation starts";
                            setupLoop = false;
                        }
                    else
                        cout << "Unknown GUI command" << endl;
                    GUISocket << DataWord;
                }
        }
    catch(SocketException& e)
        {
            std::cout << "got exeption " << e.description() << " in " << sc_get_curr_process_handle()->name() << "\n"; 
        }

    sc_report rp;
    sc_report_handler::set_log_file_name("test_simu.log");
    sc_report_handler::set_actions(g_ReportID, SC_INFO, SC_DISPLAY);
    sc_report_handler::set_actions(g_DebugID, SC_INFO, SC_DO_NOTHING);
    SC_REPORT_INFO(g_ReportID, g_SimulationVersion);

  ///initiate the simulation
    Simulation test("Test", GUISocket);

  SC_REPORT_INFO(g_ReportID, StringTools("Main").newReportString("Simulation starts"));


  ///run the simulation	
  sc_start(SIMULATION_DURATION, SC_SEC);

return 0;
}//end of main
