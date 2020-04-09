# Trabalho Prático de Sistemas Operativos
## SimpleDU
### Modo de utilização:
```console
simpledu -l [path] [-a] [-b] [-B size] [-L] [-S] [--max-depth=N]
```
### Opções de invocação:
Flags | Descrição
----- | -----------
-a/--all | a informação exibida diz respeito também a ficheiros
-b/--bytes | apresenta o número real de bytes de dados (ficheiros) ou alocados (diretórios)
-B/--block-size=SIZE | define o tamanho (bytes) do bloco para efeitos de representação
-l/--count-links | contabiliza múltiplas vezes o mesmo ficheiro
-L/--dereference | segue links simbólicos
-S/--separate-dirs | a informação exibida não inclui o tamanho dos subdiretórios
--max-depth=N | limita a informação exibida a N (0,1, ...) níveis de profundidade de diretórios

### Features
- Todas as features pedidas estão implementadas e funcionais
- A análise de diretórios é feita por recursividade

### Falta implementar
- Handler de sinais

### Notas adicionais:
- No computador de um dos elementos do grupo, o comando 'du' relativamente a symbolic links ocupava um bloco (em vez de zero)

