#include "Observer.h"
#include <iostream>
#include <list>

using namespace std;

class Subject 
{
	public:
	Subject(){}
	//virtual ~Subject(){}
	void attach(observer* observerPtr);
	void detach(observer* observerPtr);
	
	protected:
	void notifyAllObservers(void);
	
	private:
	list<observer*> listOfObservers;
};
