#! /bin/sh
rm -rf ~/cutlass/cutlass/src
rm -rf ~/cutlass/cutlass/platform/Linux
cp -r  ../../src ~/cutlass/cutlass/
cp -r  ../../platform/Linux ~/cutlass/cutlass/platform/
cd ~/cutlass/cutlass/platform/Linux/
./build.sh
