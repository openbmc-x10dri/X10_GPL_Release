#!/bin/bash

java -jar Tools/SMCIpmitool/SMCIPMITool.jar $1 ADMIN   ADMIN ipmi flasha images/AST2400_all.bin
