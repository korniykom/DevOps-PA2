FROM alpine as build

WORKDIR /home/dockerImage
COPY . .
RUN apk add --no-cache libstdc++ libc6-compat automake autoconf build-base
RUN autoreconf -fiv && automake --add-missing
RUN ./configure --disable-dependency-tracking
RUN make

FROM alpine
COPY --from=build /home/dockerImage/trig_program /usr/local/bin/trig_program
ENTRYPOINT [ "/usr/local/bin/trig_program" ]
