#include "myls.h"

uint8_t strPer[10];
Entry_t entries[MAX_ENTRIES];
uint32_t numOfEntries = 0;

void ExecuteOption_l(const uint8_t* pathName) {   
    StoreEntries(pathName);
    int32_t cnt = 0;
    numOfEntries--;
    while (cnt++ < numOfEntries) {
        printf("%c%s %3u %s %s %10lu %s %s\n",
          entries[cnt].file_type,  
          entries[cnt].permission,
          entries[cnt].nlinks,
          entries[cnt].u_name,
          entries[cnt].g_name,
          entries[cnt].size,
          entries[cnt].timebuf,
          entries[cnt].e_name
        );    
    }
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

static int cmpstringp(const void *p1, const void *p2)
{
    //static int count = 0;
    return strcmp(*(const char **) p1, *(const char **) p2);
}

void StoreEntries(const uint8_t* pathName) {
    struct stat buf;
    DIR *dirp = opendir(pathName);
    if (chdir(pathName) == -1) {
        perror("chdir");
    }
    struct dirent *entry;
    while ((entry = readdir(dirp))!= NULL) {
        if (lstat(entry->d_name, &buf) < 0) {
           perror("Error in stat");
           exit(1);
        }

        // Get modification time
        strftime(entries[numOfEntries].timebuf, sizeof(entries[numOfEntries].timebuf), "%b %d %H:%M", localtime(&buf.st_mtime));

        entries[numOfEntries].file_type = GetFileType(entry->d_name);
        entries[numOfEntries].permission = GetPermission(entry->d_name);
        entries[numOfEntries].g_name = GetGroupName(entry->d_name);
        entries[numOfEntries].u_name = GetUserName(entry->d_name);
        entries[numOfEntries].nlinks = (long)buf.st_nlink;
        entries[numOfEntries].size = (long)buf.st_size; 

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
