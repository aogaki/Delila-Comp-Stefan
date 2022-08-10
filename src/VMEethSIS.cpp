#include "../include/VMEethSIS.hpp"


VMEethSIS::VMEethSIS(){};

VMEethSIS::~VMEethSIS(){};


void VMEethSIS::utilsVMEinit(void)
{

    char ip_addr_str[32];
    strcpy(ip_addr_str, "192.168.0.198");
    sis3153eth(&this->sis_crate, ip_addr_str);
    
}

void VMEethSIS::utilsVMEend(void)
{

    this->sis_crate->vmeclose();
    delete(this->sis_crate);

}

void VMEethSIS::utilsVMEread(uint32_t busAddr, uint16_t *dataRead)
{

    int err;
    if((this->addr_mod_opt == 0) && (this->data_w_opt == 0)){
        
        err = this->sis_crate->vme_A32D16_read(busAddr, dataRead);
        if(err != 0){
            std::cout<<"Error write code: "<<err<<std::endl;
        }

    }


}

void VMEethSIS::utilsVMEwrite(uint32_t busAddr, int data)
{

    uint16_t data_loc = data;
    int err;
    if((this->addr_mod_opt == 0) && (this->data_w_opt == 0)){
        
        err = this->sis_crate->vme_A32D16_write(busAddr, data_loc);
        if(err != 0){
            std::cout<<"Error write code: "<<err<<std::endl;
        }

    }
    
}

void VMEethSIS::utilsVMEbltRead(uint32_t busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf)
{

    uint32_t gotWords;
    int err = 0;

    if((this->addr_mod_opt == 1) && (this->data_w_opt == 1)){
        
        err = this->sis_crate->vme_A32BLT32FIFO_read(busAddr, dataBuff, sizeBytes, &gotWords);
        if(err != 0){
            std::cout<<"Error write code: "<<err<<std::endl;
        }

    }


    (*dataTransf) = gotWords;




}

int VMEethSIS::utilsVMEirqCheck(uint32_t lineNr)
{

    int err = 0;
    uint32_t data_reg = 0;
    err = this->sis_crate->udp_sis3153_register_read(0x12, &data_reg);
        if(err != 0){
            std::cout<<"Error read reg code "<<err<<std::endl;
        }
    std::cout<<"irq status: "<<std::bitset<32>(data_reg)<<std::endl;
    
    if(((data_reg>>lineNr) & 1) == 1){
        return 1;
    }

    return 0;

}

/* void VMEethSIS::utilsVMEirqWait(uint32_t lineMask, uint32_t nrSec)
{

    int err = 0;
    bool irq_stat = false;
    uint32_t data_reg = 0;

    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> stop_time;

    start_time = std::chrono::system_clock::now();

    while(irq_stat == false){


        //std::cout<<"Before reg read"<<std::endl;
        err = this->sis_crate->udp_sis3153_register_read(0x12, &data_reg);
        if(err != 0){
            std::cout<<"Error read reg code "<<err<<std::endl;
        }
            

        if(data_reg != 0){
            irq_stat = true;
        }

        stop_time = std::chrono::system_clock::now();

        //std::cout<<"After reg read at "<<std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count()<<std::endl;

        if(std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count() > nrSec){
            std::cout<<"Timeout after 10000 miliseconds."<<std::endl;
            break;
        }
    }
    std::cout<<"irq status: "<<std::bitset<32>(data_reg)<<std::endl;

} */

void VMEethSIS::utilsVMEsetAddrMod(int newaddrmod)
{

    this->addr_mod_opt = newaddrmod;

}

void VMEethSIS::utilsVMEsetDataW(int newdataw)
{

    this->data_w_opt = newdataw;

}

