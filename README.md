# minishell

The objective of this project is create a simple shell.



### Implemented tasks:


* Show a prompt when waiting for a new command.

* Have a working History.

* Search and launch the right executable (based on the PATH variable or by using
relative or absolute path)

* Builtins:
  ◦ echo with option -n
  
  ◦ cd with only a relative or absolute path
  
  ◦ pwd with no options
  
  ◦ export with no options
  
  ◦ unset with no options
  
  ◦ env with no options or arguments
  
  ◦ exit with no options
  
* Redirections: > < >> <<.

* Pipes |

* Environment variables ($ followed by characters).

* $? expand to the exit status of the most recently executed foreground
pipeline.

* ctrl-C ctrl-D ctrl-\ work like in bash.


Using `make` will create the minishell executable.

Run it with :

    ./minishell
   

Created by SCASS and LKASANDR
