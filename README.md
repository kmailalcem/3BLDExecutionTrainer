# 3BLD Execution Trainer
This program is a simple C++ program that randomly generates scrambles, provide memo and timing. The letter scheme used here is traditional (mofangba) letter scheme.

# Installation
This installation assumes that you have GCC installed. Open up terminal and change directory to the folder you intend to install

    cd <directory>
    
Clone the repo

    git clone https://github.com/kmailalcem/3BLDExecutionTrainer.git

Then simply run make:

    make
    
This will create a binary called `trainer`. Then you are done!

If you do not have GCC installed and instead have some other compiler, or that `make` doesn't work for you, I suppose you could simply run
    
    CXXCOMPILER *.cpp -o trainer
 
## Usage

Type 

    ./trainer
    
To run in interactive mode. You can skip the buffer pieces part by supplying them directly in the arguments:

    ./trainer <edge_buffer> <corner_buffer>

Alternatively, you could supply a scramble file and run
    
    ./trainer <scramble_file>
    
where scramble file has the following format

```
<edge_buffer> <corner_buffer>
scramble1
scramble2
scramble3
.
.
.
```

and the results will be output to the terminal. Bare in mind that all letters are in traditional (mofangba) letter scheme.

## Maintenance
Due to the technical background required and the limited functionality this program provides, this project is clearly not within expectation of most cubers looking for such a software.
For this reason, this project is no longer maintained.
For a much more powerful tool on generating memo, see [xzTrainer](https://github.com/kmailalcem/xzTrainer).
