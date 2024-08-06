
# Shell program
**This shell program supports a set of built-in commands, along with the ability to execute external commands found in the PATH environment variable.** <BR>

# How to use?
## 1) Compilation 
```
gcc commands.c femtoShell.c -o cmd
```
## 2) Running 
```
./cmd
```
## 3) Executing Commands
**Enter commands at the prompt to execute them. Use built-in or external commands as needed.** <BR>
## 4) Exiting the Shell
**Use the exit command to exit the shell.** <BR>

 
# Built-in Commands
 
| command name | Description                                           | Args                    |  Example                  | 
| ------------ | -----------                                           | ----                    | ----------                | 
| help         | show list of supported commands                       |  no                     | help                      | 
| exit         | terminate shell                                       |  no                     | exit                      |
| mypwd          | print working directory                               |  no                     | mypwd                       | 
| cd          | change the current directory to the specified path     |  specified_path           | cd ../                      | 
| mycat          | show content of certain file                          |  filename               | mycat file                  |
| myecho         | print a user input string on stdout                   |  message                | myecho "gehad" <BR>`or`<BR> myecho gehad                  | 
| myrealpath          | print the resolved absolute path                            |  filePath <BR>`or`<BR> dirPath               | myrealpath filePath <BR>`or`<BR> myrealpath dirPath                   |
| mycp           | copy a file to another file                           |  sourcePath, targetPath | mycp  sourcePath targetPath |
| mycp -a        | append the source content to the end of the target file |  sourcePath, targetPath | mycp -a sourcePath targetPath |
| mymv           | move a file to another place           |  sourcePath, targetPath | mymv sourcePath targetPath |
| mymv -f           | force overwriting the target file if exits            |  sourcePath, targetPath | mymv -f sourcePath targetPath |
| myrm           | remove files                         |  filesname        | myrm file1 file2                   |
| myrmdir        | remove directories                   |  filesname        | myrmdir dir1 dir2                  |
| envir          | print all the environment variables  |  no               | envir                 |
| envir variable | print the value of this environment variable if exists   |  variable             | envir  PATH  <BR>`or`<BR> envir anyVariable|    
| type | return the type of the command (internal, external or unsupported command)   |  command            | type ls <BR>`or`<BR> type mypwd|  
| phist | lists the last 10 processes with their exit status   |  no           | phist | 
| myclear | clear the terminal screen   |  no           | myclear | 
# External Commands
**The shell supports executing external commands available in the directories specified by the PATH environment variable. Commands can be executed by simply entering their names, without requiring the full path** <BR> 

**`some common examples like:`**
* `mv`: Move or rename files or directories.
* `ls`: List directory contents.
* `grep`: Search for patterns in files.
* `cat`: Concatenate and display file contents.
* `mkdir`: Create a new directory.
* `rm`: Remove files or directories.
* `cp`: Copy files or directories.
* `echo`: Display a line of text or a string.
* `ps`: Report a snapshot of current processes.



## Example of the output: <BR>
<img src="https://github.com/user-attachments/assets/72a98ba6-0564-47f7-8ef8-07e920982a28">
<img src="https://github.com/user-attachments/assets/e825d27e-301e-481a-afc9-d87066536a2f">
<img src="https://github.com/user-attachments/assets/967dd6e5-4c2e-45f6-9742-5db76512dde1">
<img src="https://github.com/user-attachments/assets/907440f5-02ad-4916-bfaa-3274b211bbb1">
<img src="https://github.com/user-attachments/assets/0bb32c3e-8e7a-411d-95db-8c8a0364b0e7">
<img src="https://github.com/user-attachments/assets/0201c3ac-49a0-4076-999c-52df5ef14b64">
<img src="https://github.com/user-attachments/assets/1fddeb79-e88e-4589-b302-063af34b78c1">
<img src="https://github.com/user-attachments/assets/c6ab3094-d4d8-48ca-a478-b60eeaf84d5b">
<img src="https://github.com/user-attachments/assets/a8c4c9bf-009e-43d7-a50b-edf453d14ca2">
<img src="https://github.com/user-attachments/assets/0c904884-e28e-472b-8f03-60c100400443"> <BR>


# GDB Script:
For GDB usage you can see [GDB Usage](https://github.com/user-attachments/assets/0bdfe8f3-8ae8-426d-b634-68be87ab5075) video.
