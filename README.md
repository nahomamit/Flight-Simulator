# flightsimulatorgal

The must of this project we made thogther.\

Expression.h and Expression.cpp was taken from our first HW.\

**lexer.h** 
its the first part of this project. Take a txt file and split to list.\
the splits made first by take line and split by "=".
Then by breakless and finally by space.
If we find string or expression we connect to one part.

**main.cpp**
The start of running. first get as argument the file name and open its.
After that create the lexer by using lexer.h.\
open server thread that waiting to connect the simulator servr and start reading data.
open client thread that connect to simulator server and get client sokect.
After that run on the lexer and parsing.
When lexer list is empty we close all thread and program done.

**commend.h**
At this hader we write all commend that we need.
*commend interface* - that include virtual function that return int, that number of pops that lexer list has to do.

*Variable class* - has float value, sim and direction  (1 = reading, -1 = writing).

*Create server* - create a server by txt information and than start a loop of reading data from simulator.

*connect command* - connect as client to simulator server and create a client sokect.

*Define Var* - when var sign show in txt we crate a new variable that has name, location and direction.

 *Print command* - printing to console.
 
 *Sleep command* - force the thread sleep for a while.
 
 *update command* - sned informition to the simulator by the variable with the correct direction.
 
 *if commend* - return a negative value to sign main that its an if line, -2 true, -3 flase.
 
 *while commend* - return -4 for sign its while loop and create list that has if commend and all the other comment until '}'.
 
 
 
 


