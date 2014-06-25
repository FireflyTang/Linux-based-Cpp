//
//  Created by 唐 如麟 on 13-8-1.
//  Copyright (c) 2013年 唐 如麟. All rights reserved.
//
#ifndef __server__
#include "server.h"
#endif

#ifndef __module__
#include "module.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>

bool server_run(char* address,int port,char* modir,bool debug);

int main (int argc, char* argv[])
{
    int port=8008; //默认端口
    bool debug=false; //默认安静模式
    char modir[40];
    char address[20];
    const struct option my_long_options[] =
    {
        {"address",1,NULL,'a'},
        {"modir",1,NULL,'m'},
        { "port",1, NULL, 'p' },
        {"verbose",0,NULL,'v'},
        { NULL, 0, NULL, 0 }
    };
    char opt;
    while((opt=getopt_long(argc, argv,"p:va:m:", my_long_options, NULL))!=-1)
    {
        switch(opt)
        {
            case 'p':
            {
                port=(int)atof(optarg);
                break;
            };
            case 'v':
            {
                debug=true;
                break;
            };
            case 'm':
            {
                strcpy(modir,optarg);
                break;
            };
            case 'a':
            {
                strcpy(address,optarg);
                break;
            };
            default:
            {
                printf("inner options wrong");
                break;
            };
        };
    };
    //运行服务器
	server_run(address,port,modir,debug);
};


bool server_run(char* address,int port,char* modir,bool debug)
{
    
    int sockfd; //侦听
    int connfd; //会话
    struct sockaddr_in my_server_addr;
    char readbuf[600]; //读取缓存
    char requesttag[40]; //请求标识
    bool temp_debug;
    
    //获取一个套接字 TCP/IP 流式
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    
    //地址和端口设置 本机ip 网络字节顺序端口
    my_server_addr.sin_family=AF_INET;
    if (strcmp(address,"0.0.0.0")==0)
    {
        my_server_addr.sin_addr.s_addr=INADDR_ANY;
        strcpy(address,"localhost");
    }
    else
    {
        my_server_addr.sin_addr.s_addr= inet_addr(address);
    };
    my_server_addr.sin_port=htons(port);
    
    bzero(&my_server_addr.sin_zero,8);
    
    //端口绑定
    bind(sockfd,(struct sockaddr*)(&my_server_addr),sizeof(my_server_addr));
    
    //侦听端口
    temp_debug=listen(sockfd,20);
    
    if(debug) printf("sockfd=%d\n",sockfd);
    
    if(debug&&(temp_debug==0)) printf("listen %s:%d\n",address,port);
    
    while(1)
    {
        
        if(debug) printf("parent: wait for request \n");
        
        //建立会话
        int len_of_my_server_addr=sizeof(my_server_addr);
        connfd=accept(sockfd,(struct sockaddr*)(&my_server_addr),(socklen_t*)(&len_of_my_server_addr));
        
        //读取请求
        int num=read(connfd,readbuf,600);
        readbuf[num]='\0';
        
        
        if(debug) printf("receive request from connfd=%d: \n-------------\n%s\n-------------\n",connfd,readbuf);
        
        //提取请求标识
        *requesttag='\0';
        sscanf(readbuf,"%*[^/]/%[^ \n]",requesttag);
        if(debug) printf("recive requesttag: %s\n",requesttag);
        
        //忽略子进程结束信号，父进程无需wait
        signal(SIGCLD,SIG_IGN);
        
        if(fork())
        {
            //父进程
            if(debug) printf("parent: pid=%d\nparent: close connfd=%d\n",(int)getpid(),connfd);
            
            //父进程关闭会话
            close(connfd);
        }
        else
        {
            //子进程
            if(debug) printf("child : pid=%d\n",(int)getpid());
            
            //加载模块
            module_open(requesttag,modir,debug);
            //运行模块
            temp_debug=module_run(connfd,requesttag,debug);
            if(debug&&temp_debug) printf("child : module %s run successfully\n",requesttag);
            //卸载模块
            module_close(requesttag,debug);
            //子进程关闭会话
            if(debug) printf("child : close connfd=%d\n",connfd);
            close(connfd);
            
            //子进程退出
            exit(0);
        };
    };
    //关闭侦听
    if(debug) printf("sockfd=%d close\n",sockfd);
    close(sockfd);
    return true;
};
