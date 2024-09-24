#ifndef MYLS_H_
#define MYLS_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

#define MAX_ENTRIES (5000)
typedef struct {
    uint8_t* g_name;
    uint8_t* u_name;
    uint8_t* e_name;
    uint8_t* permission;
    uint8_t file_type;
    uint8_t timebuf[80];
    uint32_t nlinks;
    uint64_t size;
}Entry_t;

uint8_t* GetGroupName(const uint8_t* pathName);
uint8_t* GetUserName(const uint8_t* pathName);
uint8_t* GetPermission(const uint8_t* pathName);
uint8_t GetFileType(const uint8_t* pathName);
void ExecuteOption_l(const uint8_t* pathName);
void StoreEntries(const uint8_t* pathName);

#endif  // MYLS_H_