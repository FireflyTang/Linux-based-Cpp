//
//  Created by 唐 如麟 on 13-8-1.
//  Copyright (c) 2013年 唐 如麟. All rights reserved.
//
#ifndef __module__
#define __module__
bool module_open(char* requesttag,char* modir,bool debug); //加载模块
bool module_close(char* requesttag,bool debug); //卸载模块
bool module_run(int connfd,char* requesttag,bool debug); //运行模块
#endif
