#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

//g++ -c -Wall -Werror -fPIC mod_V812.cpp
//g++ -shared -o mod_V812.so mod_V812.o

extern "C"
{
    int v_thr;
    int out_width;
    int dead_time;
    int active_ch;
    int nr_active_ch;
    int ch_list[16];

    void read_cfg(uint32_t addr_offset)
    {
        char *addr_str = (char*)malloc(20*sizeof(char));
        sprintf(addr_str, "%08X", addr_offset);
        char *file_loc = (char*)malloc(100*sizeof(char));

        strcat(file_loc, "/home/gant/DELILA-main/Components/CAENVX2718cont/conf_V812_0x");
        strcat(file_loc, addr_str);
        strcat(file_loc, ".conf");

        printf("Stringul e %s\n", file_loc);

        FILE *cFile;
        cFile = fopen(file_loc, "r");

        free(addr_str);
        free(file_loc);

        if(cFile == NULL){
            printf("Error opening V812 config\n");
            return;
        }


        char name[128];
        char val[128];
        char *stop;

        while(fscanf(cFile, "%127[^=]=%127[^\n]%*c", name, val) == 2){
            if(strcmp(name, "v_thr") == 0)
                v_thr = strtol(val, &stop, 10);
            else if(strcmp(name, "out_width") == 0)
                out_width = strtol(val, &stop, 10);
            else if(strcmp(name, "dead_time") == 0)
                dead_time = strtol(val, &stop, 10);
            else if(strcmp(name, "active_ch") == 0)
                active_ch = strtol(val, &stop, 2);
        }

        nr_active_ch = 0;

        for(int i = 0; i<16; i++){
            if(((active_ch>>i) & 1) == 1){
                ch_list[nr_active_ch] = i;
                nr_active_ch++;
            }
        }
    }


    void mod_configure(void (*ptr_write)(uint32_t, int), void (*ptr_setAM)(int), void (*ptr_setDW)(int), uint32_t addr_offset, int modId)
    {

        printf("812 config begin\n");
        //read config file
        read_cfg(addr_offset);

        //set address modifier
        (*ptr_setAM)(0);
        //set data width
        (*ptr_setDW)(0);

        //set active channels
        (*ptr_write)(addr_offset + 0x004A, active_ch);

        //set voltage th
        for(int i = 0; i < nr_active_ch; i++)
            (*ptr_write)(addr_offset + 2*ch_list[i], v_thr);

        //set output width
        (*ptr_write)(addr_offset + 0x0040, out_width);
        (*ptr_write)(addr_offset + 0x0042, out_width);

        //set dead time
        (*ptr_write)(addr_offset + 0x0044, dead_time);
        (*ptr_write)(addr_offset + 0x0046, out_width);

        printf("812 config end\n");

    }

    void mod_start(void (*ptr_write)(uint32_t, int), void (*ptr_setAM)(int), void (*ptr_setDW)(int), uint32_t addr_offset, int modId)
    {
        return;
    }

    void mod_stop(void (*ptr_write)(uint32_t, int), void (*ptr_setAM)(int), void (*ptr_setDW)(int), uint32_t addr_offset, int modId)
    {
        return;
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
        return;
    }

    int mod_checkifreader(void)
    {
        return 0;
    }
}