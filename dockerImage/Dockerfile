FROM alpine
WORKDIR /home/dockerImage
COPY trig_program ./
RUN apk add libstdc++
RUN apk add libc6-compat
ENTRYPOINT [ "/home/dockerImage/trig_program" ]
