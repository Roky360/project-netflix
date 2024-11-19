FROM ubuntu:latest
LABEL authors="edens"

ENTRYPOINT ["top", "-b"]