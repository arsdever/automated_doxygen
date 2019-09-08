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
	template <typename BYTEBUF_TYPE>
	class Transferable : public Serializable<BYTEBUF_TYPE>, public Deserializable<BYTEBUF_TYPE>
	{
	public:
		typedef BYTEBUF_TYPE bytebuf_t;
		typedef Serializable<bytebuf_t> base_serializable_t;
		typedef Deserializable<bytebuf_t> base_deserializable_t;
	};
}
