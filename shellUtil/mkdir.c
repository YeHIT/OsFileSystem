#include "mkdir.h"

void createDir(char path[],char * dir_name){
    char buf[DEVICE_BLOCK_SIZE];
    dirent *item_index;
    int find_flag = 0;
    int block_number;
    //根节点
    inode root_inode;
    int inode_id = ROOT_INODE;
    readInodeInfo(&root_inode,ROOT_INODE);
    //解析路径
    char *token = path;
    token = strtok(path,"/");
    token = strtok(NULL,"/");
    while(token != NULL){
        find_flag = 0;
        // 未到目标文件
        if(token != NULL){
            for(int i = 0 ; i < BLOCK_NUMBER_IN_INODE; i++){
                block_number = root_inode.block_point[i];
                if(block_number == 0){
                    continue;
                }
                readBlokcInfo(buf,block_number);
                for(int j = 0 ; j < DATA_DIV; j++){
                    item_index = (dirent *) (buf + j * DIRENT_SIZE);
                    if(item_index->valid == VALID){
                        //找到相应路径的dirent
                        if(item_index->type == DIR_TYPE && (strcmp(item_index->name,token) == 0)){
                            inode_id = item_index->inode_id;
                            readInodeInfo(&root_inode,inode_id);
                            find_flag = 1;
                            break;
                        }
                    }
                }
                if(find_flag == 1){
                    break;
                }
                
		    }
            if(find_flag == 0){
                printf("无%s目录\n",token);
                return;
            }
            token = strtok(NULL,"/");
        }
    }
    find_flag = 0;
    //判断该块是否存在文件
    for(int i = 0 ; i < BLOCK_NUMBER_IN_INODE; i++){
        block_number = root_inode.block_point[i];
        //若没有则添加新数据块
        if(block_number == 0){
            int block_id = getAvailableDataBlock();
            root_inode.block_point[i] = block_id;
            writeInodeInfo(&root_inode,inode_id);
            block_number = root_inode.block_point[i];
        }
        readBlokcInfo(buf,block_number);
        for(int j = 0 ; j < DATA_DIV; j++){
            item_index = (dirent *) (buf + j * DIRENT_SIZE);
            if(item_index->valid == INVALID){
                //找到inode块
                int inode_id = getAvailabeInodeBlock();
                item_index->type = DIR_TYPE;
                strcpy(item_index->name ,dir_name);
                item_index->valid = VALID;
                item_index->inode_id = inode_id;
                find_flag = 1;
                writeDirentInfo(item_index, j + block_number * DATA_DIV);
                //更新超级块
                sp_block super_block;
                readSpBlockInfo(&super_block);
                super_block.dir_inode_count++;
                writeSpBlockInfo(&super_block);
                // 获取新的innode写入
                inode new_inode;
                readInodeInfo(&new_inode,inode_id);
                new_inode.file_type = DIR_TYPE;
                writeInodeInfo(&new_inode,inode_id);
                break;
            }
        }
        if(find_flag == 1){
            break;
        }
    }
    if(find_flag == 0){
        printf("无可用空间\n");
        return;
    }
}