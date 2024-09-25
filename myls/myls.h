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
#include <locale.h>
#include <ctype.h>

#define SET_BIT(val, num) (val |= (1 << num))
#define GET_BIT(val, num) ((val & (1 << num)) >> num)
#define MAX_ENTRIES (5000)

typedef enum {
    kOpt_l,
    kOpt_a,
    kOpt_t,
    kOpt_u,
    kOpt_c,
    kOpt_i,
    kOpt_f,
    kOpt_d,
    kOpt_1,
} Option_t;

typedef struct {
    uint8_t* g_name;
    uint8_t* u_name;
    uint8_t* e_name;
    uint8_t* e_nameWithoutsymlink;
    uint8_t* permission;
    uint8_t file_type;
    uint8_t timebuf[80];
    uint32_t nlinks;
    uint64_t inodeNum;
    uint64_t size;
    time_t ctime;
    time_t mtime;
    time_t atime;
}Entry_t;

uint8_t* GetGroupName(const uint8_t* pathName);
uint8_t* GetUserName(const uint8_t* pathName);
uint8_t* GetPermission(const uint8_t* pathName);
uint8_t GetFileType(const uint8_t* pathName);
void ExecuteOption_l(const uint8_t* pathName);
void StoreEntries(const uint8_t* pathName);
void DefaultPrinting(const uint8_t* pathName);
int32_t compare_name(const void *a, const void *b);
int32_t compare_ctime(const void *a, const void *b);
int32_t compare_mtime(const void *a, const void *b);
int32_t compare_atime(const void *a, const void *b);

#endif  // MYLS_H_