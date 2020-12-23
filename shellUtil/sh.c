#include "sh.h"

void errorPrint(char* errorMessage){
    printf("%s\n", errorMessage);
}

int myFork(){
    int pid;
    pid = fork();
    if(pid == -1){
        errorPrint("fork失败");
    }
    return pid;
}

int getcmd(char *buf, int bufSize){
    //打印提示符
    printf("@ ");
    //申请空间
    memset(buf, 0, bufSize);
    //读取行命令
    fgets(buf, bufSize,stdin);
    // EOF
    if(buf[0] == 0) 
        return -1;
    return 0;
}

int isBlank(char c){
	if(c == ' ' || c == '\t')
		return 1;
	else
		return 0;
}

void AnalyseCmd(char *cmd,char* argv[],int* argc){
    //读到行尾
	for(int i = 0;cmd[i] != '\n' && cmd[i] != '\0' && *argc < MAXARGS;i++){
		//去除空字符
        while(isBlank(cmd[i])){
			i++;
		}
        //添加参数到参数列表
		argv[*argc] = cmd + i;
		(*argc)++;
		//不能读取\n
		while(!isBlank(cmd[i]) && cmd[i] != '\0' && cmd[i] != '\n'){
			i++;
		}
        //参数终止
		cmd[i] = '\0';	
	}
	argv[*argc] = '\0';
}

void RunCmd(int argc,char* argv[]){
    if(strcmp(argv[0],"ls") == 0){
        if(argc != 2){
            printf("ls argument error\n");
            return;
        }
        ls(argv[1]);
    }
    else if(strcmp(argv[0],"touch") == 0){
        if(argc != 3){
            printf("touch argument error\n");
            return;
        }
        createFile(argv[1],argv[2]);
    }
    else if(strcmp(argv[0],"mkdir") == 0){
        if(argc != 3){
            printf("mkdir argument error\n");
            return;
        }
        createDir(argv[1],argv[2]);
    }
    else if(strcmp(argv[0],"cp") == 0){
        if(argc != 3){
            printf("touch argument error\n");
            return;
        }
        fileCopy(argv[1],argv[2]);
    }    
}