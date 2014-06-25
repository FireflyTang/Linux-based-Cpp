//
//  Created by 唐 如麟 on 13-8-1.
//  Copyright (c) 2013年 唐 如麟. All rights reserved.
//
//系统版本模块
//注释参见time模块
#include "issue.h"

#include "../common.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void module_generate(int connfd,bool debug)
{
    FILE *fp;
    
    char bodyheader[]=
    "<html>\n"
    "<head>\n"
    "<title>issue</title>\n"
    "</head>\n"
    "<body>\n";
    
    char bodytail[]=
    "</body>\n"
    "</html>\n";
    
    char cannotopen[]=" <p>Error: Could not open /proc/issue.</p>\n";
    char writebuf[200];
    write(connfd,bodyheader,strlen(bodyheader));
    if(debug) printf("%s",bodyheader);
    //只读打开/etc/issue
    if(fp=fopen("/etc/issue","r"))
    {
        //成功打开
        write(connfd,"<pre>\n",strlen("<pre>\n"));
        if(debug) printf("<pre>\n");
        while(!feof(fp))
        {
            //按行读取
            fgets(writebuf,200,fp);
            write(connfd,writebuf,strlen(writebuf));
            if(debug) printf("%s",writebuf);
        };
        write(connfd,"</pre>\n",strlen("</pre>\n"));
        if(debug) printf("</pre>\n");
        fclose(fp);
    }
    else
    {
        //无法打开
        write(connfd,cannotopen,strlen(cannotopen));
        if(debug) printf("%s",cannotopen);
    };
    write(connfd,bodytail,strlen(bodytail));
    if(debug) printf("%s",bodytail);
    return ;
};
