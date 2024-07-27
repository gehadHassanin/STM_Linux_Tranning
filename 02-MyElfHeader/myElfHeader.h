#ifndef MY_ELF_HEADER_H_
#define MY_ELF_HEADER_H_

#include <stdint.h>

#define IS_ELF_FILE() (elfHeader.e_ident[EI_MAG0] == 0x7f &&\
		       elfHeader.e_ident[EI_MAG1] == 'E'  &&\
		       elfHeader.e_ident[EI_MAG2] == 'L'  &&\
		       elfHeader.e_ident[EI_MAG3] == 'F') 

#define IS_VALID_CLASS() (elfHeader.e_ident[EI_CLASS] == ELFCLASS32 ||\
		          elfHeader.e_ident[EI_CLASS] == ELFCLASS64)

#define IS_VALID_DATA() (elfHeader.e_ident[EI_DATA] == ELFDATA2LSB ||\
		         elfHeader.e_ident[EI_DATA] == ELFDATA2MSB)

#define IS_VALID_OSAPI() (elfHeader.e_ident[EI_OSABI] >= ELFOSABI_SYSV &&\
		          elfHeader.e_ident[EI_OSABI] <= ELFOSABI_STANDALONE)      

#define IS_VALID_VERSION() (elfHeader.e_version == EV_CURRENT)

#define IS_VALID_MACHINE() (elfHeader.e_machine == EM_M32     || elfHeader.e_machine == EM_SPARC  ||\
		            elfHeader.e_machine == EM_386     || elfHeader.e_machine == EM_68K    ||\
			    elfHeader.e_machine == EM_88K     || elfHeader.e_machine == EM_860    ||\
			    elfHeader.e_machine == EM_MIPS    || elfHeader.e_machine == EM_PARISC ||\
			    elfHeader.e_machine == EM_AARCH64 || elfHeader.e_machine == EM_PPC    ||\
			    elfHeader.e_machine == EM_PPC64   || elfHeader.e_machine == EM_ARM    ||\
			    elfHeader.e_machine == EM_SPARCV9 || elfHeader.e_machine == EM_IA_64  ||\
			    elfHeader.e_machine == EM_X86_64  || elfHeader.e_machine == EM_VAX    ||\
			    elfHeader.e_machine == EM_SPARC32PLUS)
      
typedef enum {
   kFileType_NV,
   kClass_NV,
   kDataEncoding_NV,
   kOsApi_NV,
   kMachineType_NV,
   kFileVersion_NV,
   kSuccess,
}Error_t;

extern Elf64_Ehdr elfHeader;
void PrintElfHeader(FILE *file); 
static void PrintMagicNumber(void);
static void PrintFileClass(void);
static const uint8_t *RetOsApi(void);
static const uint8_t *RetMachineType(void);
static Error_t RetErrorType(void);

#endif /* MY_ELF_HEADER_H_ */
