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
./src/main max_iter serie_method dumper_method dump_freq (filename)
```
It takes five arguments:

* ```max_iter (int)``` represents the length of the series;
* ```serie_method (str)```controls the desired series method (```ari``` for an arithmetic evaluation of the series or ```'pi'``` for the estimation of Pi);
* ```dumper_method (str)```controls the desired dumping method (```print``` if the results should be printed to screen ```'write'``` if the results are to be saved in a text file);
* ```dump_freq (int)```controls the dumping frequency at which the results should be reported;
* ```filename (str)```gives the name of the output files for the ```write``` dumping method. It selects automatically the most suitable separator, a space or tab for a ```.txt``` file, a comma for a ```.csv```file, and a pipe for a ```.psv```file.

### Python Plotter
This file needs Python 3.6+ and recent versions of ```numpy```, ```matplotlib```, and ```pandas```.

File ```plot.py``` allows plotting of the series output generated through the ```write``` command of the routine above. It takes two arguments:

* ```file_name```, where the file with the output is stored (file extension should be included). Separator is automatically detected through the Python sniffer engine. Default is ```example.txt```;
* ```output_file```, where the plot should be saved. If none is provided, then the script will show to screen the plot. Default is ```' '```, which only shows the output to screen.

## Answer to the questions
### Question 2.1 
The strategy that we chose to divide the work amongst ourselved stemmed from the simple schedule availabilities. Overall, we collaborated equally depending on the time availabilities and were able to coordinate our work. We sought frequent communication in order to update each other on the advancement of the progress and  and select the best way to address a question. GIT helped, as allows collaborative work and keeping track of the progress. We switched between pair-programming (useful because of our different levels: we can learn and teach faster) and simple task division.

### Question 5.1
First of all, let's calculate the number of operation for a simple plain evaluation of each series up to N:
* for the ```'ari'``` (arithmetic) method, the evaluation of the series takes 1+4N computations: 1 to assign the initial index as zero, and N-times the update of the index in the loop, the addition of the unity to the index at each step, the evaluation of the term to be added in the summatory (requires only one computation) and the addition of this term to the actual summatory;
* for the ```'pi'``` method, the evaluation of the series takes 3 + 6N computations: 1 to assign the initial index as zero, and N-times the update of the index in the loop, the addition of the unity to the index at each step, the evaluation of the term to be added to the summatory (which requires three computations here) and the addition of this term to the actual summatory, plus the multiplication by 6 and the extraction of the squared root.

The unfactorized script will do the plain calculation at each iteration, meaning that at step 1 the number of calculations will be (in the arithmetic case) 1+4x1; for the step 2 it will be 1+4x2, and so on. This can be mathematically represented as (f is the frequency):

<img src="https://latex.codecogs.com/svg.latex?\Large&space;P(N)=\sum_{i=1}^{N/f}(1+4fi)=\frac{N}{f}+2N\left(\frac{N}{f}+1\right)" title="\Large P(N)=\sum_{i=1}^{N/f}(1+4fi)=\frac{N}{f}+2N\left(\frac{N}{f}+1\right)" />

For the `pi` case, the equation can be easily yielded:

<img src="https://latex.codecogs.com/svg.latex?\Large&space;P(N)=\sum_{i=1}^{N/f}(3+6fi)=\frac{3N}{f}+3N\left(\frac{N}{f}+1\right)" title="\Large P(N)=\sum_{i=1}^{N/f}(3+6fi)=\frac{3N}{f}+3N\left(\frac{N}{f}+1\right)" />

### Question 5.4
The code has been factorized in order to reduce the number of operations that should be executed at any time. Specifically, the class ```Series``` includes general definition such as the counter of the value (it updates everytime that is called) and the current value of the series. This way, calling the dumper does not need the recomputation of the series at every iteration. The number of computations depend on the maxiter (N) term. In the following computations, we only consier the number of mathematical computations that should be executed. Evaluation of the if/else statement, reads and writes is not included. 

* For the ```'ari'``` (arithmetic) method: the output of the series is now optimized, as at each step, the printer does not need to calculate the entire series up to a given iteration, but it will remember the last step and update the series based on this last step. This means that the code will be greatly optimized. The compiler will go through the 1+4 steps only once per actual natural number (plus one to update the loop that prints on screen or on file), meaning that the number of operations is now hugely cut:
 
<img src="https://latex.codecogs.com/svg.latex?\Large&space;P(N)=6N" title="\Large P(N)=P(N)=6N" />
  
* For the ```'pi'``` method: again, the compiler will go through 3+6 computations, plus one stemming from the loop that prints/writes on file. The total number of iterations is therefore:

<img src="https://latex.codecogs.com/svg.latex?\Large&space;P(N)=10N" title="\Large P(N)=P(N)=10N" />

The convenience of the factorization can be easily be recognized: while in the first case, the number of computations grows quadratically with the last term of the series, with the refactorization the growth is now linear, providing substantial advantage in terms of computational effort when handling big numbers.
 
