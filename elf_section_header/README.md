# ELF Header and Section Header Implementation
The program provides an implementation of parsing and handling ELF (Executable and Linkable Format) headers and section headers

ELF is a common file format for executables, object code, shared libraries, and core dumps. 

This implementation focuses on reading, interpreting, and displaying information from the ELF headers and section headers.

## Elf Header
The ELF header contains important information about the structure and properties of the ELF file. The following fields are typically included in the ELF header:

* **Magic Number**: Identifies the file as an ELF file.
* **Class**: Specifies whether the file is 32-bit or 64-bit.
* **Data**: Specifies the endianness (little or big).
* **Version**: Specifies the ELF version.
* **OS/ABI**: Identifies the target operating system and ABI.
* **ABI Version**: Specifies the ABI version.
* **Type**: Identifies the object file type (e.g., executable, shared object).
* **Machine**: Specifies the target architecture.
* **Entry Point**: The address where the execution starts.
* **Program Header Offset**: The offset to the program header table.
* **Section Header Offset**: The offset to the section header table.
* **Flags**: Processor-specific flags.
* **Header Size**: The size of the ELF header.
* **Program Header Size**: The size of a program header entry.
* **Program Header Count**: The number of entries in the program header table.
* **Section Header Size**: The size of a section header entry.
* **Section Header Count**: The number of entries in the section header table.
* **Section Header String Table Index**: The index of the section header string table.

## Section Header
The section header table contains entries that describe each section in the ELF file. Each section header typically includes the following fields:

* **Name**: The name of the section.
* **Type**: The type of the section.
* **Flags**: Attributes of the section.
* **Address**: The virtual address of the section in memory.
* **Offset**: The offset of the section in the file.
* **Size**: The size of the section.
* **Link**: A link to another section.
* **Info**: Additional section-specific information.
* **Address Alignment**: The alignment of the section.
* **Entry Size**: The size of entries, if the section contains a table.

**NOTE** : Implementation of section header don't work successfully, I really don't know why

## How to use  
 
### Compilation 
`gcc Header.c myElfHeader.c mySectionHeader.c -o Header` 
 
### Running 
**There are two options [-h] [-S]** <BR> <BR>
**To print elf header**: <BR>
`./Header elfFile -h`<BR>

**To print section header**: <BR>
`./Header elfFile -S`<BR>

## Examble of the output:
<img src="https://github.com/user-attachments/assets/a963f642-2a5e-49da-9244-dc031b7e5897">
