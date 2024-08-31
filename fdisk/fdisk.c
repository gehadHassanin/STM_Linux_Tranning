#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>


#define SECTOR_SIZE (512)
#define PARTITION_TABLE_SIZE (66) 
#define BOOTSTRAP_CODE_AREA (446)
#define NUM_PARTITIONS (4)
#define EXTENDED (0x05)
typedef struct {
    uint8_t status;
    uint8_t first_chs[3];
    uint8_t partitionType;
    uint8_t last_chs[3];
    uint32_t lba;
    uint32_t sectorCount;
}PartitionEntry_t;

int main(int argc, char** argv) {
    uint8_t buff[PARTITION_TABLE_SIZE];
    int32_t fd;
    if (argc == 2) {
        if ((fd = open(argv[1], O_RDONLY) == -1)) {
            perror("open");
        }
    } else {
        perror("argc");
    }

    off_t offset = lseek(fd, BOOTSTRAP_CODE_AREA, SEEK_SET);
    ssize_t bytes = read(fd, buff, PARTITION_TABLE_SIZE);
    if (bytes != PARTITION_TABLE_SIZE) {
        perror("read");
    }

    PartitionEntry_t *pPartitionEntry = buf;

    printf("%-5s %-10s        %-10s %-10s %-10s %-10s %-10s %-10s\n",
	   "Device", "Boot", "Start", "End", "Sectors", "Size", "Id",
	   "Type");

    for (int32_t iterator = 0; iterator < NUM_PARTITIONS; iterator++) {
        if (pPartitionEntry[i].partitionType == 0) {
            continue; // Skip empty entries
        }
        printf("%s%-5d %-10c %-10u %-10u %-10u %uM      %-10X\n",
            argv[1],
            iterator + 1,
            pPartitionEntry[i].status == 0x80 ? '*' : ' ';
            pPartitionEntry[i].lba,
	        pPartitionEntry[i].lba + pPartitionEntry[i].sectorCount - 1, 
            pPartitionEntry[i].sectorCount,
            (uint32_t) (((uint64_t) pPartitionEntry[i].sectorCount *
			    512) / (1024 * 1024 * 1024)),
            pPartitionEntry[i].partitionType);

	    if (pPartitionEntry[i].partitionType == EXTENDED) {              
	        ReadExtended(argv, pPartitionEntry[i].lba);
	    }   
    }

    return 0;
}