// -*- C++ -*-
/*!
 * @file
 * @brief
 * @date
 * @author
 *
 */

//cat /tmp/daqmw/log.CAENVX2718contComp

#include "CAENVX2718cont.h"

using DAQMW::FatalType::DATAPATH_DISCONNECTED;
using DAQMW::FatalType::OUTPORT_ERROR;
using DAQMW::FatalType::USER_DEFINED_ERROR1;

// Module specification
// Change following items to suit your component's spec.
static const char* caenvx2718cont_spec[] =
{
    "implementation_id", "CAENVX2718cont",
    "type_name",         "CAENVX2718cont",
    "description",       "CAENVX2718cont component",
    "version",           "1.0",
    "vendor",            "Kazuo Nakayoshi, KEK",
    "category",          "example",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
};

CAENVX2718cont::CAENVX2718cont(RTC::Manager* manager)
    : DAQMW::DaqComponentBase(manager),
      m_OutPort("caenvx2718cont_out", m_out_data),
      m_recv_byte_size(0),
      m_out_status(BUF_SUCCESS),

      m_debug(false),

      vmeBoard(0),
      evNumber(0)

{
    // Registration: InPort/OutPort/Service

    // Set OutPort buffers
    registerOutPort("caenvx2718cont_out", m_OutPort);

    init_command_port();
    init_state_table();
    set_comp_name("CAENVX2718CONT");
}

CAENVX2718cont::~CAENVX2718cont()
{
}

RTC::ReturnCode_t CAENVX2718cont::onInitialize()
{
    if (m_debug) {
        std::cerr << "CAENVX2718cont::onInitialize()" << std::endl;
    }

    return RTC::RTC_OK;
}

RTC::ReturnCode_t CAENVX2718cont::onExecute(RTC::UniqueId ec_id)
{
    daq_do();

    return RTC::RTC_OK;
}

int CAENVX2718cont::daq_dummy()
{
    return 0;
}

int CAENVX2718cont::daq_configure()
{
    std::cerr << "*** CAENVX2718cont::configure" << std::endl;

    nrMods = 0;

    ::NVList* paramList;
    paramList = m_daq_service0.getCompParams();
    parse_params(paramList);


    //init board
    vmeBoard = new VMEutils();
    calledInFct = vmeBoard;
    vmeBoard->utilsVMEinit();

    //store dlerror() value
    char *error_s;


    
    for(int i = 0; i<nrMods; i+=2){//increment by 2 because of the problem mentioned in the parse_params() function
        
        modHandle = nullptr;
        ptr_mod_configure = nullptr;

        //connect to the shared objects
        modHandle = dlopen(modName_v[i/2].c_str(), RTLD_LOCAL | RTLD_LAZY);
        
        error_s = dlerror();
        if(error_s != NULL)
            std::cout<<"Dlerror dlopen config code: "<<dlerror()<<std::endl;

        
        //save the handles
        handleSave_v.push_back((uint64_t*)modHandle);

        
        //create pointers to the functions
        *(void**)(&ptr_mod_configure) = dlsym(modHandle, "mod_configure");

        ptr_mod_configure_v.push_back(ptr_mod_configure);

        error_s = dlerror();
        if(error_s != NULL)
            std::cout<<"Dlerror dlsym config code: "<<error_s<<std::endl;




        *(void**)(&ptr_mod_start) = dlsym(modHandle, "mod_start");

        error_s = dlerror();
        if(error_s != NULL)
            std::cout<<"Dlerror dlsym start code: "<<error_s<<std::endl;

        ptr_mod_start_v.push_back(ptr_mod_start);




        *(void**)(&ptr_mod_stop) = dlsym(modHandle, "mod_stop");

        error_s = dlerror();
        if(error_s != NULL)
            std::cout<<"Dlerror dlsym config code: "<<error_s<<std::endl;
        
        ptr_mod_stop_v.push_back(ptr_mod_stop);





        *(void**)(&ptr_mod_run) = dlsym(modHandle, "mod_run");

        error_s = dlerror();
        if(error_s != NULL)
            std::cout<<"Dlerror dlsys run code: "<<dlerror()<<std::endl;

        ptr_mod_run_v.push_back(ptr_mod_run);



        *(void**)(&ptr_mod_checkifreader) = dlsym(modHandle, "mod_checkifreader");
        error_s = dlerror();
        if(error_s != NULL)
            std::cout<<"Dlerror dlsys cir code: "<<dlerror()<<std::endl;

        ptr_mod_checkifreader_v.push_back(ptr_mod_checkifreader);





        //call the configure function
        (*ptr_mod_configure_v[i/2])(ptr_utilsVMEwrite, ptr_setAddrMod, ptr_setDataW, modAddr_v[i/2], (i/2));
            
        

    }

    

    
    


    return 0;
}

