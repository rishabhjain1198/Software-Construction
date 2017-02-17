Firstly, I had to identify which part of the program does the heavy lifting,
so that I implement multi threading the most effective area.

Once I had recognized it, I had to separate it from the main function,
since a thread requires the code to be in an external function. While doing 
this, I had to be careful about variables which might be local in scope,
and thus I had to change some of them to global (like scene of type scene_t).

After organizing the code properly, I had to actually create the threads.
I did so using a for loop, and then I freed the threads using another similar
loop. 

For proper synchronization, instead of having each thread directly output its 

