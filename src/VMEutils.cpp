#include "../include/VMEutils.hpp"
#include "CAENVMElib.h"
#include "CAENComm.h"

VMEutils::VMEutils(){}
VMEutils::~VMEutils(){}


//ititialises the CAEN VX2178 module, returns a handle
void VMEutils::utilsVMEinit(void)
{
    //this->err = CAENVME_Init(this->bdType, this->bdLink, this->bdNum, &this->bdHandl);
 
    CAENComm_ErrorCode err;

    err = CAENComm_OpenDevice(CAENComm_OpticalLink, 1, 0, 0, &this->bdHandlComm);
    if(err !=0)
        std::cout<<"eroare open cod "<<err<<std::endl;
 
}

//ends the connection to the module
void VMEutils::utilsVMEend(void)
{
    //this-> err = CAENVME_End(this->bdHandl);

    CAENComm_ErrorCode err;

    err = CAENComm_CloseDevice(this->bdHandlComm);
    if(err !=0)
        std::cout<<"eroare open cod "<<err<<std::endl;
}

//performs a read operation at busAddr
void VMEutils::utilsVMEread(uint32_t busAddr, uint16_t *dataRead)
{
/*      
    this->dataPtr = dataRead;
    this->err = CAENVME_ReadCycle(this->bdHandl, busAddr, this->dataPtr, this->addrMod, this->dataW);
*/

    CAENComm_ErrorCode err;

    err = CAENComm_Read16(this->bdHandlComm, busAddr, dataRead);
    if(err !=0)
        std::cout<<"eroare write cod "<<err<<std::endl;

}


//performs a write operation at busAddr
void VMEutils::utilsVMEwrite(uint32_t busAddr, int data)
{

/*     
    this->dataPtr = &data;
    this->err = CAENVME_WriteCycle(this->bdHandl, busAddr, this->dataPtr, this->addrMod, this->dataW);
  */
 
    uint16_t dataComm = data;
    CAENComm_ErrorCode err;

    err = CAENComm_Write16(this->bdHandlComm, busAddr, dataComm);
    if(err !=0)
        std::cout<<"eroare write cod "<<err<<std::endl;

     

}

//performs a blt read operation at busAddr
//sizeBytes instructs how many bytes to read
//data is stored at dataBuff
//*dataTransf stores how many 32 bit words were transfered
void VMEutils::utilsVMEbltRead(uint32_t busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf)
{
      
    //CAENComm_ErrorCode err;

    /* err =  */CAENComm_BLTRead(this->bdHandlComm, busAddr, dataBuff, sizeBytes, dataTransf);
    //if(err !=0)
        //std::cout<<"eroare blt read cod "<<err<<std::endl;


/* 
    this->dataPtr = &this->dataRead;
    this->err = CAENVME_ReadCycle(this->bdHandl, busAddr + 0x6030, this->dataPtr, cvA32_S_DATA, cvD16);
    std::cout<<"data in buffer "<<this->dataRead<<std::endl;

    this->dataPtr = dataBuff;
    this->err = CAENVME_BLTReadCycle(this->bdHandl, busAddr, this->dataPtr, sizeBytes, this->addrMod, this->dataW, dataTransf);
    if(this->err)
        std::cout<<"Eroare blt read "<<this->err<<std::endl;

 */


}

void VMEutils::setAddrMod(int newaddrmod)
{

    //Used to set AddressModifier with CAENVMElib
/*      
    switch(newaddrmod){
        case 0:
            this->addrMod = cvA32_S_DATA;
            break;
        case 1:
            this->addrMod = cvA32_S_BLT;
            break;
        case 2:
            this->addrMod = cvA24_S_DATA;
            break;
        case 3:
            this->addrMod = cvA24_S_BLT;
            break;
        default:
            this->addrMod = cvA32_S_DATA;
    }
 */

    //Currently enables IRQ lines
 
    CAENComm_ErrorCode err;

    err = CAENComm_IRQEnable(this->bdHandlComm);
    if(err !=0)
        std::cout<<"eroare irq enable cod "<<err<<std::endl;
 
}

void VMEutils::setDataW(int newdataw)
{

    //Used with CAENVMElib, currently useless
   /*  switch(newdataw){
        case 0:
            this->dataW = cvD16;
            break;
        case 1:
            this->dataW = cvD32;
            break;
        case 2:
            this->dataW = cvD16_swapped;
            break;
        case 3:
            this->dataW = cvD32_swapped;
            break;
        default:
            this->dataW = cvD16;
    } */
}

//performs am irq wait operation for nrSec miliseconds
void VMEutils::utilsVMEirqWait(uint32_t lineMask, uint32_t nrSec)
{
/* 
    this->err = CAENVME_IRQWait(this->bdHandl, lineMask, nrSec);
    if(this->err)
        std::cout<<"Eroare irq wait "<<this->err<<std::endl;
 */

    CAENComm_ErrorCode err;

    err = CAENComm_IRQWait(this->bdHandlComm, nrSec);
    if(err !=0)
        std::cout<<"eroare irq wait cod "<<err<<std::endl; 
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

void utilsVMEirqWait_cont(uint32_t lineMask, uint32_t nrSec)
{
    calledInFct->utilsVMEirqWait(lineMask, nrSec);
}


void setAddrMod_cont(int newaddrmod)
{
    calledInFct->setAddrMod(newaddrmod);
}

void setDataW_cont(int newdataw)
{
    calledInFct->setDataW(newdataw);
}






