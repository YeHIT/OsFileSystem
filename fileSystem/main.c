#include "init.h"
#include "sh.h"

/**
 * 根据磁盘内容判断文件系统是否被破坏/无系统
 */
int magicNumberChanged(int32_t read_number){
    if(read_number == MAGIC_NUMBER){
        return 0;
    }
    return 1;
}

int main(int argc, char const *argv[]){
    //主进程
    int main_proc = getpid();
    sp_block super_block;
    readSpBlockInfo(&super_block);
    //如果磁盘幻数被改变
    if(magicNumberChanged(super_block.magic_num)){
        printf("---file system is initing----\n");
        initFileSystem();
        printf("---file system init finish----\n");
    }
    printf("---welcome come to Ye's file system ----\n");
    //命令行读取的命令
	static char buf[MAX_COMMAND_LENGTH];
    //读取指令直到结束
	while(getcmd(buf,sizeof(buf)) >= 0){
        //子进程进行
		if(myFork() == 0){
            //参数列表
			char* argv[MAXARGS];
            //参数数量
			int argc = 0;
			AnalyseCmd(buf,argv,&argc);
            if(strcmp(argv[0],"shutdown") == 0){
                if(argc != 1){
                    printf("shutdown argument error\n");
                    return 0;
                }
                printf("thank you for using Ye's file system!!\n");
                kill(main_proc,SIGKILL);
                return 0;
            }
            else{
        	    RunCmd(argc,argv);
            }
		}
        wait(0);
	}
    return 0;
}