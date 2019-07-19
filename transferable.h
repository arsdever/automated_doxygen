#pragma once
#include <serializable.h>
#include <deserializable.h>

namespace ad
{
	/**
	 * @brief This interface used to implement transferable objects.
	 * 
	 * That means, that this kind of objects can be serialized and deserialized.
	 * It makes possible to serialize them in one place, transfer them and 
	 * deserialize in another place
	 */
	template <typename bytebuf_t>
	class Transferable : public Serializable<bytebuf_t>, public Deserializable<bytebuf_t>
	{};
}
