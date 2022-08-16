#include "../include/VMEDevice.hpp"
#include "../include/VMEController.hpp"
#include "../include/TreeData.h"


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>




//g++ -c -Wall -fPIC -I../include dev_MADC32.cpp -ldl
//g++ -shared -o dev_MADC32.so dev_MADC32.o /home/gant/DELILA-main/Components/src/VMEController.o /home/gant/DELILA-main/Components/src/VMEDevice.o -ldl



class MADC32 : public VMEDevice
{
    public:
    MADC32(){};
    ~MADC32(){};


    int modId;
    uint32_t addr_offset;


    
    int mod_nr;
    int irq_l;
    int v_th[33];
    int irq_data_thr;
    int max_data_transf;
    int ext_ts;
    int res_opt;
    int in_range;
    int hold_d0;
    int hold_d1;
    int hold_w0;
    int hold_w1;


    //stores the total number of events
    uint64_t evNumber;


    








    void read_cfg();
    std::unique_ptr<VMEController> mod_configure(std::unique_ptr<VMEController> my_contr, uint32_t addr_offset, int modId);
    std::unique_ptr<VMEController> mod_start(std::unique_ptr<VMEController> my_contr);
    std::unique_ptr<VMEController> mod_stop(std::unique_ptr<VMEController> my_contr);
    std::unique_ptr<VMEController> mod_run(std::unique_ptr<VMEController> my_contr, std::shared_ptr<std::vector<TreeData>> t_data, int *fNEvents);
    int mod_checkifreader();

};



void MADC32::read_cfg()
{

    char *addr_str = (char*)malloc(20*sizeof(char));
        sprintf(addr_str, "%08X", addr_offset);
        char *file_loc = (char*)malloc(100*sizeof(char));


        memset(file_loc, '\0', sizeof(file_loc));
        strcat(file_loc, "/home/gant/DELILA-main/Components/CAENVX2718cont/conf_MADC32_0x");
        strcat(file_loc, addr_str);
        strcat(file_loc, ".conf");

        printf("Stringul e %s\n", file_loc);

        FILE *cFile;
        cFile = fopen(file_loc, "r");

        free(addr_str);
        free(file_loc);

        if(cFile == NULL){
            printf("Error opening MADC32 config\n");
            return;
        }

        char name[128];
        char val[128];
        char *stop;

        while(fscanf(cFile, "%127[^=]=%127[^\n]%*c", name, val) == 2){
            for(int i = 0; i<32; i++){
                char *v_th_str = (char*)malloc(100*sizeof(char));
                char *i_str = (char*)malloc(100*sizeof(char));

                sprintf(i_str, "%d", i);

                memset(v_th_str, '\0', sizeof(v_th_str));
                strcat(v_th_str, "v_th");
                strcat(v_th_str, i_str);

                if(strcmp(name, v_th_str) == 0){
                    v_th[i] = strtol(val, &stop, 10);
                }
                    


                free(i_str);
                free(v_th_str);
            }
            if(strcmp(name, "mod_nr") == 0)
                mod_nr = strtol(val, &stop, 10);
            else if(strcmp(name, "irq_l") == 0)
                irq_l = strtol(val, &stop, 10); 
            else if(strcmp(name, "irq_data_thr") == 0)
                irq_data_thr = strtol(val, &stop, 10);
            else if(strcmp(name, "max_data_transf") == 0)
                max_data_transf = strtol(val, &stop, 10);
            else if(strcmp(name, "ext_ts") == 0)
                ext_ts = strtol(val, &stop, 10);
            else if(strcmp(name, "res_opt") == 0)
                res_opt = strtol(val, &stop, 10);
            else if(strcmp(name, "in_range") == 0)
                in_range = strtol(val, &stop, 10);
            else if(strcmp(name, "hold_d0") == 0)
                hold_d0 = strtol(val, &stop, 10);
            else if(strcmp(name, "hold_d1") == 0)
                hold_d1 = strtol(val, &stop, 10); 
            else if(strcmp(name, "hold_w0") == 0)
                hold_w0 = strtol(val, &stop, 10); 
            else if(strcmp(name, "hold_w1") == 0)
                hold_w1 = strtol(val, &stop, 10);    
        }

}


