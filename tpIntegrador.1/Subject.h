#include "Observer.h"
#include <iostream>
#include <list>

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
	std::list<observer*> listOfObservers;
};