int CAENVX2718cont::parse_params(::NVList* list)
{
    std::cerr << "param list length:" << (*list).length() << std::endl;

    bool nameExists;
    bool addrExists;

    std::string currMod;


    int len = (*list).length();
    for (int i = 0; i < len; i+=2) {
        std::string sname  = (std::string)(*list)[i].value;
        std::string svalue = (std::string)(*list)[i+1].value;

        std::cerr << "sname: " << sname << "  ";
        std::cerr << "value: " << svalue << std::endl;

/* 
        //check params for modules and their addresses
        if(sname == "V812"){

            modName_v.push_back("/home/gant/DELILA-main/Components/CAENVX2718cont/mod_V812.so");
            modAddr_v.push_back(stoi(svalue, nullptr, 16));

            nrMods +=2;//DO NOT CHANGE!!!!!!!
        }else if(sname == "MTDC32"){

            modName_v.push_back("/home/gant/DELILA-main/Components/CAENVX2718cont/mod_MTDC32.so");
            modAddr_v.push_back(stoi(svalue, nullptr, 16));

            nrMods +=2;//DO NOT CHANGE!!!!!!

        }

 */

        //initially we set the values to false
        if(i % 4 == 0){

            nameExists = false;
            addrExists = false;

        }

        //name and address must be "modNameX" and "modAddrX" where X is a number from 0 to the number of modules
        //here we set the value of X we check for
        currMod = std::to_string(i/4);    


        //check params for modules and their addresses
        if(sname == ("modName" + currMod)){

            modName_v.push_back(svalue);

            //we found the name so we set nameExists to true
            nameExists = true;

        }else if(sname == ("modAddr" + currMod)){

            modAddr_v.push_back(stoi(svalue, nullptr, 16));

            //we found the address so we set addrExists to true
            addrExists = true;

        }


        //if both the name and address exist the module is valid
        //if not it is not counted
        if(i % 4 != 0){

            if((nameExists == false) && (addrExists == true)){

                modAddr_v.pop_back();

            }else if((nameExists == true) && (addrExists == false)){

                modName_v.pop_back();

            }else if((nameExists == true) && (addrExists == true)){

                nrMods+=2;//DO NOT CHANGE!!!!!!

            //For some reason dlsym doesn't recognise the function symbols if nrMods is an odd number.
            //I have no idea why.
            //It's working right now so don't change it unless you have figured it out.
            //If it stops working then RIP.


            }

        }

    }

    return 0;
}

