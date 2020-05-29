#include <math.h>

double calculate_phase(double a, double b)
{
	if(a>0)
		return atan(b/a);
	if(a<0 && b>=0)
		return atan(b/a)+M_PI;
	if(a<0 && b<0)
		return atan(b/a)-M_PI;
	if(a==0 && b>0)
		return M_PI/2;
	if(a==0 && b<0)
		return -1.0*M_PI/2;
	if(a==0 && b==0)
		return 0;

	return 0;
}
