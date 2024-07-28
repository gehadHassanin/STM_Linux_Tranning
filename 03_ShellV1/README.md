# How to use  
 
## Compilation
```
gcc commands.c femtoShell.c -o cmd` 
```
## Running 
```
./cmd 
```
<BR>The program will ask you to enter specified commands <BR> 
 
**NOTE** : Commands will be listed at the end of the file <BR> 
 
| command name | Description                                           | Args                    |  Example                  | 
| ------------ | -----------                                           | ----                    | ----------                | 
| help         | show list of supported commands                       |  no                     | help                      | 
| exit         | terminate shell                                       |  no                     | exit                      |
| pwd          | print working directory                               |  no                     | pwd                       | 
| cat          | show content of certain file                          |  filename               | cat file                  |
| echo         | print a user input string on stdout                   |  message                | echo "gehad" <BR>`or`<BR> echo gehad                  | 
| realpath          | print the resolved absolute path                            |  filePath <BR>`or`<BR> dirPath               | realpath filePath <BR>`or`<BR> realpath dirPath                   |
| cp           | copy a file to another file                           |  sourcePath, targetPath | cp  sourcePath targetPath |
| cp -a        | append the source content to the end of the target file |  sourcePath, targetPath | cp -a sourcePath targetPath |
| mv           | move a file to another place           |  sourcePath, targetPath | mv sourcePath targetPath |
| mv -f           | force overwriting the target file if exits            |  sourcePath, targetPath | mv -f sourcePath targetPath |
| rm          | remove files                          |  filesname               | rm file1 file2                   |
| rmdir          | remove directories                          |  filesname               | rmdir dir1 dir2                  |


## Example of the output: <BR>
<img src="https://github.com/user-attachments/assets/72a98ba6-0564-47f7-8ef8-07e920982a28">
<img src="https://github.com/user-attachments/assets/e825d27e-301e-481a-afc9-d87066536a2f">
<img src="https://github.com/user-attachments/assets/967dd6e5-4c2e-45f6-9742-5db76512dde1">
<img src="https://github.com/user-attachments/assets/907440f5-02ad-4916-bfaa-3274b211bbb1">