int CAENVX2718cont::daq_unconfigure()
{
    std::cerr << "*** CAENVX2718cont::unconfigure" << std::endl;


    //end connection to controller
    vmeBoard->utilsVMEend();


    //store dlerror() value
    char *error_s;

    for(int i = 0; i<nrMods; i+=2){
        modHandle = handleSave_v[i/2];

        dlclose(modHandle);

        error_s = dlerror();
        if(m_debug && (error_s != NULL))
            std::cout<<"Dlerror dlclose config code: "<<error_s<<std::endl;

    }


    //delete class
    if(vmeBoard){
        delete vmeBoard;
        vmeBoard = 0;
        calledInFct = 0;
    }


    //clear vectors
    //I have no idea when variables declared in the component class go out of scope in daq-middleware
    //so i use swap() with an empty vector to make sure the memory is freed after every unconfig and there is no
    //memory leak
    modName_v.clear();
    std::vector<std::string>().swap(modName_v);

    modAddr_v.clear();
    std::vector<int>().swap(modAddr_v);

    handleSave_v.clear();
    std::vector<uint64_t*>().swap(handleSave_v);

    ptr_mod_run_v.clear();
    std::vector<void(*)(void(*)(uint32_t, int, uint32_t*, int*), void(*)(uint32_t, int), void(*)(int), void(*)(int),
                         void(*)(uint32_t, uint32_t), uint32_t, unsigned char*,
                         unsigned char*, uint64_t*, double*, uint16_t*, uint16_t*, uint32_t*, uint32_t*, int*, int)>().swap(ptr_mod_run_v);

    ptr_mod_checkifreader_v.clear();
    std::vector<int(*)()>().swap(ptr_mod_checkifreader_v);

    ptr_mod_stop_v.clear();
    std::vector<void(*)(void(*)(uint32_t, int), void(*)(int), void(*)(int), uint32_t, int)>().swap(ptr_mod_stop_v);

    ptr_mod_start_v.clear();
    std::vector<void(*)(void(*)(uint32_t, int), void(*)(int), void(*)(int), uint32_t, int)>().swap(ptr_mod_start_v);

    ptr_mod_configure_v.clear();
    std::vector<void(*)(void(*)(uint32_t, int), void(*)(int), void(*)(int), uint32_t, int)>().swap(ptr_mod_configure_v);
        

    //reset number of modules
    nrMods = 0;

    

    return 0;
}

int CAENVX2718cont::daq_start()
{
    std::cerr << "*** CAENVX2718cont::start" << std::endl;

    m_out_status = BUF_SUCCESS;

    fDataContainer = TDataContainer(200000000);

    fStartTime = std::chrono::system_clock::now();

    
    
  
    //use the start function
    for(int i = 0; i<nrMods; i+=2){
 
        modHandle = handleSave_v[i/2];



        (*ptr_mod_start_v[i/2])(ptr_utilsVMEwrite, ptr_setAddrMod, ptr_setDataW, modAddr_v[i/2], (i/2));
        

    }



    return 0;
}

int CAENVX2718cont::daq_stop()
{
    std::cerr << "*** CAENVX2718cont::stop" << std::endl;

    auto stopTime = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                      stopTime - fStartTime)
                      .count();
    auto dataSize = get_total_byte_size();
    auto dataRate = 1000. * dataSize / duration;

    if(m_debug)
        std::cout << dataRate << " B/s" << std::endl;


    //call stop function
    
    for(int i = 0; i<nrMods; i+=2){
      
        modHandle = handleSave_v[i/2];


        (*ptr_mod_stop_v[i/2])(ptr_utilsVMEwrite, ptr_setAddrMod, ptr_setDataW, modAddr_v[i/2], (i/2));

    }




    return 0;
}

int CAENVX2718cont::daq_pause()
{
    std::cerr << "*** CAENVX2718cont::pause" << std::endl;

    return 0;
}

int CAENVX2718cont::daq_resume()
{
    std::cerr << "*** CAENVX2718cont::resume" << std::endl;

    return 0;
}

