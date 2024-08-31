#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SECTOR_SIZE 512
#define PARTITION_TABLE_SIZE 66 
#define BOOTSTRAP_CODE_AREA 446
#define NUM_PARTITIONS 4
#define EXTENDED 0x05

typedef struct {
    uint8_t status;
    uint8_t first_chs[3];
    uint8_t partitionType;
    uint8_t last_chs[3];
    uint32_t lba;
    uint32_t sectorCount;
} PartitionEntry_t;

int main(int argc, char **argv) {
    uint8_t buff[SECTOR_SIZE];
    int fd;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <device>\n", argv[0]);
        return 1;
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("Error opening device");
        return 1;
    }

    if (read(fd, buff, SECTOR_SIZE) != SECTOR_SIZE) {
        perror("Error reading sector");
        close(fd);
        return 1;
    }

    close(fd);

    PartitionEntry_t *pPartitionEntry = (PartitionEntry_t *) &buff[BOOTSTRAP_CODE_AREA];

    printf("%-10s %-5s %-10s %-10s %-10s %-10s %-10s\n",
           "Device", "Boot", "Start", "End", "Sectors", "Size (MB)", "Id");

    for (int iterator = 0; iterator < NUM_PARTITIONS; iterator++) {
        if (pPartitionEntry[iterator].partitionType == 0) {
            continue; // Skip empty entries
        }

        uint64_t sizeInMB = ((uint64_t) pPartitionEntry[iterator].sectorCount * SECTOR_SIZE) / (1024 * 1024);

        printf("%s%-3d %-5c %-10u %-10u %-10u %-10u %-10X\n",
               argv[1],
               iterator + 1,
               pPartitionEntry[iterator].status == 0x80 ? '*' : ' ',
               pPartitionEntry[iterator].lba,
               pPartitionEntry[iterator].lba + pPartitionEntry[iterator].sectorCount - 1,
               pPartitionEntry[iterator].sectorCount,
               (uint32_t) ((uint64_t) pPartitionEntry[iterator].sectorCount * SECTOR_SIZE) / (1024 * 1024),
               pPartitionEntry[iterator].partitionType);

        if (pPartitionEntry[iterator].partitionType == EXTENDED) {
            // ReadExtended(argv, pPartitionEntry[iterator].lba); 
        }
    }

    return 0;
}