std::unique_ptr<VMEController> MADC32::mod_configure(std::unique_ptr<VMEController> my_contr, uint32_t addr_offset, int modId)
{
    this->addr_offset = addr_offset;
    this->modId = modId;

    read_cfg();

    //set address modifier
    my_contr->utilsVMEsetAddrMod(0);
    
    //set data width
    my_contr->utilsVMEsetDataW(0);



    //stop data transfer
    my_contr->utilsVMEwrite(0x603A + addr_offset, 0);

    //init FIFO
    my_contr->utilsVMEwrite(0x603C + addr_offset, 1);

    //set multi event mode 3
    my_contr->utilsVMEwrite(0x6036 + addr_offset, 3);

    //clear BERR
    my_contr->utilsVMEwrite(0x6034 + addr_offset, 1);

    //set irq level
    my_contr->utilsVMEwrite(0x6010 + addr_offset, irq_l);

    //set irq vector
    my_contr->utilsVMEwrite(0x6012 + addr_offset, 0);

    //set resolution option
    my_contr->utilsVMEwrite(0x6042 + addr_offset, res_opt);
        
    //set input range
    my_contr->utilsVMEwrite(0x6060 + addr_offset, in_range);



    //gate generator
    //hold delay 0
    my_contr->utilsVMEwrite(0x6050 + addr_offset, hold_d0);

    //hold delay 1
    my_contr->utilsVMEwrite(0x6052 + addr_offset, hold_d1);

    //hold width 0
    my_contr->utilsVMEwrite(0x6054 + addr_offset, hold_w0);

    //hold width 1
    my_contr->utilsVMEwrite(0x6056 + addr_offset, hold_w1);







    //set voltage threshold for all 32 channels
    for(int i = 0; i<32; i++){

        printf("vth de %d e %d\n",i, v_th[i]);

        my_contr->utilsVMEwrite(addr_offset + 0x4000 + 2*i, v_th[i]);

    }

    //set irq data transf
    my_contr->utilsVMEwrite(0x6018 + addr_offset, irq_data_thr);

    //set max data transf
    my_contr->utilsVMEwrite(0x601A + addr_offset, max_data_transf);



    //if extended time stamp is on
    if(ext_ts){
        //enable extended time stamp mode
        my_contr->utilsVMEwrite(0x6038 + addr_offset, 3);
    }else{
        //disable extended ts
        my_contr->utilsVMEwrite(0x6038 + addr_offset, 0);
    }



    //set event number to 0
    evNumber = 0;


    printf("Configure for mod %d end\n", modId);
    fflush(stdout);




    return std::move(my_contr);

}





std::unique_ptr<VMEController> MADC32::mod_start(std::unique_ptr<VMEController> my_contr)
{

    printf("Start for mod %d begin\n", this->modId);
    fflush(stdout);

    //set address modifier
    my_contr->utilsVMEsetAddrMod(0);
    //set data width
    my_contr->utilsVMEsetDataW(0);

    //start data transfer
    my_contr->utilsVMEwrite(0x603A + this->addr_offset, 1);


    //reset counter for ext ts
    if(ext_ts){
        my_contr->utilsVMEwrite(this->addr_offset + 0x6090, 1);
    }

    //start test
    //(*ptr_write)(0x6070 + addr_offset, 0b111);



    printf("Start for mod %d end\n", this->modId);
    fflush(stdout);


    return std::move(my_contr);

}






std::unique_ptr<VMEController> MADC32::mod_stop(std::unique_ptr<VMEController> my_contr)
{

    printf("Stop for mod %d begin\n", this->modId);
    fflush(stdout);



    //set address modifier
    my_contr->utilsVMEsetAddrMod(0);
    //set data width
    my_contr->utilsVMEsetDataW(0);

    //stop data transfer
    my_contr->utilsVMEwrite(0x603A + this->addr_offset, 0);



    //stop test
    //(*ptr_write)(0x6070 + addr_offset, 0);


    printf("Stop for mod %d end\n", this->modId);
    fflush(stdout);




    return std::move(my_contr);

}


