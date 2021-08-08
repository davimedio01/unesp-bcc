import java.sql.*;

class Criar {
     public static void main(String[] args) {
          try{
               //Carregando o driver do HypersonicSQL
               Class.forName("org.hsql.jdbcDriver");
               //Abrindo a conexão (porta 8080 definida em Server.properties)
               Connection con = DriverManager.getConnection("jdbc:HypersonicSQL:hsql://localhost:8080", "sa", "");
               //Criando variável para realizar comandos ao Banco de Dados (Statement)
               Statement stmt = con.createStatement();
               
               //Criando tabela e campos
                    //Tabela: Estudantes
                    //Campos: RA (Primary Key); Nome; Telefone; Curso
               stmt.executeUpdate("CREATE TABLE ESTUDANTES (" +
               "RA INT NOT NULL PRIMARY KEY," +
               "NOME VARCHAR(50) NOT NULL," +
               "TELEFONE CHAR(11)," +
               "CURSO VARCHAR(30) NOT NULL" +
               ");");

               //Fechando a conexão e a variável de comandos
               stmt.close();
               con.close();
          }catch(Exception e){
               System.out.println("Erro: " + e);
          }
     }
}
