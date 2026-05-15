#!/bin/bash
set -e

export PATH="$HOME/opt/cross/bin:$PATH"

PROJECT=/home/pl/ParadoxOS
BUILD=$PROJECT/build
ISO=$PROJECT/isodir

ld -r -b binary font.bin -o font.o
