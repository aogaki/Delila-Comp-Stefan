#ifndef VMEutils_hpp
#define VMEutils_hpp 1


#include <string>
#include <iostream>
#include <bitset>

#include "../include/VMEbase.hpp"
#include "CAENComm.h"



class VMEcaen : public VMEbase
{
    public:
    VMEcaen();
    ~VMEcaen();


    short bdLink = 0;
    short bdNum = 1;
    int bdHandlComm;
    int buffSize;
    int byteCount;
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