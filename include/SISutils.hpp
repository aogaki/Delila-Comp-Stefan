#ifndef SISutils_hpp
#define SISutils_hpp 1

//#include <dlfcn.h>
#include <string>
#include <iostream>
#include <bitset>
#include "sis3150usb_vme.h"
//#include "sis3150usb_vme_calls.h"
#include <chrono>
#include <iomanip>


class SISutils
{
    public:
    SISutils();
    ~SISutils();

    int err;
    struct SIS3150USB_Device_Struct myDev;
    uint32_t addrMod;
    uint32_t dataW;

    void utilsSISinit(void);
    void utilsSISend(void);

    void utilsSISread(uint32_t busAddr, uint16_t *dataRead);
    void utilsSISwrite(uint32_t busAddr, int data);

    void utilsSISbltRead(uint32_t busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf);

    void utilsSISirqWait(uint32_t lineMask, uint32_t nrSec);

    void setAddrModSIS(int newaddrmod);
    void setDataWSIS(int newdataw);

};

//object to be called in container functions
inline SISutils *calledInFctSIS;


//container functions
void utilsSISread_cont(uint32_t busAddr, uint16_t *dataRead);
void utilsSISwrite_cont(uint32_t busAddr, int data);

void utilsSISbltRead_cont(uint32_t  busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf);

void utilsSISirqWait_cont(uint32_t lineMask, uint32_t nrSec);

void setAddrModSIS_cont(int newaddrmod);
void setDataWSIS_cont(int newdataw);


//pointers to functions declaration
inline void (*ptr_utilsSISread)(uint32_t, uint16_t*) = &utilsSISread_cont;
inline void (*ptr_utilsSISwrite)(uint32_t, int) = &utilsSISwrite_cont;

inline void (*ptr_utilsSISbltRead)(uint32_t, int, uint32_t*, int*) = &utilsSISbltRead_cont;

inline void (*ptr_utilsSISirqWait)(uint32_t, uint32_t) = &utilsSISirqWait_cont;

inline void (*ptr_setAddrModSIS)(int) = &setAddrModSIS_cont;
inline void (*ptr_setDataWSIS)(int) = &setDataWSIS_cont;





#endif