#include "cp.h"

void fileCopy(char *src_path,char *dst_path){
    //根节点
    inode root_inode;
    readInodeInfo(&root_inode,ROOT_INODE);
    char buf[DEVICE_BLOCK_SIZE];
    dirent *item_index;
    int find_flag = 0;
    int block_number;
    int inode_id = ROOT_INODE;
    //解析路径
    char *token = src_path;
    char *file_name = token;
    token = strtok(src_path,"/");
    token = strtok(NULL,"/");
    while(token != NULL){
        file_name = strtok(NULL,"/");
        if(file_name == NULL){
            break;
        }
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
            token = file_name;
        }
    }
    file_name = token;
    find_flag = 0;
    //判断该块是否存在文件
    for(int i = 0 ; i < BLOCK_NUMBER_IN_INODE; i++){
        block_number = root_inode.block_point[i];
        //若没有则添加新数据块
        if(block_number == 0){
            continue;
        }
        readBlokcInfo(buf,block_number);
        for(int j = 0 ; j < DATA_DIV; j++){
            item_index = (dirent *) (buf + j * DIRENT_SIZE);
            if(item_index->valid == VALID){
                //找到相应路径的dirent
                if(item_index->type == FILE_TYPE && (strcmp(item_index->name,file_name) == 0)){
                    find_flag = 1;
                    createFile(dst_path,file_name);
                }
            }
        }
        if(find_flag == 1){
            break;
        }
    }
    if(find_flag == 0){
        printf("原目录中无%s文件\n",file_name);
        return;
    }
}   