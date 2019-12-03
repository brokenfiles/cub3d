#!/usr/bin/env bash
./cub3d $1 2> errors.log
touch void
DIFF=$(diff errors.log void)
if [ "$DIFF" == "" ]
then
  printf "======= \033[1;32m0 error found 👏\033[0;0m =======\n"
else
  printf "======= \033[1;31mERROR(S) FOUND!\033[0;0m 😢 =======\n\033[0;0m"
  cat errors.log
  printf "\033[0;0m"
fi
rm -f void