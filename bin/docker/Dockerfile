FROM ubuntu:24.04

RUN apt-get update &&\
 apt-get install -y software-properties-common zip unzip python3 python3-pip nodejs npm git gh &&\
 add-apt-repository -y ppa:kicad/kicad-9.0-releases &&\
 apt-get update &&\
 apt-get install -y kicad &&\
 python3 -m pip install InteractiveHtmlBom --break-system-packages
