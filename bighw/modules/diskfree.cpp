//
//  Created by 唐 如麟 on 13-8-1.
//  Copyright (c) 2013年 唐 如麟. All rights reserved.
//
//磁盘空间模块
//注释参见time模块
#include "diskfree.h"

#include "../common.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void module_generate(int connfd,bool debug)
{
    char bodyheader[]=
    "<html>\n"
    "<head>\n"
    "<title>diskfree</title>\n"
    "</head>\n"
    "<body>\n";
    char bodytail[]=
    "</body>\n"
    "</html>\n";
    
    write(connfd,bodyheader,strlen(bodyheader));
    if(debug) printf("%s",bodyheader);
    
    writecommand(connfd,(char*)"df",debug);
    
    write(connfd,bodytail,strlen(bodytail));
    if(debug) printf("%s",bodytail);
    return ;
};
