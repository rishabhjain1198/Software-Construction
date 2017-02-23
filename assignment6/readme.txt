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
results, I stored it into an array and outputted the results at the end.

Then, to test performance of multi threading implementation, I took a look at
make-log.txt and compared the first time result to the rest,

time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m28.276s
user	0m27.697s
sys	0m0.201s

time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m17.683s
user	0m33.192s
sys	0m0.141s

time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m16.696s
user	0m49.176s
sys	0m0.249s

time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m8.335s
user	0m56.021s
sys	0m0.324s


As we can see, the real time elapsed is reduced significantly in 8 core multi threading
as compared to single core processing.
