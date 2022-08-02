#ifndef VMEutils_hpp
#define VMEutils_hpp 1


#include <dlfcn.h>
#include <string>
#include <iostream>
#include <bitset>
#include "CAENVMElib.h"
#include "CAENComm.h"


class VMEutils
{
    public:
    VMEutils();
    ~VMEutils();

    //Used with CAENVMElib, no longer useful with CAENComm
    //###########
    CVErrorCodes err;
    CVBoardTypes bdType = cvV2718;
    int32_t bdHandl;
    CVAddressModifier addrMod;
    CVDataWidth dataW;
    void *dataPtr; 
    //###########

    short bdLink = 0;
    short bdNum = 1;
    int bdHandlComm;
    int buffSize;
    int byteCount;


    void utilsVMEinit(void);
    void utilsVMEend(void);

    void utilsVMEread(uint32_t busAddr, uint16_t *dataRead);
    void utilsVMEwrite(uint32_t busAddr, int data);

    void utilsVMEbltRead(uint32_t busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf);

    void utilsVMEirqWait(uint32_t lineMask, uint32_t nrSec);

    void setAddrMod(int newaddrmod);
    void setDataW(int newdataw);
    
};

//object to be called in container functions
inline VMEutils *calledInFct;


//container functions
void utilsVMEread_cont(uint32_t busAddr, uint16_t *dataRead);
void utilsVMEwrite_cont(uint32_t busAddr, int data);

void utilsVMEbltRead_cont(uint32_t  busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf);

void utilsVMEirqWait_cont(uint32_t lineMask, uint32_t nrSec);

void setAddrMod_cont(int newaddrmod);
void setDataW_cont(int newdataw);



//pointers to functions declaration
inline void (*ptr_utilsVMEread)(uint32_t, uint16_t*) = &utilsVMEread_cont;
inline void (*ptr_utilsVMEwrite)(uint32_t, int) = &utilsVMEwrite_cont;

inline void (*ptr_utilsVMEbltRead)(uint32_t, int, uint32_t*, int*) = &utilsVMEbltRead_cont;

inline void (*ptr_utilsVMEirqWait)(uint32_t, uint32_t) = &utilsVMEirqWait_cont;

inline void (*ptr_setAddrMod)(int) = &setAddrMod_cont;
inline void (*ptr_setDataW)(int) = &setDataW_cont;


#endif