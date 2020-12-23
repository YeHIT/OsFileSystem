#include "util.h"

uint32_t bit_map[32];


void writeSpBlockInfo(sp_block *super_block){
    open_disk();
    disk_write_block(0,(char *) super_block);
    disk_write_block(1,(char *) super_block + DEVICE_BLOCK_SIZE);
    close_disk();
}

void writeInodeInfo(inode *inode_block,int inumber){
    char * inode_str = (char*) inode_block;
    int start_index = 2 + inumber / INODE_DIV;
    int offset = inumber % INODE_DIV;
    int true_offset = offset * sizeof(inode);
    open_disk();
    char temp_buf[DEVICE_BLOCK_SIZE];
    disk_read_block(start_index,temp_buf);
    //拷贝值
    for(int i = 0 ; i < sizeof(inode); i++){
        temp_buf[i + true_offset] = inode_str[i];
    }
    disk_write_block(start_index,temp_buf);
    close_disk();
}

void writeDirentInfo(dirent *dirent_block,int dnumber){
    char * dirent_str = (char*) dirent_block;
    int start_index = ROOT_BLOCK + dnumber / DATA_DIV;
    int offset = dnumber % DATA_DIV;
    int true_offset = offset * sizeof(dirent);
    open_disk();
    char temp_buf[DEVICE_BLOCK_SIZE];
    disk_read_block(start_index,temp_buf);
    //拷贝值
    for(int i = 0 ; i < sizeof(inode); i++){
        temp_buf[i + true_offset] = dirent_str[i];
    }
    disk_write_block(start_index,temp_buf);
    close_disk();
}

void readSpBlockInfo(sp_block * super_block){
    char * sp_str = (char *)super_block;
    char temp_buf[DEVICE_BLOCK_SIZE];
    open_disk();
    disk_read_block(0,sp_str);
    disk_read_block(1,temp_buf);

    for(int i = 0 ; i < sizeof(sp_block) - DEVICE_BLOCK_SIZE; i++){
        sp_str[i + DEVICE_BLOCK_SIZE] = temp_buf[i];
    }
    close_disk();
}

void readInodeInfo(inode *inode_block,int inumber){
    char * inode_str = (char*) inode_block;
    int start_index = 2 + inumber / INODE_DIV;
    int offset = inumber % INODE_DIV;
    int true_offset = offset * sizeof(inode);
    open_disk();
    char temp_buf[DEVICE_BLOCK_SIZE];
    disk_read_block(start_index,temp_buf);
    //拷贝值
    for(int i = 0 ; i < sizeof(inode); i++){
        inode_str[i] = temp_buf[i + true_offset];
    }
    close_disk();
}

void readDirentInfo(dirent *dirent_block,int dnumber){
    char * dirent_str = (char*) dirent_block;
    int start_index = ROOT_BLOCK + dnumber / DATA_DIV;
    int offset = dnumber % DATA_DIV;
    int true_offset = offset * sizeof(dirent);
    open_disk();
    char temp_buf[DEVICE_BLOCK_SIZE];
    disk_read_block(start_index,temp_buf);
    //拷贝值
    for(int i = 0 ; i < sizeof(inode); i++){
        dirent_str[i] = temp_buf[i + true_offset] ;
    }
    close_disk();
}

void readBlokcInfo(char *block_buf,int blokc_number){
    open_disk();
    disk_read_block(blokc_number + ROOT_BLOCK,block_buf);
    close_disk();
}

void writeBlokcInfo(char *block_buf,int blokc_number){
    open_disk();
    disk_write_block(blokc_number,block_buf);
    close_disk();
}





int getAvailabeInodeBlock(){
    sp_block super_block;
    readSpBlockInfo(&super_block);
    for(int i = 0 ; i < INODE_MAP_LENGTH;i++){
        for(int j = 0 ; j < 32; j++){
            int bit_value = 1 << j;
            if( (super_block.inode_map[i] & bit_value) == 0){
                super_block.inode_map[i] = super_block.inode_map[i] | bit_value;
                super_block.free_inode_count--;
                writeSpBlockInfo(&super_block);
                return i * 32 + j;
            }
        }
    }
}

int getAvailableDataBlock(){
    sp_block super_block;
    readSpBlockInfo(&super_block);
    for(int i = 0 ; i < BLOCK_MAP_LENGTH;i++){
        for(int j = 0 ; j < 32; j++){
            int bit_value = 1 << j;
            if( (super_block.block_map[i] & bit_value) == 0){                
                super_block.block_map[i] = super_block.block_map[i] | bit_value;
                super_block.free_block_count--;
                writeSpBlockInfo(&super_block);
                return i * 32 + j + 1;
            }
        }
    }
}
