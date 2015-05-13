#include <iostream>

using namespace std;

#if USE_GMP
#include <gmpxx.h>
typedef mpz_class number;
number my_pow(const number &x, unsigned long int y)
{
    mpz_class r;
    mpz_pow_ui(r.get_mpz_t(), x.get_mpz_t(), y);
    return r;
}
number my_sqrt(const number &x)
{
    mpz_class r;
    mpz_sqrt(r.get_mpz_t(), x.get_mpz_t());
    return r;
}
#else
#include <cmath>
typedef unsigned long int number;
#define my_pow(...) static_cast<number>(pow(__VA_ARGS__))
#define my_sqrt(...) static_cast<number>(sqrt(__VA_ARGS__))
#endif

bool LLT(unsigned long int p)
{
    number s;

    s = 4;

    for(unsigned long int i = 1;i < p - 1;i++)
    {
        s = s*s - 2;
    }

#if DEBUG
    cout << "finished calculation of s." << endl;
#endif

    return (s % (my_pow(2, p) - 1)) == 0;
}

bool is_prime(number n)
{
    for(number x = 2;x <= my_sqrt(n);x++)
    {
        if(n % x == 0)
        {
            return false;
        }
    }

    return true;
}

void usage(char *name)
{
    cout << "usage:" << endl;
    cout << name << " p" << endl;
    cout << "p\tMust be prime." << endl;
}

int main(int argc, char *argv[])
{
    unsigned long int p;

    if(argc != 2)
    {
        usage(argv[0]);
        return -1;
    }

    p = strtoull(argv[1], NULL, 10);

    if(!is_prime(static_cast<number>(p)))
    {
        usage(argv[0]);
        return -2;
    }

    if(LLT(p))
    {
        cout << "2^p - 1 is prime." << endl;
    }
    else
    {
        cout << "2^p - 1 is not prime" << endl;
    }

    return 0;
}

