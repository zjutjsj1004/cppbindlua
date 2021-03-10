# cppbindlua
cppbindlua工程:导出 C/C++ API 给 Lua 使用
luacallcpp工程: Lua 调用 导出的 C/C++ API

注意:
1、使用VS中配置正确的Lua路径，目前使用的Lua 5.1版本
2、VS2012 中配置Lua环境，安装babelua.vsix
3、先编译cppbindlua，编译完成后cppbindlua.exe 会拷贝到luacallcpp\MCRuntime下
4、luacallcpp工程设置属性，修改Lua exe path,Working path,Command line
