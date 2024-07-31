#ifndef COMMANDS_H_
#define COMMANDS_H_

#define SIZE_HISTORY (1000)
#define SIZE_BUFF    (100)
#define MSG_SIZE     (100)
#define COMMAND_SIZE  (100)
#define BUFF_SIZE     (10)

#define STDIN  (0)
#define STDOUT (1)
#define STDERR (2)

#define TOK_NUM      (20)
#define NUM_PROCESS  (10)

#define COLON_DELIMETER (":")
#define SPACE_DELIMETER (" ")

typedef struct {
    pid_t pid__;
    int32_t status__;
    uint8_t __cmd[SIZE_BUFF];
}ProcessInfo_t;


typedef struct {
    ProcessInfo_t __info[SIZE_HISTORY];
    uint32_t top__;
}ProcessHist_t;

void ImplementEchoCommand(uint8_t *buff);
void ImplementCpCommand(uint8_t argc, uint8_t** argv);
void ImplementPwdCommand(uint8_t argc);
void ImplementCatCommand(uint8_t argc, uint8_t** argv);
void FindRealPath(uint8_t* file, uint8_t* pathBuf);
void RemoveFile(const uint8_t *pathname);
void RemoveDirectory(const uint8_t *pathname);
void ImplementMvCommand(uint8_t argc, uint8_t** argv);
void ChangeCurrentDirectory(uint8_t argc, uint8_t** argv);
void ImplementEnvCommand(uint8_t argc, uint8_t** argv);
void ImplementTypeCommand(uint8_t argc, uint8_t** argv);
int8_t Is_InternalCmd(uint8_t *cmd);
int8_t Is_ExternalCmd(const uint8_t *cmd);
uint32_t Get_Size(ProcessHist_t *pHistory);
void clear_screen(void) ;
void Push_Process(ProcessHist_t *pHistory, ProcessInfo_t *pInfo);
void Pop_Process(ProcessHist_t *pHistory, ProcessInfo_t *pInfo);
void Parsing(uint8_t command[], uint8_t *__token[], uint8_t *token_num);
static int8_t CheckFileInPath(const uint8_t* filePath);
static int8_t Is_File(const uint8_t* pathName);
static int8_t Is_Directory(const uint8_t* pathName);
static const uint8_t* Get_FileName(const uint8_t *path);

#endif /*COMMANDS_H_*/
