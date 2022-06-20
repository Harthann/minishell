## MINISHELL

Minishell is little reimplementation of bash like command line tools.
As it is a school a project, parsing and command implementation remain pretty basic.

# Builtins:

  - `echo`
  - `env`
  - `export`
  - `unset`
  - `cd`
  - `exit`

Every other command will go through `execve` if there's a binary available on the path. Else `Command not found` will be prompt.

# Pipe and redirections:

Pipe and redirections are handled but could probably more efficient, as we didn't use an AST for the parsing these were kind of hard to manage
