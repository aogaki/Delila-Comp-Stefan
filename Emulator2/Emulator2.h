// -*- C++ -*-
/*!
 * @file 
 * @brief
 * @date
 * @author
 *
 */

#ifndef EMULATOR2_H
#define EMULATOR2_H


#include <TF1.h>

#include <chrono>
#include <deque>
#include <memory>
#include <string>
#include <random>

#include "../include/TDataContainer.hpp"
#include "../include/RandomGenFromParams.hpp"

#include "DaqComponentBase.h"

using namespace RTC;

class Emulator2
    : public DAQMW::DaqComponentBase
{
public:
    Emulator2(RTC::Manager* manager);
    ~Emulator2();

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

    static const int SEND_BUFFER_SIZE = 0;
    unsigned char m_data[SEND_BUFFER_SIZE];
    unsigned int m_recv_byte_size;

    BufferStatus m_out_status;
    bool m_debug;

    unsigned int fCounter = 0;

    TDataContainer fDataContainer;

    std::chrono::system_clock::time_point fStartTime;

   
    int fNEvents;

    RandomGenFromParams *data_setter;
    TRandom3 *rand_gen;


};


extern "C"
{
    void Emulator2Init(RTC::Manager* manager);
};

#endif // EMULATOR2_H
