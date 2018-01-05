
class FactorialPlus extends Thread
{
    public void run()
	{
		while(true)
		{
		    result += factorial(count);
			count++;
			try{sleep(500);}
			catch(InterruptedException e){};
		}
	}
	
	public long  factorial(int n)
    {
        long ret = 1;
        for(int i= 1; i<=n; i++)
        ret *=i;
        return ret;
    }

	public static long get_result()
	{
	    return result;
	}
	
	private int count = 1;
    private static long result = 0;
}

class PrintResult extends Thread
{
    public void run()
	{
	    while(true)
		{
		    System.out.println(""+FactorialPlus.get_result());
			try{sleep(500);}
			catch(InterruptedException e){};
		}
	}
}

class Test
{
    static FactorialPlus factorial_plus;
	static PrintResult print_result;
	public static void main(String[] args)
	{
	    factorial_plus = new FactorialPlus();
		print_result = new PrintResult();
		factorial_plus.start();
		print_result.start();
	}
	
}