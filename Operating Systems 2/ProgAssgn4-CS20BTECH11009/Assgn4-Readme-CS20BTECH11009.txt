Instructions:

--This program takes the input as "inp-params.txt"

--open the folder in which code is there , make sure the inp-para.txt is also there and run the following commands
   
   1) g++ SrcAssgn4-tas-CS20BTECH11009.cpp -o tas -lpthread
      #it will compile the tas code
   2) g++ SrcAssgn4-cas-CS20BTECH11009.cpp -o cas -lpthread
      #it will compile the cas code
   3) g++ SrcAssgn4-cas-bounded-CS20BTECH11009.cpp -o cas-bounded -lpthread
      #it will compile the cas-bounded code
      
-- To execute the output file , run the following command.

   1) ./tas
   
   2) ./cas
   
   3) ./cas-bounded
   
--output

  1) For each it will give average waiting time , maximum waiting time in terminal
  
  2) For each terminal it will generate a txt file in which it has information about at what time it has entered and and at what request has made , and at what time it has exited the system.
     
