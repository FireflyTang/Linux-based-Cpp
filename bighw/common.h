//
//  Created by 唐 如麟 on 13-8-1.
//  Copyright (c) 2013年 唐 如麟. All rights reserved.
//
#ifndef __common__
#define __common__
char* strandstr(char* a,char* b); //字符串拼接
char* getlocation(char* requesttag,char* modir,bool debug);//获取模块相对位置

extern "C" //由于需要在以C编译的各个模块中调用，所以也需要以C编译 C++使用了mangled name
{
    bool  writecommand(int connfd,char* command,bool debug); //执行系统命令并写返回
};
#endif
