#pragma once
class Singleton
{
private:
	static Singleton* sIntance;
	Singleton();
public:
	void Init();//initializari - pot fi si in constructor
	static Singleton* getInstance();
	void metodaInstanta();//o metoda oarecare, nestatica
	void freeResources();//eliberarea zonelor de memorie alocate dinamic - se poate realiza si in destructor
	~Singleton();
};