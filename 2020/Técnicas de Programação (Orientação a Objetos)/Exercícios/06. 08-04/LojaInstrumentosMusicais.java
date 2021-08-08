import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.sql.*;

//Imagens
import java.net.*;

class LojaInstrumentosMusicais extends JFrame implements ActionListener {

     // Tamanho da Janela
     final int WIDTH = 1200, HEIGHT = 700;

     // Variáveis para o Banco de Dados
     Connection con; // Abrir Conexão
     Statement stmt; // Comandos

     // Janela para os JInternalFrame
     JDesktopPane desktopPrincipal; // "Desktop Virtual"
     JMenuItem clienteInsere;
     JMenuItem fornecedorInsere;
     JMenuItem instrumentoInsere;
     JMenuItem clienteConsulta;
     JMenuItem fornecedorConsulta;
     JMenuItem instrumentoConsulta;
     JMenuItem vendasInsere;
     JMenuItem vendasConsulta;

     public LojaInstrumentosMusicais() {
          // Nome da Loja
          super("Instrumentos JMusic");

          // Configuração Inicial da Janela Principal
          setSize(WIDTH, HEIGHT); // Tamanho da Janela
          setResizable(false);
          setLocationRelativeTo(null); // Centro da Tela
          // Tratamento do Fechamento
          addWindowListener(new WindowAdapter() {
               public void windowClosing(final WindowEvent e) {
                    final int opc = JOptionPane.showConfirmDialog(null, "Deseja realmente fechar o programa?", "Fechar",
                              JOptionPane.YES_NO_OPTION);
                    if (opc == 0) {
                         try {
                              con.close();
                         } catch (SQLException sqle) {
                              JOptionPane.showMessageDialog(null,
                                        "Erro no fechamento do servidor do banco de dados.\nErro: " + sqle,
                                        "Erro de Fechamento de Servidor", JOptionPane.ERROR_MESSAGE);
                         }
                         finally{
                              System.exit(0);
                         }
                    }
               }
          });
          setDefaultCloseOperation(DO_NOTHING_ON_CLOSE); // Saída

          // Iniciando Banco de Dados
          iniciarBancoDeDados();
          iniciarTabelas(); // Criar Tabelas

          // Adicionando o JDesktopPane no JFrame
          desktopPrincipal = new JDesktopPane();
          desktopPrincipal.setBackground(Color.BLACK);
          setContentPane(desktopPrincipal);

          ////////////////////////////////////////////
          defineFundoIcone(); // Fundo de Tela e Icone
          ////////////////////////////////////////////

          // Configurando o Menu Superior
          setJMenuBar(criarMenu());

          setVisible(true); // Visível
     }

     // Fundo de Tela e Icone
     protected void defineFundoIcone() {
          URL site;
          // Icone do JFrame
          try {
               site = new URL("https://i.ibb.co/KVThd47/icon.png");
               ImageIcon icone = new ImageIcon(site);
               this.setIconImage(icone.getImage());
          } catch (MalformedURLException e) {
               e.printStackTrace();
          }

          // Fundo de Tela
          try {
               site = new URL("https://i.ibb.co/5RVkz7X/fundo2.jpg");
               ImageIcon fundo = new ImageIcon(site);
               JLabel label = new JLabel(fundo);
               label.setBounds(0, 0, WIDTH, HEIGHT);

               desktopPrincipal.add(label, Integer.MIN_VALUE);
          } catch (MalformedURLException e) {
               e.printStackTrace();
          }
     }

     // Inicialização do Banco de Dados
     void iniciarBancoDeDados() {
          try {
               Class.forName("org.hsql.jdbcDriver");
               con = DriverManager.getConnection("jdbc:HypersonicSQL:hsql://localhost:8080", "sa", "");
          } catch (ClassNotFoundException e) {
               JOptionPane.showMessageDialog(null, "O driver do banco de dados não foi encontrado.\nErro: " + e,
                         "Erro de Driver", JOptionPane.ERROR_MESSAGE);
               System.exit(0);
          } catch (SQLException e) {
               JOptionPane.showMessageDialog(null, "Erro na abertura do servidor do banco de dados.\nErro: " + e,
                         "Erro de Abertura de Servidor", JOptionPane.ERROR_MESSAGE);
               System.exit(0);
          }
     }

