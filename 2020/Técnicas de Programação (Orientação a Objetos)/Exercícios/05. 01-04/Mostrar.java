import java.sql.*;

class Mostrar {
     public static void main(String[] args) {
          try{
               //Carregando driver do HypersonicSQL
               Class.forName("org.hsql.jdbcDriver");
               //Abrindo a conexão
               Connection con = DriverManager.getConnection("jdbc:HypersonicSQL:hsql://localhost:8080", "sa", "");
               //Variável para comandos no Banco de Dados
               Statement stmt = con.createStatement();

               //Criando variável para recuperar CADA campo da tabela (com Select)
               ResultSet rs = stmt.executeQuery("SELECT * FROM ESTUDANTES");
               System.out.println("RA\t\tNOME\t\tTELEFONE\tCURSO\n");
               while(rs.next()){
                    //Mostrando campos (por linha)
                    System.out.println(rs.getInt("RA") + "\t" + rs.getString("NOME") + "\t"
                              + rs.getString("TELEFONE") + "\t" + rs.getString("CURSO"));
               }

               //Fechando a conexão e os comandos
               stmt.close();
               con.close(); 

          }catch(Exception e){
               System.out.println("Erro: " + e);
          }
     }
}