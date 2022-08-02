// -*- C++ -*-
/*!
 * @file
 * @brief
 * @date
 * @author
 *
 */

#include "Emulator2.h"

using DAQMW::FatalType::DATAPATH_DISCONNECTED;
using DAQMW::FatalType::OUTPORT_ERROR;
using DAQMW::FatalType::USER_DEFINED_ERROR1;

// Module specification
// Change following items to suit your component's spec.
static const char* emulator2_spec[] =
{
    "implementation_id", "Emulator2",
    "type_name",         "Emulator2",
    "description",       "Emulator2 component",
    "version",           "1.0",
    "vendor",            "Kazuo Nakayoshi, KEK",
    "category",          "example",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
};



Emulator2::Emulator2(RTC::Manager* manager)
    : DAQMW::DaqComponentBase(manager),
      m_OutPort("emulator2_out", m_out_data),
      m_recv_byte_size(0),
      m_out_status(BUF_SUCCESS),




      rand_gen(0),
      data_setter(0),
      m_debug(false)
{
    // Registration: InPort/OutPort/Service

    // Set OutPort buffers
    registerOutPort("emulator2_out", m_OutPort);

    init_command_port();
    init_state_table();
    set_comp_name("EMULATOR2");

    fNEvents = 1000;

    

}

Emulator2::~Emulator2()
{
}

RTC::ReturnCode_t Emulator2::onInitialize()
{
    if (m_debug) {
        std::cerr << "Emulator2::onInitialize()" << std::endl;
    }

    return RTC::RTC_OK;
}

RTC::ReturnCode_t Emulator2::onExecute(RTC::UniqueId ec_id)
{
    daq_do();

    return RTC::RTC_OK;
}

int Emulator2::daq_dummy()
{
    return 0;
}

int Emulator2::daq_configure()
{
    std::cerr << "*** Emulator2::configure" << std::endl;

    std::random_device rd;
    rand_gen = new TRandom3(rd());
    data_setter = new RandomGenFromParams();

    ::NVList* paramList;
    paramList = m_daq_service0.getCompParams();
    parse_params(paramList);

    

    return 0;
}

int Emulator2::parse_params(::NVList* list)
{
    std::cerr << "param list length:" << (*list).length() << std::endl;

    int len = (*list).length();
    for (int i = 0; i < len; i+=2) {
        std::string sname  = (std::string)(*list)[i].value;
        std::string svalue = (std::string)(*list)[i+1].value;

        std::cerr << "sname: " << sname << "  ";
        std::cerr << "value: " << svalue << std::endl;


    if (sname == "NEvents") {
      fNEvents = std::stoi(svalue);
    } else if (sname == "NumMod"){
        data_setter->setMod(svalue);
    }else if (sname == "NumCh"){
        data_setter->setCh(svalue);
    }else if (sname == "FMean"){
        data_setter->setFMean(svalue);
    }else if (sname == "FSigma"){
        data_setter->setFSigma(svalue);
    }else if (sname == "CLMean"){
        data_setter->setCLMean(svalue);
    }else if (sname == "CLSigma"){
        data_setter->setCLSigma(svalue);
    }else if (sname == "CSMean"){
        data_setter->setCSMean(svalue);
    }else if (sname == "CSSigma"){
        data_setter->setCSSigma(svalue);
    }
  }

    return 0;
}

int Emulator2::daq_unconfigure()
{
    std::cerr << "*** Emulator2::unconfigure" << std::endl;

    if(rand_gen){
        delete rand_gen;
        rand_gen = 0;
    }
    
    if(data_setter){
        delete data_setter;
        data_setter = 0;
    }
    

    return 0;
}

int Emulator2::daq_start()
{
    std::cerr << "*** Emulator2::start" << std::endl;

    m_out_status = BUF_SUCCESS;

    fDataContainer = TDataContainer(200000000);

    fStartTime = std::chrono::system_clock::now();

    return 0;
}

int Emulator2::daq_stop()
{
    std::cerr << "*** Emulator2::stop" << std::endl;

    auto stopTime = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                      stopTime - fStartTime)
                      .count();
    auto dataSize = get_total_byte_size();
    auto dataRate = 1000. * dataSize / duration;

    //std::cout << dataRate << " B/s" << std::endl;

    return 0;
}

int Emulator2::daq_pause()
{
    std::cerr << "*** Emulator2::pause" << std::endl;

    return 0;
}

int Emulator2::daq_resume()
{
    std::cerr << "*** Emulator2::resume" << std::endl;

    return 0;
}