     // Criação das Tabelas
     void iniciarTabelas() {
          try {
               // Verificando se Tabelas já existem
               ResultSet tabelaVenda = con.getMetaData().getTables(null, null, "VENDA", null);

               // Se não existirem, criar
               stmt = con.createStatement();
               if (tabelaVenda.next() == false) {
                    // Cliente
                    stmt.executeUpdate("CREATE TABLE CLIENTE (" + "ID INT NOT NULL PRIMARY KEY,"
                              + "NOME VARCHAR(50) NOT NULL," + "RG CHAR(9) NOT NULL," + "TELEFONE CHAR(11),"
                              + "ENDERECO VARCHAR(50) NOT NULL" + ");");
                    // Fornecedor
                    stmt.executeUpdate("CREATE TABLE FORNECEDOR (" + "ID INT NOT NULL PRIMARY KEY,"
                              + "NOME VARCHAR(50) NOT NULL," + "CNPJ CHAR(14) NOT NULL," + "TELEFONE CHAR(11),"
                              + "ENDERECO VARCHAR(50) NOT NULL" + ");");
                    // Instrumentos Musicais
                    stmt.executeUpdate("CREATE TABLE INSTRUMENTO (" + "ID INT NOT NULL PRIMARY KEY,"
                              + "NOME VARCHAR(50) NOT NULL," + "MARCA VARCHAR(10) NOT NULL,"
                              + "TIPO VARCHAR(20) NOT NULL," + "PRECO_UNIDADE FLOAT NOT NULL" + ");");
                    // Vendas
                    stmt.executeUpdate("CREATE TABLE VENDA (" + "ID INT NOT NULL PRIMARY KEY,"
                              + "ID_CLIENTE INT NOT NULL," + "ID_INSTRUMENTO INT NOT NULL," + "QUANTIDADE INT NOT NULL,"
                              + "PRECO_TOTAL FLOAT NOT NULL" + ");");
               }

          } catch (SQLException e) {
               JOptionPane.showMessageDialog(null, "Erro ao criar tabelas.\nErro: " + e, "Erro de Criação de Tabelas",
                         JOptionPane.ERROR_MESSAGE);
          } catch (NullPointerException e) {
               JOptionPane.showMessageDialog(null, "Erro interno.\nErro: " + e, "Erro Interno",
                         JOptionPane.ERROR_MESSAGE);
          } finally {
               try {
                    stmt.close();
               } catch (SQLException e) {
                    JOptionPane.showMessageDialog(null, "Erro ao criar tabelas.\nErro: " + e,
                              "Erro de Criação de Tabelas", JOptionPane.ERROR_MESSAGE);
               }
          }
     }

     // Criação do Menu
     JMenuBar criarMenu() {
          JMenuBar menuBar = new JMenuBar();

          // Criação do Menu: "Inserção"
          JMenu menuInsercao = new JMenu("Inserção");
          // Sub-Menu: Cliente, Fornecedor, Instrumento
          clienteInsere = new JMenuItem("Cliente", 1);
          fornecedorInsere = new JMenuItem("Fornecedor", 2);
          instrumentoInsere = new JMenuItem("Instrumento", 3);
          menuInsercao.add(clienteInsere);
          menuInsercao.add(fornecedorInsere);
          menuInsercao.add(instrumentoInsere);
          menuBar.add(menuInsercao);

          // Criação do Menu: "Consulta"
          JMenu menuConsulta = new JMenu("Consulta");
          // Sub-Menu: Cliente, Fornecedor, Instrumento
          clienteConsulta = new JMenuItem("Cliente", 4);
          fornecedorConsulta = new JMenuItem("Fornecedor", 5);
          instrumentoConsulta = new JMenuItem("Instrumento", 6);
          menuConsulta.add(clienteConsulta);
          menuConsulta.add(fornecedorConsulta);
          menuConsulta.add(instrumentoConsulta);
          menuBar.add(menuConsulta);

          // Criação do Menu: "Vendas"
          JMenu menuVendas = new JMenu("Vendas");
          // Sub-Menu: Inserção, Consulta
          vendasInsere = new JMenuItem("Inserção", 7);
          vendasConsulta = new JMenuItem("Consulta", 8);
          menuVendas.add(vendasInsere);
          menuVendas.add(vendasConsulta);
          menuBar.add(menuVendas);

          // Ações dos Botões
          clienteInsere.addActionListener(this);
          fornecedorInsere.addActionListener(this);
          instrumentoInsere.addActionListener(this);
          clienteConsulta.addActionListener(this);
          fornecedorConsulta.addActionListener(this);
          instrumentoConsulta.addActionListener(this);
          vendasInsere.addActionListener(this);
          vendasConsulta.addActionListener(this);

          return menuBar;
     }

