#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include "mySectionHeader.h"

void PrintSectionHeaders(FILE *file) {
   /*Read elf header*/
   Elf64_Ehdr elfHeader;
   size_t bytesRead = fread(&elfHeader, sizeof(elfHeader), 1, file);
   /*Read section header table*/
   Elf64_Shdr *sectionHeaders = (Elf64_Shdr *)malloc(elfHeader.e_shentsize * elfHeader.e_shnum);
   fseek(file, elfHeader.e_shoff, SEEK_SET);
   bytesRead = fread(sectionHeaders, elfHeader.e_shentsize, elfHeader.e_shnum, file);
   /*Read string table section*/
   uint8_t *stringTable = (uint8_t *)malloc(sectionHeaders[elfHeader.e_shstrndx].sh_size);
   fseek(file, sectionHeaders[elfHeader.e_shstrndx].sh_offset, SEEK_SET);   
   bytesRead = fread(stringTable, sectionHeaders[elfHeader.e_shstrndx].sh_size, 1, file);

   printf("Section Headers:\n");
   printf("  [Nr] Name              Type             Address           Offset\n");
   printf("       Size              EntSize          Flags  Link  Info  Align\n");
   for (int32_t iterator = 0; iterator < elfHeader.e_shnum; iterator++) {
	printf("  [%2d] %-17s %-16s %016lx  %08lx\n",	
			iterator, 
			stringTable + sectionHeaders[iterator].sh_name,
	                RetSectionType(sectionHeaders, iterator),
	                sectionHeaders[iterator].sh_addr,
			sectionHeaders[iterator].sh_offset);

	printf("       %016lx  %016lx %3s %7u %5u %5lu\n",
			sectionHeaders[iterator].sh_size,
			sectionHeaders[iterator].sh_entsize,
			RetFlagType(sectionHeaders, iterator),
			sectionHeaders[iterator].sh_link,
			sectionHeaders[iterator].sh_info,
			sectionHeaders[iterator].sh_addralign);

   }
   free(sectionHeaders);
   free(stringTable);
}

const uint8_t *RetSectionType(Elf64_Shdr *sectionHeaders, int32_t iterator) {
   switch (sectionHeaders[iterator].sh_type) {
	case SHT_NULL:
		{	
		   	return "NULL";
		}
        case SHT_PROGBITS:
		{
		   	return "PROGBITS";
		}
	case SHT_SYMTAB:
		{
		   	return "SYMTAB";
		}
	case SHT_STRTAB:
		{
		   	return "STRTAB";
		}
	case SHT_RELA:
		{
			return "RELA";
		}
	case SHT_HASH:
		{
			return "HASH";
		}
	case SHT_DYNAMIC:
		{	
			return "DYNAMIC";
		}
	case SHT_NOTE:
		{
			return "NOTE";
		}
	case SHT_NOBITS:
		{
			return "NOBITS";
		}
	case SHT_REL:
		{
			return "REL";
		}
	case SHT_SHLIB:
		{
			return "SHLIB";
		}
	case SHT_DYNSYM:
		{
			return "DYNSYM";
		}
	case SHT_LOUSER:
		{
			return "LOUSER";
		}
	case SHT_HIUSER:
		{
			return "HIUSER";
		}
	case SHT_LOPROC:
		{
			return "LOPROC";
		}
	case SHT_HIPROC:
		{
			return "HIPROC";
		}
	default:
		{
			;
		}
   }
}

const uint8_t *RetFlagType(Elf64_Shdr *sectionHeaders, int32_t iterator) {
   switch (sectionHeaders[iterator].sh_flags) {
	case SHF_WRITE:
		{
			return "WA";
		}
        case SHF_ALLOC:
		{
			return "A";
		}
        case SHF_EXECINSTR:
		{
			return "AX";
		}
        case SHF_MASKPROC:
		{
			return "MS"; 
		}
        default:
		{	
			return " " ;
		}
   }
}

