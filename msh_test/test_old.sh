# MINISHELL-TESTER-2020.08

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell


GOOD=0
TOTAL=0

function exec_test()
{
  ((TOTAL++))
  TEST1=$(echo $@ | ./minishell 2>&-)
  ES_1=$?
  TEST2=$(echo $@ | bash 2>&-)
  ES_2=$?
  if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
    printf "$BOLDGREEN%s$RESET" "✓ "
    ((GOOD++))
  else
    printf "\n$BOLDRED%s$RESET" "✗ "
    printf "$CYAN \"$@\" $RESET"
  fi
  if [ "$TEST1" != "$TEST2" ]; then
    echo
    printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
    printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
    echo
  fi
  if [ "$ES_1" != "$ES_2" ]; then
    echo
    printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
    printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
    echo
  fi
  sleep 0.1
}

if [ "$1" == "" ] || [ "$1" == "help" ]; then
  printf "$BOLDMAGENTA Available arg: $RED all$RESET echo cd pipe env1 export redirect multi syntax exit"
fi
if [ "$1" == "all" ]; then
  printf "$BOLDMAGENTA    _____ _ _ _____ _____ _ _ ______ _ _ \n"
  printf "| \/ |_ _| \ | |_ _|/ ____| | | | ____| | | | \n"
  printf "| \ / | | | | \| | | | | (___ | || | |  | | | | \n"
  printf "| |\/| | | | | . \` | | | \___ \|   | | | | | | \n"
  printf "| | | |_| |_| |\ |_| |_ ____) | | | | |____| |____| |____ \n"
  printf "|_| |_|_____|_| \_|_____|_____/|_| |_|______|______|______|\n$RESET"
fi
echo


# ECHO TESTS
if [ "$1" == "echo" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tECHO TESTS\n"$RESET
  exec_test 'echo test tout'
  exec_test 'echo test tout'
  exec_test 'echo -n test tout'
  exec_test 'echo -n -n -n test tout'
fi

# CD TESTS
if [ "$1" == "cd" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tCD TESTS\n"$RESET
  exec_test 'cd ..\npwd'
  exec_test 'cd /Users\npwd'
  exec_test 'cd\npwd'
  exec_test 'cd .\npwd'
  exec_test 'mkdir test_dir\ncd test_dir\nrm -rf ../test_dir\ncd .\npwd\ncd ..\npwd'
fi



# PIPE TESTS
if [ "$1" == "pipe" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tPIPE TESTS\n"$RESET
	exec_test 'cat tests/lorem.txt | grep arcu | cat -e'
	exec_test 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
	exec_test 'cat /dev/random | head -c 100 | wc -c'
	exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
	exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
  exec_test ' cat big | ls'
  exec_test ' cat big | echo lol'
fi


# ENV EXPANSIONS
if [ "$1" == "env1" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tENV EXPANSIONS TESTS\n"$RESET
	exec_test 'echo test test'
	exec_test 'echo test'
	exec_test 'echo $TEST'
	exec_test 'echo "$TEST"'
	exec_test "echo '$TEST'"
	exec_test 'echo "$TEST$TEST$TEST"'
	exec_test 'echo "$TEST$TEST=lol$TEST"'
	exec_test 'echo " $TEST lol $TEST"'
	exec_test 'echo $TEST$TEST$TEST'
	exec_test 'echo $TEST$TEST=lol$TEST""lol'
	exec_test 'echo $TEST lol $TEST'
	exec_test 'echo test "" test "" test'
	exec_test 'echo "$=TEST"'
	exec_test 'echo "$"'
	exec_test 'echo "$?TEST"'
	exec_test 'echo $TEST $TEST'
	exec_test 'echo "$1TEST"'
	exec_test 'echo "$T1TEST"'
fi

# EXPORT
if [ "$1" == "export" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tEXPORT TESTS\n"$RESET
  ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
  EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
  exec_test 'export ='
  exec_test 'export 1TEST= \n' $ENV_SHOW
  exec_test 'export TEST \n' $EXPORT_SHOW
  exec_test 'export ""="" \n ' $ENV_SHOW
  exec_test 'export TES=T="" \n ' $ENV_SHOW
  exec_test 'export TE+S=T="" \n ' $ENV_SHOW
  exec_test 'export TEST=LOL \n echo $TEST \n ' $ENV_SHOW
  exec_test 'export TEST=LOL \n echo $TEST$TEST$TEST=lol$TEST'
  exec_test 'export TEST=LOL \n export TEST+=LOL \n echo $TEST \n ' $ENV_SHOW
  exec_test $ENV_SHOW
  exec_test $EXPORT_SHOW
  exec_test 'export TEST="ls -l - a" \n echo $TEST \n $LS \n ' $ENV_SHOW
fi


# REDIRECTIONS
if [ "$1" == "redirect" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tREDIRECTION TESTS\n"$RESET
  exec_test 'echo test > ls \n cat ls'
  exec_test 'echo test > ls >> ls >> ls \n echo test >> ls \n cat ls'
  exec_test '> lol echo test lol \n cat lol'
  exec_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test \n cat test'
  exec_test 'cat < ls'
  exec_test 'cat < ls > ls'
  exec_test 'ls > ls'
  exec_test 'cat <ls'
  exec_test 'cat <test.sh <ls'
  
  exec_test 'cat << stop \n1 \nstop'
  exec_test 'cat << stop \n1'
  exec_test 'cat <test.sh <<stop \n1 \nstop'
  exec_test 'cat <<stop<ls  \n1 \nstop'
  exec_test 'cat <test.sh << stop1 <<stop2 \na\n \nb \nc \nstop1\n run2 \nstop2'
  exec_test 'rm -f ls >ls'
fi


# MULTI TESTS
if [ "$1" == "multi" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tMULTI TESTS\n"$RESET
  exec_test 'echo testing multi >lol \n echo <lol \n echo "test 1 ; | and 2" >>lol \n echo <lol \n cat tests/lorem.txt | grep Lorem'
  
fi

# SYNTAX ERROR
if [ "$1" == "syntax" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tSYNTAX ERROR\n"$RESET
  # exec_test ';; test'
  exec_test '| test'
  exec_test 'echo > <'
  exec_test 'echo | |'
  exec_test 'echo "||"'
  exec_test '<'
  exec_test "grep -z"
fi

# EXIT
if [ "$1" == "exit" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tEXIT\n"$RESET
  # exec_test "exit 42"
  # exec_test "exit 42 53 68"
  # exec_test "exit 259"
  # exec_test "exit 9223372036854775807"
  # exec_test "exit -9223372036854775808"
  exec_test "exit 9223372036854775808"
  exec_test "exit -9223372036854775810"
  # exec_test "exit -4"
  # exec_test "exit wrong"
  # exec_test "exit wrong_command"
  # exec_test "gdagadgag"
  # exec_test "ls -Z"
  exec_test "cd gdhahahad"
  exec_test "ls -la | wtf"
fi


echo
if [[ $GOOD == $TOTAL ]]; then
  printf $GREEN"\n\tPASS: $GOOD / $TOTAL\n"$RESET
elif (( $GOOD < $TOTAL )) && (( $GOOD >= $TOTAL * 3 / 4 )); then
  printf $YELLOW"\n\tPASS: $GOOD / $TOTAL\n"$RESET
else
  printf $RED"\nPASS: $GOOD / $TOTAL\n"$RESET
fi
echo

rm -f lol ls 1 test