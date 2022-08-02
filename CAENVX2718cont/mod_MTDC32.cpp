#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


//g++ -c -Wall -Werror -fPIC mod_MTDC32.cpp
//g++ -shared -o mod_MTDC32.so mod_MTDC32.o


extern "C"
{

    int win_start[100];
    int b_width[100];
    int res_opt[100];
    int trig_source[100];
    int trig_opt[100];
    int irq_data_thr[100];
    int max_data_transf[100];
    int ttl_opt[100];//TTL is active for 1 and inactive for 0
    int mod_nr[100];
    int ext_ts[100];



    void read_cfg(uint32_t addr_offset, int modId)
    {
        char *addr_str = (char*)malloc(20*sizeof(char));
        sprintf(addr_str, "%08X", addr_offset);
        char *file_loc = (char*)malloc(100*sizeof(char));

        strcat(file_loc, "/home/gant/DELILA-main/Components/CAENVX2718cont/conf_MTDC32_0x");
        strcat(file_loc, addr_str);
        strcat(file_loc, ".conf");

        printf("Stringul e %s\n", file_loc);

        FILE *cFile;
        cFile = fopen(file_loc, "r");

        free(addr_str);
        free(file_loc);

        if(cFile == NULL){
            printf("Error opening MTDC32 config\n");
            return;
        }

        char name[128];
        char val[128];
        char *stop;

        while(fscanf(cFile, "%127[^=]=%127[^\n]%*c", name, val) == 2){
            if(strcmp(name, "win_start") == 0)
                win_start[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "b_width") == 0)
                b_width[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "res_opt") == 0)
                res_opt[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "trig_source") == 0)
                trig_source[modId] = strtol(val, &stop, 2);
            else if(strcmp(name, "trig_opt") == 0)
                trig_opt[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "irq_data_thr") == 0)
                irq_data_thr[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "max_data_transf") == 0)
                max_data_transf[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "ttl_opt") == 0)
                ttl_opt[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "mod_nr") == 0)
                mod_nr[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "ext_ts") == 0)
                ext_ts[modId] = strtol(val, &stop, 10);
        }
    //printf("ws = %d\nbw = %d\nro = %d\nts = %d\nto = %d\nidq = %d\nmdt = %d\nto = %d\nmodnr = %d\nextts = %d\n",
             //win_start[modId], b_width[modId], res_opt[modId], trig_source[modId], trig_opt[modId],
             // irq_data_thr[modId], max_data_transf[modId], ttl_opt[modId], mod_nr[modId], ext_ts[modId]);
        
    }

    void mod_configure(void (*ptr_write)(uint32_t, int), void (*ptr_setAM)(int), void (*ptr_setDW)(int),
                         uint32_t addr_offset, int modId)
    {

        //read config file
        read_cfg(addr_offset, modId);

        //set address modifier
        (*ptr_setAM)(0);
        //set data width
        (*ptr_setDW)(0);
 
        //stop data transfer
        (*ptr_write)(0x603A + addr_offset, 0);

        //init FIFO
        (*ptr_write)(0x603C + addr_offset, 1);

        //set multi event mode 3
        (*ptr_write)(0x6036 + addr_offset, 3);

        //clear BERR
        (*ptr_write)(0x6034 + addr_offset, 1);

        //set irq level 1
        (*ptr_write)(0x6010 + addr_offset, 1);

        //set irq vector
        (*ptr_write)(0x6012 + addr_offset, 0);

        //set trig ecl
        (*ptr_write)(0x6068 + addr_offset, 1);

        //set win start
        (*ptr_write)(0x6050 + addr_offset, win_start[modId]);

        //set bank width
        (*ptr_write)(0x6054 + addr_offset, b_width[modId]);

        //set resolution option
        (*ptr_write)(0x6042 + addr_offset, res_opt[modId]);


        //set trig source
        (*ptr_write)(0x6058 + addr_offset, trig_source[modId]);

        //set irq data transf
        (*ptr_write)(0x6018 + addr_offset, irq_data_thr[modId]);

        //set max data transf
        (*ptr_write)(0x601A + addr_offset, max_data_transf[modId]);


        //run if ttl
        if(ttl_opt){

            //TTL bank th
            (*ptr_write)(0x6078 + addr_offset, 255);

            //TTL pos sig edge
            (*ptr_write)(0x6060 + addr_offset, 3);

        }

        //if extended time stamp is on
        if(ext_ts){
            //enable extended time stamp mode
            (*ptr_write)(0x6038 + addr_offset, 3);
        }



    }

    void mod_start(void (*ptr_write)(uint32_t, int), void (*ptr_setAM)(int), void (*ptr_setDW)(int),
                     uint32_t addr_offset, int modId)
    {

        //set address modifier
        (*ptr_setAM)(0);
        //set data width
        (*ptr_setDW)(0);

        //start data transfer
        (*ptr_write)(0x603A + addr_offset, 1);


        //reset counter
        (*ptr_write)(addr_offset + 0x6090, 1);

    }

    void mod_stop(void (*ptr_write)(uint32_t, int), void (*ptr_setAM)(int), void (*ptr_setDW)(int),
                     uint32_t addr_offset, int modId)
    {

        //set address modifier
        (*ptr_setAM)(0);
        //set data width
        (*ptr_setDW)(0);

        //stop data transfer
        (*ptr_write)(0x603A + addr_offset, 0);
    }    



    //for testing
    char* toBinary(int n, int len)
    {
        char* binary = (char*)malloc(sizeof(char) * len);
        int k = 0;
        for (unsigned i = (1 << (len - 1)); i > 0; i = i / 2) {
            binary[k++] = (n & i) ? '1' : '0';
        }
        binary[k] = '\0';
        return binary;
    }









    void mod_run(void (*ptr_blt_read)(uint32_t, int, uint32_t*, int*), void (*ptr_write)(uint32_t, int),
                 void (*ptr_setAM)(int), void (*ptr_setDW)(int), void (*ptr_irqWait)(uint32_t, uint32_t), 
                 uint32_t addr_offset,
                 unsigned char *mod_Mod,
                 unsigned char *mod_Ch,
                 uint64_t *mod_TimeStamp,
                 double *mod_FineTS,
                 uint16_t *mod_ChargeLong,
                 uint16_t *mod_ChargeShort,
                 uint32_t *mod_Extras,
                 uint32_t *mod_RecordLength,
                 int *fNEvents,
                 int modId)
    {

        //normall sets address modifiern; it Enables IRQ lines for CAENComm
        (*ptr_setAM)(1);
        //set data width
        (*ptr_setDW)(1);  

        //allocate memory for data
        uint32_t *dataBuff = (uint32_t*)malloc(50000*sizeof(uint32_t));



        //amount of data transfered
        int buffSize = -1;

        //irq wait
        (*ptr_irqWait)(1, 100);

        //blt read from FIFO
        (*ptr_blt_read)(addr_offset + 0x0000,  50000/* *sizeof(uint32_t) */, dataBuff, &buffSize);

        printf("buffsize de %d\n", buffSize);

        //reset BERR
        (*ptr_write)(addr_offset + 0x6034, 1);

        //set nr of events to 0
        (*fNEvents) = 0;


        if(ext_ts == 0){
            //Event number for this sequence
            uint64_t evNumberSq = 0;

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
                        mod_Mod[*fNEvents] = mod_nr[modId];
                        mod_Ch[*fNEvents] = ((dataBuff[i]>>16)&0b0000000000011111);
                        mod_TimeStamp[*fNEvents] = evNumberSq;
                        mod_FineTS[*fNEvents] = (double)(dataBuff[i] & 0x0000FFFF);
                        mod_ChargeLong[*fNEvents] = 0xFFFF;
                        mod_ChargeShort[*fNEvents] = 0xFFFF;
                        mod_RecordLength[*fNEvents] = 1;
                        mod_Extras[*fNEvents] = 0xFFFF0032;

                        (*fNEvents)++;

                    }else if(dataBuff[i] != 0){

                        printf("Data event invalid\n");

                    }


                }else if((dataBuff[i]>>30) == 3){
                
                    evNumberSq++;

                }



                



                //free(binary);
            
            }
        }else{
            //low bits of extended time stamp
            uint16_t ext_ts_lb = 0;

            //high bits of extended time stamp
            uint64_t ext_ts_hb = 0;

            //tells if time stamp is valid
            bool ts_valid = false;

            //nr of events in header
            int ev_in_h = 0;


            for(int i = 0; i<buffSize; i++){
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

                        mod_Mod[*fNEvents] = mod_nr[modId];
                        mod_Ch[*fNEvents] = ((dataBuff[i]>>16)&0b0000000000011111);

                        //nonsense value that is changed if the time stamp is valid
                        mod_TimeStamp[*fNEvents] = 0xFFFFFFFFFFFFFFFF;

                        mod_FineTS[*fNEvents] = (double)(dataBuff[i] & 0x0000FFFF);
                        mod_ChargeLong[*fNEvents] = 0xFFFF;
                        mod_ChargeShort[*fNEvents] = 0xFFFF;
                        mod_RecordLength[*fNEvents] = 1;
                        mod_Extras[*fNEvents] = 0xFFFF0032;

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

                            mod_TimeStamp[*fNEvents - (ev_in_h - iter_eoe)] = (ext_ts_hb<<16) + ext_ts_lb;

                        }

                    }
                    


                }


            }
        }



        free(dataBuff);

    }


    //checks if the device outputs data
    //0 for no and 1 for yes
    int mod_checkifreader(void)
    {
        return 1;
    }



}