import javax.swing.*;
import java.io.File;

public class Frame extends JFrame {

    public Frame() {
        JFrame frame = new JFrame("Registration From");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400,450);
        frame.setLayout(null);

        JLabel nameLabel = new JLabel("Name:");
        nameLabel.setBounds(30,30,100,30);
        frame.add(nameLabel);

        JTextField nameField = new JTextField();
        nameField.setBounds(110,30,250,30);
        frame.add(nameField);

        JLabel emailLabel = new JLabel("Email:");
        emailLabel.setBounds(30,60,100,30);
        frame.add(emailLabel);

        JTextField emailField = new JTextField();
        emailField.setBounds(110,60,250,30);
        frame.add(emailField);

        JLabel phoneLabel = new JLabel("Phone:");
        phoneLabel.setBounds(30,90,100,30);
        frame.add(phoneLabel);

        JTextField phoneField = new JTextField();
        phoneField.setBounds(110,90,250,30);
        frame.add(phoneField);

        JLabel addressLabel = new JLabel("Address:");
        addressLabel.setBounds(30,120,100,30);
        frame.add(addressLabel);

        JTextField addressField = new JTextField();
        addressField.setBounds(110,120,250,30);
        frame.add(addressField);

        JLabel genderLabel = new JLabel("Gender:");
        genderLabel.setBounds(30,150,100,30);
        frame.add(genderLabel);

        JRadioButton maleRadioButton = new JRadioButton("Male");
        maleRadioButton.setBounds(130,150,100,30);
        frame.add(maleRadioButton);

        JRadioButton femaleRadioButton = new JRadioButton("Female");
        femaleRadioButton.setBounds(240,150,100,30);
        frame.add(femaleRadioButton);

        ButtonGroup buttonGroup = new ButtonGroup();
        buttonGroup.add(maleRadioButton);
        buttonGroup.add(femaleRadioButton);

        String[] day = new String[31];
        String[] month = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        String[] year = new String[50];
        for (int i = 0; i < 31; i++) {
            day[i] = String.valueOf(i+1);
        }
        for (int i = 0; i < 50; i++) {
            year[i] = String.valueOf(2025 - i);
        }

        JLabel dateLabel = new JLabel("Date:");
        dateLabel.setBounds(30,180,100,30);
        frame.add(dateLabel);

        JComboBox<String> dayBox = new JComboBox<>(day);
        dayBox.setBounds(110,180,70,30);
        frame.add(dayBox);

        JComboBox<String> monthBox = new JComboBox<>(month);
        monthBox.setBounds(185,180,80,30);
        frame.add(monthBox);

        JComboBox<String> yearBox = new JComboBox<>(year);
        yearBox.setBounds(270,180,90,30);
        frame.add(yearBox);

        JLabel degreeLabel = new JLabel("Degree:");
        degreeLabel.setBounds(30,210,100,30);
        frame.add(degreeLabel);

        String[] degrees = {"Select", "BSSE", "MSSE"};
        JComboBox<String> degreeBox = new JComboBox<>(degrees);
        degreeBox.setBounds(110,210,250,30);
        frame.add(degreeBox);

        JLabel fileLabel = new JLabel("Picture:");
        fileLabel.setBounds(30,240,100,30);
        frame.add(fileLabel);

        JButton fileButton = new JButton("Choose");
        fileButton.setBounds(110,240, 80,30);
        fileButton.setFocusable(false);
        frame.add(fileButton);

        JLabel filePathLabel = new JLabel("Path:");
        filePathLabel.setBounds(200,240,150,30);
        frame.add(filePathLabel);

        final String[] filePath = {""};
        fileButton.addActionListener(e ->{
            JFileChooser fileChooser = new JFileChooser();
            int option = fileChooser.showOpenDialog(frame);
            if (option == JFileChooser.APPROVE_OPTION) {
                File file = fileChooser.getSelectedFile();
                filePath[0] = file.getAbsolutePath();
                filePathLabel.setText(file.getName());
            }
        });

        JLabel positionLabel = new JLabel("Position:");
        positionLabel.setBounds(30,270,100,30);
        frame.add(positionLabel);

        String[] position = {"Select", "Defensive midfielder", "Goalkeeper", "Centre-back", "Central midfielder", "Fullback", "Full back", "Attacking midfielder", "Striker", "Center forwards"};
        JComboBox<String> positionBox = new JComboBox<>(position);
        positionBox.setBounds(110,270,250,30);
        frame.add(positionBox);

        JLabel experienceLabel = new JLabel("Experience:");
        experienceLabel.setBounds(30,300,100,30);
        frame.add(experienceLabel);

        JTextField experienceField = new JTextField();
        experienceField.setBounds(110,300,250,30);
        frame.add(experienceField);

        JButton saveButton = new JButton("Save");
        saveButton.setBounds(100,360,80,30);
        saveButton.setFocusable(false);
        frame.add(saveButton);
        saveButton.addActionListener(e ->{



        });

        JButton resetButton = new JButton("Reset");
        resetButton.setBounds(200,360,80,30);
        resetButton.setFocusable(false);
        frame.add(resetButton);
        resetButton.addActionListener(e ->{
           nameField.setText("");
           emailField.setText("");
           phoneField.setText("");
           addressField.setText("");
           experienceField.setText("");
           positionBox.setSelectedIndex(0);
           buttonGroup.clearSelection();
           dayBox.setSelectedIndex(0);
           monthBox.setSelectedIndex(0);
           yearBox.setSelectedIndex(0);
           filePathLabel.setText("");
        });



        frame.setVisible(true);
    }
}
