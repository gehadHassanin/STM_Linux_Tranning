#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "commands.h"
#include <limits.h>

#define SIZE_BUFF (100)
#define STDOUT    (1)

void ImplementPwdCommand(uint8_t argc) {
        uint8_t buff[PATH_MAX];
        ssize_t bytes = 0;
        if (argc == 1 && getcwd(buff, PATH_MAX) != NULL) {
                bytes = write(STDOUT, buff, strlen(buff));
                bytes = write(STDOUT, "\n", 1);
                if (bytes == -1) {
                        perror("pwd: write");
                } else if (getcwd(buff, PATH_MAX) == NULL) {
                        perror("pwd: error");
                } else if (argc > 1) {
                        perror("pwd: argc");
                }
        }
}

void ImplementEchoCommand(uint8_t *buff) {
        ssize_t bytes = 0;
        bytes = write(STDOUT, buff, strlen(buff));
	bytes = write(STDOUT, "\n", 1);
        if (bytes == -1) {
                perror("pwd: write");
        }
}

void ImplementCatCommand(uint8_t argc, uint8_t** argv) {
        uint8_t buff[SIZE_BUFF];
        ssize_t bytesW = 0;
        ssize_t bytesR = 0;

        if (argc == 2) {
                int32_t fd = open(argv[1], O_RDONLY);
                if (fd == -1) {
                        perror("cat: open");
                }

                do{
                        bytesR = read(fd, buff, 100);
                        bytesW = write(STDOUT, buff, bytesR);
                        if (fd != -1 && bytesW == -1) {
                                perror("cat: write");
                                break;
                        }        
                        uint8_t sourcePath[PATH_MAX];
                        uint8_t distinationPath[PATH_MAX];
                }while(bytesR != 0);
                close(fd);
        } else {
                perror("cat: argc");
        }
}

void ImplementCpCommand(uint8_t argc, uint8_t** argv) {
        ssize_t bytes = 0;
        uint8_t buff[100];
        ssize_t size = 0;
	int32_t desFlags = 0;
	int32_t fd_S = 0;
	int32_t fd_D = 0;
	uint8_t sourcePath[PATH_MAX];
	uint8_t distinationPath[PATH_MAX];

        desFlags = (argc == 3)  ? (O_CREAT | O_WRONLY) : 
		                  (O_CREAT | O_APPEND | O_WRONLY);
        
	if (argc == 3 || (argc == 4 && !strcmp(argv[1], "-a"))) {
                FindRealPath(argv[argc - 2], sourcePath);
                FindRealPath(argv[argc - 1], distinationPath);

                if (!strcmp(distinationPath, sourcePath)) {
                        fprintf(stderr, "cp: '%s' and '%s' are the same file\n", argv[argc - 2], argv[argc - 1]);

                } else if (!Is_File(distinationPath)) {
			strcat(distinationPath, "/");
			strcat(distinationPath, Get_FileName(sourcePath));
		}

		fd_S = open(sourcePath, O_RDONLY);
		fd_D = open(distinationPath, desFlags, S_IRWXU);

	} else {
		perror("cp: argc");
	}

        if (fd_S == -1) {
                perror("cp: open source");
		close(fd_D);
                close(fd_S);
        }

        if (fd_D == -1) {
                perror("cp: open destination");
                close(fd_D);
                close(fd_S);
        }

        do{
                size = read(fd_S, buff, 100);
                if (size == -1) {
                        perror("cp: read");
                        close(fd_S);
                        close(fd_D);
                        break;
                }
                bytes = write(fd_D, buff, size);
                if (bytes == -1) {
                        perror("cp: write");
                        close(fd_S);
                        close(fd_D);
                        break;
                }
        }while (size != 0);

        close(fd_S);
        close(fd_D); 
}

void ImplementMvCommand(uint8_t argc, uint8_t** argv) {
        uint8_t sourcePath[PATH_MAX];
        uint8_t distinationPath[PATH_MAX];

	FindRealPath(argv[argc - 2], sourcePath);
	realpath(argv[argc - 1], distinationPath);
        
	if (argc == 3 || (argc == 4 && !strcmp(argv[1], "-f"))) {
		if (!strcmp(distinationPath, sourcePath)) {
                	fprintf(stderr, "cp: '%s' and '%s' are the same file\n", argv[argc - 2], argv[argc - 1]);

        	} else if (Is_File(distinationPath) == 0 && Is_Directory(distinationPath) == 1) {
                	strcat(distinationPath, "/");
               		strcat(distinationPath, Get_FileName(sourcePath));
		}
		
		if (argc == 3 && CheckFileInPath(distinationPath) == 0 && strcmp(distinationPath, sourcePath) != 0) {
			perror("mv");
		} else {
			if (rename(sourcePath, distinationPath) == -1) {
               			perror("mv");
			}
       		}
	} else {
		perror("mv: argc");
	}
}

void FindRealPath(uint8_t* file, uint8_t* pathBuf) {
	if(realpath(file, pathBuf) == NULL) {
		perror("realPath");
	}
}

void RemoveFile(const uint8_t *pathname) {
        if (Is_Directory(pathname) == 1 && Is_File(pathname) == 0) {
                fprintf(stderr, "rm: cannot remove '%s': Is a directory\n", pathname);
        } else if (Is_Directory(pathname) != 1 && Is_File(pathname) != 1) {
                fprintf(stderr, "rm: cannot remove '%s': No such file or directory\n", pathname);
        } else if (unlink(pathname) == -1) {
                perror("rm");
        }
}

void RemoveDirectory(const uint8_t *pathname) {
        if (Is_Directory(pathname) == 0 && Is_File(pathname) == 1) {
                fprintf(stderr, "rmdir: failed to remove '%s': Not a directory\n", pathname);
        } else if (Is_Directory(pathname) != 1 && Is_File(pathname) != 1) {
                fprintf(stderr, "rmdir: cannot remove '%s': No such file or directory\n", pathname);
        } else if (rmdir(pathname) == -1) {
                perror("rmdir");
        }
}

int8_t Is_File(const uint8_t* pathName) {
	struct stat statBuf;
	if(stat(pathName, &statBuf) == -1) {
		return -1;
        }
	if ((S_ISREG(statBuf.st_mode))) {
		return 1;
	} else {
		return 0;
	}
}

int8_t Is_Directory(const uint8_t *pathName) {
        struct stat statBuf;
        if(stat(pathName, &statBuf) == -1) {
                return -1;
        }
        if ((S_ISDIR(statBuf.st_mode))) {
                return 1;
        } else {
                return 0;
        }
}

const uint8_t* Get_FileName(const uint8_t *path) {
    const uint8_t *file_name = strrchr(path, '/');
    if (file_name) {
        file_name++;
    } else {
        file_name = path;
    }
    return file_name;
}

int8_t CheckFileInPath(const uint8_t* filePath) {
    return access(filePath, F_OK) != -1 ? 0 : -1;
}
