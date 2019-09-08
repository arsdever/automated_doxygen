#pragma once
namespace ad
{
	/**
	 * @brief This interface is used to serialize the objects.
	 * 
	 * After serialization the objects can be deserialized from the data if they implement the interface **Deserializable**
	 * @tparam BYTEBUF_TYPE the output type of serialization
	 * @see Deserializable
	 */
	template <typename BYTEBUF_TYPE>
	class Serializable
	{
	public:
		typedef BYTEBUF_TYPE bytebuf_t;
		
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
