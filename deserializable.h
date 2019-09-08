#pragma once
namespace ad
{
	/**
	 * @brief This interface is used to deserialize the objects.
	 * 
	 * Objects can be deserialized from the data serialized using the interface Serializable.
	 * It also is possible to deserialize from custom defined data (if such implementation exists).
	 * @tparam BYTEBUF_TYPE the output type of serialization
	 * @see Serializable
	 */
	template <typename BYTEBUF_TYPE>
	class Deserializable
	{
	public:
		typedef BYTEBUF_TYPE bytebuf_t;

	public:
		/**
		 * @brief The destructor.
		 */
		virtual ~Deserializable() = default;

		/**
		 * @brief This function deserializes the object.
		 * @param data the data
		 */
		virtual void deserialize(bytebuf_t const& data) = 0;
	};
}
