import java.util.Scanner;


class PhoneInput
{
    private final String[] phone_str = new String[]{"0","1","abc","def","ghi"
		                             ,"jkl","mno","pqrs","tuv","wxyz"};
	private final int[] num = {1,1,3,3,3,3,3,4,3,4};
	
	public int len;
	
	public char[] prt;
	
	PhoneInput(int Len)
	{
		len = Len;
		prt = new char[Len];
	}
	
	public int[] transform(String str)
	{
	    int[] array = new int[str.length()];
		for(int i=0; i<str.length(); i++)
		array[i] = Integer.parseInt(String.valueOf(str.charAt(i)));
		return array;
	}
	
	public void print(int cou,int[] array)
    {
	    int count = cou;
		for (int i=0;i<num[array[count]];i++)
		{
		    prt[count] = phone_str[array[count]].charAt(i);
			if (count<array.length-1)
			    print(count+1,array);
			else
			    System.out.println(prt);
		}
	}
	
}


class Test
{
    public static void main(String[] args)
	{

	    Scanner input = new Scanner(System.in);
		String in = input.next();
		PhoneInput test = new PhoneInput(in.length());
		test.print(0,test.transform(in));
	}
}						