#!/bin/bash

date
echo "Starting job with input from "$1"..."

## config with directory of files sharing common name
#cmsRun test_ahtt.py inputDir=$1 outputName=$2 fileBase=$3

## files explicitly given
#cmsRun test_smtt.py outputName=$1

## list of files to be taken from another .py config
cmsRun test_cfg.py inputName=$1 outputName=$2

echo "Job finished!"
date
