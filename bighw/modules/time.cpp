//
//  Created by 唐 如麟 on 13-8-1.
//  Copyright (c) 2013年 唐 如麟. All rights reserved.
//
//系统时间模块
#include "time.h"

#include "../common.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void module_generate(int connfd,bool debug)
{
    //html主体部分头部
    char bodyheader[]=
    "<html>\n"
    "<head>\n"
    "<title>time</title>\n"
    "<meta http-equiv=\"refresh\" content=\"5\">\n" //自动刷新
    "</head>\n"
    "<body>\n"
    "The current time is";
    
    //html主体部分尾部
    char bodytail[]=
    "</body>\n"
    "</html>\n";
    
    //写html主体部分头部
    write(connfd,bodyheader,strlen(bodyheader));
    if(debug) printf("%s",bodyheader);
    
    //写系统命令date的执行结果
    writecommand(connfd,(char*)"date",debug);
    
    //写html主体部分尾部
    write(connfd,bodytail,strlen(bodytail));
    if(debug) printf("%s",bodytail);
    return ;
};
