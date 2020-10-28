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
* ```arg2 (char)```controls the desired series method (```'arithmetic'``` for an arithmetic evaluation of the series or ```'pi'``` for the estimation of Pi);
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
The strategy that we chose to divide the work amongst ourselved stemmed from the simple schedule availabilities and we collaborated equally depending on the spare time from other academic needs. We sought frequent communication in order to update each other and select the best way to address a question. GIT helped, as allows collaborative work and keeping track of the progress.

