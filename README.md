组件描述：一个非常强大的运行时类型反射库，具备 类型注册，类型反射，获取属性方法列表等。。。  
官网: https://www.rttr.org/  
git: https://github.com/rttrorg/rttr  
version：release 0.9.6  

编译步骤  
1.wget https://github.com/rttrorg/rttr/archive/refs/tags/v0.9.6.tar.gz  
2.tar zxvf v0.9.6.tar.gz && cd rttr-0.9.6  
3.修改CMakelist.txt中编译选项，关闭多余的编译过程 

    - BUILD_RTTR_DYNAMIC  
    - BUILD_UNIT_TESTS  
    - BUILD_EXAMPLES  
4.cmake -DCMAKE_BUILD_TYPE=Release .  

    - 如果cmake版本较低，请进行升级 https://blog.csdn.net/u013714645/article/details/77002555  
5.make && make install，执行完后，所需的头文件，lib库都在install目录里
