// -*- C++ -*-
/*!
 * @file 
 * @brief
 * @date
 * @author
 *
 */

#ifndef CAENVX2718CONT_H
#define CAENVX2718CONT_H

#include <chrono>
#include <deque>
#include <memory>
#include <string>
#include <vector>

#include "DaqComponentBase.h"
#include "CAENVMElib.h"
#include "../include/VMEutils.hpp"
#include "../include/TDataContainer.hpp"
#include "../include/TreeData.h"

#include "CAENComm.h"

using namespace RTC;

class CAENVX2718cont
    : public DAQMW::DaqComponentBase
{
public:
    CAENVX2718cont(RTC::Manager* manager);
    ~CAENVX2718cont();

    // The initialize action (on CREATED->ALIVE transition)
    // former rtc_init_entry()
    virtual RTC::ReturnCode_t onInitialize();

    // The execution action that is invoked periodically
    // former rtc_active_do()
    virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

private:
    TimedOctetSeq          m_out_data;
    OutPort<TimedOctetSeq> m_OutPort;

private:
    int daq_dummy();
    int daq_configure();
    int daq_unconfigure();
    int daq_start();
    int daq_run();
    int daq_stop();
    int daq_pause();
    int daq_resume();

    int parse_params(::NVList* list);
    int read_data_from_detectors();
    int set_data();
    int write_OutPort();

    static const int SEND_BUFFER_SIZE = 4096;
    unsigned char m_data[SEND_BUFFER_SIZE];
    unsigned int m_recv_byte_size;

    BufferStatus m_out_status;
    bool m_debug;

    //created in configure, destoryed in unconfigure
    VMEutils *vmeBoard;

    //number of modules
    int nrMods = 0;

    //used to get the handle from dlopen
    void *modHandle;
 
    //stores the module names
    std::vector<std::string>modName_v;
    //stores the module addresses
    std::vector<int>modAddr_v;
    //stores the handles returned by dlopen
    std::vector<uint64_t*>handleSave_v;


    unsigned int fCounter = 0;
    TDataContainer fDataContainer;
    std::chrono::system_clock::time_point fStartTime;
    int fNEvents = 0;

    //global event number
    uint64_t evNumber = 0;




    //create pointers to functions and store them in vectors
    void (*ptr_mod_run)(void(*)(uint32_t, int, uint32_t*, int*), void(*)(uint32_t, int), void(*)(int), void(*)(int),
                         void(*)(uint32_t, uint32_t), uint32_t, unsigned char*,
                         unsigned char*, uint64_t*, double*, uint16_t*, uint16_t*, uint32_t*, uint32_t*, int*, int);
    std::vector<void(*)(void(*)(uint32_t, int, uint32_t*, int*), void(*)(uint32_t, int), void(*)(int), void(*)(int),
                         void(*)(uint32_t, uint32_t), uint32_t, unsigned char*,
                         unsigned char*, uint64_t*, double*, uint16_t*, uint16_t*, uint32_t*, uint32_t*, int*, int)>ptr_mod_run_v;

    int (*ptr_mod_checkifreader)();
    std::vector<int(*)()>ptr_mod_checkifreader_v;
    
    void (*ptr_mod_stop)(void(*)(uint32_t, int), void(*)(int), void(*)(int), uint32_t, int);
    std::vector<void(*)(void(*)(uint32_t, int), void(*)(int), void(*)(int), uint32_t, int)>ptr_mod_stop_v;
   
    void (*ptr_mod_start)(void(*)(uint32_t, int), void(*)(int), void(*)(int), uint32_t, int);
    std::vector<void(*)(void(*)(uint32_t, int), void(*)(int), void(*)(int), uint32_t, int)>ptr_mod_start_v;

    void (*ptr_mod_configure)(void(*)(uint32_t, int), void(*)(int), void(*)(int), uint32_t, int);
    std::vector<void(*)(void(*)(uint32_t, int), void(*)(int), void(*)(int), uint32_t, int)>ptr_mod_configure_v;
};




extern "C"
{
    void CAENVX2718contInit(RTC::Manager* manager);
};

#endif // CAENVX2718CONT_H
