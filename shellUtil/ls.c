#include "ls.h"


void ls(char *path){
	char buf[DEVICE_BLOCK_SIZE];
    dirent *item_index;
    int find_flag = 0;
    int block_number;
    //根节点
    inode root_inode;
    readInodeInfo(&root_inode,ROOT_INODE);
	//解析路径
    char *token = path;
    token = strtok(path,"/");
    token = strtok(NULL,"/");
	while(token != NULL){
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
                            int inode_id = item_index->inode_id;
                            readInodeInfo(&root_inode,inode_id);
                            find_flag = 1;
                            break;
                        }
                    }
                }
                if(find_flag == 1){
                    break;
                }
                else{
                    printf("无%s目录\n",token);
                    return;
                }
		    }
            token = strtok(NULL,"/");
        }
    }


	//判断该块是否存在文件
	for(int i = 0 ; i < BLOCK_NUMBER_IN_INODE; i++){
		block_number = root_inode.block_point[i];
		if(block_number == 0){
			continue;
		}
		readBlokcInfo(buf,block_number);
		for(int j = 0 ; j < DATA_DIV; j++){
			item_index = (dirent *) (buf + j * DIRENT_SIZE);
			if(item_index->valid == VALID){
				if(item_index->type == FILE_TYPE){
					printf("/root/%s ------ file\n",item_index->name);
				}
				if(item_index->type == DIR_TYPE){
					printf("/root/%s ------ dir\n",item_index->name);
				}
			}
		}
	}


}
