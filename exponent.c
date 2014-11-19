#include<stdio.h>
long long fast_exp(int base, int exp,int n) 
{
    long long res=1;
    while(exp>0) {
       if(exp%2==1) res=(res*base)%n;
       base=(base*base)%n;
       exp/=2;
    }
    return res%n;
}
/*
long long int fast_exp(long long int base,long long int exp,long long int n)
{
    if(exp==1)
    {
	return base;
    }
    else
    {
        if(exp%2 == 0)
        {
            long long int base1 = pow(fast_exp(base, exp/2,n),2);
            if(base1 >= n)
            {
            	return base1%n;
            }
            else
            {
            	return base1;
    	    }
        }
        else
        {
            long long int ans = (base*  pow(fast_exp(base,(exp-1)/2,n),2));
            if(ans >= n)
            {
            	return ans%n;
    	    }
            else
            {
            	return ans;
            }
        }
    }
}
int modular(int base, unsigned int exp, unsigned int mod)
{
    int x = 1,i;
    int power = base % mod;
    for (i = 0; i < sizeof(int) * 8; i++) 
    {
        int least_sig_bit = 0x00000001 & (exp >> i);
        if (least_sig_bit)
            x = (x * power) % mod;
        power = (power * power) % mod;
    }
    return x;
}
/*
a1 = a reduced mod m
p = 1
while (b > 0) {
     if (b is odd) {
         p *= a1
         p = p reduced mod m
     }
     b /= 2
     a1 = (a1 * a1) reduced mod m
}
*/
int main()
{
	printf("\n%lld\n",fast_exp(5,55,221));
	return 0;
}
