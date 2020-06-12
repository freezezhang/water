#/bin/sh
g++ server.cc -o server -g -I../water -L../water/bin/Debug -lwater
g++ client.cc -o client -g -I../water -L../water/bin/Debug -lwater
