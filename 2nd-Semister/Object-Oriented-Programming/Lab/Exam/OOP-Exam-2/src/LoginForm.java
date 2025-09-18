
import javax.swing.*;
import java.awt.*;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Map;

public class LoginForm extends JFrame {

    Map<String, Account> accounts;

    JTextField idField;
    JPasswordField passwordField;
    JButton loginButton, publishButton;

    private final String ID_PLACE_HOLDER = "ID/Registration Number";
    private final String PASSWORD_PLACE_HOLDER = "Password";

    public LoginForm() {

        try {
            this.accounts = Main.accounts;
            createComponents();
            layoutComponents();
            setPlaceHolders();
            addEvenListeners();
            setupFrame();
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(null, "Error initializing login form: " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            System.err.println("Exception in LoginForm constructor: " + ex.getMessage());
        }
    }

    private void setupFrame() {

        setTitle("Login");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(800, 600);
        setResizable(false);
        setLocationRelativeTo(null);
        pack();
        setVisible(true);
        if (loginButton != null) {
            loginButton.requestFocusInWindow();
        }
    }

    private void createComponents() {

        idField = new JTextField(20);
        idField.setFont(new Font("Arial", Font.PLAIN, 16));
        passwordField = new JPasswordField(20);
        passwordField.setFont(new Font("Arial", Font.PLAIN, 16));

        idField.setFocusable(true);
        passwordField.setFocusable(true);

        loginButton = new JButton("Log In");
        loginButton.setFocusPainted(false);

        publishButton = new JButton("Publish Account");

    }

    private void layoutComponents() {
        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();

        // add title label

        c.gridx = 0;
        c.gridy = 0;
        c.gridwidth = 2;
        c.insets = new Insets(20, 0, 20, 0);
        add(setHeader(new JLabel("Log in")), c);

        // add id field
        c.gridy++;
        c.gridwidth = 2;
        c.insets = new Insets(5, 20, 5, 20);
        c.fill = GridBagConstraints.HORIZONTAL;
        add(idField, c);

        // add password field
        c.gridy++;
        c.gridwidth = 2;
        c.insets = new Insets(5, 20, 5, 20);
        add(passwordField, c);

        // add buttons
        JPanel buttonPanel = new JPanel(new FlowLayout());
        buttonPanel.add(loginButton);
        buttonPanel.add(publishButton);
        c.gridy++;
        c.gridwidth = 2;
        c.insets = new Insets(5, 20, 5, 20);
        add(buttonPanel, c);

    }

    private void setPlaceHolders() {

        idField.setText(ID_PLACE_HOLDER);
        idField.setHorizontalAlignment(JTextField.CENTER);
        idField.setForeground(Color.GRAY);

        passwordField.setText(PASSWORD_PLACE_HOLDER);
        passwordField.setHorizontalAlignment(JTextField.CENTER);
        passwordField.setForeground(Color.GRAY);
        passwordField.setEchoChar((char) 0);

        idField.addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {
                if (idField.getText().equals(ID_PLACE_HOLDER)) {
                    idField.setText("");
                    idField.setForeground(Color.BLACK);
                }
            }

            @Override
            public void focusLost(FocusEvent e) {
                if (idField.getText().isEmpty()) {
                    idField.setText(ID_PLACE_HOLDER);
                    idField.setForeground(Color.GRAY);
                }
            }
        });

        passwordField.addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {
                if (String.valueOf(passwordField.getPassword()).equals(PASSWORD_PLACE_HOLDER)) {
                    passwordField.setText("");
                    passwordField.setForeground(Color.BLACK);
                    passwordField.setEchoChar('*');
                }
            }

