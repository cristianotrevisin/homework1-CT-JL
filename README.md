# Homework 2 by Joseph Lemaitre and Cristiano Trevisin
 
## Documentation
### C++ routines
First of all, the executable files should be generated. To do so, we recommend the following commands:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
The ```main``` script can then be executed through the following command
```
./src/main arg1 arg2 arg3 arg4 
```
It takes five arguments:

* ```arg1 (int)``` represents the length of the series;
* ```arg2 (char)```controls the desired series method (```'ari'``` for an arithmetic evaluation of the series or ```'pi'``` for the estimation of Pi);
* ```arg3 (char)```controls the desired dumping method (```'print'``` if the results should be printed to screen ```'write'``` if the results are to be saved in a text file);
* ```arg4 (int)```controls the dumping frequency at which the results should be reported;
* ```arg5 (char)```gives the name of the output files for the ```'write'``` dumping method. It selects automatically the most suitable separator, a space or tab for a ```.txt``` file, a comma for a ```.csv```file, and a pipe for a ```.psv```file.

### Python Plotter
This file needs Python 3.6+ and recent versions of ```numpy```, ```matplotlib```, and ```pandas```.

File ```plot.py``` allows plotting of the series output generated through the ```write``` command of the routine above. It takes three arguments:

* ```file_name```, where the file with the output is stored (file extension should be included). Separator is automatically detected through the Python sniffer engine. Default is ```example.txt```;
* ```output_file```, where the plot should be saved. If none is provided, then the script will show to screen the plot. Default is ```' '```, which only shows the output to screen.

## Answer to the questions
### Question 2.1 
The strategy that we chose to divide the work amongst ourselved stemmed from the simple schedule availabilities. Overall, we collaborated equally depending on the time availabilities and were able to coordinate our work. We sought frequent communication in order to update each other on the advancement of the progress and  and select the best way to address a question. GIT helped, as allows collaborative work and keeping track of the progress.

### Question 5.4
The code has been factorized in order to reduce the number of operations that should be executed at any time. Specifically, the class ```Series``` includes general definition such as the counter of the value (it updates everytime that is called) and the current value of the series. This way, calling the dumper does not need the recomputation of the series at every iteration. The number of computations depend on the maxiter (N) term. In the following computations, we only consier the number of mathematical computations that should be executed. Evaluation of the if/else statement, reads and writes is not included. 

* For the ```'ari'``` (arithmetic) method:
  * The plain calculation of the series takes 1+4N computations: 1 to assign the initial index as zero, and N-times the update of the index in the loop, the addition of the unity to the index at each step, the evaluation of the term to be added in the summatory (requires only one computation) and the addition of this term to the actual summatory;
  * The output of the series is now optimized, as at each step, the printer does not need to calculate the entire series up to a given iteration, but it will remember the last step and update the series based on this last step. This means that the code will be greatly optimized. Let's assume that the frequency is defined equal to the unity (i.e. the entire series will be printed). The first operation that is done is the evaluation of the series for N = 1. This means that the loop will be updated (one operation) and calculate four steps. 
  
* For the ```'pi'``` method:
  * The plain calculation of the series takes 3 + 6N computations: 1 to assign the initial index as zero, and N-times the update of the index in the loop, the addition of the unity to the index at each step, the evaluation of the term to be added to the summatory (which requires three computations here) and the addition of this term to the actual summatory, plus the multiplication by 6 and the extraction of the squared root;
 
