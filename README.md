# **lsh - Simple Shell 🐚 **

This is a simple UNIX command interpreter written as part of the low-level programming and algorithm track at ALX Africa.

## Description 📝

Lsh is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

## Invocation 🪄

Usage: **lsh** [*filename*]

To invoke **lsh**, compile all `.c` files in the repository and run the resulting executable:

```
  gcc *.c -o shellby
  ./shellby
```

**lsh** can be invoked both interactively and non-interactively. If shellby is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

Example:
```
  $ echo "echo 'hello'" | ./lsh
  'hello'
  $
  ```
  
  If **lsh** is invoked with standard input connected to a terminal (determined by [isatty(3)])(https://linux.die.net/man/3/isatty), an interactive shell is opened. When executing interactively, shellby displays the prompt $ when it is ready to read a command.
  
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
  
  Upon invocation, sodash receives and copies the environment of the parent process in which it was executed. This environment is an array of name-value strings describing variables in the format *NAME=VALUE*. A few key environmental variables are:
  
  ## Home 

The home directory of the current user and the default directory argument for the cd builtin command.
```
  $ echo "echo $HOME" | ./lsh
  /home/vagrant
  ```
  
##  PWD
The current working directory as set by the **cd** command.
 ```
  $ echo "echo $PWD" | ./shellby
  /home/vagrant/holberton/simple_shell
  ```

## OLDPWD

The previous working directory as set by the **cd** command.
```
  $ echo "echo $OLDPWD" | ./shellby
  /home/vagrant/holberton/printf
  ```
  
## PATH

A colon-separated list of directories in which the shell looks for commands. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directory.
```
$ echo "echo $PATH" | ./lsh
/home/vagrant/.cargo/bin:/home/vagrant/.local/bin:/home/vagrant/.rbenv/plugins/ruby-build/bin:/home/vagrant/.rbenv/shims:/home/vagrant/.rbenv/bin:/home/vagrant/.nvm/versions/node/v10.15.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/vagrant/.cargo/bin:/home/vagrant/workflow:/home/vagrant/.local/bin
```