int Emulator2::read_data_from_detectors()
{
  if (m_debug) {
    std::cerr << "Generate data" << std::endl;
  }
  int received_data_size = 0;
  /// write your logic here

  constexpr auto sizeMod = sizeof(TreeData::Mod);
  constexpr auto sizeCh = sizeof(TreeData::Ch);
  constexpr auto sizeTS = sizeof(TreeData::TimeStamp);
  constexpr auto sizeFineTS = sizeof(TreeData::FineTS);
  constexpr auto sizeLong = sizeof(TreeData::ChargeLong);
  constexpr auto sizeShort = sizeof(TreeData::ChargeShort);
  constexpr auto sizeRL = sizeof(TreeData::RecordLength);

  TreeData *data = new TreeData();

 
  

  // if (doOrNot(fRandom) == 0) {
  if (true) {
    for (auto i = 0; i < fNEvents; i++) {

      data_setter->setTreeDataGaus(data, rand_gen);


      const auto oneHitSize = sizeMod + sizeCh + sizeTS + sizeFineTS +
                              sizeLong + sizeShort + sizeRL +
                              (sizeof(TreeData::Trace1[0]) * data->RecordLength);

      std::vector<char> hit;
      hit.resize(oneHitSize);
      auto index = 0;

      memcpy(&hit[index], &(data->Mod), sizeMod);
      index += sizeMod;
      received_data_size += sizeMod;

      memcpy(&hit[index], &(data->Ch), sizeCh);
      index += sizeCh;
      received_data_size += sizeCh;

      memcpy(&hit[index], &(data->TimeStamp), sizeTS);
      index += sizeTS;
      received_data_size += sizeTS;

      memcpy(&hit[index], &(data->FineTS), sizeFineTS);
      index += sizeFineTS;
      received_data_size += sizeFineTS;

      memcpy(&hit[index], &(data->ChargeLong), sizeLong);
      index += sizeLong;
      received_data_size += sizeLong;

      memcpy(&hit[index], &(data->ChargeShort), sizeShort);
      index += sizeShort;
      received_data_size += sizeShort;

      memcpy(&hit[index], &(data->RecordLength), sizeRL);
      index += sizeRL;
      received_data_size += sizeRL;
 
      if (data->RecordLength > 0) {
        const auto sizeTrace = sizeof(TreeData::Trace1[0]) * data->RecordLength;
        data->Trace1.resize(data->RecordLength);
        //fSignalGen->SetParameter(0, fAmplitudeGen(fRandom));
        for (auto iSample = 0; iSample < data->RecordLength; iSample++) {
          //constexpr auto deltaT = 2;
          data->Trace1[iSample] = 1;//fSignalGen->Eval(iSample * deltaT);
        }
        memcpy(&hit[index], &(data->Trace1[0]), sizeTrace);
        index += sizeTrace;
        received_data_size += sizeTrace;
      }
 
      fDataContainer.AddData(hit);
    }
  }

  if (m_debug) {
    std::cerr << received_data_size << std::endl;
  }

  return received_data_size;
}

int Emulator2::set_data()
{
    unsigned char header[8];
    unsigned char footer[8];

    auto packet = fDataContainer.GetPacket();

    set_header(&header[0], packet.size());
    set_footer(&footer[0]);

    ///set OutPort buffer length
    m_out_data.data.length(packet.size() + HEADER_BYTE_SIZE + FOOTER_BYTE_SIZE);
    memcpy(&(m_out_data.data[0]), &header[0], HEADER_BYTE_SIZE);
    memcpy(&(m_out_data.data[HEADER_BYTE_SIZE]), &packet[0], packet.size());
    memcpy(&(m_out_data.data[HEADER_BYTE_SIZE + packet.size()]), &footer[0],
           FOOTER_BYTE_SIZE);

    return packet.size();
}

int Emulator2::write_OutPort()
{
    ////////////////// send data from OutPort  //////////////////
    bool ret = m_OutPort.write();

    //////////////////// check write status /////////////////////
    if (ret == false) {  // TIMEOUT or FATAL
        m_out_status  = check_outPort_status(m_OutPort);
        if (m_out_status == BUF_FATAL) {   // Fatal error
            fatal_error_report(OUTPORT_ERROR);
        }
        if (m_out_status == BUF_TIMEOUT) { // Timeout
            return -1;
        }
    }
    else {
        m_out_status = BUF_SUCCESS; // successfully done
    }

    return 0;
}

int Emulator2::daq_run()
{
  if (m_debug) {
    std::cerr << "*** Emulator::run" << std::endl;
  }

  if (check_trans_lock()) {  // check if stop command has come
    set_trans_unlock();      // transit to CONFIGURED state
    return 0;
  }

  int sentDataSize = 0;
  
  if (m_out_status ==
      BUF_SUCCESS) {  // previous OutPort.write() successfully done
    if (fDataContainer.GetSize() == 0) {
      fCounter = 0;
      read_data_from_detectors();
    }
    sentDataSize = set_data();  // set data to OutPort Buffer
  }

  if (m_debug) {
    std::cout << "Size: " << sentDataSize << "\t"
              << "Sequence: " << get_sequence_num() << std::endl;
  }

  if (write_OutPort() < 0) {
    std::cout << m_out_status << std::endl;
    // } else if (sentDataSize > 0) {  // OutPort write successfully done
  } else {                              // OutPort write successfully done
    inc_sequence_num();                 // increase sequence num.
    inc_total_data_size(sentDataSize);  // increase total data byte size
  }



    return 0;
}

extern "C"
{
    void Emulator2Init(RTC::Manager* manager)
    {
        RTC::Properties profile(emulator2_spec);
        manager->registerFactory(profile,
                    RTC::Create<Emulator2>,
                    RTC::Delete<Emulator2>);
    }
};
