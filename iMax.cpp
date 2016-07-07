#include <iostream>
using namespace std;

int iMax( int iNum1, int iNum2 )
{
	return iNum1 > iNum2?iNum1:iNum2;
}
int main()
{
	int iNum1 = 10, iNum2 = 20;
	cout << "the max is :" << iMax(iNum1, iNum2) << endl;
	return 0;
}
