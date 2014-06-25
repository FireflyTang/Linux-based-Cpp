//
//  Created by 唐 如麟 on 13-8-1.
//  Copyright (c) 2013年 唐 如麟. All rights reserved.
//
#ifndef __common__
#include "common.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//字符串拼接，返回新空间指针，需要外部释放
char* strandstr(char* a,char* b)
{
    int i,j;
    char* c=(char*)malloc(strlen(a)+strlen(b)-1);
    char* p;
    p=c;
    j=strlen(a);
    for(i=0;i<j;a++,p++,i++)
    {
        *p=*a;
    };
    j=strlen(b);
    for(i=0;i<j;b++,p++,i++)
    {
        *p=*b;
    };
    *(p++)='\0';
    return c;
};

//返回模块相对地址，默认在./modules/下
char* getlocation(char* requesttag,char* modir,bool debug)
{
    char* location;
    char ext[]=".so";
    char* m1;
    location=strandstr(modir,m1=strandstr(requesttag,ext));
    free(m1);
    return location;
};

//执行系统命令并写返回
bool writecommand(int connfd,char* command,bool debug)
{
    FILE *fp;
    char writebuf[600];//写缓存
    fp=popen(command,"r");//执行系统命令command,返回文件描述符
    //执行错误
    if(fp==0)
    {
        return false;
    };
    //成功执行，分配执行时间
    sleep(1);
    //为了保证显示效果与源文件效果一致,需要,<pre>标签
    write(connfd,"<pre>\n",strlen("<pre>\n"));
    if(debug) printf("<pre>\n");
    while(!feof(fp))//未到文件尾部
    {
        if(fgets(writebuf,600,fp)) //读取一行
        {
            write(connfd,writebuf,strlen(writebuf));//写这一行
            if(debug) printf("%s",writebuf);
        };
    };
    write(connfd,"</pre>\n",strlen("</pre>\n"));
    if(debug) printf("</pre>\n");
    //关闭文件
    pclose(fp);
    return true;
};
