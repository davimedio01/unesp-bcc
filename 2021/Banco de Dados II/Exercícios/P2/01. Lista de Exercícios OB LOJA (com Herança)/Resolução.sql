rem Lista de Exercícios sobre Banco de Dados Objeto-Relacional
rem Minimundo: LOJA
rem Autor: Davi Augusto Neves Leite
rem ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
rem 1) Faça a modelagem objeto-relacionado correspondente ao DER do PDF, seguindo as restrições
rem     - Restrições de chave primária devem ser definidas e observadas;
rem     - Restrições de chave estrangeira devem ser definidas e observadas;
rem     - A classe "Pessoa" não poderá ser instanciada;
rem     - O "Nome" da entidade "Loja" deve ser ÚNICO;
rem     - O "Nome" da entidade "Cliente" não pode ser NULL.


rem Restrição: classe "Pessoa" não pode ser instanciável
create or replace type PESSOA_TY
NOT Instantiable NOT Final;



rem 2) Criar uma instância de cada entidade e de cada relacionamento (desde que sejam instanciáveis)
rem Nada mais é do que construir e popular as tabelas!



rem 3) Expressar as seguintes consultas
rem a) Para cada produto que foi comprado por um cliente, retornar o nome do produto, o nome da loja que possui o produto e o nome do cliente que comprou o produto.
rem     * Utilizar na consulta apenas a tabela correspondente ao tipo entidade Produto



rem b) Retornar os nomes e os respectivos telefones dos funcionários da loja "Sears"



rem 4) Adicione um método "TempoServico" na classe Funcionário que calcula e retorna quantos anos o funcionário trabalha na empresa



rem 5) Escreva gatilhos para garantir a restrição de disjunção entre as subclasses Funcionário e Cliente


