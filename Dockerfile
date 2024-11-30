# Build stage
FROM alpine as build

WORKDIR /home/dockerImage
COPY . .
RUN apk add --no-cache libstdc++ libc6-compat automake autoconf build-base
RUN autoreconf -fiv && automake --add-missing
RUN ./configure --disable-dependency-tracking
RUN make

# Runtime stage
FROM alpine
RUN apk add --no-cache libstdc++ libc6-compat
WORKDIR /
COPY --from=build /home/dockerImage/trig_program /home/trig_program

# Set the desired entrypoint for the second alpine
ENTRYPOINT ["/home/trig_program"]
