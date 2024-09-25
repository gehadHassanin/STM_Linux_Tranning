#include "myls.h"

uint8_t strPer[10];
Entry_t entries[MAX_ENTRIES];
uint32_t numOfEntries = 0;
uint16_t option;

void DefaultPrinting(const uint8_t* pathName) {  
    StoreEntries(pathName);
    for (int32_t i = 0; i < numOfEntries; i++) {
        if (GET_BIT(option, kOpt_i)) {
            printf("%lu ", entries[i].inodeNum);
        }

        if (GET_BIT(option, kOpt_f)) {
            /* NO SORTING */
        } else if (GET_BIT(option, kOpt_t)) {
            qsort(entries, numOfEntries, sizeof(Entry_t), compare_mtime);
        } else if (GET_BIT(option, kOpt_u)) {
            qsort(entries, numOfEntries, sizeof(Entry_t), compare_atime);
        } else if (GET_BIT(option, kOpt_c)) {
            qsort(entries, numOfEntries, sizeof(Entry_t), compare_ctime);
        } else {
           qsort(entries, numOfEntries, sizeof(Entry_t), compare_name); 
        }

        if (!GET_BIT(option, kOpt_f) && !GET_BIT(option, kOpt_a)) {
            if (entries[i].e_name[0] == '.') {
                continue;
            }       
        }
        
        if (GET_BIT(option, kOpt_l) && !GET_BIT(option, kOpt_f)) {
            printf("%c%s %3u %s %s %10lu %s %s",
              entries[i].file_type,  
              entries[i].permission,
              entries[i].nlinks,
              entries[i].u_name,
              entries[i].g_name,
              entries[i].size,
              entries[i].timebuf,
              entries[i].e_name
            ); 
            if ((i + 1) < numOfEntries) {
                printf("\n");
            }
        } else {
            printf("%s  ", entries[i].e_nameWithoutsymlink);
        }

        if (GET_BIT(option, kOpt_1) && ((i + 1) < numOfEntries) && !GET_BIT(option, kOpt_l)) {
            printf("\n");
        }
    }
    printf("\n");
}

uint8_t GetFileType(const uint8_t* pathName) {
    struct stat buf;
    uint8_t fileType = '-';
    if (lstat(pathName, &buf) < 0){
       perror("Error in stat");
       exit(1);
    }
    if (S_ISFIFO(buf.st_mode)) {
        fileType = 'p';
    } else if (S_ISCHR(buf.st_mode)) {
        fileType = 'c';
    } else if (S_ISDIR(buf.st_mode)) {
       fileType = 'd'; 
    } else if (S_ISBLK(buf.st_mode)) {
       fileType = 'b'; 
    } else if (S_ISLNK(buf.st_mode)) {
       fileType = 'l'; 
    } else if (S_ISSOCK(buf.st_mode)) {
       fileType = 's'; 
    } else if (S_ISREG(buf.st_mode)) {
        fileType = '-';
    }
    return fileType;
}

uint8_t* GetGroupName(const uint8_t* pathName) {
    struct stat buf;
    if (lstat(pathName, &buf) < 0){
       perror("Error in stat");
       exit(1);
    }
    struct group *grp = getgrgid(buf.st_gid);
    grp->gr_name = (grp == NULL) ? NULL : grp->gr_name;  
    return grp->gr_name; 
}

uint8_t* GetUserName(const uint8_t* pathName) {
    struct stat buf;
    if (lstat(pathName, &buf) < 0){
       perror("Error in stat");
       exit(1);
    }
    struct passwd *usr = getpwuid(buf.st_uid);
    usr->pw_name = (usr == NULL) ? NULL : usr->pw_name;  
    return usr->pw_name; 
}

