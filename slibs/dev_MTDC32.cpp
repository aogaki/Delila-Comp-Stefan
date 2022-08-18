#include "../include/VMEDevice.hpp"
#include "../include/VMEController.hpp"
#include "../include/TreeData.h"


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>




//g++ -c -Wall -fPIC -I../include dev_MTDC32.cpp -ldl
//g++ -shared -o dev_MTDC32.so dev_MTDC32.o /home/gant/DELILA-main/Components/src/VMEController.o /home/gant/DELILA-main/Components/src/VMEDevice.o -ldl



class MTDC32 : public VMEDevice
{
    public:
    MTDC32(){};
    ~MTDC32(){};


    int modId;
    uint32_t addr_offset;


    
    int win_start;
    int b_width;
    int res_opt;
    int trig_source;
    int trig_opt;
    int irq_data_thr;
    int max_data_transf;
    int ttl_opt;//TTL is active for 1 and inactive for 0
    int mod_nr;
    int ext_ts;
    int irq_l;


    //stores the total number of events
    uint64_t evNumber;


    








    void read_cfg();
    std::unique_ptr<VMEController> mod_configure(std::unique_ptr<VMEController> my_contr, uint32_t addr_offset, int modId);
    std::unique_ptr<VMEController> mod_start(std::unique_ptr<VMEController> my_contr);
    std::unique_ptr<VMEController> mod_stop(std::unique_ptr<VMEController> my_contr);
    std::unique_ptr<VMEController> mod_run(std::unique_ptr<VMEController> my_contr, std::shared_ptr<std::vector<TreeData>> t_data, int *fNEvents);
    int mod_checkifreader();

};



void MTDC32::read_cfg()
{

    std::string disk_loc_begin = "/home/gant/DELILA-main/Components/slibs/conf_MADC32_0x";

    std::stringstream disk_loc_mid;
    disk_loc_mid << std::hex << this->addr_offset;

    std::string disk_loc_end = ".json";

    std::string disk_loc = disk_loc_begin + disk_loc_mid.str() + disk_loc_end;




    std::ifstream conf_file(disk_loc.c_str());
    if(!conf_file.is_open()){
        std::cerr<<"Failed to open config file "<<disk_loc<<std::endl;
    }else{
        std::cout<<"File opened successfully "<<disk_loc<<std::endl;
    }



    nlohmann::json conf_data;
    bool has_exception = false;

    try
    {
        conf_data = nlohmann::json::parse(conf_file);
    }
    catch(nlohmann::json::parse_error &ex)
    {
        has_exception = true;
        std::cerr<<"Parse error at byte "<<ex.byte<<std::endl;
    }

 
    if(has_exception == false){
        
        //std::cout<<stoi(conf_data["mod_nr"].get<std::string>());
        this->mod_nr = stoi(conf_data["mod_nr"].get<std::string>());
        this->irq_l = stoi(conf_data["irq_l"].get<std::string>());
        this->irq_data_thr = stoi(conf_data["irq_data_thr"].get<std::string>());
        this->max_data_transf = stoi(conf_data["max_data_transf"].get<std::string>());
        this->ext_ts = stoi(conf_data["ext_ts"].get<std::string>());
        this->res_opt = stoi(conf_data["res_opt"].get<std::string>());
        this->win_start = stoi(conf_data["win_start"].get<std::string>());
        this->b_width = stoi(conf_data["b_width"].get<std::string>());
        this->trig_opt = stoi(conf_data["trig_opt"].get<std::string>());
        this->ttl_opt = stoi(conf_data["ttl_opt"].get<std::string>());
        this->trig_source = stoi(conf_data["trig_source"].get<std::string>(), 0, 2);











        std::cout<<"mod_nr="<<this->mod_nr<<" irql="<<this->irq_l<<" irqdt="<<this->irq_data_thr
        <<" mdt="<<this->max_data_transf<<" ets="<<this->ext_ts<<" ro="<<this->res_opt
        <<" ws="<<this->win_start<<" bw="<<this->b_width<<" to="<<this->trig_opt
        <<" ttlo="<<this->ttl_opt<<" ts="<<this->trig_source<<std::endl;



    }else{
        std::cerr<<"Coud not set parameters due to exception"<<std::endl;
    }
     


}
































//checks if the device outputs data
//0 for no and 1 for yes
int MTDC32::mod_checkifreader()
{
    return 1;
}





extern "C"
{


    std::unique_ptr<VMEDevice> MakeDevObj()
    {
        return std::unique_ptr<VMEDevice>(new MTDC32());
    }



}