# Linux Shell in C 
## Running Shell
> - Go to the directory
> - Type the command **make** on the terminal
> - Run **./a.out** on the terminal
> - The shell starts with prompt on the terminal
---
## Exit Shell
> To exit the shell you should type `exit` . You can also use `Ctrl + C` to exit the shell.
---
## Important Features
> - This shell is **colorful** (prompts ,errors,success etc are displayed in various colors )
> - **Spaces** and **tabs** are handled for all commands
> - You can enter multiple commands separated by `;`
---
### NOTE 
> Some of the **.h** files also contain header files specific to their corresponding **.c** file
---
## Files

- **headers.h** : It contains the common header files used across all the **C** files
- **main.c** : It contains the **shell loop** and also checks for which command to execute.
- **pwd.h** : It contains the declaration of functions used in pwd.c
- **pwd.c** : It contains the implementation of `pwd` command.
    * You **cannot** enter argument along with pwd command (**only spaces and tabs is allowed**)
- **pinfo.h** : It contains the declaration of functions used in pinfo.c
- **pinfo.c** : It contains the implementation of `pinfo` command(user defined).
    * You **cannot** enter more than one pid as an argument. If enterred then error is displayed.
- **ls.h** : contains the declaration of functions used in ls.c
- **ls.c** : It contains the implementation of `ls` command (along with the flags)
    * In case of long listing format the normal file is displayed with different colour, directory with other and executable file with other (*If directory has execute permissions for user then also directory is displayed with color of directory*)
    * You can have repetitions  in flag such as : [-la -la], [ -llalal ] etc.
- **changedir.h** : contains the declaration of functions used in changedir.c
- **changedir.c** : It contains the implementation of `cd` command
    *  If just cd (i.e no argument to cd) is typed it works same as cd ~ 
    *  Error is displayed if directory does not exist
- **echo.h** : contains the declaration of functions used in echo.c
- **echo.c** : It contains the implementation of `echo` command
- **run.h** : contains the declaration of functions used in run.c
- **run.c** : It contains the code to manage `system commands` (i.e **NOT built-in** commands). 
    * It checks if there is & at the end of string (of form "&" or "xyz&") , if it is there then the command is run in background else foreground .If no such command then error is displayed.
    * The pid of a background process is printed on the stdout if succesfully created along with the count of background process (if suppose 2 background process are already running then for new process count=3). The display format is : `[count] pid`
    * On termination of a background process appropriate message is displayed.
- **prompt.h** : contains the declaration of functions used in prompt.c
- **prompt.c** : It contains the implementation of the `prompt` on the stdout (**<username@system_name:curr_dir>**)
    * if there is any error getting any of the values required for prompt then error is displayed.
- **nightswatch.h** : contains the declaration of functions used in nightswatch.c
- **nightswatch.c** : It contains the implementation of the `nightswatch` command.
    * Implemented for `interrupt` command
    * If you run this command as `nightswatch interrupt` (i.e without specifying seconds ) then the default time after which it displays interrupts is **5 seconds**.
    * To exit you need to type **q followed by Enter** . It will exit instead of writing the interrupts next time.
    * If instead of q you type any string and press Enter it won't affect the nightswatch command (**but `\n` should be there only at the end of the string**)
- **history_store.txt** : stores the history of the last 20 commands . Commands are written in it according to the algo described in history.c
    * **Do not alter this file after running a.out**
- **makefile** : It is the makefile that is used to compile all the c programs together (just need to type `make` in the terminal)
- **history.h** : contains the declaration of functions used in history.c
- **history.c** : It contains the implementation of `history` command
    * The new command enterred is added at the end of the history_store.txt file (**if already 20 then first is deleted**)
    * When you type a command and press enter then first it gets updated in th history_store.txt and then the command is executed.
    * If the string typed is exactly same as the last one it is not added in the history_store.txt file. 
    * The string is as it is written(that is tabs and spaces are left as it is) in the history_store.txt.
    * If there are multiple commands separated by **;** then each of them is stored in history as a separate command one after the other in the order they appear.

### Files added in Assignment-3
- **manage_jobs.h** : contains the declaration of functions used in manage_jobs.c
- **manage_jobs.c** : contains the implementation of `jobs` and `kjob` commands . In `jobs` command if there is no background process that is displayed . 
- **manage_signal.h** : contains the declaration of functions used in manage_signal.c
- **manage_signal.c** : contains the signal handlers for signals `SIGINT` `SIGTSTP` `SIGCHLD`
- **overkill.h** : contains the declaration of functions used in overkill.c
- **overkill.c** : contains the implementation of `overkill` command . If there is no background process already then it is displayed .
- **pipe.h** : contains the declaration of functions used in pipe.c
- **pipe.c** : contains functions to implement piping . It is checked in the main.c file if the command contains `|` , if present then piping is executed by using functions in pipe.c
- **logical_chain.h** : contains the declaration of functions used in logical_chain.c
- **logical_chain.c** : contains functions to implement logical chaining of commands using operators `@`  (**logical AND**) and `$` (**logical OR**) . Error is displayed if the number of operators is not 1 less than the number of commands in the chain . Chain is executed from left to right along with short circuit if the next command exit status is not required .
- **io_redirection.h** : contains the declaration of functions used in io_redirection.c
- **io_redirection.c** : contains functions to implement redirection of input output . It is checked in the main.c file if the command contains `>` `>>` `<` , if present then IO redirection is executed by using functions in io_redirection.c
- **handle_env.h** : contains the declaration of functions used in handle_env.c
- **handle_env.c** : contains implementation of `setenv` and `unsetenv` commands that are used to set and unset environment variables for the shell .
- **fg.h** : contains the declaration of functions used in fg.c
- **fg.c** : contains the implementation of `fg` command
- **bg.h** : contains the declaration of functions used in bg.c
- **bg.h** : contains the implementation of `bg` command 

## Important Point on `exit codes`

The exit code for a currently running foreground process when `Ctrl+C` is pressed is according to exit status received when child process is killed .

---
