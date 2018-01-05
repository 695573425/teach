import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class transformText extends JFrame implements ActionListener
{
    Container contentpane = getContentPane();
	JTextField txt = new JTexTField(1);
	JButton btn = new JButton("Transform");
	JLable lab = new JLabel();
	JLable lab_1 = new JLabel("Please enter a number");
	 
	public transformText()
	{
	    super("ActionEvent");
		setTitle("数字英文查询");
		setSize(200,100);
		btn.addActionListener(this);
		contentpane.setLayout(new FlowLayout());
		contentpane.add(lab_1);
		contentpane.add(txt);
		contentpane.add(btn);
		contentpane.add(lab);

		setVisible(true);	  
	}
	 
	public void actionPerformed(ActionEvent event)
	{
	    String[] str = new String[]{"zero","one","two","three","four"
		                      ,"five","six","seven","eight","night"};
            try{
                String s = txt.getText();	
		lab.setText(str[Integer.parseInt(s)]);
               }catch(Exception e){lab.setText("Error!");}	
        		
	}
	
	public static void main(String[] args)
	{
	    transformText text = new transformText();
		text.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);	
	}
}