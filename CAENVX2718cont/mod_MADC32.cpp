#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


//g++ -c -Wall -fPIC -I../include mod_MADC32.cpp
//g++ -shared -o mod_MADC32.so mod_MADC32.o



extern "C"
{

    typedef void (*writeFct)(uint32_t, int);
    typedef void (*setamFct)(int);
    typedef void (*setdwFct)(int);
    typedef void (*bltreadFct)(uint32_t, int, uint32_t*, int*);
    typedef int (*irqcheckFct)(uint32_t);


    int mod_nr[100];
    int irq_l[100];
    int v_th[100][33];
    int irq_data_thr[100];
    int max_data_transf[100];
    int ext_ts[100];
    int res_opt[100];
    int in_range[100];
    int hold_d0[100];
    int hold_d1[100];
    int hold_w0[100];
    int hold_w1[100];

    uint64_t evNumber[100];

    

    void read_cfg(uint32_t addr_offset, int modId)
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
                    v_th[modId][i] = strtol(val, &stop, 10);
                }
                    


                free(i_str);
                free(v_th_str);
            }
            if(strcmp(name, "mod_nr") == 0)
                mod_nr[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "irq_l") == 0)
                irq_l[modId] = strtol(val, &stop, 10); 
            else if(strcmp(name, "irq_data_thr") == 0)
                irq_data_thr[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "max_data_transf") == 0)
                max_data_transf[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "ext_ts") == 0)
                ext_ts[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "res_opt") == 0)
                res_opt[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "in_range") == 0)
                in_range[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "hold_d0") == 0)
                hold_d0[modId] = strtol(val, &stop, 10);
            else if(strcmp(name, "hold_d1") == 0)
                hold_d1[modId] = strtol(val, &stop, 10); 
            else if(strcmp(name, "hold_w0") == 0)
                hold_w0[modId] = strtol(val, &stop, 10); 
            else if(strcmp(name, "hold_w1") == 0)
                hold_w1[modId] = strtol(val, &stop, 10);    
        }
    //printf("ws = %d\nbw = %d\nro = %d\nts = %d\nto = %d\nidq = %d\nmdt = %d\nto = %d\nmodnr = %d\nextts = %d\n",
             //win_start[modId], b_width[modId], res_opt[modId], trig_source[modId], trig_opt[modId],
             // irq_data_thr[modId], max_data_transf[modId], ttl_opt[modId], mod_nr[modId], ext_ts[modId]);
        
    }


    void mod_configure(writeFct ptr_write, setamFct ptr_setAM, setdwFct ptr_setDW, uint32_t addr_offset, int modId)
    {

        printf("Configure for mod %d begin\n", modId);
        fflush(stdout);

        //set number of events to 0
        evNumber[modId] = 0;

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

        //set irq level
        (*ptr_write)(0x6010 + addr_offset, irq_l[modId]);

        //set irq vector
        (*ptr_write)(0x6012 + addr_offset, 0);

        //set resolution option
        (*ptr_write)(0x6042 + addr_offset, res_opt[modId]);
        
        //set input range
        (*ptr_write)(0x6060 + addr_offset, in_range[modId]);



        //gate generator
        //hold delay 0
        (*ptr_write)(0x6050 + addr_offset, hold_d0[modId]);

        //hold delay 1
        (*ptr_write)(0x6052 + addr_offset, hold_d1[modId]);

        //hold width 0
        (*ptr_write)(0x6054 + addr_offset, hold_w0[modId]);

        //hold width 1
        (*ptr_write)(0x6056 + addr_offset, hold_w1[modId]);







        //set voltage threshold for all 32 channels
        for(int i = 0; i<32; i++){

            printf("vth de %d e %d\n",i, v_th[modId][i]);

            (*ptr_write)(addr_offset + 0x4000 + 2*i, v_th[modId][i]);

        }

        //set irq data transf
        (*ptr_write)(0x6018 + addr_offset, irq_data_thr[modId]);

        //set max data transf
        (*ptr_write)(0x601A + addr_offset, max_data_transf[modId]);



        //if extended time stamp is on
        if(ext_ts[modId]){
            //enable extended time stamp mode
            (*ptr_write)(0x6038 + addr_offset, 3);
        }else{
            //disable extended ts
            (*ptr_write)(0x6038 + addr_offset, 0);
        }


        printf("Configure for mod %d end\n", modId);
        fflush(stdout);

    }


    void mod_start(writeFct ptr_write, setamFct ptr_setAM, setdwFct ptr_setDW, uint32_t addr_offset, int modId)
    {

        printf("Start for mod %d begin\n", modId);
        fflush(stdout);

        //set address modifier
        (*ptr_setAM)(0);
        //set data width
        (*ptr_setDW)(0);

        //start data transfer
        (*ptr_write)(0x603A + addr_offset, 1);


        //reset counter for ext ts
        if(ext_ts[modId]){
            (*ptr_write)(addr_offset + 0x6090, 1);
        }

        //start test
        //(*ptr_write)(0x6070 + addr_offset, 0b111);



        printf("Start for mod %d end\n", modId);
        fflush(stdout);

    }


    void mod_stop(writeFct ptr_write, setamFct ptr_setAM, setdwFct ptr_setDW, uint32_t addr_offset, int modId)
    {

        printf("Stop for mod %d begin\n", modId);
        fflush(stdout);

        //set address modifier
        (*ptr_setAM)(0);
        //set data width
        (*ptr_setDW)(0);

        //stop data transfer
        (*ptr_write)(0x603A + addr_offset, 0);



        //stop test
        //(*ptr_write)(0x6070 + addr_offset, 0);


        printf("Stop for mod %d end\n", modId);
        fflush(stdout);

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




    void mod_run(bltreadFct ptr_blt_read, writeFct ptr_write,
                 setamFct ptr_setAM, setdwFct ptr_setDW, irqcheckFct ptr_irqCheck, 
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

        //set nr of events to 0
        (*fNEvents) = 0;

        if((*ptr_irqCheck)(irq_l[modId]) == 1){

            //allocate memory for data
            uint32_t *dataBuff = (uint32_t*)malloc(10000*sizeof(uint32_t));


            //amount of data transfered
            int buffSize = -1;

            //sets address modifiern
            (*ptr_setAM)(1);
            //set data width
            (*ptr_setDW)(1);

            //blt read from FIFO
            (*ptr_blt_read)(addr_offset + 0x0000,  10000, dataBuff, &buffSize);


            printf("buffsize of %d from module %d\n", buffSize, modId);
            fflush(stdout);

            //set data width and am for single write
            (*ptr_setAM)(0);
            //set data width
            (*ptr_setDW)(0);
            
            //reset BERR
            (*ptr_write)(addr_offset + 0x6034, 1); 


            if(ext_ts[modId] == 0){


                for(int i = 0; i<buffSize; i++){

                    //used for testing
                    //######
                    //char *binary = toBinary((dataBuff[i]), 32);
                    //printf("The binary representation of %u is %s\n", (dataBuff[i]), binary);
                    //######

                    if((dataBuff[i]>>30) == 1){

                        if((dataBuff[i]>>24) != 64){

                            //printf("Event header invalid\n");
                            
                        }

                    }else if((dataBuff[i]>>30) == 0){

                        if((dataBuff[i]>>22) == 16){

                            mod_Mod[*fNEvents] = mod_nr[modId];
                            mod_Ch[*fNEvents] = ((dataBuff[i]>>16)&0b0000000000011111);
                            mod_TimeStamp[*fNEvents] = evNumber[modId];
                            mod_FineTS[*fNEvents] = 0;

                            if(((dataBuff[i]>>14) & 0x1) == 1){
                                mod_ChargeLong[*fNEvents] = 0xFFFF;
                            }else{
                                mod_ChargeLong[*fNEvents] = (uint16_t)(dataBuff[i] & 0x00003FFF);
                            }
                            

                            mod_ChargeShort[*fNEvents] = 0xFFFF;
                            mod_RecordLength[*fNEvents] = 1;
                            mod_Extras[*fNEvents] = 0xFFFF0032;

                            (*fNEvents)++;

                        }else if(dataBuff[i] != 0){

                            //printf("Data event invalid\n");
                            char *binary = toBinary((dataBuff[i]), 32);
                            //printf("Data event invalid %u is %s at i = %d\n", (dataBuff[i]), binary, i);
                            free(binary);

                        }


                    }else if((dataBuff[i]>>30) == 3){
                    
                        evNumber[modId]++;

                    }



                    



                    //free(binary);
                
                }
            }else if(ext_ts[modId] == 1){

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

                            mod_Mod[*fNEvents] = mod_nr[modId];
                            mod_Ch[*fNEvents] = ((dataBuff[i]>>16)&0b0000000000011111);

                            //nonsense value that is changed if the time stamp is valid
                            mod_TimeStamp[*fNEvents] = 0xFFFFFFFFFFFFFFFF;

                            mod_FineTS[*fNEvents] = 0;

                            if(((dataBuff[i]>>14) & 0x1) == 1){
                                mod_ChargeLong[*fNEvents] = 0xFFFF;
                            }else{
                                mod_ChargeLong[*fNEvents] = (uint16_t)(dataBuff[i] & 0x00003FFF);
                            }

                            mod_ChargeShort[*fNEvents] = 0xFFFF;
                            mod_RecordLength[*fNEvents] = 1;
                            mod_Extras[*fNEvents] = 0xFFFF0032;

                            (*fNEvents)++;

                            ev_in_h++;

                        }else if((dataBuff[i]>>16) == 1152){

                            ext_ts_lb = (dataBuff[i] & 0x0000FFFF);
                            ts_valid = true;

                        }else if(dataBuff[i] != 0){

                            //printf("Data event invalid\n");
                            char *binary = toBinary((dataBuff[i]), 32);
                            printf("Data event invalid %u is %s at i = %d\n", (dataBuff[i]), binary, i);
                            free(binary);

                        }

                    }else if((dataBuff[i]>>30) == 3){

                        //first 2 bits are always 11 for EOE mark; we only use 30 for the time stamp
                        ext_ts_hb = (dataBuff[i] && 0x3FFFFFFF);

                        //checks if the 16 low bits of extended time stamp were present
                        if(ts_valid){

                            for(int iter_eoe = 0; iter_eoe<ev_in_h; iter_eoe++){

                                mod_TimeStamp[*fNEvents - (ev_in_h - iter_eoe)] = (ext_ts_hb<<16) + ext_ts_lb;

                            }

                        }else{

                            printf("\nTime stamp invalid!!!\n");

                        }
                        


                    }


                }
            }






            free(dataBuff);

        }





    }













    //checks if the device outputs data
    //0 for no and 1 for yes
    int mod_checkifreader(void)
    {
        return 1;
    }
                         


}