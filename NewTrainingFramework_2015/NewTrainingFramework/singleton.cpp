#include "singleton.h"

Singleton* Singleton::spInstance = NULL;
Singleton* Singleton::getInstance()
{
	if (!spInstance)
	{
		spInstance = new Singleton();
	}
	return spInstance;
}
void Singleton::metodaInstanta() {
	//nitel cod
}