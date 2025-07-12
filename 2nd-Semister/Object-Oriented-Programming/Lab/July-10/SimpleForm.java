import javax.swing.*;

public class SimpleForm {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Registration Form");
        frame.setSize(300, 350);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(null);  // absolute positioning

        JLabel userLabel = new JLabel("Name:");
        userLabel.setBounds(10, 10, 80, 25);
        frame.add(userLabel);

        JTextField userText = new JTextField();
        userText.setBounds(100, 10, 160, 25);
        frame.add(userText);

        JLabel rollLevel = new JLabel("Roll Level:");
        rollLevel.setBounds(10, 50, 80, 25);
        frame.add(rollLevel);

        JTextField rollText = new JTextField();
        rollText.setBounds(100, 50, 160, 25);
        frame.add(rollText);

        JLabel departmentLevel = new JLabel("Department:");
        departmentLevel.setBounds(10, 100, 80, 25);
        frame.add(departmentLevel);

        JTextField departmentText = new JTextField();
        departmentText.setBounds(100, 100, 160, 25);
        frame.add(departmentText);

        JLabel sessionLabel = new JLabel("Session:");
        sessionLabel.setBounds(10, 150, 80, 25);
        frame.add(sessionLabel);

        JTextField sessionText = new JTextField();
        sessionText.setBounds(100, 150, 160, 25);
        frame.add(sessionText);

        JButton loginButton = new JButton("Submit");
        loginButton.setBounds(100, 190, 80, 25);
        frame.add(loginButton);

//        Event Handling
    //We are going to see how to handle button clicks:
    //addActionListener
    //Lambda syntax
    //JOptionPane

        loginButton.addActionListener(e -> {
            String username = userText.getText();
            String department = departmentText.getText();
            String session = sessionText.getText();
            JOptionPane.showMessageDialog(frame, "Hello " + username + "\nDepartment: " + department + "\nSession: " + session);
        });


//        Task: Change labels and button texts
//      Add a password field (JPasswordField)
//      Create a simple calculator (2 inputs, + button, and output label)

        frame.setVisible(true);

    }
}
