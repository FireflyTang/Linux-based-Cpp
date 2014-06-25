//
//  Created by 唐 如麟 on 13-8-1.
//  Copyright (c) 2013年 唐 如麟. All rights reserved.
//
extern "C" //dlopen 和 dlsym 由C写成所以需要以C编译才可动态加载 C++使用mangled name来重载函数
{
    void module_generate(int connfd,bool debug);
};
