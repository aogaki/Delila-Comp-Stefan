#include "../include/VMEbase.hpp"


VMEbase::VMEbase(){};
VMEbase::~VMEbase(){};


void VMEbase::utilsVMEinit(void)
{
    
    std::cout<<"Called base init!"<<std::endl;

}

void VMEbase::utilsVMEend(void)
{

    std::cout<<"Called base end!"<<std::endl;

}

void VMEbase::utilsVMEread(uint32_t busAddr, uint16_t *dataRead)
{

    std::cout<<"Called base read!"<<std::endl;

}

void VMEbase::utilsVMEwrite(uint32_t busAddr, int data)
{

    std::cout<<"Called base write!"<<std::endl;
    
}

void VMEbase::utilsVMEbltRead(uint32_t busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf)
{

    std::cout<<"Called base blt read!"<<std::endl;

}

int VMEbase::utilsVMEirqCheck(uint32_t lineNr)
{

    std::cout<<"Called base irq wait!"<<std::endl;

    return 0;

}

void VMEbase::utilsVMEsetAddrMod(int newaddrmod)
{

    std::cout<<"Called base addr mod!"<<std::endl;

}

void VMEbase::utilsVMEsetDataW(int newdataw)
{

    std::cout<<"Called base data w!"<<std::endl;

}


void utilsVMEread_cont(uint32_t busAddr, uint16_t *dataRead)
{
    calledInFct->utilsVMEread(busAddr, dataRead);
}

void utilsVMEwrite_cont(uint32_t busAddr, int data)
{
    calledInFct->utilsVMEwrite(busAddr, data);
}

void utilsVMEbltRead_cont(uint32_t  busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf)
{
    calledInFct->utilsVMEbltRead(busAddr, sizeBytes, dataBuff, dataTransf);
}

int utilsVMEirqCheck_cont(uint32_t lineNr)
{
    return calledInFct->utilsVMEirqCheck(lineNr);
}


void setAddrMod_cont(int newaddrmod)
{
    calledInFct->utilsVMEsetAddrMod(newaddrmod);
}

void setDataW_cont(int newdataw)
{
    calledInFct->utilsVMEsetDataW(newdataw);
}


