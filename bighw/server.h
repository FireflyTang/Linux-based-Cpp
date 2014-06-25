//
//  Created by 唐 如麟 on 13-8-1.
//  Copyright (c) 2013年 唐 如麟. All rights reserved.
//
#ifndef __server__
#define __server__
extern bool server_run(char* address,int port,char* modir,bool debug); //运行服务器
extern bool module_open(char* commabdtag,bool debug);//加载模块
extern bool module_close(char* requesttag,bool debug);//卸载模块
#endif
