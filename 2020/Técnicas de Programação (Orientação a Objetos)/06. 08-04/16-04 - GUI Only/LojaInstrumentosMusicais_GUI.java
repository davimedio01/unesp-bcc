import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

//Imagens
import java.net.*;

class LojaInstrumentosMusicais_GUI extends JFrame implements ActionListener {

     // Tamanho da Janela
     final int WIDTH = 1200, HEIGHT = 700;

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

     public LojaInstrumentosMusicais_GUI() {
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
                         System.exit(0);
                    }
               }
          });
          setDefaultCloseOperation(DO_NOTHING_ON_CLOSE); // Saída

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
               new janelaInsere(desktopPrincipal, "CLIENTE");
          } else if (e.getSource() == fornecedorInsere) {
               new janelaInsere(desktopPrincipal, "FORNECEDOR");
          } else if (e.getSource() == instrumentoInsere) {
               new janelaInsere(desktopPrincipal, "INSTRUMENTO");
          } else if (e.getSource() == clienteConsulta) {
               new janelaConsulta(desktopPrincipal, "CLIENTE");
          } else if (e.getSource() == fornecedorConsulta) {
               new janelaConsulta(desktopPrincipal, "FORNECEDOR");
          } else if (e.getSource() == instrumentoConsulta) {
               new janelaConsulta(desktopPrincipal, "INSTRUMENTO");
          } else if (e.getSource() == vendasInsere) {
               new janelaVenda(desktopPrincipal);
          } else if (e.getSource() == vendasConsulta) {
               new janelaConsulta(desktopPrincipal, "VENDA");
          }
     }

     public static void main(String[] args) {
          new LojaInstrumentosMusicais_GUI();
     }
}

// Classe de Inserção
class janelaInsere extends JInternalFrame {
     JDesktopPane desktop; // Janela
     JButton btnInserir; // Botão para Enviar
     JTextField campo1, campo2, campo3, campo4, campo5; // Campos

     public janelaInsere(JDesktopPane desk, String opc) {
          super("Inserção na Tabela " + opc, false, true, false, false);
          desktop = desk;

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

          // Configuração da Ação do Botão "Inserir"
          btnInserir.addActionListener(new ActionListener() {
               public void actionPerformed(ActionEvent e) {
                    // Caso obtenha sucesso ao inserir dados...
                    JOptionPane.showMessageDialog(desktop, "Dados inseridos com sucesso!", "Sucesso",
                              JOptionPane.INFORMATION_MESSAGE);
               }
          });
     }
}

// Classe de Consulta
class janelaConsulta extends JInternalFrame {
     JDesktopPane desktop; // Janela
     JButton btnConsulta; // Botão para Confirmar Consulta
     JTextField campo; // Código digitado pelo Usuário
     JTextArea mostraDados;

     public janelaConsulta(JDesktopPane desk, String opc) {
          super("Consulta na Tabela " + opc, false, true, false, false);
          desktop = desk;

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
          dados.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
          JPanel txtPanel = new JPanel(new BorderLayout());
          txtPanel.add(dados, BorderLayout.CENTER);

          add(txtPanel, BorderLayout.CENTER);
          pack();
          setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
          setVisible(true);
          desktop.add(this);

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

     public janelaVenda(JDesktopPane desk) {
          super("Inserção na Tabela VENDA", false, true, false, false);
          desktop = desk;

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

     }

     // Ações dos Botões
     public void actionPerformed(ActionEvent e) {
          if (e.getSource() == btnCliente) {

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

               JOptionPane.showMessageDialog(desktop, "Cliente encontrado! Seguem seus dados.", "Sucesso",
                         JOptionPane.INFORMATION_MESSAGE);

          } else if (e.getSource() == btnProduto) {

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

               JOptionPane.showMessageDialog(desktop, "Produto encontrado! Seguem seus dados.", "Sucesso",
                         JOptionPane.INFORMATION_MESSAGE);

          } else if (e.getSource() == btnVenda) {

               // Tornar campos da Quantidade não editaveis/invisíveis
               txtQtdProduto.setEditable(false);
               btnVenda.setVisible(false);
               // Tornar campos de Label's do resultado final
               sucessoVenda.setVisible(true);

               // Mostrar o Preço Final
               JOptionPane.showMessageDialog(desktop, "R$ " + "PREÇO_TOTAL_AQUI", "Preço Total",
                         JOptionPane.INFORMATION_MESSAGE);
          }
     }
}
