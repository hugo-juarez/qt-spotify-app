FROM rust:trixie AS builder

WORKDIR /usr/src/librespot

RUN apt-get update && apt-get install -y \
        go \
        alsa-lib-dev \
        libogg-dev \
        libvorbis-dev \
        flac-dev \
        gcc \
        musl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN cargo install librespot --locked --features pulseaudio-backend

FROM ubuntu:26.04

RUN apt-get update && apt-get install -y \
    libasound2t64 \
    libpulse0 \
    ca-certificates \
    alsa-utils \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /usr/local/cargo/bin/librespot /usr/local/bin/librespot

CMD ["librespot", "-n", "\"Librespot Speaker\"", "-b", "160", "--backend", "pulseaudio"]