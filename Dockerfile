FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y socat && \
    rm -rf /var/lib/apt/lists/*

RUN useradd -d /home/ctf -m -s /bin/false ctf

WORKDIR /home/ctf

COPY puhosos .

RUN chown root:ctf puhosos && \
    chmod 750 puhosos

USER ctf

EXPOSE 1337

CMD ["socat", "-T30", "TCP-LISTEN:1337,reuseaddr,fork", "EXEC:/home/ctf/puhosos"]