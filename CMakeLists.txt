cmake_minimum_required(VERSION 3.29)
project(verteile_systeme C)

set(CMAKE_C_STANDARD 11)
include_directories(/usr/include/tirpc)
link_libraries(nsl tirpc)

add_executable(server math_xdr.c math_svc.c math.h server.c)
add_executable(client math_xdr.c math_clnt.c math.h client.c)