std::unique_ptr<VMEController> MADC32::mod_run(std::unique_ptr<VMEController> my_contr, std::shared_ptr<std::vector<TreeData>> t_data, int *fNEvents)
{

    //set nr of events to 0
    (*fNEvents) = 0;

    if(my_contr->utilsVMEirqCheck(this->irq_l) == 1){

        //allocate memory for data
        uint32_t *dataBuff = (uint32_t*)malloc(10000*sizeof(uint32_t));


        //amount of data transfered
        int buffSize = -1;

        //set address modifier for blt read
        my_contr->utilsVMEsetAddrMod(1);
        //set data width
        my_contr->utilsVMEsetDataW(1);


        my_contr->utilsVMEbltRead(this->addr_offset, 10000, dataBuff, &buffSize);

        std::cout<<"Buffsize is "<<buffSize<<std::endl;


        //set set data width and am for single write
        my_contr->utilsVMEsetAddrMod(0);
        //set data width
        my_contr->utilsVMEsetDataW(0);


        //reset BERR
        my_contr->utilsVMEwrite(addr_offset + 0x6034, 1);
    


        if(ext_ts == 0){

            for(int i = 0; i<buffSize; i++){

                    //used for testing
                    //######
                    //char *binary = toBinary((dataBuff[i]), 32);
                    //printf("The binary representation of %u is %s\n", (dataBuff[i]), binary);
                    //######


                if((dataBuff[i]>>30) == 1){

                    if((dataBuff[i]>>24) != 64){

                        printf("Event header invalid\n");
                            
                    }

                }else if((dataBuff[i]>>30) == 0){

                    if((dataBuff[i]>>22) == 16){

                        TreeData loc_data;

                        loc_data.Mod = mod_nr;
                        loc_data.Ch = ((dataBuff[i]>>16)&0b0000000000011111);
                        loc_data.TimeStamp = evNumber;
                        loc_data.FineTS = 0;

                        if(((dataBuff[i]>>14) & 0x1) == 1){
                            loc_data.ChargeLong = 0xFFFF;
                        }else{
                            loc_data.ChargeLong = (uint16_t)(dataBuff[i] & 0x00003FFF);
                        }

                        loc_data.ChargeShort = 0xFFFF;
                        loc_data.RecordLength = 1;
                        loc_data.Extras = 0xFFFF0032;


                            


                        t_data->push_back(loc_data);

                        (*fNEvents)++;

                    }else if(dataBuff[i] != 0){

                        printf("Data event invalid\n");
                            

                    }


                }else if((dataBuff[i]>>30) == 3){
                    
                    evNumber++;

                }



                    



                   
                
            }
        }else if(ext_ts == 1){


            //low bits of extended time stamp
            uint16_t ext_ts_lb = 0;

            //high bits of extended time stamp
            uint64_t ext_ts_hb = 0;

            //tells if time stamp is valid
            bool ts_valid = false;

            //nr of events in header
            int ev_in_h = 0;


            for(int i = 0; i<buffSize; i++){

                    //used for testing
                    //######
                    /* if(dataBuff[i] != 0){
                        char *binary = toBinary((dataBuff[i]), 32);
                        printf("The binary representation of %u is %s\n", (dataBuff[i]), binary);
                        fflush(stdout);
                    } */
                    
                    //######


                if((dataBuff[i]>>30) == 1){

                    ev_in_h = 0;

                    ts_valid = false;

                    ext_ts_lb = 0;

                    ext_ts_hb = 0;

                    if((dataBuff[i]>>24) != 64){
                        printf("Event header invalid\n");
                    }

                }else if((dataBuff[i]>>30) == 0){

                    if((dataBuff[i]>>22) == 16){


                        TreeData loc_data;

                        loc_data.Mod = mod_nr;
                        loc_data.Ch = ((dataBuff[i]>>16)&0b0000000000011111);


                        //nonsense value that gets changed
                        loc_data.TimeStamp = 0xFFFFFFFFFFFFFFFF;



                        loc_data.FineTS = 0;

                        if(((dataBuff[i]>>14) & 0x1) == 1){
                            loc_data.ChargeLong = 0xFFFF;
                        }else{
                            loc_data.ChargeLong = (uint16_t)(dataBuff[i] & 0x00003FFF);
                        }

                        loc_data.ChargeShort = 0xFFFF;
                        loc_data.RecordLength = 1;
                        loc_data.Extras = 0xFFFF0032;


                            


                        t_data->push_back(loc_data);

                        (*fNEvents)++;

                        ev_in_h++;

                    }else if((dataBuff[i]>>16) == 1152){

                        ext_ts_lb = (dataBuff[i] & 0x0000FFFF);
                        ts_valid = true;

                    }else if(dataBuff[i] != 0){

                        printf("Data event invalid\n");
                           

                    }

                }else if((dataBuff[i]>>30) == 3){

                    //first 2 bits are always 11 for EOE mark; we only use 30 for the time stamp
                    ext_ts_hb = (dataBuff[i] && 0x3FFFFFFF);

                    //checks if the 16 low bits of extended time stamp were present
                    if(ts_valid){

                        for(int iter_eoe = 0; iter_eoe<ev_in_h; iter_eoe++){

                            t_data->at((*fNEvents) - (ev_in_h - iter_eoe)).TimeStamp = (ext_ts_hb<<16) + ext_ts_lb;

                        }

                    }else{

                        printf("\nTime stamp invalid!!!\n");

                    }
                        


                }


            }
        }




        free(dataBuff);






    }






    return std::move(my_contr);

}








//checks if the device outputs data
//0 for no and 1 for yes
int MADC32::mod_checkifreader()
{
    return 1;
}





extern "C"
{


    std::unique_ptr<VMEDevice> MakeDevObj()
    {
        return std::unique_ptr<VMEDevice>(new MADC32());
    }



}
