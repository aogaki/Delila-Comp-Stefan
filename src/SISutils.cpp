#include "../include/SISutils.hpp"



SISutils::SISutils(){}
SISutils::~SISutils(){}


void SISutils::utilsSISinit(void)
{

    uint32_t foundDev = 0;

    this->err = FindAll_SIS3150USB_Devices(&this->myDev, &foundDev, 1);
    if(this->err != 0){
        std::cout<<"Error find dev code: "<<this->err<<std::endl;
    }

    std::cout<<"Found "<<foundDev<<" devices."<<std::endl;


    this->err = Sis3150usb_OpenDriver_And_Download_FX2_Setup((PCHAR)this->myDev.cDName, &this->myDev);
    if(this->err != 0){
        std::cout<<"Error open driver code: "<<this->err<<std::endl;
    }

}

void SISutils::utilsSISend(void)
{

    this->err = Sis3150usb_CloseDriver(this->myDev.hDev);
    if(this->err != 0){
        std::cout<<"Error close driver code: "<<this->err<<std::endl;
    }

}

void SISutils::utilsSISread(uint32_t busAddr, uint16_t *dataRead)
{

    ULONG data_r;

    this->err = sis3150Usb_Vme_Single_Read(this->myDev.hDev, busAddr, this->addrMod, 2, &data_r);
    if(this->err != 0){
        std::cout<<"Error single read code: "<<this->err<<std::endl;
    }

    *dataRead = (uint16_t)data_r;

}

void SISutils::utilsSISwrite(uint32_t busAddr, int data)
{

    ULONG data_w = data;

    this->err = sis3150Usb_Vme_Single_Write(this->myDev.hDev, busAddr, this->addrMod, this->dataW, data_w);
    if(this->err != 0){
        std::cout<<"Error single write code: "<<this->err<<std::endl;
    }

}

void SISutils::utilsSISbltRead(uint32_t busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf)
{

    ULONG req_data = sizeBytes;
    ULONG rec_data = 0;

    std::cout<<"Before FIFO read!"<<std::endl;

    //this->err = vme_A32BLT32FIFO_read(this->myDev.hDev, busAddr, dataBuff, req_data, &rec_data);
    this->err = sis3150Usb_Vme_Dma_Read(this->myDev.hDev, busAddr, this->addrMod, this->dataW, 1, dataBuff, req_data, &rec_data);
    if(this->err != 0){
        std::cout<<"Error dma read code: "<<this->err<<std::endl;
    }

    std::cout<<"Read data in bytes: "<<rec_data<<" from mod "<<busAddr<<std::endl;

    //rec_data = 40000;

    for(int i =0; i<rec_data; i++){
        
        //dataBuff[i] = 0b00000100000000000000000000000001;
        
        if((dataBuff[i]>>30) == 1){
                if((dataBuff[i]>>24) != 64){

                    std::cout<<"Event header invalid!"<<std::endl;
                    //std::cout<<std::endl<<"Invalid header and bits starting at i: "<<i<<" ";
/*                     if(((i > 2000) && (i<3000)) || ((i>20000) && (i<21000)))
                        std::cout<<"!!!!Header invalid at i: "<<i<<" with value "<<std::bitset<32>(dataBuff[i])<<std::endl;
 */
                }else{

                    std::cout<<"header bits: "<<std::bitset<32>(dataBuff[i])<<std::endl;
/*                     if(((i > 2000) && (i<3000)) || ((i>20000) && (i<21000)))
                        std::cout<<"Header valid at i: "<<i<<" with value "<<std::bitset<32>(dataBuff[i])<<std::endl; */

                }
        }else if((dataBuff[i]>>30) == 0){

            if((dataBuff[i]>>22) == 16){

                std::cout<<"data bits: "<<std::bitset<32>(dataBuff[i])<<", value: "<<(dataBuff[i] & 0x0000FFFF)<<std::endl;
/*                 if(((i > 2000) && (i<3000)) || ((i>20000) && (i<21000)))
                        std::cout<<"Data valid at i: "<<i<<" with value "<<std::bitset<32>(dataBuff[i])<<std::endl; */

            }else if(dataBuff[i] != 0){

                std::cout<<"Data invalid bits: "<<std::bitset<32>(dataBuff[i])<<std::endl;
                //std::cout<<i<<" ";
/*                 if(((i > 2000) && (i<3000)) || ((i>20000) && (i<21000)))
                        std::cout<<"!!!!Data invalid at i: "<<i<<" with value "<<std::bitset<32>(dataBuff[i])<<std::endl; */

            }

        }else{

            std::cout<<"eoe bits: "<<std::bitset<32>(dataBuff[i])<<std::endl<<std::endl;

        }

    }


    *dataTransf = rec_data;
}

void SISutils::setAddrModSIS(int newaddrmod)
{

    //I'm still not sure what each address modifier means, but I found this value in one of their examples
    // and it seems to work. If you find out feel free to change it.
    switch(newaddrmod){
        case 0:
            this->addrMod = 0x9;
            break;
        case 1:
            this->addrMod = 0x9;
            break;
        default:
            this->addrMod = 0x9;
    }

}

void SISutils::setDataWSIS(int newdataw)
{

    switch(newdataw){
        case 0:
            this->dataW = 2;
            break;
        case 1:
            this->dataW = 4;
            break;
        default:
            this->dataW = 2;
    }

}

void SISutils::utilsSISirqWait(uint32_t lineMask, uint32_t nrSec)
{

    ULONG irq_mask = 0;
    bool irq_stat = false;


    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> stop_time;

    start_time = std::chrono::system_clock::now(); 

    while(irq_stat == false){

        this->err = sis3150Usb_Register_Single_Read(this->myDev.hDev, 0x12, &irq_mask);
        if(this->err != 0){
            std::cout<<"Error register single read code: "<<this->err<<std::endl;
        }


        if(irq_mask != 0){
            irq_stat = true;
            std::cout<<"Irq mask is "<<std::bitset<32>(irq_mask)<<std::endl;
        }

        stop_time = std::chrono::system_clock::now();

        if(std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time).count() > (nrSec)){
            std::cout<<"Timeout after "<<nrSec<<" miliseconds."<<std::endl;
            break;
        }


    }

}


void utilsSISread_cont(uint32_t busAddr, uint16_t *dataRead)
{
    calledInFctSIS->utilsSISread(busAddr, dataRead);
}

void utilsSISwrite_cont(uint32_t busAddr, int data)
{
    calledInFctSIS->utilsSISwrite(busAddr, data);
}


void utilsSISbltRead_cont(uint32_t  busAddr, int sizeBytes, uint32_t *dataBuff, int *dataTransf)
{
    calledInFctSIS->utilsSISbltRead(busAddr, sizeBytes, dataBuff, dataTransf);
}


void utilsSISirqWait_cont(uint32_t lineMask, uint32_t nrSec)
{
    calledInFctSIS->utilsSISirqWait(lineMask, nrSec);
}


void setAddrModSIS_cont(int newaddrmod)
{
    calledInFctSIS->setAddrModSIS(newaddrmod);
}

void setDataWSIS_cont(int newdataw)
{
    calledInFctSIS->setDataWSIS(newdataw);
}
