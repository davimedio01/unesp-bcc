import java.sql.*;

class Inserir {
     public static void main(String[] args) {
          try{
               // Carregando driver da HypersonicSQL
               Class.forName("org.hsql.jdbcDriver");
               //Abrindo a conexão
               Connection con = DriverManager.getConnection("jdbc:HypersonicSQL:hsql://localhost:8080", "sa", "");
               //Criando variável genérica (PreparedStatement) para comandos
               PreparedStatement pStmt = con.prepareStatement("INSERT INTO ESTUDANTES VALUES (?, ?, ?, ?);");

               //Inserindo alguns campos...
               // Campo 1
               pStmt.setInt(1, 191027383);
               pStmt.setString(2, "Davi Neves");
               pStmt.setString(3, "11958682744");
               pStmt.setString(4, "BCC");
               pStmt.executeUpdate(); // Atualizando tabela

               // Campo 2
               pStmt.setInt(1, 191128494);
               pStmt.setString(2, "Luis Henrique");
               pStmt.setString(3, "14999992176");
               pStmt.setString(4, "Matemática");
               pStmt.executeUpdate(); // Atualizando tabela

               // Campo 3
               pStmt.setInt(1, 204829942);
               pStmt.setString(2, "Gustavo Stahl");
               pStmt.setString(3, "19992740000");
               pStmt.setString(4, "Química");
               pStmt.executeUpdate(); // Atualizando tabela

               // Campo 4
               pStmt.setInt(1, 902948215);
               pStmt.setString(2, "Rafael Kawagoe");
               pStmt.setString(3, "11970005555");
               pStmt.setString(4, "Design Gráfico");
               pStmt.executeUpdate(); // Atualizando tabela

               //Fechando banco de dados e comandos
               pStmt.close();
               con.close();

          }catch(Exception e){
               System.out.println("Erro: " + e);
          }

     }
}