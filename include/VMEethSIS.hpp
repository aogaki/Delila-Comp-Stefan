#ifndef VMEethSIS_hpp
#define VMEethSIS_hpp 1

#include<iostream>
#include<chrono>
#include<bitset>

#include "../include/VMEbase.hpp"

#include "../include/includesiseth/project_system_define.h"
#include "../include/includesiseth/project_interface_define.h"
#include "../include/includesiseth/sis3153usb.h"
#include "../include/includesiseth/vme_interface_class.h"
#include "../include/includesiseth/sis3153ETH_vme_class.h"

class VMEethSIS : public VMEbase
{
    public:

    VMEethSIS();

    ~VMEethSIS();

    sis3153eth *sis_crate;
    int addr_mod_opt;
    int data_w_opt;



    void utilsVMEinit(void);
    void utilsVMEend(void);

    void utilsVMEread(uint32_t busAddr, uint16_t *dataRead);
    void utilsVMEwrite(uint32_t busAddr, int data);

    void utilsVMEbltRead(uint32_t busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf);

    int utilsVMEirqCheck(uint32_t lineNr);

    void utilsVMEsetAddrMod(int newaddrmod);
    void utilsVMEsetDataW(int newdataw);

};




#endif