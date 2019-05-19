#pragma once

#include "decorators_global.h"

class QPainter;

struct DECORATORS_EXPORT DecoratorOptions
{
public:
	virtual ~DecoratorOptions() {}
};

class DecoratorBase
{
public:
	inline DecoratorBase(DecoratorOptions* options = nullptr) : __options(options) {}
	virtual void decorate(QPainter& painter) const = 0;
	virtual ~DecoratorBase() { delete __options; }

protected:
	inline void setOptions(DecoratorOptions* options) { __options = options; }
	inline DecoratorOptions const* options() const { return __options; }

private:
	DecoratorOptions* __options;
};
