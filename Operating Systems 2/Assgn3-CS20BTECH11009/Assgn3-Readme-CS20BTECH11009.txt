Instructions:

--This program takes the input as "inp-params.txt"

--open the folder in which code is there , make sure the inp-para.txt is also there and run the following commands

  1) g++ Assgn3-RMSCS20BTECH11009.cpp -o RMS
     #it will compile the RMS code
  2) g++ Assgn3-EDFCS20BTECH11009.cpp -o EDF
     #it will compile the EDF code
     
-- To execute the output file , run the following command.
  
   1) ./RMS
   
   2) ./EDF
   
-- output 

 1)It will generate files RMS-Log.txt and EDF-Log.txt which have information about completed processes, preempted process,
   processes that missed the deadline and cpu sleep time.

 2)It will genrate 2 files RMS-Stats.txt and EDF-Stats.txt which have information about no
   of process completed , no of process that came into the system , no of process missed their
   deadline,average time for each process for each RMS and EDF.
  
