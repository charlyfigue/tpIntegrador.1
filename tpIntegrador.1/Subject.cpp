#include "Subject.h"

using namespace std;

void
Subject::attach(observer * observerPtr)
{
	listOfObservers.push_back(observerPtr);
}

void
Subject::detach(observer * observerPtr)
{
	listOfObservers.remove(observerPtr);
}

void
Subject::notifyAllObservers(void)
{
	list<observer * >::iterator it;
	for(it= listOfObservers.begin(); it != listOfObservers.end(); it++)
		(*it)->update(this);
}