     // Configuração dos Botões
     public void actionPerformed(ActionEvent e) {
          if (e.getSource() == clienteInsere) {
               new janelaInsere(desktopPrincipal, con, "CLIENTE");
          } else if (e.getSource() == fornecedorInsere) {
               new janelaInsere(desktopPrincipal, con, "FORNECEDOR");
          } else if (e.getSource() == instrumentoInsere) {
               new janelaInsere(desktopPrincipal, con, "INSTRUMENTO");
          } else if (e.getSource() == clienteConsulta) {
               new janelaConsulta(desktopPrincipal, con, "CLIENTE");
          } else if (e.getSource() == fornecedorConsulta) {
               new janelaConsulta(desktopPrincipal, con, "FORNECEDOR");
          } else if (e.getSource() == instrumentoConsulta) {
               new janelaConsulta(desktopPrincipal, con, "INSTRUMENTO");
          } else if (e.getSource() == vendasInsere) {
               new janelaVenda(desktopPrincipal, con);
          } else if (e.getSource() == vendasConsulta) {
               new janelaConsulta(desktopPrincipal, con, "VENDA");
          }
     }

     public static void main(String[] args) {
          new LojaInstrumentosMusicais();
     }
}

// Classe de Inserção
class janelaInsere extends JInternalFrame {
     PreparedStatement pstmt; // Comandos SQL
     JDesktopPane desktop; // Janela
     JButton btnInserir; // Botão para Enviar
     JTextField campo1, campo2, campo3, campo4, campo5; // Campos

     public janelaInsere(JDesktopPane desk, Connection con, String opc) {
          super("Inserção na Tabela " + opc, false, true, false, false);
          desktop = desk;

          try {
               pstmt = con.prepareStatement("INSERT INTO " + opc + " VALUES (?, ?, ?, ?, ?)");

               // Configurando layout da janela
               JPanel sup1 = new JPanel(new GridLayout(10, 1));
               // Verificando a opção para acrescentar campos corretamente
               sup1.add(new JLabel("ID: "));
               sup1.add(campo1 = new JTextField(10));
               if (opc.equals("CLIENTE")) { // Cliente
                    sup1.add(new JLabel("Nome: "));
                    sup1.add(campo2 = new JTextField(50));
                    sup1.add(new JLabel("RG (SOMENTE NÚMEROS): "));
                    sup1.add(campo3 = new JTextField(9));
                    sup1.add(new JLabel("Telefone (SOMENTE NÚMEROS): "));
                    sup1.add(campo4 = new JTextField(11));
                    sup1.add(new JLabel("Endereço: "));
                    sup1.add(campo5 = new JTextField(50));
               } else if (opc.equals("FORNECEDOR")) { // Fornecedor
                    sup1.add(new JLabel("Nome: "));
                    sup1.add(campo2 = new JTextField(50));
                    sup1.add(new JLabel("CNPJ (SOMENTE NÚMEROS): "));
                    sup1.add(campo3 = new JTextField(14));
                    sup1.add(new JLabel("Telefone (SOMENTE NÚMEROS): "));
                    sup1.add(campo4 = new JTextField(11));
                    sup1.add(new JLabel("Endereço: "));
                    sup1.add(campo5 = new JTextField(50));
               } else if (opc.equals("INSTRUMENTO")) { // Instrumentos de Música
                    sup1.add(new JLabel("Nome do Produto: "));
                    sup1.add(campo2 = new JTextField(50));
                    sup1.add(new JLabel("Marca: "));
                    sup1.add(campo3 = new JTextField(10));
                    sup1.add(new JLabel("Tipo de Instrumento: "));
                    sup1.add(campo4 = new JTextField(20));
                    sup1.add(new JLabel("Preço (SOMENTE NÚMEROS): "));
                    sup1.add(campo5 = new JTextField(10));
               }

               add(sup1, BorderLayout.NORTH);
               add(new JLabel(" "), BorderLayout.CENTER);
               add(btnInserir = new JButton("Inserir"), BorderLayout.SOUTH);
               pack();
               setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
               setVisible(true);
               desktop.add(this);

               // Configurando ação do botão para inserir
               btnInserir.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                         if (campo1.getText().isEmpty() == false && campo2.getText().isEmpty() == false
                                   && campo3.getText().isEmpty() == false && campo4.getText().isEmpty() == false
                                   && campo5.getText().isEmpty() == false) {
                              try {
                                   // Setando campos com as strings colocadas e com a opção desejada
                                   pstmt.setInt(1, Integer.parseInt(campo1.getText()));
                                   pstmt.setString(2, campo2.getText());
                                   pstmt.setString(3, campo3.getText());
                                   pstmt.setString(4, campo4.getText());
                                   if (opc.equals("CLIENTE") || opc.equals("FORNECEDOR")) {
                                        pstmt.setString(5, campo5.getText());
                                   } else if (opc.equals("INSTRUMENTO")) {
                                        pstmt.setFloat(5, Float.parseFloat(campo5.getText()));
                                   }

                                   campo1.setText("");
                                   campo2.setText("");
                                   campo3.setText("");
                                   campo4.setText("");
                                   campo5.setText("");

                                   // Atualizando a tabela
                                   pstmt.executeUpdate();

                                   // Caso obtenha sucesso ao inserir dados...
                                   JOptionPane.showMessageDialog(desktop, "Dados inseridos com sucesso!", "Sucesso",
                                             JOptionPane.INFORMATION_MESSAGE);
                              } catch (Exception ex) {
                                   JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + ex, "Erro Interno",
                                             JOptionPane.ERROR_MESSAGE);
                              }
                         } else {
                              JOptionPane.showMessageDialog(desktop,
                                        "Campo(s) vazio(s). Preencha todos corretamente.", "Erro de Inserção",
                                        JOptionPane.ERROR_MESSAGE);
                         }

                    }
               });

          } catch (Exception ex) {
               JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + ex, "Erro Interno",
                         JOptionPane.ERROR_MESSAGE);
          } finally {
               try {
                    pstmt.close();
                    // con.close();
               } catch (SQLException esql) {
                    JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + esql, "Erro Interno",
                              JOptionPane.ERROR_MESSAGE);
               }
          }
     }
}

