#ifndef MY_SECTION_HEADER_H_
#define MY_SECTION_HEADER_H_

void PrintSectionHeaders(FILE *file);
static const uint8_t *RetSectionType(Elf64_Shdr *sectionHeaders, int32_t iterator);
static const uint8_t *RetFlagType(Elf64_Shdr *sectionHeaders, int32_t iterator);
#endif /*MY_SECTION_HEADER_H_*/
