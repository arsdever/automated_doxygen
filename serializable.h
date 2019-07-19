#pragma once
namespace ad
{
	/**
	 * @brief This interface is used to serialize the objects.
	 * 
	 * After serialization the objects can be deserialized from the data if they implement the interface **Deserializable**
	 * @tparam bytebuf_t the output type of serialization
	 * @see Deserializable
	 */
	template <typename bytebuf_t>
	class Serializable
	{
	public:
		/**
		 * @brief The destructor.
		 */
		virtual ~Serializable() = default;

		/**
		 * @brief This function serializes the object.
		 * @return serialized object in ByteBuf
		 * @see ByteBuf
		 */
		virtual bytebuf_t serialize() const = 0;
	};
}
