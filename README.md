Eh, why not? Took direction from [this](https://inst.eecs.berkeley.edu/~cs61c/sp15/hw/01/hw1.html) statement. (and [this](https://inst.eecs.berkeley.edu/~cs61c/sp15/hw/02/hw2.html) one)

## Why?  
I got bored, and the above reference caught my eye. I thought it was interesting homework, so i tried it. Originally intended to write it procedurally in C, but ended up writing it in C++ after being quickly reminded of my place by C-strings. Also the filesystem module abstraction in cpp appeals to me over making linux-specific syscalls.  
Currently, it can track files/directories and make commits. I will implement as much as is specified in the above references, and will move forward if intellectually curious. The current commit strategy is hilariously suboptimal, and i will change that when i get to actually studying version control systems.
## Usage
Currently works reliably on Linux systems. Use ```make compile``` to build the binary and then use ```./vcs init``` to intialize a repo.  
currently, ```add```, ```rm```, ```commit``` options are supported.  