            @Override
            public void focusLost(FocusEvent e) {
                if (String.valueOf(passwordField.getPassword()).isEmpty()) {
                    passwordField.setText(PASSWORD_PLACE_HOLDER);
                    passwordField.setForeground(Color.GRAY);
                    passwordField.setEchoChar((char) 0);
                }
            }
        });
    }

    private void addEvenListeners() {

        loginButton.addActionListener(e -> {

            try {
                String id = idField.getText().trim();
                String password = String.valueOf(passwordField.getPassword()).trim();

                if (validForm()) {
                    Account account = accounts.get(id);
                    if (account == null) {
                        JOptionPane.showMessageDialog(this, "Invalid ID\n\n", "Error", JOptionPane.ERROR_MESSAGE);
                        return;
                    }


                    if (!account.getPassword().equals(password)) {
                        JOptionPane.showMessageDialog(this, "Passwords do not match", "Error", JOptionPane.ERROR_MESSAGE);
                    } else {
                        JOptionPane.showMessageDialog(this, "Login Successful!!", "Success", JOptionPane.INFORMATION_MESSAGE);

                        dispose();
                        new Frame(new Account("hamim", ""));

                    }
                }
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Error during administration login: " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
                System.err.println("Exception in LoginForm (loginButton.addActionListener): " + ex.getMessage());
            }
        });
        getRootPane().setDefaultButton(loginButton);

        publishButton.addActionListener(e -> {

           StringBuilder builder1 = new StringBuilder("1");
           StringBuilder builder2 = new StringBuilder("2");
           StringBuilder builder3 = new StringBuilder("3");
           StringBuilder builder4 = new StringBuilder("4");

           for (Account account : accounts.values()) {
               if(account.getVote().equals("1")){
                   builder1.append("\n" + account.getUsername());
               }
               if(account.getVote().equals("2")){
                   builder2.append("\n" + account.getUsername());
               }
               if(account.getVote().equals("3")){
                   builder3.append("\n" + account.getUsername());
               }
               if(account.getVote().equals("4")){
                   builder4.append("\n" + account.getUsername());
               }
           }
           StringBuilder builder = new StringBuilder();
           builder1.append(builder1.toString());
           builder2.append(builder2.toString());
           builder3.append(builder3.toString());
           builder4.append(builder4.toString());
           String fileName = "Vote.txt";

//            try {
//                FileWriter fileWriter = new FileWriter(fileName, true);
//                fileWriter.write(builder.toString());
//            } catch (IOException f) {
//                System.out.println("Error opening file " + fileName + ": " + f.getMessage());
//            }
            JOptionPane.showMessageDialog(this, ScrollPanel(builder), "vote Details", JOptionPane.INFORMATION_MESSAGE);
        });

    }

    private boolean validForm() {
        try {
            if (idField.getText().equals(ID_PLACE_HOLDER) || String.valueOf(passwordField.getPassword()).equals(PASSWORD_PLACE_HOLDER)) {
                JOptionPane.showMessageDialog(this, "Please fill all the fields!", "Error", JOptionPane.ERROR_MESSAGE);
                return false;
            }
            return true;
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(this, "Error validating form: " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            return false;
        }
    }


    public static JLabel setHeader(JLabel headerLabel) {
        headerLabel.setFont(new Font("Arial", Font.BOLD, 28));
        headerLabel.setBorder(BorderFactory.createEmptyBorder(24, 0, 24, 0));
        headerLabel.setForeground(new Color(44, 62, 80));
        return headerLabel;
    }

    public static void styleButton(JButton button) {

        button.setFont(new Font("Arial", Font.BOLD, 16));
        button.setBackground(new Color(52, 152, 219));
        button.setForeground(Color.BLACK);
        button.setFocusPainted(false);
        button.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(new Color(41, 128, 185)),
                BorderFactory.createEmptyBorder(8, 18, 8, 18)));
        button.setCursor(new Cursor(Cursor.HAND_CURSOR));
        button.addMouseListener(new java.awt.event.MouseAdapter() {

            public void mouseEntered(java.awt.event.MouseEvent evt) {

                button.setBackground(new Color(41, 128, 185));
            }

            public void mouseExited(java.awt.event.MouseEvent evt) {

                button.setBackground(new Color(52, 152, 219));
            }
        });
    }
    public static JScrollPane ScrollPanel(StringBuilder result) {
        JTextArea textArea = new JTextArea(result.toString());
        textArea.setEditable(false);
        textArea.setFont(new Font("Monospaced", Font.PLAIN, 14));
        textArea.setBackground(new Color(245, 247, 250));
        JScrollPane scrollPane = new JScrollPane(textArea);
        scrollPane.setPreferredSize(new Dimension(400, 250));
        return scrollPane;
    }

}












