#ifndef VMEbase_hpp
#define VMEbase_hpp 1

#include <cstdint>
#include <iostream>

typedef void (*readFct)(uint32_t, uint16_t*);
typedef void (*writeFct)(uint32_t, int);

typedef void (*bltreadFct)(uint32_t, int, uint32_t*, int*);

typedef int (*irqchFct)(uint32_t);

typedef void (*setamFct)(int);
typedef void (*setdwFct)(int);


class VMEbase
{
    public:
    VMEbase();
    virtual ~VMEbase();



    virtual void utilsVMEinit(void);
    virtual void utilsVMEend(void);

    virtual void utilsVMEread(uint32_t busAddr, uint16_t *dataRead);
    virtual void utilsVMEwrite(uint32_t busAddr, int data);

    virtual void utilsVMEbltRead(uint32_t busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf);

    virtual int utilsVMEirqCheck(uint32_t lineNr);

    virtual void utilsVMEsetAddrMod(int newaddrmod);
    virtual void utilsVMEsetDataW(int newdataw);

};

//object to be called in container functions
inline VMEbase *calledInFct;


//container functions
void utilsVMEread_cont(uint32_t busAddr, uint16_t *dataRead);
void utilsVMEwrite_cont(uint32_t busAddr, int data);

void utilsVMEbltRead_cont(uint32_t  busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf);

int utilsVMEirqCheck_cont(uint32_t lineNr);

void setAddrMod_cont(int newaddrmod);
void setDataW_cont(int newdataw);


/* 
//pointers to functions declaration
inline void (*ptr_utilsVMEread)(uint32_t, uint16_t*) = &utilsVMEread_cont;
inline void (*ptr_utilsVMEwrite)(uint32_t, int) = &utilsVMEwrite_cont;

inline void (*ptr_utilsVMEbltRead)(uint32_t, int, uint32_t*, int*) = &utilsVMEbltRead_cont;

inline int (*ptr_utilsVMEirqCheck)(uint32_t) = &utilsVMEirqCheck_cont;

inline void (*ptr_setAddrMod)(int) = &setAddrMod_cont;
inline void (*ptr_setDataW)(int) = &setDataW_cont; */

inline readFct ptr_utilsVMEread = &utilsVMEread_cont;
inline writeFct ptr_utilsVMEwrite = &utilsVMEwrite_cont;

inline bltreadFct ptr_utilsVMEbltRead = &utilsVMEbltRead_cont;

inline irqchFct ptr_utilsVMEirqCheck = &utilsVMEirqCheck_cont;

inline setamFct ptr_setAddrMod = &setAddrMod_cont;
inline setdwFct ptr_setDataW = &setDataW_cont;



#endif