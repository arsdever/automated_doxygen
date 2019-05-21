#pragma once

class QByteArray;

__interface Deserializable
{
	virtual void deserialize(QByteArray const&) = 0;
};