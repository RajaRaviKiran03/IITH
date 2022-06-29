Instructions:

--This program takes the input as "inp-params.txt"

--open the folder in which code is there , make sure the inp-params.txt is also there and run the following commands

   1) g++ Assn5-rw-CS20BTECH11009.cpp -o rw -lpthread -lrt
      #it will compile the rw code
   2) g++ Assn5-frw-CS20BTECH11009.cpp -o frw -lpthread -lrt
      #it will compile the frw code
   
-- To execute the output file , run the following command.

   1)./rw
   
   2)./frw
   
--Output
  
   1) For each code it will generate a Log.txt in which it has information about at what time it has entered and and at what request has made , and at what time it has exited the system.
   
   2) For each code it will generate a Avg_time.txt in which it has information about average time for each writer and reader thread , and also average waiting time , max waiting time for all writer
     and reader threads
   