uint8_t* GetPermission(const uint8_t* pathName) {
    struct stat buf;
    if (lstat(pathName, &buf) < 0){
       perror("Error in stat");
       exit(1);
    }
    int32_t mode = buf.st_mode; 
    //owner  permissions
    strPer[0] = (mode & 0000400) == 0000400 ? 'r' : '-';
    strPer[1] = (mode & 0000200) == 0000200 ? 'w' : '-';
    strPer[2] = (mode & 0000100) == 0000100 ? 'x' : '-';
    //group permissions
    strPer[3] = (mode & 0000040) == 0000040 ? 'r' : '-';
    strPer[4] = (mode & 0000020) == 0000020 ? 'w' : '-';
    strPer[5] = (mode & 0000010) == 0000010 ? 'x' : '-';
    //others  permissions
    strPer[6] = (mode & 0000004) == 0000004 ? 'r' : '-';
    strPer[7] = (mode & 0000002) == 0000002 ? 'w' : '-';
    strPer[8] = (mode & 0000001) == 0000001 ? 'x' : '-';
    //special  permissions
    strPer[2] = (mode & 0004000) == 0004000 ? 's' : strPer[2];
    strPer[5] = (mode & 0002000) == 0002000 ? 's' : strPer[5];
    strPer[8] = (mode & 0001000) == 0001000 ? 't' : strPer[8];
    strPer[9] = '\0';
    return strPer;
}

void StoreEntries(const uint8_t* pathName) {
    struct stat buf;
    numOfEntries = 0;
    struct dirent *entry;
    DIR *dirp = opendir(pathName);
    if (chdir(pathName) == -1) {
        perror("chdir");
    }
    while ((entry = readdir(dirp)) != NULL) {
        //printf("%s\n", entry->d_name);
        if (lstat(entry->d_name, &buf) < 0) {
           perror("Error in stat");
           exit(1);
        }

        // Get modification time
        strftime(entries[numOfEntries].timebuf, sizeof(entries[numOfEntries].timebuf), 
            "%b %d %H:%M", localtime(&buf.st_mtime));

        entries[numOfEntries].file_type = GetFileType(entry->d_name);
        entries[numOfEntries].permission = GetPermission(entry->d_name);
        entries[numOfEntries].g_name = GetGroupName(entry->d_name);
        entries[numOfEntries].u_name = GetUserName(entry->d_name);
        entries[numOfEntries].nlinks = (long)buf.st_nlink;
        entries[numOfEntries].size = (long)buf.st_size; 
        entries[numOfEntries].inodeNum = (long)buf.st_ino;
        entries[numOfEntries].ctime = buf.st_ctime;
        entries[numOfEntries].mtime = buf.st_mtime;
        entries[numOfEntries].atime = buf.st_atime;
        entries[numOfEntries].e_nameWithoutsymlink = entry->d_name;

        if (GetFileType(entry->d_name) == 'l') {
            uint8_t linkname[1024];
            ssize_t len;
            // Get the target of the symbolic link
            if ((len = readlink(entry->d_name, linkname, sizeof(linkname)-1)) != -1) {
                linkname[len] = '\0'; 
            } else {
                perror("readlink");
            }
            entries[numOfEntries].e_name = entry->d_name;
            strcat(entries[numOfEntries].e_name, " -> ");
            strcat(entries[numOfEntries].e_name, linkname);

        } else {
            entries[numOfEntries].e_name = entry->d_name;
        }
        numOfEntries++;
    }
}

int32_t compare_name(const void *a, const void *b) {
    Entry_t *p1 = (Entry_t *)a;
    Entry_t *p2 = (Entry_t *)b;

	uint8_t str1[strlen(p1->e_name)];
	uint8_t str2[strlen(p2->e_name)];
	
	strcpy(str1, p1->e_name);
	strcpy(str2, p2->e_name);
	
	for (int32_t i = 0; str1[i] != '\0'; i++) {
		str1[i] = tolower(str1[i]);
        str2[i] = tolower(str2[i]);
	}

	return strcoll( str1 ,  str2); 
}

int32_t compare_ctime(const void *a, const void *b) {
    Entry_t *p1 = (Entry_t *)a;
    Entry_t *p2 = (Entry_t *)b;
    if (p1->ctime > p2->ctime) {
        return -1;
    } else if (p1->ctime < p2->ctime) {
        return 1;
    } else {
        return 0;
    }   
}

int32_t compare_mtime(const void *a, const void *b) {
    Entry_t *p1 = (Entry_t *)a;
    Entry_t *p2 = (Entry_t *)b;
    if (p1->mtime > p2->mtime) {
        return -1;
    } else if (p1->mtime < p2->mtime) {
        return 1;
    } else {
        return 0;
    }       
}

int32_t compare_atime(const void *a, const void *b) {
    Entry_t *p1 = (Entry_t *)a;
    Entry_t *p2 = (Entry_t *)b;
    if (p1->atime > p2->atime) {
        return -1;
    } else if (p1->atime < p2->atime) {
        return 1;
    } else {
        return 0;
    } 
}