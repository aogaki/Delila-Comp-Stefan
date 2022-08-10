#include "../include/VMEcaen.hpp"



VMEcaen::VMEcaen(){};
VMEcaen::~VMEcaen(){};


//ititialises the CAEN VX2178 module, returns a handle
void VMEcaen::utilsVMEinit(void)
{
 
    CAENComm_ErrorCode err;

    err = CAENComm_OpenDevice(CAENComm_OpticalLink, 1, 0, 0, &this->bdHandlComm);
    if(err !=0)
        std::cout<<"eroare open cod "<<err<<std::endl;
 
}

//ends the connection to the module
void VMEcaen::utilsVMEend(void)
{

    CAENComm_ErrorCode err;

    err = CAENComm_CloseDevice(this->bdHandlComm);
    if(err !=0)
        std::cout<<"eroare open cod "<<err<<std::endl;
}

//performs a read operation at busAddr
void VMEcaen::utilsVMEread(uint32_t busAddr, uint16_t *dataRead)
{

    CAENComm_ErrorCode err;

    if((this->addr_mod_opt == 0) && (this->data_w_opt == 0)){

        err = CAENComm_Read16(this->bdHandlComm, busAddr, dataRead);
        if(err !=0)
            std::cout<<"eroare write cod "<<err<<std::endl;

    }


}


//performs a write operation at busAddr
void VMEcaen::utilsVMEwrite(uint32_t busAddr, int data)
{
 
    uint16_t dataComm = data;
    CAENComm_ErrorCode err;

    if((this->addr_mod_opt == 0) && (this->data_w_opt == 0)){
        err = CAENComm_Write16(this->bdHandlComm, busAddr, dataComm);
        if(err !=0)
            std::cout<<"eroare write cod "<<err<<std::endl;
    }

     

}

//performs a blt read operation at busAddr
//sizeBytes instructs how many bytes to read
//data is stored at dataBuff
//*dataTransf stores how many 32 bit words were transfered
void VMEcaen::utilsVMEbltRead(uint32_t busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf)
{
      
    CAENComm_ErrorCode err;

    if((this->addr_mod_opt == 1) && (this->data_w_opt == 1)){
        err =  CAENComm_BLTRead(this->bdHandlComm, busAddr, dataBuff, sizeBytes, dataTransf);
        if(err !=0)
            std::cout<<"eroare blt read cod "<<err<<std::endl;
    }


}

void VMEcaen::utilsVMEsetAddrMod(int newaddrmod)
{

    this->addr_mod_opt = newaddrmod;

}

void VMEcaen::utilsVMEsetDataW(int newdataw)
{

    this->data_w_opt = newdataw;

}


int VMEcaen::utilsVMEirqCheck(uint32_t lineNr)
{

    /* int err = 0;
    uint32_t data_reg = 0;
    err = this->sis_crate->udp_sis3153_register_read(0x12, &data_reg);
        if(err != 0){
            std::cout<<"Error read reg code "<<err<<std::endl;
        }
    std::cout<<"irq status: "<<std::bitset<32>(data_reg)<<std::endl;
    
    if(((data_reg>>lineNr) & 1) == 1){
        return 1;
    } */

    CAENComm_ErrorCode err;

    err = CAENComm_IRQEnable(this->bdHandlComm);
    if(err !=0)
        std::cout<<"eroare irq enable cod "<<err<<std::endl;
 

    err = CAENComm_IRQWait(this->bdHandlComm, 100);
    if(err !=0)
        std::cout<<"eroare irq wait cod "<<err<<std::endl;

    return 1;

/*     uint8_t irq_mask;

    err = CAENComm_VMEIRQCheck(this->bdHandlComm, &irq_mask);
    if(err !=0)
        std::cout<<"eroare irq check cod "<<err<<std::endl;
    
    std::cout<<"irq status: "<<std::bitset<8>(irq_mask)<<" with irq line needed "<<lineNr<<std::endl;

    if((irq_mask & (1<<lineNr)) != 0){
        return 1;
    }



    return 0; */

}
