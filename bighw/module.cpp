//
//  Created by 唐 如麟 on 13-8-1.
//  Copyright (c) 2013年 唐 如麟. All rights reserved.
//
#ifndef __module__
#include "module.h"
#endif

#ifndef __common__
#include "common.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

#include <map>
#include <string.h>

char  SUCCESS_HEADER[]= //成功连接返回头部
"HTTP/1.0 200 OK\n"
"Content-type: text/html\n\n";
char BAD_REQUEST[]= //错误连接返回
"HTTP/1.0 400 Bad Request\n"
"Content-type: text/html\n\n"
"<html>\n "
"<body>\n "
"<h1>Bad Request</h1>\n"
"<p>This server did not understand your request.</p>\n"
"</body>\n"
"</html>\n";
char ERROR_404[]= //404错误返回
"HTTP/1.0 404 Not Found\n"
"Content-type: text/html\n\n"
"<html>\n"
"<body>\n"
"<h1> Not Found</h1> \n"
"<p>The requested URL %s was not found on this server.</p>\n"
"</body>\n"
"</html>\n";
char ERROR_501[]= //501错误返回
"HTTP/1.0 501 Method Not Implemented\n"
"Content-type: text/html\n\n"
"<html>\n"
"<body>\n"
"<h1>Method Not Implemented</h1>\n"
"<p>The method %s is not implemented by this server.</p>\n"
"</body>\n"
"</html>\n";
char WELCOME[]= //欢迎返回主体
"<html>\n"
"<body>"
"<h1>Welcome</h1>"
"</body>"
"</html>\n";

struct ptrCmp //重载char*比较函数
{
    bool operator()( const char * s1, const char * s2 ) const
    {
        return strcmp( s1, s2 ) < 0;
    }
};

struct handle //记录模块入口相关数据
{
    void* module_handle; //模块入口句柄
    void (*entrance_handle)(int,bool);//函数入口句柄
};

typedef handle* phandle; //定义指针


std::map<char*,phandle,ptrCmp> modulerecord;//完成模块名(char*)到相应模块入口句柄的映射

//某个模块是否已经加载
bool _in_modulerecord(char* requesttag,bool debug)
{
    return modulerecord.find(requesttag)!=modulerecord.end() ? true:false;
};

//加载模块
bool module_open(char* requesttag,char* modir,bool debug)
{
    void* temp_module_handle; //临时模块入口句柄
    char* m2;
    void (*temp_entrance_handle)(int connfd,bool debug); //临时函数入口句柄
    
    if(!_in_modulerecord(requesttag,debug))
    {
        
        //获取模块入口
        if(debug) printf("child : try to load %s.so\n",requesttag);
        m2=getlocation(requesttag,modir,debug);
	if(debug) printf("child : get location of %s.so:%s\n",requesttag,m2);
	temp_module_handle=dlopen(m2,RTLD_LAZY) ;
	free(m2); //由于strandstr使用malloc分配空间，所以要有free
        if(temp_module_handle)
        {
            if(debug) printf("child : get module_handle successfully\n");
            
            //获取函数入口句柄
            temp_entrance_handle=(void(*)(int,bool))dlsym(temp_module_handle,"module_generate");
            if(temp_entrance_handle)
            {
                if(debug) printf("child : get module_generate_handle successfully\nopen module successfully\n");
                
                //记录相关句柄
                modulerecord[requesttag]=new handle;
                modulerecord[requesttag]->entrance_handle=temp_entrance_handle;
                modulerecord[requesttag]->module_handle=temp_module_handle;
            }
            else
            {
                //函数入口获取错误
                if(debug) printf("child : fail to get module_generate_handle\n");
                return false;
            };
        }
        else
        {
            //模块入口获取错误
            if(debug) printf("child : fail to get module_handle\n");
            return false;
        };
    };
    return true;
};

bool module_close(char* requesttag,bool debug)
{
    //卸载模块
    if(debug) printf("child : try to close module %s\n",requesttag);
    if(!_in_modulerecord(requesttag,debug))
    {
        //模块没有加载
        if(debug) printf("child : module %s not existed in modulerecord\n",requesttag);
        return false;
    };
    
    //卸载句柄
    dlclose(modulerecord[requesttag]->module_handle);
    
    //释放结构
    delete(modulerecord[requesttag]);
    
    //从map中清除
    modulerecord.erase(modulerecord.find(requesttag));
    if(debug) printf("child : close %s module successfully\n",requesttag);
    return true;
};


bool module_run(int connfd,char* requesttag,bool debug)
{
    //运行模块，不需要断开会话
    void* modulehandle;
    void (*entrancehandle)(int connfd,bool debug);
    char* m1;
    if(debug) printf("child : start to response\n",requesttag);
    
    //欢迎
    if(*requesttag=='\0')
    {
        if(debug) printf("child : response WELCOME\n",requesttag);
        
        //写成功返回头部
        write(connfd,SUCCESS_HEADER,strlen(SUCCESS_HEADER));
        //写欢迎返回主体
        write(connfd,WELCOME,strlen(WELCOME));
        if(debug) printf("child : response:\n-------------\n%s%s\n-------------\n",SUCCESS_HEADER,WELCOME);
        return true;
    };
    if(!_in_modulerecord(requesttag,debug))
    {
        //未加载模块或错误请求
        
        char writebuf[300];//读取缓存
        
        //501错误生成
        sprintf(writebuf,ERROR_501,m1=strandstr((char*)"/",requesttag));
        //写501错误
        write(connfd,writebuf,strlen(writebuf));
        if(debug) printf("child : response 501 ERROR\nchild : response:\n-------------\n%s\n-------------\n",writebuf);
        //释放strandstr返回指针
        free(m1);
        return false;
    }
    else
    {
        //正常请求
        if(debug) printf("child : response %s\n",requesttag);
        //写成功返回头部
        write(connfd,SUCCESS_HEADER,strlen(SUCCESS_HEADER));
        if(debug) printf("child : response:\n-------------\n%s",SUCCESS_HEADER);
        //执行相应模块函数，由函数内部写返回
        (*(modulerecord[requesttag]->entrance_handle))(connfd,debug);
        if(debug) printf("-------------\n");
        return true;
    };
};

