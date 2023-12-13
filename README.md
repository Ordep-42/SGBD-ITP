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
  ***
  ### 2. Listar tabelas
  Todas as tabelas criadas serão listadas.\
  Exemplo de saída:
  ```
  ====================================
  Nomes das tabelas existentes:
  Tabela 1
  Tabela 2
  Tabela 3
  ```  
  ***
  ### 3. Listar dados de uma tabela
  O programa irá pedir o nome da tabela a ser listada e mostrará os nomes das colunas e todas as linhas da tabela. 


  ### 4. Adicionar uma linha a uma tabela


  ### 5. Pesquisar um valor em uma tabela


  ### 6. Apagar uma linha de uma tabela


  ### 7. Apagar uma tabela


  ### 8. Sair