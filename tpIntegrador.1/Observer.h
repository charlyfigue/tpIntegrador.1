#pragma once

class observer
{
	public:
	observer(){}
	virtual ~observer(){}
	virtual void update(void *) = 0;
};