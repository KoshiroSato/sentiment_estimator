FROM python:3.13.3

RUN apt-get update -y && apt-get upgrade -y &&\
  apt-get install build-essential make -y &&\
  apt-get autoremove -y &&\
  apt-get clean &&\
  rm -rf /usr/local/src/*

COPY requirements.txt requirements.txt
RUN pip install -U pip &&\
  pip install --no-cache-dir -r requirements.txt 