
#include <stdio.h>
#include <stdint.h>
#include <elf.h>
#include "myElfHeader.h"

const uint8_t *fileType[] = {
   "REL (Relocatable file)",
   "EXEC (Executable file)",
   "DYN (Position-Independent Executable file)",
   "CORE (Core file)",
};

const uint8_t *dataEncoding[] = {
   "2's complement, little endian",
   "2's complement, big endian",
};

const uint8_t *messageError[] = {
    "Invalid file type",
    "Invalid class",
    "Invalid data encoding",
    "Invalid OS ABI identification",
    "Invalid machine type",
    "Invalid file version",
};

/*Global variable of Elf64_Ehdr type*/
Elf64_Ehdr elfHeader;

void PrintElfHeader(FILE *file) {
   size_t bytesRead =  fread(&elfHeader, sizeof(elfHeader), 1, file);

   if (RetErrorType() != kSuccess) {
        printf("%s\n", messageError[RetErrorType()]);
        fclose(file);
       // return 0;
   }

   printf("ELF Header:\n");
   PrintMagicNumber();
   PrintFileClass();
   printf("  Data:                              %s\n",dataEncoding[1 - elfHeader.e_ident[EI_DATA]]);
   printf("  Version:                           %u (current)\n", elfHeader.e_version);
   printf("  OS/ABI:                            %s\n", RetOsApi());
   printf("  ABI Version:                       %hhu\n", elfHeader.e_ident[EI_ABIVERSION]);
   printf("  Type:                              %s\n", fileType[elfHeader.e_type - 1]);
   printf("  Machine:                           %s\n", RetMachineType());
   printf("  Version:                           0x%x\n", elfHeader.e_version);
   printf("  Entry point address:               0x%lx\n", elfHeader.e_entry);
   printf("  Start of program headers:          %lu (bytes into file)\n", elfHeader.e_phoff);
   printf("  Start of section headers:          %lu (bytes into file)\n", elfHeader.e_shoff);
   printf("  Flags:                             0x%x\n", elfHeader.e_flags);
   printf("  Size of this header:               %hu (bytes)\n", elfHeader.e_ehsize);
   printf("  Size of program headers:           %hu (bytes)\n", elfHeader.e_phentsize);
   printf("  Number of program headers:         %hu\n", elfHeader.e_phnum);
   printf("  Size of section headers:           %hu (bytes)\n", elfHeader.e_shentsize);
   printf("  Number of section headers:         %hu\n", elfHeader.e_shnum);
   printf("  Section header string table index: %hu\n", elfHeader.e_shstrndx);
}

void PrintMagicNumber(void) {
   printf("  Magic:   ");
   for (uint8_t iterator = 0; iterator < EI_NIDENT; iterator++) {
	printf("%02x ", elfHeader.e_ident[iterator]);
   }
}

void PrintFileClass(void) {
   if (elfHeader.e_ident[EI_CLASS] == ELFCLASS32) {
        printf("\n  Class:                             ELF32\n");
   } else if (elfHeader.e_ident[EI_CLASS] == ELFCLASS64) {
	printf("\n  Class:                             ELF64\n");
   }   
}

const uint8_t *RetOsApi(void) {
   switch(elfHeader.e_ident[EI_OSABI]) {
	case ELFOSABI_SYSV: return "UNIX - System V";
	case ELFOSABI_HPUX: return "HP-UX";
	case ELFOSABI_NETBSD: return "NetBSD";
	case ELFOSABI_GNU: return "UNIX - GNU";
        case ELFOSABI_SOLARIS: return "Sun Solaris";
	case ELFOSABI_AIX: return "IBM AIX";
        case ELFOSABI_IRIX: return "SGI Irix";
        case ELFOSABI_FREEBSD: return "FreeBSD";
	case ELFOSABI_TRU64: return "Compaq TRU64 UNIX";
	case ELFOSABI_MODESTO: return "Novell Modesto";
	case ELFOSABI_OPENBSD: return "OpenBSD";
	case ELFOSABI_ARM_AEABI: return "ARM EABI";
	case ELFOSABI_ARM: return "ARM";
	case ELFOSABI_STANDALONE: return "Standalone (embedded) application";
	default: ;  	       
   }
}

const uint8_t *RetMachineType(void) {
   switch(elfHeader.e_machine) {
        case EM_M32: return "AT&T WE 32100";
        case EM_SPARC: return "SPARC";
        case EM_386: return "Intel 80386";
        case EM_68K: return "Motorola 68000 (M68k)";
        case EM_88K: return "Motorola 88000 (M88k)";
        case EM_860: return "Intel 80860";
        case EM_MIPS: return "MIPS RS3000";
        case EM_PARISC: return "HP/PA";
        case EM_SPARC32PLUS: return "SPARC with enhanced instruction set";
        case EM_PPC: return "PowerPC";
        case EM_PPC64: return "PowerPC 64-bit";
        case EM_ARM: return "ARM";
        case EM_SPARCV9: return "SPARC v9 64-bit";
        case EM_IA_64: return "Intel Itanium";
        case EM_X86_64: return "Advanced Micro Devices x86-64";
        case EM_VAX: return "DEC Vax";
        case EM_AARCH64: return "ARM AArch64";
        // Add more machine types as needed
        default: ;
   }	   
}

Error_t RetErrorType(void) {
   if (!IS_ELF_FILE()) {
	return kFileType_NV;
   } else if (!IS_VALID_CLASS()) {
	return kClass_NV;
   } else if (!IS_VALID_DATA()) {
	return kDataEncoding_NV;
   } else if (!IS_VALID_OSAPI()) {
        return kOsApi_NV;
   } else if (!IS_VALID_VERSION()) {
	return kFileVersion_NV;
   } else if (!IS_VALID_MACHINE()) {
	return kMachineType_NV;
   } else {
	return kSuccess;
   }
}
