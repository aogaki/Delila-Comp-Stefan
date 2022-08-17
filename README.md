# Delila-Comp-Stefan


These are the components I made for DELILA.
Just include them in the Components folder, 'make' and follow the example in the xml to run them.
Don't forget to get what files you don't have from /include and /src.



For the VMEConductor additional steps are required:
  -Go to the src folder and type
    g++ -fPIC -shared -o VMEController.o VMEController.cpp
    g++ -fPIC -shared -o VMEDevice.o VMEDevice.cpp VMEController.o
  
  
  -Go to the slibs folder and type
  
    g++ -c -Wall -fPIC -lCAENComm -I../include cont_2718.cpp -ldl
    g++ -shared -o cont_2718.so cont_2718.o /home/gant/DELILA-main/Components/src/VMEController.o -ldl -lCAENComm
    
    g++ -c -Wall -fPIC -I../include -I../include/includesiseth /home/gant/DELILA-main/Components/include/includesiseth/sis3153ETH_vme_class.cpp  cont_SISeth.cpp -ldl 
    g++ -shared -o cont_SISeth.so cont_SISeth.o /home/gant/DELILA-main/Components/src/VMEController.o sis3153ETH_vme_class.o -ldl
    
    g++ -c -Wall -fPIC -I../include dev_MADC32.cpp -ldl
    g++ -shared -o dev_MADC32.so dev_MADC32.o /home/gant/DELILA-main/Components/src/VMEController.o /home/gant/DELILA-main/Components/src/VMEDevice.o -ldl
    
    
  -Edit or create a json config file for your module. The name should be something like 'conf_MADC32_{address fron the board}.json'
    example 'conf_MADC32_0x4000000.json'



    



