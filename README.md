# 42-minishell

```
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck --track-fds=yes --trace-children=yes --quiet --suppressions=readline.supp ./minishell
```