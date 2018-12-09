#! /bin/sh
rm -rf ~/cutlass/cutlass/src
cp -r  ../../src ~/cutlass/cutlass
cd ~/cutlass/cutlass/platform/Linux/
./build.sh
