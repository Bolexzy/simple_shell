# **lsh - Simple Shell 🐚 **

This is a simple UNIX command interpreter written as part of the low-level programming and algorithm track at ALX Africa.

## Description 📝

Lsh is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

## Invocation 🪄

Usage: **lsh** [*filename*]

To invoke **lsh**, compile all `.c` files in the repository and run the resulting executable:

```
  gcc *.c -o shellby
  ./lsh
```

**lsh** can be invoked both interactively and non-interactively. If **lsh** is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

Example:
```
  $ echo "echo 'hello'" | ./lsh
  'hello'
  $
  ```
  
  If **lsh** is invoked with standard input connected to a terminal (determined by [isatty(3)])(https://linux.die.net/man/3/isatty), an interactive shell is opened. When executing interactively, **lsh** displays the prompt $ when it is ready to read a command.
  
  Example:
```
  $./lsh
  $
  ```
  
  If a command line argument is invoked, sodash will take that first argument as a file from which to read commands.

Example:
 ```
  $ cat text
  echo 'holberton'
  $ ./lsh text
  'holberton'
  $
  ```
  
  ## Environment ⚙️
  
  Upon invocation, **lsh** receives and copies the environment of the parent process in which it was executed. This environment is an array of name-value strings describing variables in the format *NAME=VALUE*. A few key environmental variables are:
  
  ### Home 

The home directory of the current user and the default directory argument for the **cd** builtin command.
```
  $ echo "echo $HOME" | ./lsh
  /home/vagrant
  ```
  
####  PWD
The current working directory as set by the **cd** command.
 ```
  $ echo "echo $PWD" | ./shellby
  /home/vagrant/holberton/simple_shell
  ```

#### OLDPWD

The previous working directory as set by the **cd** command.
```
  $ echo "echo $OLDPWD" | ./shellby
  /home/vagrant/holberton/printf
  ```
  
#### PATH

A colon-separated list of directories in which the shell looks for commands. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directory.
```
$ echo "echo $PATH" | ./lsh
/home/vagrant/.cargo/bin:/home/vagrant/.local/bin:/home/vagrant/.rbenv/plugins/ruby-build/bin:/home/vagrant/.rbenv/shims:/home/vagrant/.rbenv/bin:/home/vagrant/.nvm/versions/node/v10.15.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/vagrant/.cargo/bin:/home/vagrant/workflow:/home/vagrant/.local/bin
```
### Command Execution 🔫

After receiving a command, lsh tokenizes it into words using `" "` as a delimiter. The first word is considered the command and all remaining words are considered arguments to that command. sodash then proceeds with the following actions:

If the first character of the command is neither a slash (`\`) nor dot (`.`), the shell searches for it in the list of shell builtins. If there exists a builtin by that name, the builtin is invoked.
If the first character of the command is none of a slash (`\`), dot (`.`), nor builtin, sodash searches each element of the PATH environmental variable for a directory containing an executable file by that name.
If the first character of the command is a slash (`\`) or dot (`.`) or either of the above searches was successful, the shell executes the named program with any remaining given arguments in a separate execution environment.

### Exit Status 👋

**Lsh** returns the exit status of the last command executed, with zero indicating success and non-zero indicating failure.

If a command is not found, the return status is `127`; if a command is found but is not executable, the return status is 126.

All builtins return zero on success and one or two on incorrect usage (indicated by a corresponding error message).

### Signals ❗
While running in interactive mode, **lsh** ignores the keyboard input `Ctrl+c`. Alternatively, an input of end-of-file `(Ctrl+d)` will exit the program.

User hits `Ctrl+d` in the third line.
```
  $ ./lsh
  $ ^C
  $ ^C
  $
  ```
### Variable Replacement ＄

**lsh** interprets the `$` character for variable replacement.

#### $ENV_VARIABLE
`ENV_VARIABLE` is substituted with its value.

Example:
```
  $ echo "echo $PWD" | ./lsh
  /home/vagrant/holberton/simple_shell
  ```
  
  ### $?
`?` is substitued with the return value of the last program executed.

Example:
```
  $ echo "echo $?" | ./lsh
  0
```

### $$
The second `$` is substitued with the current process ID.

Example:
 ```
  $ echo "echo $$" | ./lsh
  6494
```

### Comments 💭
**lsh** ignores all words and characters preceeded by a `#` character on a line.

Example:
```
  $ echo "echo 'hello' #this will be ignored!" | ./lsh
  'hello'
```

### Operators 🎸
**lsh** specially interprets the following operator characters:

; - Command separator
Commands separated by a `;` are executed sequentially.

Example:
```
  $ echo "echo 'hello' ; echo 'world'" | ./lsh
  'hello'
  'world'
```

### && - AND logical operator
`command1 && command2`: `command2` is executed if, and only if, `command1` returns an exit status of zero.

Example:
```
  $ echo "error! && echo 'hello'" | ./lsh
  ./lsh: 1: error!: not found
  $ echo "echo 'all good' && echo 'hello'" | ./lsh
  'all good'
  'hello'
```

### || - OR logical operator
`command1 || command2`: `command2` is executed if, and only if, `command1` returns a non-zero exit status.

Example:
```
  $ echo "error! || echo 'but still runs'" | ./lsh
  ./lsh: 1: error!: not found
  'but still runs'
```
The operators `&&` and `||` have equal precedence, followed by `;`.

### Lsh Builtin Commands 🔩
**cd**

- Usage: `cd [DIRECTORY]`
- Changes the current directory of the process to `DIRECTORY`.
- If no argument is given, the command is interpreted as `cd $HOME`.
- If the argument `-` is given, the command is interpreted as `cd $OLDPWD` and the pathname of the new working directory is printed to standad output.
- If the argument, `--` is given, the command is interpreted as `cd $OLDPWD` but the pathname of the new working directory is not printed.
- The environment variables `PWD` and `OLDPWD` are updated after a change of directory.
Example:
```
  $ ./lsh
  $ pwd
  /home/vagrant/holberton/simple_shell
  $ cd ../
  $ pwd
  /home/vagrant/holberton
  $ cd -
  $ pwd
  /home/vagrant/holberton/simple_shell
```

### alias
- Usage: `alias [NAME[='VALUE'] ...]`
- Handles aliases.
- `alias`: Prints a list of all aliases, one per line, in the form `NAME='VALUE'`.
- `alias NAME [NAME2 ...]`: Prints the aliases `NAME`, `NAME2`, etc. one per line, in the form `NAME='VALUE'`.
- `alias NAME='VALUE' [...]`: Defines an alias for each `NAME` whose `VALUE` is given. If `name` is already an alias, its value is replaced with `VALUE`.
Example:
```
  $ ./slsh
  $ alias show=ls
  $ show
  AUTHORS     environ.c  getenv.c   lists.c             realloc.c     string1.c
  README.md   errors.c   getinfo.c  lsh                 shell.c       tokenizer.c
  _atoi.c     errors1.c  getline.c  man_1_simple_shell  shell.h       vars.c
  builtin.c   history.c  memory.c   shell_loop.c        string.c      parser.c 
  builtin1.c  exits.c    list1.c               
```

### exit
- Usage: `exit [STATUS]`
- Exits the shell.
- The `STATUS` argument is the integer used to exit the shell.
- If no argument is given, the command is interpreted as exit `0`.
Example:
```
  $ ./lsh
  $ exit
  ```
 ### env
- Usage: `env`
- Prints the current environment.
Example:
```
  $ ./lsh
  $ env
NVM_DIR=/home/vagrant/.nvm
...
```
### setenv
- Usage: `setenv [VARIABLE] [VALUE]`
- Initializes a new environment variable, or modifies an existing one.
- Upon failure, prints a message to `stderr`.

Example:
```
  $ ./lsh
  $ setenv NAME Poppy
  $ echo $NAME
  Poppy
  ```
  
### unsetenv
- Usage: `unsetenv [VARIABLE]`
- Removes an environmental variable.
- Upon failure, prints a message to `stderr`.

Example:
```
  $ ./lsh
  $ setenv NAME Poppy
  $ unsetenv NAME
  $ echo $NAME
  
  $
  ```
 
### flowcart

### Authors ✒️
- Boluwatife Oyewumi <[Bolexzy]()>
- Brennan D Baraban <[bdbaraban]()>

Acknowledgements 🙏
**Lsh** emulates basic functionality of the **sh** shell. This README borrows form the Linux man pages [sh(1)](https://linux.die.net/man/1/sh) and [dash(1)](https://linux.die.net/man/1/dash).

This project was written as part of the curriculum for ALX-Holberton School. ALX Africa is a project-based full-stack software engineering program that prepares students for careers in the tech industry using project-based peer learning. For more information, visit this [link](https://www.alxafrica.com/alx-se-oct-2022-high-school?utm_source=google&utm_medium=youth-search&utm_campaign=18-24-se-youth-nigeria&gclid=Cj0KCQjwk5ibBhDqARIsACzmgLSTQeXelpWqV326kaO4CVdhyFJPnRjWYcIM43YQdQ5tcbhNFPEDqr8aAikkEALw_wcB).
