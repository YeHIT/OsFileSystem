#include <stdint.h>
#include "param.h"

typedef struct super_block {
    int32_t magic_num;                              // 幻数
    int32_t free_block_count;                       // 空闲数据块数
    int32_t free_inode_count;                       // 空闲inode数
    int32_t dir_inode_count;                        // 目录inode数
    uint32_t block_map[BLOCK_MAP_LENGTH];           // 数据块占用位图
    uint32_t inode_map[INODE_MAP_LENGTH];           // inode占用位图
} sp_block;