// Classe de Consulta
class janelaConsulta extends JInternalFrame {
     PreparedStatement pstmt1, pstmt2; // Comandos SQL
     JDesktopPane desktop; // Janela
     JButton btnConsulta; // Botão para Confirmar Consulta
     JTextField campo; // Código digitado pelo Usuário
     JTextArea mostraDados;

     public janelaConsulta(JDesktopPane desk, Connection con, String opc) {
          super("Consulta na Tabela " + opc, false, true, false, false);
          desktop = desk;
          try {
               pstmt1 = con.prepareStatement("SELECT * FROM " + opc + " WHERE ID LIKE ?");

               // Configurando Layout
               setLayout(new BorderLayout());

               // Configurando Janela
               // ID Panel
               JPanel idPanel = new JPanel(new FlowLayout());
               idPanel.add(new JLabel("ID: "));
               idPanel.add(campo = new JTextField(10));
               idPanel.add(btnConsulta = new JButton("Consultar"));
               add(idPanel, BorderLayout.NORTH);

               // Dados Panel
               JScrollPane dados = new JScrollPane(mostraDados = new JTextArea(20, 80));
               dados.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
               dados.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
               mostraDados.setFont(new Font(Font.SANS_SERIF, Font.PLAIN, 14));
               
               JPanel txtPanel = new JPanel(new BorderLayout());
               txtPanel.add(dados, BorderLayout.CENTER);

               add(txtPanel, BorderLayout.CENTER);
               pack();
               setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
               setVisible(true);
               desktop.add(this);

               ////////////////////////////////////////////////////
               // Mostrando todos os dados e colocando no JTextArea
               mostraTodosDados(con, opc);
               ///////////////////////////////////////////////////

               // Configurando ação do botão
               btnConsulta.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                         try {
                              mostraDados.setText("");
                              pstmt1.setInt(1, Integer.parseInt(campo.getText()));
                              // Mostrando dados
                              ResultSet rs = pstmt1.executeQuery();
                              while (rs.next()) {
                                   if (opc.equals("CLIENTE")) {
                                        mostraDados.append(String.format(
                                                  "ID: %d\n" + "Nome: %s\n" + "RG: %s\n" + "Telefone: %s\n"
                                                            + "Endereço: %s\n\n",
                                                  rs.getInt(1), rs.getString(2), rs.getString(3), rs.getString(4),
                                                  rs.getString(5)));
                                   } else if (opc.equals("FORNECEDOR")) {
                                        mostraDados.append(String.format(
                                                  "ID: %d\n" + "Nome: %s\n" + "CNPJ: %s\n" + "Telefone: %s\n"
                                                            + "Endereço: %s\n\n",
                                                  rs.getInt(1), rs.getString(2), rs.getString(3), rs.getString(4),
                                                  rs.getString(5)));
                                   } else if (opc.equals("INSTRUMENTO")) {
                                        mostraDados.append(String.format(
                                                  "ID: %d\n" + "Nome do Produto: %s\n" + "Marca: %s\n"
                                                            + "Tipo de Instrumento: %s\n" + "Preço Unitário: %.2f\n\n",
                                                  rs.getInt(1), rs.getString(2), rs.getString(3), rs.getString(4),
                                                  rs.getFloat(5)));
                                   } else if (opc.equals("VENDA")) {
                                        mostraDados.append(String.format(
                                                  "ID: %d\n" + "ID do Cliente: %d\n" + "ID do Produto: %d\n"
                                                            + "Quantidade: %d\n" + "Preço Total: %.2f\n\n",
                                                  rs.getInt(1), rs.getInt(2), rs.getInt(3), rs.getInt(4),
                                                  rs.getFloat(5)));
                                   }
                              }
                              // mostraDados.selectAll();
                         } catch (Exception ex) {
                              JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + ex, "Erro Interno",
                                        JOptionPane.ERROR_MESSAGE);
                         }
                    }
               });
          } catch (Exception ex) {
               JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + ex, "Erro Interno",
                         JOptionPane.ERROR_MESSAGE);
          } finally {
               try {
                    pstmt1.close();
                    // con.close();
               } catch (SQLException esql) {
                    JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + esql, "Erro Interno",
                              JOptionPane.ERROR_MESSAGE);
               }
          }
     }

     // Método para mostrar todos os dados presentes na tabela
     void mostraTodosDados(Connection con, String opc) {
          try {
               pstmt2 = con.prepareStatement("SELECT * FROM " + opc);
               mostraDados.setText("");
               // Mostrando dados
               ResultSet rs = pstmt2.executeQuery();
               while (rs.next()) {
                    if (opc.equals("CLIENTE")) {
                         mostraDados.append(String.format(
                                   "ID: %d\n" + "Nome: %s\n" + "RG: %s\n" + "Telefone: %s\n" + "Endereço: %s\n\n",
                                   rs.getInt(1), rs.getString(2), rs.getString(3), rs.getString(4), rs.getString(5)));
                    } else if(opc.equals("FORNECEDOR")){
                         mostraDados.append(String.format(
                                   "ID: %d\n" + "Nome: %s\n" + "CNPJ: %s\n" + "Telefone: %s\n" + "Endereço: %s\n\n",
                                   rs.getInt(1), rs.getString(2), rs.getString(3), rs.getString(4), rs.getString(5)));
                    } else if (opc.equals("INSTRUMENTO")) {
                         mostraDados.append(String.format(
                                   "ID: %d\n" + "Nome do Produto: %s\n" + "Marca: %s\n" + "Tipo de Instrumento: %s\n"
                                             + "Preço Unitário: %.2f\n\n",
                                   rs.getInt(1), rs.getString(2), rs.getString(3), rs.getString(4), rs.getFloat(5)));
                    } else if (opc.equals("VENDA")) {
                         mostraDados.append(String.format(
                                   "ID: %d\n" + "ID do Cliente: %d\n" + "ID do Produto: %d\n" + "Quantidade: %d\n"
                                             + "Preço Total: %.2f\n\n",
                                   rs.getInt(1), rs.getInt(2), rs.getInt(3), rs.getInt(4), rs.getFloat(5)));
                    }
               }
               // mostraDados.selectAll();
          } catch (Exception ex) {
               JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + ex, "Erro Interno",
                         JOptionPane.ERROR_MESSAGE);
          } finally {
               try {
                    pstmt2.close();
                    // con.close();
               } catch (SQLException esql) {
                    JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + esql, "Erro Interno",
                              JOptionPane.ERROR_MESSAGE);
               }
          }
     }

}

