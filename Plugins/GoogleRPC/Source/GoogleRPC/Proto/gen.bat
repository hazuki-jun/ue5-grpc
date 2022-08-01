set /p file=
protoc.exe -I . --cpp_out=. %file%
protoc.exe -I . --grpc_out=. --plugin=protoc-gen-grpc="grpc_cpp_plugin.exe" %file%