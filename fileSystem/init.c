#include "init.h"

void initSuperBlock(){
    sp_block target_sp_block;
    target_sp_block.magic_num = MAGIC_NUMBER;                  // 幻数
    target_sp_block.free_block_count = MAX_BLOCK_NUMBER;       // 空闲数据块数
    target_sp_block.free_inode_count = MAX_INODE_NUMBER;       // 空闲inode数
    target_sp_block.dir_inode_count = 0;                       // 目录inode数
    for(int i = 0 ; i < BLOCK_MAP_LENGTH; i++){
        target_sp_block.block_map[i] = 0;                      // 数据块占用位
    }
    for(int i = 0 ; i < INODE_MAP_LENGTH; i++){
        target_sp_block.inode_map[i] = 0;                      // inode占用位图
    }
    // 将当前数据写入磁盘
    writeSpBlockInfo(&target_sp_block);
}

void initInodes(){
    inode inodes[MAX_INODE_NUMBER];
    for(int i = 0 ; i < MAX_INODE_NUMBER; i++){
        inodes[i].size = 0;
        inodes[i].file_type = 0;
        inodes[i].link = 0;
        for(int j = 0 ; j < BLOCK_NUMBER_IN_INODE; j++){
            inodes[i].block_point[j] = 0;
        }
        writeInodeInfo(&inodes[i],i);
    }
}

void initDataBlocks(){
    dirent item[MAX_BLOCK_NUMBER];
    for(int i = 0; i < MAX_BLOCK_NUMBER ; i++){
        item[i].inode_id = 0;
        item[i].valid = 0;
        item[i].type = UNUSED_TYPE;
        for(int j = 0; j < MAX_NAME_LENGTH; j++){
            item[i].name[j] = 0;
        }
        writeDirentInfo(&item[i],i);
    }
}


void initRootDir(){
    //修改超级块
    sp_block super_block;
    readSpBlockInfo(&super_block);
    super_block.dir_inode_count++;
    super_block.free_block_count--;
    super_block.free_inode_count--;
    super_block.inode_map[0] = 1;
    super_block.block_map[0] = 1;
    writeSpBlockInfo(&super_block);
    //修改inode
    inode root_inode;
    readInodeInfo(&root_inode,ROOT_INODE);
    root_inode.size = 0;
    root_inode.file_type = DIR_TYPE;
    root_inode.block_point[0] = 1;
    writeInodeInfo(&root_inode,ROOT_INODE);
}



void initFileSystem(){
    initSuperBlock();
    initInodes();
    initDataBlocks();
    initRootDir();
    return;
}