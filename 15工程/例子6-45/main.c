
 int i=0;
int cal(int x)
{
	static int y=0;
    y=x-y-i;
	return y;
}

main()
{
	int j=1000;
	int k;
	i=cal(j);
	i=cal(j);
	i=cal(j);
}