// Classe da Venda (Inserção/Nova Venda)
class janelaVenda extends JInternalFrame implements ActionListener {

     // Tamanho da Janela
     final int WIDTH = 600;

     // Necessário: ID_Cliente, ID_Produto, Quantidade_Produto
     JDesktopPane desktop; // Janela
     JTextField txtCliente, txtProduto, txtQtdProduto; // TextField do Usuário e Produto
     JButton btnCliente, btnProduto, btnVenda; // Botões de Consulta do Usuário e Produto
     // Label's (Consulta)
     JLabel nomeCliente, rgCliente, telCliente, endCliente; // Cliente
     JLabel nomeProduto, marcaProduto, tipoProduto, precoProduto; // Preço
     JLabel sucessoVenda; // Venda (Sucesso ou Não)
     // Banco de Dados
     Connection con1;
     PreparedStatement pstmt;
     Statement stmt;
     int id_cliente, id_produto, id_venda; // ID's
     int quantidade_final; // Quantidade da Venda
     float preco_total; // Preço Total do Produto Vendido
     float preco_unit; // Preço Unitário do Produto

     public janelaVenda(JDesktopPane desk, Connection con) {
          super("Inserção na Tabela VENDA", false, true, false, false);
          desktop = desk;
          con1 = con;
          try {
               // Configurando PStatement
               pstmt = con.prepareStatement("INSERT INTO VENDA VALUES (?, ?, ?, ?, ?)");

               // Configurando Layout
               // Cliente
               JPanel idCliente1 = new JPanel(new FlowLayout());
               idCliente1.add(new JLabel("ID do Cliente: "));
               idCliente1.add(txtCliente = new JTextField(10));
               JPanel idCliente2 = new JPanel(new FlowLayout());
               idCliente2.add(btnCliente = new JButton("Consultar"));
               JPanel idClienteFinal = new JPanel(new BorderLayout());
               idClienteFinal.add(idCliente1, BorderLayout.NORTH);
               idClienteFinal.add(idCliente2, BorderLayout.SOUTH);

               JPanel dadosCliente1 = new JPanel(new FlowLayout());
               dadosCliente1.add(new JLabel("DADOS DO CLIENTE"));
               JPanel dadosCliente2 = new JPanel(new GridLayout(4, 1));
               dadosCliente2.add(new JLabel("NOME:       "));
               dadosCliente2.add(new JLabel("RG:         "));
               dadosCliente2.add(new JLabel("TELEFONE:   "));
               dadosCliente2.add(new JLabel("ENDEREÇO:   "));
               JPanel dadosCliente3 = new JPanel(new GridLayout(4, 1));
               dadosCliente3.add(nomeCliente = new JLabel(" ---MUDAR AQUI---"));
               dadosCliente3.add(rgCliente = new JLabel(" ---MUDAR AQUI---"));
               dadosCliente3.add(telCliente = new JLabel(" ---MUDAR AQUI---"));
               dadosCliente3.add(endCliente = new JLabel(" ---MUDAR AQUI---"));
               JPanel dadosClienteFinal = new JPanel(new BorderLayout());
               dadosClienteFinal.add(dadosCliente1, BorderLayout.NORTH);
               dadosClienteFinal.add(dadosCliente2, BorderLayout.WEST);
               dadosClienteFinal.add(dadosCliente3, BorderLayout.CENTER);

               JPanel panelCliente = new JPanel(new BorderLayout());
               panelCliente.add(idClienteFinal, BorderLayout.NORTH);
               panelCliente.add(dadosClienteFinal, BorderLayout.SOUTH);

               // Instrumento Musical (Produto)
               JPanel idProduto1 = new JPanel(new FlowLayout());
               idProduto1.add(new JLabel("ID do Produto: "));
               idProduto1.add(txtProduto = new JTextField(10));
               JPanel idProduto2 = new JPanel(new FlowLayout());
               idProduto2.add(btnProduto = new JButton("Consultar"));
               JPanel idProdutoFinal = new JPanel(new BorderLayout());
               idProdutoFinal.add(idProduto1, BorderLayout.NORTH);
               idProdutoFinal.add(idProduto2, BorderLayout.SOUTH);

               JPanel dadosProduto1 = new JPanel(new FlowLayout());
               dadosProduto1.add(new JLabel("DADOS DO PRODUTO"));
               JPanel dadosProduto2 = new JPanel(new GridLayout(4, 1));
               dadosProduto2.add(new JLabel("NOME:   "));
               dadosProduto2.add(new JLabel("MARCA:  "));
               dadosProduto2.add(new JLabel("TIPO:   "));
               dadosProduto2.add(new JLabel("PREÇO (UNID.):  R$    "));
               JPanel dadosProduto3 = new JPanel(new GridLayout(4, 1));
               dadosProduto3.add(nomeProduto = new JLabel("---MUDAR AQUI---"));
               dadosProduto3.add(marcaProduto = new JLabel("---MUDAR AQUI---"));
               dadosProduto3.add(tipoProduto = new JLabel("---MUDAR AQUI---"));
               dadosProduto3.add(precoProduto = new JLabel("---MUDAR AQUI---"));
               JPanel dadosProdutoFinal = new JPanel(new BorderLayout());
               dadosProdutoFinal.add(dadosProduto1, BorderLayout.NORTH);
               dadosProdutoFinal.add(dadosProduto2, BorderLayout.WEST);
               dadosProdutoFinal.add(dadosProduto3, BorderLayout.CENTER);

               JPanel panelProduto = new JPanel(new BorderLayout());
               panelProduto.add(idProdutoFinal, BorderLayout.NORTH);
               panelProduto.add(dadosProdutoFinal, BorderLayout.SOUTH);

               // Quantidade (Venda/Inserção)
               JPanel qtd1 = new JPanel(new FlowLayout());
               qtd1.add(new JLabel("Quantidade: "));
               qtd1.add(txtQtdProduto = new JTextField(10));
               JPanel qtd2 = new JPanel(new FlowLayout());
               qtd2.add(btnVenda = new JButton("Vender"));
               JPanel qtdFinal = new JPanel(new BorderLayout());
               qtdFinal.add(qtd1, BorderLayout.NORTH);
               qtdFinal.add(qtd2, BorderLayout.SOUTH);

               JPanel labelSucesso = new JPanel(new FlowLayout());
               labelSucesso.add(sucessoVenda = new JLabel("---SUCESSO OU NÃO---"));

               JPanel panelQTD = new JPanel(new BorderLayout());
               panelQTD.add(qtdFinal, BorderLayout.NORTH);
               panelQTD.add(labelSucesso, BorderLayout.SOUTH);

               // Adicionando no Painel Final
               setLayout(new GridLayout(3, 1));
               add(panelCliente);
               add(panelProduto);
               add(panelQTD);

               pack();
               setSize(WIDTH, this.getHeight());
               setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
               setVisible(true);
               desktop.add(this);

               // Configurando botões e JText (ao iniciar)
               nomeCliente.setVisible(false);
               rgCliente.setVisible(false);
               telCliente.setVisible(false);
               endCliente.setVisible(false);

               txtProduto.setEditable(false);
               btnProduto.setVisible(false);
               nomeProduto.setVisible(false);
               marcaProduto.setVisible(false);
               tipoProduto.setVisible(false);
               precoProduto.setVisible(false);

               txtQtdProduto.setEditable(false);
               btnVenda.setVisible(false);
               sucessoVenda.setVisible(false);

               // Tratamento dos botões e outras ações
               btnCliente.addActionListener(this);
               btnProduto.addActionListener(this);
               btnVenda.addActionListener(this);

          } catch (Exception ex) {
               JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + ex, "Erro Interno",
                         JOptionPane.ERROR_MESSAGE);
          } finally {
               try {
                    pstmt.close();
                    // con.close();
               } catch (SQLException esql) {
                    JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + esql, "Erro Interno",
                              JOptionPane.ERROR_MESSAGE);
               }
          }

     }

     // Ações dos Botões
     public void actionPerformed(ActionEvent e) {
          if (e.getSource() == btnCliente) {
               // Caso o campo esteja diferente de vazio, faz a verificação
               if (txtCliente.getText().isEmpty() == false) {
                    try {
                         // Procurar ID digitada no banco de dados..
                         stmt = con1.createStatement();
                         ResultSet rs1 = stmt
                                   .executeQuery("SELECT * FROM CLIENTE WHERE ID LIKE " + txtCliente.getText());

                         // Caso verdadeiro, significa que encontrou o ID do Cliente...
                         if (rs1.next()) {
                              // Salvar ID de Cliente para tabela de vendas...
                              id_cliente = Integer.parseInt(txtCliente.getText());

                              // Alterar label's do Cliente com suas informações...
                              nomeCliente.setText(rs1.getString(2));
                              rgCliente.setText(rs1.getString(3));
                              telCliente.setText(rs1.getString(4));
                              endCliente.setText(rs1.getString(5));

                              // Tornar campos de Cliente invisíveis
                              txtCliente.setEditable(false);
                              btnCliente.setVisible(false);
                              // Tornar campos de Label's do Cliente e do Produto visíveis
                              nomeCliente.setVisible(true);
                              rgCliente.setVisible(true);
                              telCliente.setVisible(true);
                              endCliente.setVisible(true);

                              txtProduto.setEditable(true);
                              btnProduto.setVisible(true);

                              JOptionPane.showMessageDialog(desktop, "Cliente encontrado! Seguem seus dados.",
                                        "Sucesso", JOptionPane.INFORMATION_MESSAGE);
                              stmt.close();

                         } else {
                              JOptionPane.showMessageDialog(desktop, "Cliente inexistente. Tente novamente.",
                                        "Erro de ID", JOptionPane.ERROR_MESSAGE);
                         }

                    } catch (SQLException esql) {
                         JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + esql, "Erro Interno",
                                   JOptionPane.ERROR_MESSAGE);
                    }

               }
          } else if (e.getSource() == btnProduto) {
               // Caso o campo esteja diferente de vazio, faz a verificação
               if (txtProduto.getText().isEmpty() == false) {
                    try {
                         // Procurar ID digitada no banco de dados..
                         stmt = con1.createStatement();
                         ResultSet rs1 = stmt
                                   .executeQuery("SELECT * FROM INSTRUMENTO WHERE ID LIKE " + txtProduto.getText());

                         // Caso verdadeiro, significa que encontrou o ID do Produto...
                         if (rs1.next()) {

                              // Salvar ID de Produto para tabela de vendas...
                              id_produto = Integer.parseInt(txtProduto.getText());
                              // Salvar Preço Unitário do Produto para Cálculo final..
                              preco_unit = rs1.getFloat(5);

                              // Alterar label's do Produto com suas informações...
                              nomeProduto.setText(rs1.getString(2));
                              marcaProduto.setText(rs1.getString(3));
                              tipoProduto.setText(rs1.getString(4));
                              precoProduto.setText(Float.toString(rs1.getFloat(5)));

                              // Tornar campos de Produto não editaveis/invisíveis
                              txtProduto.setEditable(false);
                              btnProduto.setVisible(false);
                              // Tornar campos de Label's do Produto e da Quantidade visíveis
                              nomeProduto.setVisible(true);
                              marcaProduto.setVisible(true);
                              tipoProduto.setVisible(true);
                              precoProduto.setVisible(true);

                              txtQtdProduto.setEditable(true);
                              btnVenda.setVisible(true);

                              JOptionPane.showMessageDialog(desktop, "Produto encontrado! Seguem seus dados.",
                                        "Sucesso", JOptionPane.INFORMATION_MESSAGE);
                              stmt.close();

                         } else {
                              JOptionPane.showMessageDialog(desktop, "Produto inexistente. Tente novamente.",
                                        "Erro de ID", JOptionPane.ERROR_MESSAGE);
                         }

                    } catch (SQLException esql) {
                         JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + esql, "Erro Interno",
                                   JOptionPane.ERROR_MESSAGE);
                    }

               }
          } else if (e.getSource() == btnVenda) {

               // Recuperando última ID de Venda (caso exista)
               try {
                    // Verificando se a tabela está vazia...
                    stmt = con1.createStatement();
                    ResultSet rs1 = stmt.executeQuery("SELECT * FROM VENDA");

                    // Caso esteja nula....
                    if (rs1.next() == false) {
                         id_venda = 1; // Início de ID
                    } else {
                         // Do contrário, pegar ID Máximo e continuar contagem
                         rs1 = stmt.executeQuery("SELECT * FROM VENDA ORDER BY ID DESC");
                         rs1.next();
                         id_venda = rs1.getInt(1) + 1;
                    }
               } catch (SQLException esql) {
                    JOptionPane.showMessageDialog(desktop, "Erro interno.\nErro: " + esql, "Erro Interno",
                              JOptionPane.ERROR_MESSAGE);
               }

               // Caso o campo esteja diferente de vazio, faz a verificação
               if (txtQtdProduto.getText().isEmpty() == false) {
                    // Salvar campo de quantidade
                    quantidade_final = Integer.parseInt(txtQtdProduto.getText());

                    // Cálculo do Preço Total
                    preco_total = (quantidade_final * preco_unit);

                    // Inserindo na Tabela de Vendas...
                    try {
                         pstmt.setInt(1, id_venda);
                         pstmt.setInt(2, id_cliente);
                         pstmt.setInt(3, id_produto);
                         pstmt.setInt(4, quantidade_final);
                         pstmt.setFloat(5, preco_total);

                         // Atualizando a tabela
                         pstmt.executeUpdate();

                         // Alterar label's do resultado final caso sucesso
                         sucessoVenda.setText("VENDA REALIZADA COM SUCESSO!");

                         // Tornar campos da Quantidade não editaveis/invisíveis
                         txtQtdProduto.setEditable(false);
                         btnVenda.setVisible(false);
                         // Tornar campos de Label's do resultado final
                         sucessoVenda.setVisible(true);

                         // Mostrar o Preço Final
                         JOptionPane.showMessageDialog(desktop, "R$ " + preco_total, "Preço Total",
                                   JOptionPane.INFORMATION_MESSAGE);

                    } catch (SQLException esql) {
                         JOptionPane.showMessageDialog(desktop, "Erro ao Inserir na Tabela Venda.\nErro: " + esql,
                                   "Erro de Inserção", JOptionPane.ERROR_MESSAGE);
                    }

               }
          }
     }

}