#pragma once

class QByteArray;

__interface Serializable
{
	virtual QByteArray serialize() const = 0;
};