int CAENVX2718cont::read_data_from_detectors()
{
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




    //run for each module connected to the CAEN controller
    for(int iter = 0; iter<nrMods; iter+=2){

        unsigned char *mod_Mod = (unsigned char*)malloc(sizeof(unsigned char)*50000);
        unsigned char *mod_Ch = (unsigned char*)malloc(sizeof(unsigned char)*50000);
        uint64_t *mod_TimeStamp = (uint64_t*)malloc(sizeof(uint64_t)*50000);
        double *mod_FineTS = (double*)malloc(sizeof(uint64_t)*50000);
        uint16_t *mod_ChargeLong = (uint16_t*)malloc(sizeof(uint16_t)*50000);
        uint16_t *mod_ChargeShort = (uint16_t*)malloc(sizeof(uint16_t)*50000);
        uint32_t *mod_Extras = (uint32_t*)malloc(sizeof(uint32_t)*50000);
        uint32_t *mod_RecordLength = (uint32_t*)malloc(sizeof(uint32_t)*50000);

 

        modHandle = handleSave_v[iter/2];




        //check if there is any data to read
        //some modules, like V812 don't send data
        if((*ptr_mod_checkifreader_v[iter/2])() == 1){


            //call the run function
            (*ptr_mod_run_v[iter/2])(ptr_utilsVMEbltRead, ptr_utilsVMEwrite, ptr_setAddrMod, ptr_setDataW, ptr_utilsVMEirqWait, modAddr_v[iter/2], 
                            mod_Mod, mod_Ch, mod_TimeStamp, mod_FineTS, mod_ChargeLong, mod_ChargeShort, mod_Extras, 
                            mod_RecordLength, &fNEvents, (iter/2));




            for (auto i = 0; i < fNEvents; i++) {
                

                data->Mod = mod_Mod[i];
                data->Ch = mod_Ch[i];
                data->FineTS = mod_FineTS[i];
                data->TimeStamp = mod_TimeStamp[i] + evNumber;
                data->ChargeLong = mod_ChargeLong[i];
                data->ChargeShort = mod_ChargeShort[i];
                data->Extras = mod_Extras[i];
                data->RecordLength = mod_RecordLength[i];


                if(m_debug)
                    std::cout<<"la i "<<i<<" avem ts "<<data->FineTS<<" si "<<data->TimeStamp<<std::endl;

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
        
                    for (auto iSample = 0; iSample < data->RecordLength; iSample++) {
          
                        data->Trace1[iSample] = 0;
                    }
                    memcpy(&hit[index], &(data->Trace1[0]), sizeTrace);
                    index += sizeTrace;
                    received_data_size += sizeTrace;
                }
 
                fDataContainer.AddData(hit);
            }

            evNumber += mod_TimeStamp[fNEvents - 1];

        }

        free(mod_Mod);
        free(mod_Ch);
        free(mod_TimeStamp);
        free(mod_FineTS);
        free(mod_ChargeLong);
        free(mod_ChargeShort);
        free(mod_Extras);
        free(mod_RecordLength);
        



    }

    if (m_debug) {
        std::cerr << received_data_size << std::endl;
  }

    return received_data_size;
}

int CAENVX2718cont::set_data()
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

int CAENVX2718cont::write_OutPort()
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

int CAENVX2718cont::daq_run()
{
  if (m_debug) {
    std::cerr << "*** CAENVX2718::run" << std::endl;
  }


  if (check_trans_lock()) {  // check if stop command has come
    set_trans_unlock();      // transit to CONFIGURED state
    return 0;
  }


  int sentDataSize = 0;

  if (m_out_status == BUF_SUCCESS) {  // previous OutPort.write() successfully done
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
    if (m_debug){
    std::cout << m_out_status << std::endl;
    }
    // } else if (sentDataSize > 0) {  // OutPort write successfully done
  } else {                              // OutPort write successfully done
    inc_sequence_num();                 // increase sequence num.
    inc_total_data_size(sentDataSize);  // increase total data byte size
  }



    return 0;
}




extern "C"
{
    void CAENVX2718contInit(RTC::Manager* manager)
    {
        RTC::Properties profile(caenvx2718cont_spec);
        manager->registerFactory(profile,
                    RTC::Create<CAENVX2718cont>,
                    RTC::Delete<CAENVX2718cont>);
    }
};
