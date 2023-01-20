# Reconhece

- identficadores
  - iniciando com letras
  - iniciando com `$`
  - iniciando com `_`
- sinais de pontuação
  - não vê se uma `{` tem seu fechamento, mas acho que esse seria o papel do analisador sintático
- operadores
  - identifica todos os operadores descritos em código
- palavras reservadas
  - idenfica todas as palavras reservadas descritas em código
- literais
  - identifica números inteiros
  - identifica números reais
    - valida se tem apenas 1 `.`
  - identifica char
    - valida a quantidade de caracteres
    - valida se o char termina (se existe um par de `'`)
  - identifica string
    - validade se a string termina (se existe um par de `"`)
- comentário
  - linha simples
  - bloco

---

## Detalhes

Os tokens são agrupados de forma ordenada em `tuplas` estruturadas por um vetor de structs do tipo `token`.

Para encontrar um elemento nesse vetor de tuplas, é utilizado `busca binária` para garantir um desempenho superior à uma `busca sequencial` simples.

## O que falta?

- validar erros nos identificadores
- validar errors nos numeros
