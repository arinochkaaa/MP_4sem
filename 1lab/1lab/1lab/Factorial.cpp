#include "pch.h"
#include "Factorial.h" 
namespace Factorial {
	int factorial(int var) {
		if (var <= 1) return 1;

		return var * factorial(--var);
	}
}