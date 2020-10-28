# Homework 2 by Joseph Lemaitre and Cristiano Trevisin
 
## Documentation
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
It takes four arguments:

* ```arg1 (int)``` represents the length of the series;
* ```arg2 (char)```controls the desired series method (```'arithmetic'``` for an arithmetic evaluation of the series or ```'pi'``` for the estimation of Pi);
* ```arg3 (char)```controls the desired dumping method (```'print'``` if the results should be printed to screen ```'write'``` if the results are to be saved in a text file);
  * if the chosen dumping method is ```'print'```, then ```arg4 (int)``` controls the precision format of the printing to screen;
  * if the chosen dumping method is ```'write'```, then ```arg4 (char)``` allows to choose the separator to use in the file (options are ```'space'```, ```'tab'```,```'comma'```, and ```'pipe'```).
