# ECE 220 Honor
# MP4 Parallel Tree Finder

In this MP you will implement a parallel algorithm that finds a specific element in a binary tree.

General guidelines:  

1. You can choose any threading model you'd like. 
3. Do not change any of the python (.py) files  
4. Use Applications -> System Tools -> Mate System Monitor -> Resources -> CPU History to see how CPU  responds to spawning multiple threads  
5. In Linux, use $lscpu command to show CPU resources you have.  
6. Write your own tree construction algorithm in make_tree.cpp to construct a big-enough tree to show your multi-threading performance benefit  


Usage:  

  1. compile program

    $ make

  2. run test program

    $ ./find_parallel
    $ ./find_serial

  3. run both versions of the accumulator, compare the output and speedup

    $ python benchmark.py

Todos:  

  1. Complete the cpp class member functions in tree.cpp  
  2. Complete util functions in utils.cpp
  3. Write your own tree construction function in make_tree.cpp and test your search algorithm with your tree

Report:

  Answer the following questions in "report.pdf":
  1. Include the console output from running `python benchmark.py`.
  2. What is your threading model? Why you chose this threading model?
  3. How does your constructed tree look like?
  4. In worst case, if our input tree just looks like a linked list. Can we still improve the runtime?