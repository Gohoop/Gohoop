Gohoop简介
====
    Gohoop分布式存储与计算平台(Gohoop Distributed Storage And Compute Platforms)，简称GDSCP。
    开发语言C++，可运行在Linux平台上。

背景
====
    1. 实现大数据分布式存储。
    2. 实现任务分布式运算。
    3. 对外以RPC方式提供。

发布
====
### Gohoop.1.2.0 2015.06.30
    增加结构和非结构化数据存取服务，包括：
    GStoreMaster 进程
    GStoreServer 进程
    GSQLMaster 进程
    GSQLServer 进程

### Gohoop.1.1.0 2015.02.28
    增加文件系统服务、Task服务，Mapreduce框架实现、丰富基础库，包括：
    GDFSMaster 进程
    GDFSServer 进程
    GTaskMaster 进程
    GTaskServer 进程
    基础库增加和修复

### Gohoop.1.0.0 2014.10.31
    基础库实现，包括：
    libgsystem.so
    libgutils.so(包括gini gxml gzip grpc gsoap)
    libglogger.so
    libgcommon.so(包括filesys function iostream network)
    
下载
====
[gohoop.1.2.0 新增结构化和非结构化存取服务](https://github.com/Gohoop/Gohoop/tag/gohoop.1.0.0.tar.gz) <br />
[gohoop.1.1.0 新增文件系统服务](https://github.com/Gohoop/Gohoop/tag/gohoop.1.0.2.tar.gz) <br />
[gohoop.1.0.0 仅完成基础库实现](https://github.com/Gohoop/Gohoop/tag/gohoop.1.0.4.tar.gz) <br />

部署
====
部署分为Master端和Slave端。Master负责管理、控制Slave端服务，Slave端负责具休的数据存储和运行行为。

### Master端布署
----
GTaskMaster、GDFSMaster、GStoreMaster、GSQLMaster

### Slave端布署
----
GTaskServer、GDFSServer、GStoreServer、GSQLServer

安装
====
1. 配置
./configuration --prefix=/etc/usr/local

2. 编译
make 

3. 安装
make install

4. 测试安装
gohoop_guide

使用
====
> 详细见gohoop_guide.pdf

### GTaskMaster & GTaskServer

### GDFSMaster & GDFSServer

### GStoreMaster & GStoreServer

### GSQLMaster & GSQLServer
