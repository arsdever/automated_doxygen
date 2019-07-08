#pragma once
#include <serializable.h>
#include <deserializable.h>

namespace ad
{
	/**
	 * \brief This interface used to implement transferable objects.
	 * 
	 * That means, that this kind of objects can be serialized and deserialized.
	 * It makes possible to serialize them in one place, transfer them and 
	 * deserialize in another place
	 */
	template <typename BYTE_ARRAY_TYPE>
	class Transferable : public Serializable<BYTE_ARRAY_TYPE>, public Deserializable<BYTE_ARRAY_TYPE>
	{};
}
