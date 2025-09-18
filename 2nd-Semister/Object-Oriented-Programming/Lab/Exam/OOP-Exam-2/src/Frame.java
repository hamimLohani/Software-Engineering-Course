
import javax.swing.*;
import java.awt.*;


public class Frame extends JFrame {


    Account account;
    private JPanel mainPanel;
    JTextField examSearchField;

    public Frame(Account account) {

        this.account = account;
        setTitle("Vote Panel");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        getContentPane().setBackground(new Color(245, 247, 250));
        add(createHeader(), BorderLayout.NORTH);
        setupMainPanel();
        add(mainPanel, BorderLayout.CENTER);
        pack();
        setMinimumSize(new Dimension(500, 600));
        setLocationRelativeTo(null);
        setVisible(true);
    }

    private JLabel createHeader() {

        JLabel headerLabel = new JLabel("Vote Dashboard", SwingConstants.CENTER);

        return LoginForm.setHeader(headerLabel);
    }

    private void setupMainPanel() {

        mainPanel = new JPanel(new GridBagLayout());
        mainPanel.setBackground(new Color(255, 255, 255));
        mainPanel.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createEmptyBorder(24, 32, 24, 32),
                BorderFactory.createTitledBorder(BorderFactory.createLineBorder(new Color(200, 200, 200)),
                        "Candidates", 0, 0,
                        new Font("Arial", Font.BOLD, 16), new Color(52, 73, 94))
        ));
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(12, 12, 12, 12);
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 2;
        gbc.fill = GridBagConstraints.HORIZONTAL;


        // create exam button
        gbc.gridy++;
        JButton createExamButton = new JButton("1");
        LoginForm.styleButton(createExamButton);
        mainPanel.add(createExamButton, gbc);

        createExamButton.addActionListener(e -> {
            account.setVote("1");
            JOptionPane.showMessageDialog(Frame.this, "Your vote is done\nVotes: " + account.getVote());
            dispose();
            new LoginForm();
        });

        // search button
        gbc.gridy++;
        gbc.gridx = 0;
        gbc.gridwidth = 2;
        JButton searchExamButton = new JButton("2");
        LoginForm.styleButton(searchExamButton);
        mainPanel.add(searchExamButton, gbc);
        searchExamButton.addActionListener(e -> {
            account.setVote("2");
            JOptionPane.showMessageDialog(Frame.this, "Your vote is done\nVotes: " + account.getVote());
            dispose();
            new LoginForm();
        });

        // publish exam button
        gbc.gridy++;
        JButton publishExamButton = new JButton("3");
        LoginForm.styleButton(publishExamButton);
        mainPanel.add(publishExamButton, gbc);
        publishExamButton.addActionListener(e -> {
            account.setVote("3");
            JOptionPane.showMessageDialog(Frame.this, "Your vote is done\nVotes: " + account.getVote());
            dispose();
            new LoginForm();
        });

        // publish result button
        gbc.gridy++;
        JButton publishResultButton = new JButton("4");
        LoginForm.styleButton(publishResultButton);
        mainPanel.add(publishResultButton, gbc);
        publishResultButton.addActionListener(e -> {
            account.setVote("4");
            JOptionPane.showMessageDialog(Frame.this, "Your vote is done\nVotes: " + account.getVote());
            dispose();
            new LoginForm();
        });



    }


}