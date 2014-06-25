//
//  Created by 唐 如麟 on 13-8-1.
//  Copyright (c) 2013年 唐 如麟. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char* argv[])
{
    bool run=true; //是否运行
    bool debug=false; //调试模式
    int port=8008; //默认端口
    char portstr[10]; //端口字符串
    char opt;
    char modir[20]="./modules/";
    char address[20]="0.0.0.0";
    //选项列表
    const struct option my_long_options[] =
    {
        {"address",1,NULL,'a'},
        { "help", 0, NULL, 'h' },
        { "modir", 1, NULL, 'm' },
        { "port", 1, NULL, 'p' },
        {"verbose",0,NULL,'v'},
        { NULL, 0, NULL, 0 }
    };
    
    //识别选项
    while((opt=getopt_long(argc, argv,"a:hm:p:v", my_long_options, NULL))!=-1)
    {
        switch(opt)
        {
            case 'p': //端口 默认8080
            {
                port=(int)atof(optarg);
                break;
            };
            case 'v': //verbose
            {
                debug=true;
                break;
            };
            case 'm'://模块目录 默认./modules/
            {
                strcpy(modir,optarg);
                break;
            };
            case 'a'://服务器地址 默认本机
            {
                strcpy(address,optarg);
                break;
            };
            case 'h': //帮助 服务器不运行
            {
                printf(
                       "[options]\n"
                       "   -a [--adress]\n"
                       "      address of server\n"
                       "      default: localhost\n"
                       "   -p [--port]\n"
                       "      port of server\n"
                       "      default: 8080\n"
                       "   -m [--modir]\n"
                       "      loaction of modules\n"
                       "      default: /modules/\n"
                       "   -v [--verbose]\n"
                       "      turn on verbose mode\n"
                       "      default: off\n"
                       "   -h [--help]\n"
                       "      show help and server will not run\n");
                run=false;
                break;
            };
            default: //其他
            {
                printf("options wrong\n");
                run=false;
                break;
            };
        };
    };
    
    
    if(run)
    {
        sprintf(portstr, "%d",port);
        printf("server start to run\n");
        if(debug)
	    {
            //以调试模式运行
            execlp("./server","server","-a",address,"-p",portstr,"-m",modir,"-v",(char*)0);
	    }
        else
        {
            //以安静模式运行
            execlp("./server","server","-a",address,"-p",portstr,"-m",modir,(char*)0);
        };
    };
    return 0;
};
