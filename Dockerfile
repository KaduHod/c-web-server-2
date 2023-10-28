FROM debian:latest

RUN apt-get update

RUN apt-get -y install inotify-tools ca-certificates gcc 
