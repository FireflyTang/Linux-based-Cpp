//
//  Created by 唐 如麟 on 13-8-1.
//  Copyright (c) 2013年 唐 如麟. All rights reserved.
//
//系统进程模块
//注释参见time模块
#include "processes.h"

#include "../common.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void module_generate(int connfd,bool debug )
{
    char bodyheader[]=
    "<html>\n"
    "<head>\n"
    "<title>processes</title>\n"
    "</head>\n"
    "<body>\n";
    
    char bodytail[]=
    "</body>\n"
    "</html>\n";
    
    //第一行为标题 ps -o 参数选择显示列 tail 去掉第一行 sort 排序
    char command[]="echo \"COMMAND              PID     PPID USER            GROUP                RSS     %CPU     %MEM STAT\";"
    "ps -eo comm:15,pid:8,ppid:8,user:15,group:15,rss:8,pcpu:8,pmem:8,stat:8|tail -n +2|sort";
    
    write(connfd,bodyheader,strlen(bodyheader));
    if(debug) printf("%s",bodyheader);
    
    writecommand(connfd,command,debug);
    
    write(connfd,bodytail,strlen(bodytail));
    if(debug) printf("%s",bodytail);
    return ;
};
