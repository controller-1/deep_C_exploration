# How does the computer remember where it stored the value for a certain variable?

Need to look deeper into the topic of computer memory.

One role of a computer's OS is to manage the memory of the computer. Memory refers to the hardware in the computer that is involved in 
storing information for use in the computer. Two types of memory: 1. RAM which is temporary memory that is easy and quick to access and 
used to execute programs (also called volatile memory), and 2. Lasting memory for more permanent storage of data (also known as nonvolatile).

Vast majority of computer programs uses RAM during execution. Values of variables, for example, are stored (written to and read from) in
RAM. For simplicity, think of RAM as a sequence of binary memory cells (each cell containing 0 or 1). Each cell is called 1 bit. A group
of these bits is called a "word". The word is the fundamental unit of data that can be moved between the RAM and computer processor. Size of
a word is expressed in number of bits or bytes (where 1 byte = 8 bits). Modern computers use 8, 16, 32, or 64 bits for one word but other 
sizes are possible. 

Why group bits into words?
Allows for addressing of memory. An address assigned to each word, which is called memory address and it is a whole number that describes
the location of the word in the computer memory. For example, suppose a computer can store a total of four words then the address for the 
first word is 0, the second is 1, the third is 2 and the last is 3. 

In C its possible to get these memory addresses during the execution of a program. For example, can obtain the address of where an integer 
variable is stored. In other words, using memory addresses allows low-level access to the computer by allowing direct access to the 
computer's memory. This technique allows for optimization of memory usage at a very precise level or of performance in terms of 
execution speed.
