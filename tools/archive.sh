#!/bin/bash

# tars and zips a folder (taken as input), and moves it to my Dropbox archive
# use as:
# archive.sh <folder_to_be_archived>

DIR_NAME=$(echo ${1%/})
ARCH_PATH="~/Dropbox/CPCB_Classes/ResearchArchive/wemdFiles"
ARCH_DATE=$(date +%y%m%d)

tar -czvf ${ARCH_PATH}/${DIR_NAME}_${ARCH_DATE}.tar.gz ${DIR_NAME}