#include <stdint.h>
#include "param.h"

typedef struct inode {
    uint32_t size;                                  // 文件大小
    uint16_t file_type;                             // 文件类型（文件/文件夹）
    uint16_t link;                                  // 连接数
    uint32_t block_point[BLOCK_NUMBER_IN_INODE];    // 数据块指针
}inode;