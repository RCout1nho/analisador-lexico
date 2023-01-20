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
  - identifica char
    - valida a quantidade de caracteres
    - valida se o char termina (se existe um par de `'`)
  - identifica string
    - validade se a string termina (se existe um par de `"`)
