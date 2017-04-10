# init-c
###### Creates the skeleton for a basic C project

```shell
#!/bin/sh
# function to print usage
print_usage () {
	printf "Usage: $0 <projectname>\n"
	exit 1
}
# function to print errors
err () {
	printf "\x1b[38;2;255;40;40mError: %s\x1b[0m\n" "$1"
}
# test if arguments == 1
if [ $# -ne 1 ]; then
	print_usage
fi
progname=$1
# clone base repo
git clone https://github.com/ertw/init-c.git $1
# if clone fails, error
if [ $? -ne 0 ]; then
	err "Unable to clone base"
else
	printf "\x1b[38;2;40;177;249mCreated: Makefile README.md .gitignore\x1b[0m\n"
fi
cd $progname
# remove remote
git remote rm origin
# clone libft
git submodule add https://github.com/ertw/libft.git
# if clone fails, error
if [ $? -ne 0 ]; then
	err "Unable to clone libft"
else
	printf "\x1b[38;2;40;177;249mAdded libft\x1b[0m\n"
fi
# create author file
printf $(whoami) > author
# update makefile with correct name
ed -s Makefile <<!
,s/program/$progname/g
w
q
!
printf "#include \"%s\"" "$progname.h" > $progname.c
printf "#include \"%s\"" "./libft/libft.h" > $progname.h
printf "Readme for %s.\n" "$progname" > README.md
printf "\x1b[38;2;40;177;249mCreated: author $progname.c $progname.h\x1b[0m\n"
```
