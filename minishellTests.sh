#!/usr/bin/env Bash

##to fix syntahxes not fully working for our minishell commands##

echo 'Test line is: echo $USER $PWD $? + $? $+ $, $PWD'
echo 'Expected Output is:'
/bin/echo $USER $PWD $? + $? $+ $, $PWD # using our echo instead of sys echo
echo "Minishell output is:"
echo $USER $PWD $? + $? $+ $, $PWD
