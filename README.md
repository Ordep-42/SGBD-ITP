# SGBD-ITP

### Implementação de um Sistema de Gerenciamento de Banco de Dados básico em C

## Autores:
  Pedro Galvão do Amaral Neto\
  Bianca Maciel Medeiros

## Instruções de instalação e compilação
  1. **Clone o repositório**

    git clone git@github.com:Ordep-42/SGBD-ITP.git SGBD
    
  2. **Rode o make, crie uma pasta "data" no diretório raiz e execute o código**

    make build
    mkdir data
    ./SGBD

## Instruções de uso
  ## Menu
  Ao iniciar o SGBD você dará de cara com o menu inicial:
  ```
  ====================================
  ------------Bem Vindo(a)------------
  ----------------MENU----------------
  O que gostaria de fazer?
  1 - Criar uma nova tabela
  2 - Listar todas as tabelas
  3 - Listar dados de uma tabela
  4 - Adicionar uma tupla em uma tabela
  5 - Pesquisar valor em uma tabela
  6 - Apagar uma tupla de uma tabela
  7 - Deletar uma tabela
  8 - Sair
  Digite o numero da acao desejada:
  ```
  ***
  ### 1. Criar tabela
  Digite o nome da tabela e a quantidade de colunas que sua tabela terá. Após isso o programa pedirá o nome e o tipo de cada uma das colunas. O padrão dos tipos é similar aos tipos primitivos de C:

  * UNSIGNED_INT
  * INT
  * FLOAT
  * DOUBLE
  * CHAR
  * STRING

  Após isso o programa irá solicitar qual das colunas deverá armazenar a chave primária das linhas da tabela. A coluna selecionada deve ser do tipo UNSIGNED_INT (Inteiro sem sinal).

  Exemplo:
  ```
  ====================================
  Digite o nome da tabela: Aluno
  Digite o número de colunas para a tabela: 3
  ====================================
  Digite o nome da 1ª coluna: Matrícula
  O tipo da coluna pode ser:
  INT, UNSIGNED_INT, FLOAT, DOUBLE, CHAR ou STRING
  Digite o tipo desejado da 1ª coluna: UNSIGNED_INT
  ====================================
  Digite o nome da 2ª coluna: Nome
  O tipo da coluna pode ser:
  INT, UNSIGNED_INT, FLOAT, DOUBLE, CHAR ou STRING
  Digite o tipo desejado da 2ª coluna: STRING
  ====================================
  Digite o nome da 3ª coluna: Nota
  O tipo da coluna pode ser:
  INT, UNSIGNED_INT, FLOAT, DOUBLE, CHAR ou STRING
  Digite o tipo desejado da 3ª coluna: FLOAT
  ====================================
  Digite o nome da coluna que contem a chave primária: Matrícula
  ====================================
  Tabela Aluno adicionada com sucesso!
  ```
  ***
  ### 2. Listar tabelas
  Todas as tabelas criadas serão listadas.\
  Exemplo de saída:
  ```
  ====================================
  Nomes das tabelas existentes:
  Aluno
  Tabela 1
  Tabela 2
  Tabela 3
  ```  
  ***
  ### 3. Listar dados de uma tabela
  O programa irá pedir o nome da tabela a ser listada e mostrará os nomes das colunas e todas as linhas da tabela.

  Exemplo de saída:
  ```
  ====================================
  Nomes das tabelas existentes:
  Aluno
  Tabela 1
  Tabela 2
  Tabela 3
  ====================================
  Digite o nome da tabela que deseja visualizar:
  Aluno
  ====================================
  |    Matrícula|         Nome|         Nota|
  ====================================
  |            1|       Fulano|     2.356500|
  ====================================
  |            2|      Cicrano|     2.000000|
  ====================================
  |            3|     Beltrano|     5.000000|
  ====================================
  ```
  ***
  ### 4. Adicionar uma linha a uma tabela
  O programa irá pedir o nome da tabela na qual a linha será adicionada, e irá pedir os valores para cada coluna da linha a ser criada, incluindo a chave primária da linha, que o programa verificará se é valida.

  Exemplo:
  ```
  ====================================
  Digite o nome da tabela que deseja adicionar uma linha: Aluno
  ====================================
  Digite o valor da coluna Matrícula de tipo UNSIGNED_INT: 4
  ====================================
  Digite o valor da coluna Nome de tipo STRING: Fulaninho
  ====================================
  Digite o valor da coluna Nota de tipo FLOAT: 5.3
  ====================================
  Linha 4 adicionada na tabela Aluno com sucesso!
  ```
  ***
  ### 5. Pesquisar um valor em uma tabela

  ***
  ### 6. Apagar uma linha de uma tabela
  O programa pedirá o valor da chave primária da linha a ser apagada e verificará se existe alguma linha com essa chave primária, se existir, irá apaga-la. **CUIDADO essa ação é destrutiva e não pode ser revertida!**
  ***
  ### 7. Apagar uma tabela
  O programa pedirá o nome da tabela a ser apagada e verificará se existe alguma tabela com esse nome, se existir, irá apaga-la. **CUIDADO essa ação é destrutiva e não pode ser revertida!**

  Exemplo:
  ```
  ====================================
  Nomes das tabelas existentes:
  Aluno
  Tabela 1
  Tabela 2
  Tabela 3
  ====================================
  Digite o nome da tabela que deseja apagar:
  Aluno
  ====================================
  Tabela Aluno apagada com sucesso!
  ```
  ***
  ### 8. Sair
  Ao selecionar essa opção o programa é encerrado.