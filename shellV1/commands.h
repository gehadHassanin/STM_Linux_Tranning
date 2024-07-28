#ifndef COMMANDS_H_
#define COMMANDS_H_

void ImplementEchoCommand(uint8_t *buff);
void ImplementCpCommand(uint8_t argc, uint8_t** argv);
void ImplementPwdCommand(uint8_t argc);
void ImplementCatCommand(uint8_t argc, uint8_t** argv);
void FindRealPath(uint8_t* file, uint8_t* pathBuf);
void RemoveFile(const uint8_t *pathname);
void RemoveDirectory(const uint8_t *pathname);
void ImplementMvCommand(uint8_t argc, uint8_t** argv);
static int8_t CheckFileInPath(const uint8_t* filePath);
static int8_t Is_File(const uint8_t* pathName);
static int8_t Is_Directory(const uint8_t* pathName);
static const uint8_t* Get_FileName(const uint8_t *path);
#endif /*COMMANDS_H_*/
