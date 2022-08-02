# gRPC for Uneal Engine 5

Developed with Unreal Engine 5

gRPC 的 ue5 插件


### 1.将.proto文件放在项目目录/Source/Proto(没有则新建)下
### 2.点击 菜单栏 windows-GoogleRPC可自动生成pb文件
### 3.Proto目录可在可自行修改
```
  // Proto目录代码位置
  void FGoogleRPCEditorModule::RegenerateAllPBFiles()
  {
    const FString Path= FPaths::GameSourceDir() / "Proto";
    DeleteAllPBFiles(Path);
    GenerateAllPBFiles(GetProtocExecPath(), Path);
  }
```
